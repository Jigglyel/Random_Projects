#include "Renderer.hpp"

Renderer::Renderer(MatManager &matManager)
{
    this->matManager=&matManager;
}
int Renderer::count_hiden(Clipped_triangle &tri,const plan &P)
        {
           Point aux;

           float scal1=prodscal3D(tri.p1.pos-P.N*P.D,P.N);
           float scal2=prodscal3D(tri.p2.pos-P.N*P.D,P.N);
           float scal3=prodscal3D(tri.p3.pos-P.N*P.D,P.N);
                int count=0;
                if(scal1<0)
                {
                    count++;
                }


                if(scal2<0)
                {
                    count++;
                }


                if(scal3<0)
                {
                    count++;
                }
                if (scal1>scal2)
                {
                    aux=tri.p1;
                    tri.p1=tri.p2;
                    tri.p2=aux;
                    std::swap(scal1,scal2);
                }
                if (scal1>scal3)
                {
                    aux=tri.p1;
                    tri.p1=tri.p3;
                    tri.p3=aux;
                    std::swap(scal1,scal3);
                }
                if (scal2>scal3)
                {
                    aux=tri.p2;
                    tri.p2=tri.p3;
                    tri.p3=aux;
                    std::swap(scal2,scal3);
                }

                return count;
        }

void Renderer::clip( plan &P,std::vector<Clipped_triangle> &visibles)
        {
           std::vector<Clipped_triangle>aux;
                for (Clipped_triangle &triangle : visibles)
                {
                    int count=count_hiden(triangle,P);
                    sf::Vector3f p1=triangle.p1.pos;
                    sf::Vector3f p2=triangle.p2.pos;
                    sf::Vector3f p3=triangle.p3.pos;
                    if (count==0)
                    {
                        aux.push_back(triangle);
                    }

                    float t12=near_projection(p2,p1,P);
                    float t13=near_projection(p3,p1,P);
                    
                    Point p12={p2+t12*(p1-p2),triangle.p1.uv+t12*(triangle.p2.uv-triangle.p1.uv),triangle.p1.vn+t12*(triangle.p2.vn-triangle.p1.vn)};
                    Point p13={p3+t13*(p1-p3),triangle.p1.uv+t13*(triangle.p3.uv-triangle.p1.uv),triangle.p1.vn+t13*(triangle.p3.vn-triangle.p1.vn)};
                    
                    if (count==1 )
                    {
                        
                        aux.push_back(Clipped_triangle(triangle.p2,p12,p13,triangle.mat,triangle.proprietaire));
                        aux.push_back(Clipped_triangle(triangle.p3,triangle.p2,p13,triangle.mat,triangle.proprietaire));
                    }
                    if (count==2 )
                    {
                        float t23=near_projection(p3,p2,P);
                        Point p23={p3+t23*(p2-p3),triangle.p2.uv+t23*(triangle.p3.uv-triangle.p2.uv),triangle.p2.vn+t23*(triangle.p3.vn-triangle.p2.vn)};
                        aux.push_back(Clipped_triangle(triangle.p3,p13,p23,triangle.mat,triangle.proprietaire));
                    }
                }
                visibles=aux;
        }

