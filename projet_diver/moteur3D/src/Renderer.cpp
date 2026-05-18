#include "Renderer.hpp"

Renderer::Renderer(MatManager &matManager)
{
    this->matManager=&matManager;
}
int Renderer::count_hiden(Clipped_triangle &tri,const plan &P)
        {
           
        }

void Renderer::clip( plan &P,std::vector<Clipped_triangle> &visibles)
        {
           
        }

void Renderer::getTriangles(Objet3D &Model)
{
    meshs.push_back(Model.getMesh());
    Map[Model.getNom()]=Model.getTransfo();
}
void Renderer::removeMesh(std::string nom)
{
    for (auto it=meshs.begin(); it!=meshs.end(); ++it)
    {
        if ((*it)->nomModel==nom)
        {
            meshs.erase(it);
            break;
        }
    }
}
void Renderer::draw(sf::RenderTarget& target,Camera &camera,std::vector<Light*> &globalLights)
{
    
    std::string newmat="";
    std::string newobj="";
    sf::VertexArray triangles(sf::Triangles);

    std::vector<Clipped_triangle> visibles;
    visibles.reserve(500000);
    std::vector<Eigen::Vector4f>pointscam;

    for (Mesh* &mesh : meshs)
    {
        
        pointscam.resize(mesh->points.size());
        int n=0;
        for(const  Eigen::Vector3f& point : mesh->points)
        {
            pointscam[n]=camera.getMatriceView()*getMatriceTransformation(mesh)*Eigen::Vector4f(point.x(),point.y(),point.z(),1);
            n++;
        }
        for(const triangle & tri : mesh->triangles)
        {
                
            const auto& P1 = pointscam[tri.p1.ipos];
            const auto& P2 = pointscam[tri.p2.ipos];
            const auto& P3 = pointscam[tri.p3.ipos];

            if(prodscal3D(P1, prodvect3D(P2-P1, P3-P1)) <= 0)
            {
                visibles.push_back({
                    {P1, mesh->vts[tri.p1.ivt], mesh->vns[tri.p1.ivn]},
                    {P2, mesh->vts[tri.p2.ivt], mesh->vns[tri.p2.ivn]},
                    {P3, mesh->vts[tri.p3.ivt], mesh->vns[tri.p3.ivn]},
                    tri.mat,
                    tri.proprietaire
                });
            }

        }
    }
    std::sort(visibles.begin(),visibles.end(),[this](const Clipped_triangle & a,const Clipped_triangle & b)
                                                    {
                                                        return (a.p1.pos.z()+a.p2.pos.z()+a.p3.pos.z())>(b.p1.pos.z()+b.p2.pos.z()+b.p3.pos.z());
                                                    });
    for (Clipped_triangle &triangle : visibles)
    {
        std::string model =triangle.proprietaire->getNom();
        matérieau* mat=matManager->getMaterieau(triangle.mat,model);
        if (newmat!=triangle.mat or newobj!=model)
        {
            if(newmat!="" and newobj!="")
            {

                matérieau* mat=matManager->getMaterieau(newmat,newobj);
                if(mat->check_map_Kd)
                {
                    target.draw(triangles,&mat->map_Kd);
                }
                    
                else if(mat->check_map_Ke)
                        target.draw(triangles,&mat->map_Ke);
                else
                {
                    target.draw(triangles);
                }
                triangles.clear();
            }
            newmat=triangle.mat;
            newobj=triangle.proprietaire->getNom();
            
        }
            
           

        
        // si la texture est une nouvelle, alors on dessine tous les triangles déjà implémentés, on reset le tableau et on initialise la nouvelle texture
    }
    matérieau* mat=matManager->getMaterieau(newmat,newobj);
    if(mat->check_map_Kd)
        target.draw(triangles,&mat->map_Kd);
    else if(mat->check_map_Ke)
            target.draw(triangles,&mat->map_Ke);
    else
    {
        target.draw(triangles);
    }
    triangles.clear();
    visibles.clear();
}










