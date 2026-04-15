#include "3D_Engine.hpp"


class Renderer
{
private:
    /* data */
public:
    void draw(sf::RenderTarget& target,Camera &camera,std::vector<Light*> &globalLights)
    {

        std::string newmat="";
        sf::VertexArray triangles(sf::Triangles);

        std::vector<Clipped_triangle> visibles;



        std::sort(visibles.begin(),visibles.end(),[this](const Clipped_triangle & a,const Clipped_triangle & b)
                                                        {
                                                            return (a.p1.pos.z+a.p2.pos.z+a.p3.pos.z)>(b.p1.pos.z+b.p2.pos.z+b.p3.pos.z);
                                                        });
        for (const Clipped_triangle &triangle : visibles)
        {
            if (newmat!=triangle.mat)
           {
                if(newmat!="")
                {
                    if(Materieaux[newmat].check_map_Kd)
                        target.draw(triangles,&Materieaux[newmat].map_Kd);
                    else if(Materieaux[newmat].check_map_Ke)
                            target.draw(triangles,&Materieaux[newmat].map_Ke);
                    else
                    {
                        target.draw(triangles);
                    }
                    triangles.clear();
                }
                newmat=triangle.mat;
                
           }
                
                sf::Vertex pr1=camera.Projection(triangle.p1.pos);
                sf::Vertex pr2=camera.Projection(triangle.p2.pos);
                sf::Vertex pr3=camera.Projection(triangle.p3.pos);
                pr1=SFMLScale(pr1.position,target);
                pr2=SFMLScale(pr2.position,target);
                pr3=SFMLScale(pr3.position,target);
                sf::Vector2u size=Materieaux[triangle.mat].map_Kd.getSize();
                pr1.texCoords={triangle.p1.uv.x*size.x,(1-triangle.p1.uv.y)*size.y};
                pr2.texCoords={triangle.p2.uv.x*size.x,(1-triangle.p2.uv.y)*size.y};
                pr3.texCoords={triangle.p3.uv.x*size.x,(1-triangle.p3.uv.y)*size.y};
                if (camera.lights)
                {
                    sf::Vector3f diffuse1={0,0,0}, diffuse2={0,0,0},diffuse3={0,0,0};
                    sf::Vector3f spec1={0,0,0},spec2={0,0,0},spec3={0,0,0};
                    sf::Color ambiantLight={50,50,50};

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
                            if (Materieaux[triangle.mat].Ns>0)
                            {
                                if (dot1>0)
                                {
                                    sf::Vector3f R1=2.f*N1*dot1-L;
                                    float dotr1=prodscal3D(R1,-Normalize3D(triangle.p1.pos));
                                    if (dotr1>0)
                                    {
                                        float pow1=pow(dotr1, Materieaux[triangle.mat].Ns);
                                        spec1 += pow1*lightcolor;
                                    }
                                    
                                    
                                }
                                if (dot2>0)
                                {
                                    sf::Vector3f R2=2.f*N2*dot2-L;
                                    float dotr2=prodscal3D(R2,-Normalize3D(triangle.p2.pos));
                                    if (dotr2>0)
                                    {
                                        float pow2=pow(dotr2, Materieaux[triangle.mat].Ns);
                                        spec2 += pow2*lightcolor;
                                    }
                                    
                                    
                                }
                                if (dot3>0)
                                {
                                    sf::Vector3f R3=2.f*N3*dot3-L;
                                    float dotr3=prodscal3D(R3,-Normalize3D(triangle.p3.pos));
                                    if (dotr3>0)
                                    {
                                        float pow3=pow(dotr3, Materieaux[triangle.mat].Ns);
                                        spec3 += pow3*lightcolor;
                                    }
                                }
                                
                            }

                        }
                            
                    }
                    sf::Vector3f constantemat=multvect(Materieaux[triangle.mat].ka,sf::Vector3f(ambiantLight.r/255.f,ambiantLight.g/255.f,ambiantLight.b/255.f))+Materieaux[triangle.mat].ke;
                    sf::Vector3f final_color1=multvect(diffuse1,Materieaux[triangle.mat].kd)+
                    multvect(spec1,Materieaux[triangle.mat].ks)+constantemat;

                    sf::Vector3f final_color2=multvect(diffuse2,Materieaux[triangle.mat].kd)+
                    multvect(spec2,Materieaux[triangle.mat].ks)+constantemat;

                    sf::Vector3f final_color3=multvect(diffuse3,Materieaux[triangle.mat].kd)+
                    multvect(spec3,Materieaux[triangle.mat].ks)+constantemat;
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
            

           
            // si la texture est une nouvelle, alors on dessine tous les triangles déjà implémentés, on reset le tableau et on initialise la nouvelle texture
        }
        if(Materieaux[newmat].check_map_Kd)
            target.draw(triangles,&Materieaux[newmat].map_Kd);
        else if(Materieaux[newmat].check_map_Ke)
                target.draw(triangles,&Materieaux[newmat].map_Ke);
        else
        {
            target.draw(triangles);
        }
        triangles.clear();
        visibles.clear();
        
        
    }
    }
};