void Renderer::getTriangles(Objet3D &Model)
{
    meshs.push_back(Model.getMesh());
    Map[Model.getNom()]=&Model;
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
    std::vector<sf::Vector3f>pointscam;
    
    for (Mesh* &mesh : meshs)
    {
        
        pointscam.resize(mesh->points.size());
        int n=0;
        Objet3D* model=Map[mesh->nomModel];
        for(const  sf::Vector3f& point : mesh->points)
        {
            

            pointscam[n]=camera.switch_base(model->apply_Rotation(point)*model->getTransfo()->size+model->getTransfo()->position);
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
        float M_1_sqrt2=1/sqrt(2);
        plan P;
        P.N={0,0,1};
        P.D=0.001;
        clip(P,visibles);//plan sur l'axe de la cam
    }
    std::sort(visibles.begin(),visibles.end(),[this](const Clipped_triangle & a,const Clipped_triangle & b)
                                                    {
                                                        return (a.p1.pos.z+a.p2.pos.z+a.p3.pos.z)>(b.p1.pos.z+b.p2.pos.z+b.p3.pos.z);
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
        drawTriangle(triangles,triangle,mat,camera,globalLights,target);
            
           

        
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




void Renderer::drawHitbox(Objet3D* model,Camera &camera,sf::RenderTarget& target)
{
    sf::VertexArray lines(sf::Lines,24);
    float size=model->getTransfo()->size;
    sf::Vector3f pos=model->getTransfo()->position;
    sf::Vector3f topLeftNear=sf::Vector3f{model->left,model->top,model->near}*size+pos;
    sf::Vector3f topRightNear=sf::Vector3f{model->right,model->top,model->near}*size+pos;
    sf::Vector3f bottomLeftNear=sf::Vector3f{model->left,model->bottom,model->near}*size+pos;
    sf::Vector3f bottomRightNear=sf::Vector3f{model->right,model->bottom,model->near}*size+pos;

    sf::Vector3f topLeftFar=sf::Vector3f{model->left,model->top,model->far}*size+pos;
    sf::Vector3f topRightFar=sf::Vector3f{model->right,model->top,model->far}*size+pos;
    sf::Vector3f bottomLeftFar=sf::Vector3f{model->left,model->bottom,model->far}*size+pos;
    sf::Vector3f bottomRightFar=sf::Vector3f{model->right,model->bottom,model->far}*size+pos;

    lines.append(SFMLScale(camera.Projection(camera.switch_base(topLeftNear)),target));
    lines.append(SFMLScale(camera.Projection(camera.switch_base(topRightNear)),target));

    lines.append(SFMLScale(camera.Projection(camera.switch_base(topRightNear)),target));
    lines.append(SFMLScale(camera.Projection(camera.switch_base(bottomRightNear)),target));

    lines.append(SFMLScale(camera.Projection(camera.switch_base(bottomRightNear)),target));
    lines.append(SFMLScale(camera.Projection(camera.switch_base(bottomLeftNear)),target));

    lines.append(SFMLScale(camera.Projection(camera.switch_base(bottomLeftNear)),target));
    lines.append(SFMLScale(camera.Projection(camera.switch_base(topLeftNear)),target));

    lines.append(SFMLScale(camera.Projection(camera.switch_base(topLeftFar)),target));
    lines.append(SFMLScale(camera.Projection(camera.switch_base(topRightFar)),target));

    lines.append(SFMLScale(camera.Projection(camera.switch_base(topRightFar)),target));
    lines.append(SFMLScale(camera.Projection(camera.switch_base(bottomRightFar)),target));

    lines.append(SFMLScale(camera.Projection(camera.switch_base(bottomRightFar)),target));
    lines.append(SFMLScale(camera.Projection(camera.switch_base(bottomLeftFar)),target));

    lines.append(SFMLScale(camera.Projection(camera.switch_base(bottomLeftFar)),target));
    lines.append(SFMLScale(camera.Projection(camera.switch_base(topLeftFar)),target));

    lines.append(SFMLScale(camera.Projection(camera.switch_base(topLeftNear)),target));
    lines.append(SFMLScale(camera.Projection(camera.switch_base(topLeftFar)),target));

    lines.append(SFMLScale(camera.Projection(camera.switch_base(topRightNear)),target));
    lines.append(SFMLScale(camera.Projection(camera.switch_base(topRightFar)),target));

    lines.append(SFMLScale(camera.Projection(camera.switch_base(bottomRightNear)),target));
    lines.append(SFMLScale(camera.Projection(camera.switch_base(bottomRightFar)),target));

    lines.append(SFMLScale(camera.Projection(camera.switch_base(bottomLeftNear)),target));
    lines.append(SFMLScale(camera.Projection(camera.switch_base(bottomLeftFar)),target));
    target.draw(lines);
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
            pr1.texCoords={triangle.p1.uv.x*size.x,(1-triangle.p1.uv.y)*size.y};
            pr2.texCoords={triangle.p2.uv.x*size.x,(1-triangle.p2.uv.y)*size.y};
            pr3.texCoords={triangle.p3.uv.x*size.x,(1-triangle.p3.uv.y)*size.y};
            if (camera.lights)
            {
                sf::Vector3f diffuse1={0,0,0}, diffuse2={0,0,0},diffuse3={0,0,0};
                sf::Vector3f spec1={0,0,0},spec2={0,0,0},spec3={0,0,0};
                sf::Color ambiantLight={150,150,150};

                for(Light* &light  :globalLights)
                {
                    float dot1;
                    float dot2;
                    float dot3;
                    if(light->getType()==LightType::Directional)
                    {
                        sf::Vector3f L=-Normalize3D(static_cast<Directional*>(light)->direction);
                        sf::Vector3f lightcolor=sf::Vector3f(light->couleur.r/255.f,light->couleur.g/255.f,light->couleur.b/255.f);
                        sf::Vector3f N1=Normalize3D(triangle.p1.vn);
                        sf::Vector3f N2=Normalize3D(triangle.p2.vn);
                        sf::Vector3f N3=Normalize3D(triangle.p3.vn);
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
                                sf::Vector3f R1=2.f*N1*dot1-L;
                                float dotr1=prodscal3D(R1,-Normalize3D(triangle.p1.pos));
                                if (dotr1>0)
                                {
                                    float pow1=pow(dotr1, mat->Ns);
                                    spec1 += pow1*lightcolor;
                                }
                                
                                
                            }
                            if (dot2>0)
                            {
                                sf::Vector3f R2=2.f*N2*dot2-L;
                                float dotr2=prodscal3D(R2,-Normalize3D(triangle.p2.pos));
                                if (dotr2>0)
                                {
                                    float pow2=pow(dotr2, mat->Ns);
                                    spec2 += pow2*lightcolor;
                                }
                                
                                
                            }
                            if (dot3>0)
                            {
                                sf::Vector3f R3=2.f*N3*dot3-L;
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
                sf::Vector3f constantemat=multvect(mat->ka,sf::Vector3f(ambiantLight.r/255.f,ambiantLight.g/255.f,ambiantLight.b/255.f))+mat->ke;
                sf::Vector3f final_color1=multvect(diffuse1,mat->kd)+
                multvect(spec1,mat->ks)+constantemat;

                sf::Vector3f final_color2=multvect(diffuse2,mat->kd)+
                multvect(spec2,mat->ks)+constantemat;

                sf::Vector3f final_color3=multvect(diffuse3,mat->kd)+
                multvect(spec3,mat->ks)+constantemat;
                pr1.color=sf::Color(std::clamp(final_color1.x*255.f,0.f,255.f),std::clamp(final_color1.y*255.f,0.f,255.f),std::clamp(final_color1.z*255.f,0.f,255.f));
                pr2.color=sf::Color(std::clamp(final_color2.x*255.f,0.f,255.f),std::clamp(final_color2.y*255.f,0.f,255.f),std::clamp(final_color2.z*255.f,0.f,255.f));
                pr3.color=sf::Color(std::clamp(final_color3.x*255.f,0.f,255.f),std::clamp(final_color3.y*255.f,0.f,255.f),std::clamp(final_color3.z*255.f,0.f,255.f));
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

        Transformation* transfo=Map[mesh->nomModel]->getTransfo();
        
        Eigen::Matrix4f Mtranslation;
            Mtranslation<<transfo->size,0,0,transfo->position.x,
            0,transfo->size,0,transfo->position.y,
            0,0,transfo->size,transfo->position.z,
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