void Renderer::drawTriangle(sf::VertexArray &triangles,Clipped_triangle &triangle,matérieau* mat,Camera &camera,std::vector<Light*> &globalLights,sf::RenderTarget& target)
{
     sf::Vertex pr1=camera.Projection(triangle.p1.pos);
            sf::Vertex pr2=camera.Projection(triangle.p2.pos);
            sf::Vertex pr3=camera.Projection(triangle.p3.pos);
            pr1=SFMLScale(pr1.position,target);
            pr2=SFMLScale(pr2.position,target);
            pr3=SFMLScale(pr3.position,target);
            sf::Vector2u size=mat->map_Kd.getSize();
            pr1.texCoords={triangle.p1.uv.x()*size.x,(1-triangle.p1.uv.y())*size.y};
            pr2.texCoords={triangle.p2.uv.x()*size.x,(1-triangle.p2.uv.y())*size.y};
            pr3.texCoords={triangle.p3.uv.x()*size.x,(1-triangle.p3.uv.y())*size.y};
            if (camera.lights)
            {
                Eigen::Vector3f diffuse1={0,0,0}, diffuse2={0,0,0},diffuse3={0,0,0};
                Eigen::Vector3f spec1={0,0,0},spec2={0,0,0},spec3={0,0,0};
                sf::Color ambiantLight={150,150,150};

                for(Light* &light  :globalLights)
                {
                    float dot1;
                    float dot2;
                    float dot3;
                    if(light->getType()==LightType::Directional)
                    {
                        Eigen::Vector3f L=-Normalize3D(static_cast<Directional*>(light)->direction);
                        Eigen::Vector3f lightcolor=Eigen::Vector3f(light->couleur.r/255.f,light->couleur.g/255.f,light->couleur.b/255.f);
                        Eigen::Vector3f N1=Normalize3D(triangle.p1.vn);
                        Eigen::Vector3f N2=Normalize3D(triangle.p2.vn);
                        Eigen::Vector3f N3=Normalize3D(triangle.p3.vn);
                        dot1=prodscal3D(N1,L);
                        if(dot1>0)
                        {
                            diffuse1+=dot1*lightcolor;
                        }
                        dot2=prodscal3D(N2,L);
                        if(dot2>0)
                        {
                            diffuse2+=dot2*lightcolor;
                        }
                        dot3=prodscal3D(N3,L);
                        if(dot3>0)
                        {
                            diffuse3+=dot3*lightcolor;
                        }
                        if (mat->Ns>0)
                        {
                            if (dot1>0)
                            {
                                Eigen::Vector3f R1=2.f*N1*dot1-L;
                                float dotr1=prodscal3D(R1,-Normalize3D(triangle.p1.pos));
                                if (dotr1>0)
                                {
                                    float pow1=pow(dotr1, mat->Ns);
                                    spec1 += pow1*lightcolor;
                                }
                                
                                
                            }
                            if (dot2>0)
                            {
                                Eigen::Vector3f R2=2.f*N2*dot2-L;
                                float dotr2=prodscal3D(R2,-Normalize3D(triangle.p2.pos));
                                if (dotr2>0)
                                {
                                    float pow2=pow(dotr2, mat->Ns);
                                    spec2 += pow2*lightcolor;
                                }
                                
                                
                            }
                            if (dot3>0)
                            {
                                Eigen::Vector3f R3=2.f*N3*dot3-L;
                                float dotr3=prodscal3D(R3,-Normalize3D(triangle.p3.pos));
                                if (dotr3>0)
                                {
                                    float pow3=pow(dotr3, mat->Ns);
                                    spec3 += pow3*lightcolor;
                                }
                            }
                            
                        }

                    }
                        
                }
                Eigen::Vector3f constantemat=multvect(mat->ka,Eigen::Vector3f(ambiantLight.r/255.f,ambiantLight.g/255.f,ambiantLight.b/255.f))+mat->ke;
                Eigen::Vector3f final_color1=multvect(diffuse1,mat->kd)+
                multvect(spec1,mat->ks)+constantemat;

                Eigen::Vector3f final_color2=multvect(diffuse2,mat->kd)+
                multvect(spec2,mat->ks)+constantemat;

                Eigen::Vector3f final_color3=multvect(diffuse3,mat->kd)+
                multvect(spec3,mat->ks)+constantemat;
                pr1.color=sf::Color(std::clamp(final_color1.x()*255.f,0.f,255.f),std::clamp(final_color1.y()*255.f,0.f,255.f),std::clamp(final_color1.z()*255.f,0.f,255.f));
                pr2.color=sf::Color(std::clamp(final_color2.x()*255.f,0.f,255.f),std::clamp(final_color2.y()*255.f,0.f,255.f),std::clamp(final_color2.z()*255.f,0.f,255.f));
                pr3.color=sf::Color(std::clamp(final_color3.x()*255.f,0.f,255.f),std::clamp(final_color3.y()*255.f,0.f,255.f),std::clamp(final_color3.z()*255.f,0.f,255.f));
            }
            else
            {
                pr1.color={255,255,255};
                pr2.color={255,255,255};
                pr3.color={255,255,255};
            }
            
            triangles.append(pr1);
            triangles.append(pr2);
            triangles.append(pr3);
        
}

Eigen::Matrix4f Renderer::getMatriceTransformation(Mesh* & mesh)
{

        Transformation* transfo=Map[mesh->nomModel];
        
        Eigen::Matrix4f Mtranslation;
            Mtranslation<<transfo->size,0,0,transfo->position.x(),
            0,transfo->size,0,transfo->position.y(),
            0,0,transfo->size,transfo->position.z(),
            0,0,0,1;
        float c,s;
        Eigen::Matrix4f Rx;
        
        c=cos(transfo->RotationAngleX);
        s=sin(transfo->RotationAngleX);
        Rx<<1,0,0,0,
            0,c,-s,0,
            0,s,c,0,
            0,0,0,1;

        Eigen::Matrix4f Ry;
        
        c=cos(transfo->RotationAngleY);
        s=sin(transfo->RotationAngleY);
        Ry<<c,0,s,0,
            0,1,0,0,
            -s,0,c,0,
            0,0,0,1;

        Eigen::Matrix4f Rz;          
        c=cos(transfo->RotationAngleZ);
        s=sin(transfo->RotationAngleZ);
        Rz<<c,-s,0,0,
            s,c,0,0,
            0,0,1,0,
            0,0,0,1;

        Eigen::Matrix4f M=Rz*Ry*Rx*Mtranslation;

        return M;
   
}

