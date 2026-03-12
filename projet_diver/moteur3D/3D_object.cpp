#include <SFML/Graphics.hpp>
#include"Calcules.hpp"
#include"Camera.hpp"
#include<fstream>
#include<iostream>
#include <filesystem>
#include<map>
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <string_view>
struct matérieau
{
    sf::Vector3f kd,ke;
    float d;
    sf::Texture map_Kd;
    sf::Texture map_Ke;

};

struct IndexPoint
{
    long unsigned int ipos;
    long unsigned int ivt;

    IndexPoint(){}

    IndexPoint(long unsigned int ipos){
        this->ipos=ipos;
    }
    IndexPoint(long unsigned int ipos,long unsigned int ivt){
        this->ipos=ipos;
        this->ivt=ivt;
    }
};

struct triangle
{
    IndexPoint p1;
    IndexPoint p2;
    IndexPoint p3;
    std::string mat;
};

class Objet3D { 
     public:
    std::vector<std::vector<IndexPoint>>faces;
    std::vector<sf::Vector3f> points;
    std::vector<sf::Vector2f> vts;
    sf::Vector3f position;
    sf::Vector3f speed;
    std::map<std::string,matérieau> Materieaux;
    float size;
    float RotationAngle;
    Objet3D()
    {
        size=1;
        position={0,0,0};
        RotationAngle=0;
        speed={0,0,0};
    }
    Objet3D(std::string dirname)
    {
        load(dirname);
        std::cout<<"Nombre de matérieaux chargées : "<<Materieaux.size()<<std::endl;
        size=1;
        position={0,0,0};
        RotationAngle=0;
    }

    void move()
    {
        position+=speed;
    }

    
    
    void draw(sf::RenderTarget& target,Camera &camera) 
    {
        std::string newmat="";
        sf::VertexArray triangles(sf::Triangles);
        
        
        
        for(const sf::Vector3f & point : points)
            pointscam.push_back(camera.switch_base((point+position)*size));
        
        // traite les triangles, dessine ceux visibles, ignores ceux qui sont invisible et projette ceux qui sont entre les deux
        std::vector<triangle> visibles=triangles3D;
        float M_1_sqrt2=1/sqrt(2);
        plan P;


        P.N={0,0,1};
        P.D=1;
        clip(P,visibles);//plan sur l'axe de la cam

        // P.D=0;
        // P.N={M_1_sqrt2,0,M_1_sqrt2};
        // clip(P,visibles);//plan sur l'axe gauche

        // P.N={-1*M_1_sqrt2,0,M_1_sqrt2};
        // clip(P,visibles);//plan sur l'axe droit

        // P.N={0,M_1_sqrt2,M_1_sqrt2};
        // clip(P,visibles);//plan sur l'axe bas

        // P.N={0,-1*M_1_sqrt2,M_1_sqrt2};
        // clip(P,visibles);//plan sur l'axe haut

        std::sort(visibles.begin(),visibles.end(),[this](const triangle & a,const triangle & b)
                                                        {
                                                            return (pointscam[a.p1.ipos].z+pointscam[a.p2.ipos].z+pointscam[a.p3.ipos].z)/3>(pointscam[b.p1.ipos].z+pointscam[b.p2.ipos].z+pointscam[b.p3.ipos].z)/3;
                                                        });
        for (const triangle &triangle : visibles)
        {
            sf::Vector3f p1=pointscam[triangle.p1.ipos];
            sf::Vector3f p2=pointscam[triangle.p2.ipos];
            sf::Vector3f p3=pointscam[triangle.p3.ipos];

            if (newmat!=triangle.mat)
           {
                if(newmat!="")
                {
                    target.draw(triangles,&Materieaux[newmat].map_Kd);
                    triangles.clear();
                }
                newmat=triangle.mat;
                
           }
            
                sf::Vertex pr1=camera.Projection(p1);
                sf::Vertex pr2=camera.Projection(p2);
                sf::Vertex pr3=camera.Projection(p3);
                pr1=SFMLScale(pr1.position,target);
                pr2=SFMLScale(pr2.position,target);
                pr3=SFMLScale(pr3.position,target);
                sf::Vector2u size=Materieaux[triangle.mat].map_Kd.getSize();
                pr1.texCoords={vts[triangle.p1.ivt].x*size.x,(1-vts[triangle.p1.ivt].y)*size.y};
                pr2.texCoords={vts[triangle.p2.ivt].x*size.x,(1-vts[triangle.p2.ivt].y)*size.y};
                pr3.texCoords={vts[triangle.p3.ivt].x*size.x,(1-vts[triangle.p3.ivt].y)*size.y};
                triangles.append(pr1);
                triangles.append(pr2);
                triangles.append(pr3);
            

           
            // si la texture est une nouvelle, alors on dessine tous les triangles déjà implémentés, on reset le tableau et on initialise la nouvelle texture
        }
        target.draw(triangles,&Materieaux[newmat].map_Kd);
        triangles.clear();
        pointscam.clear();
        visibles.clear();
        
    }



        void load(std::string dirname)
        {
            std::ifstream fic;
            std::string currentmat="";
            std::string filename=split(dirname,"/")[3]+".obj";
            std::cout<<"ouverture de "+dirname+"/source/"+filename<<std::endl;
            fic.open(dirname+"/source/"+filename);
            if (!fic.is_open())
            {
                std::cout<<"erreur d'ouverture de : "<<dirname+"/source/"+filename<<std::endl;
            }
            

            std::string donnee;
            
            while (fic>>donnee)
            {   if (donnee=="mtllib")
                {
                    std::string mtlname;
                    fic>>mtlname;
                    parsemtl(mtlname,dirname);
                }

                if (donnee=="usemtl")
                {
                    if(currentmat!="")
                    {
                        create_triangles(currentmat);
                        faces.clear();
                    }
                    fic>>currentmat;
                }
                
                if (donnee=="v")  
                {
                    float x,y,z;
                    fic>>x;
                    fic>>y;
                    fic>>z;
                    points.push_back({x,y,z});
                }

                if (donnee=="vt")  
                {   float x,y;
                    fic>>x;
                    fic>>y;
                    vts.push_back({x,y});
                }
                if (donnee=="f")
                {  
                    bool again; //au cas où la suite est sur la ligne d'après (backslash)
                    std::vector<IndexPoint> face;
                    
                    do
                    {
                        again=false;
                        getline(fic,donnee);
                        std::vector<std::string> ligne=split(donnee," ");
                        for (std::string &vertex: ligne)
                        {
                            if (vertex!="" and vertex!="\\" and vertex!="\\\r" and vertex!="\\\n" and vertex!="\\\r\n" and vertex!="f") 
                            {
                                std::vector<std::string> index=split(vertex,"/");
                                if(index[0]=="")index[0]="1";
                                if(index[1]=="")index[1]="1";
                                
                                face.push_back({unsigned(stoi(index[0])-1),unsigned(stoi(index[1])-1)});
                            }
                            if(vertex=="\\\r" or vertex=="\\\n" or vertex=="\\" or vertex=="\\\r\n")
                            {
                                again=true;
                            }
                            
                        }
                    }while(again);
                    
                    
                    faces.push_back(face);
                    face.clear();
                }
            }
            fic.close();
            create_triangles(currentmat);
            faces.clear();
        }

        private :
            void drawPoints(sf::RenderWindow & window,double dt,Camera & camera)
            {
                for(sf::Vector3f & point :points)
                {
                    drawRectangle(SFMLScale(camera.Projection(point),window),window);
                }
            }
            
            std::vector<triangle> triangles3D;
            std::vector<sf::Vector3f> pointscam;
            std::vector<sf::Texture> loadTexturesFromFolder(const std::string& folderPath)
            {
                std::vector<sf::Texture> textures;

                for (const auto& entry : std::filesystem::directory_iterator(folderPath))
                {
                    if (entry.is_regular_file())
                    {
                        std::string path = entry.path().string();

                        // Filtrer les extensions image
                        if (entry.path().extension() == ".png" ||
                            entry.path().extension() == ".jpg" ||
                            entry.path().extension() == ".jpeg")
                        {
                            sf::Texture texture;
                            if (texture.loadFromFile(path))
                            {
                                textures.push_back(std::move(texture));
                            }
                            else
                                std::cout<<"erreur chargement texture"<<std::endl;
                        }
                    }
                }

                return textures;
            }

            void create_triangles(const std::string &mat)
            {
                std::cout<<"je cree les triangles de mat : "<<mat<<std::endl;
                for (std::vector<IndexPoint> const &face : faces)
                {
                    for (size_t i = 1; i < face.size()-1; i++)
                    {
                        triangle tri;
                        tri.p1=face[0];
                        tri.p2=face[i];
                        tri.p3=face[i+1];
                        tri.mat=mat;
                        triangles3D.push_back(tri);
                    }
                }
            }

            int count_hiden(triangle &tri,const plan &P)
            {
                IndexPoint aux;
                int count=0;
                if(prodscal3D(pointscam[tri.p1.ipos]-P.N*P.D,P.N)<0)
                {
                    count++;
                }
                if(prodscal3D(pointscam[tri.p2.ipos]-P.N*P.D,P.N)<0)
                {
                    count++;
                }
                if(prodscal3D(pointscam[tri.p3.ipos]-P.N*P.D,P.N)<0)
                {
                    count++;
                }
                if (prodscal3D(pointscam[tri.p1.ipos]-P.N*P.D,P.N)>prodscal3D(pointscam[tri.p2.ipos]-P.N*P.D,P.N))
                {
                    aux=tri.p1;
                    tri.p1=tri.p2;
                    tri.p2=aux;
                }
                if (prodscal3D(pointscam[tri.p1.ipos]-P.N*P.D,P.N)>prodscal3D(pointscam[tri.p3.ipos]-P.N*P.D,P.N))
                {
                    aux=tri.p1;
                    tri.p1=tri.p3;
                    tri.p3=aux;
                }
                if (prodscal3D(pointscam[tri.p2.ipos]-P.N*P.D,P.N)>prodscal3D(pointscam[tri.p3.ipos]-P.N*P.D,P.N))
                {
                    aux=tri.p2;
                    tri.p2=tri.p3;
                    tri.p3=aux;
                }
                sf::Vector3f p1 =pointscam[tri.p1.ipos],p2=pointscam[tri.p2.ipos],p3=pointscam[tri.p3.ipos];
                if (p3.z<=1)
                {
                    return 3;
                }
                if (p2.z<=1)
                {
                    return 2;
                }
                if (p1.z<=1)
                {
                    return 1;
                }
                return 0;
            }

            void parsemtl(const std::string &mtlname,const std::string &dirname)
            {
                std::string donneemtl;
                    std::string nommat;
                    std::string nomtext;
                    
                    std::cout<<dirname+"/source/"+mtlname<<std::endl;
                    std::ifstream ficmtl;
                    ficmtl.open(dirname+"/source/"+mtlname);
                    if (!ficmtl.is_open())
                    {
                        std::cout<<"erreur d'ouverture de : "<<dirname+"/source/"+mtlname<<std::endl;
                    }
                    while(ficmtl>>donneemtl)
                    {
                        if(donneemtl=="newmtl") 
                        {   
                            ficmtl>>donneemtl;
                            nommat=donneemtl;
                            std::cout<<nommat<<std::endl;
                        }
                        if(donneemtl=="Kd")
                        {
                            ficmtl>>Materieaux[nommat].kd.x;
                            ficmtl>>Materieaux[nommat].kd.y;
                            ficmtl>>Materieaux[nommat].kd.z;
                        }

                        if(donneemtl=="Ke")
                        {
                            ficmtl>>Materieaux[nommat].ke.x;
                            ficmtl>>Materieaux[nommat].ke.y;
                            ficmtl>>Materieaux[nommat].ke.z;
                        }

                        if(donneemtl=="d")
                        {
                            ficmtl>>Materieaux[nommat].d;
                        }
                            
                        if(donneemtl=="map_Kd")
                        {
                            ficmtl>>nomtext;
                            Materieaux[nommat].map_Kd.loadFromFile(dirname+"/textures/"+ nomtext);
                            Materieaux[nommat].map_Kd.setRepeated(true);
                            std::cout<<" loading : "+dirname+"/textures/"+ nomtext<<std::endl;
                        }
                        if(donneemtl=="map_Ke")
                        {
                            ficmtl>>nomtext;
                            Materieaux[nommat].map_Ke.loadFromFile(dirname+"/textures/"+ nomtext);
                            Materieaux[nommat].map_Kd.setRepeated(true);
                            std::cout<<" loading : "+dirname+"/textures/"+ nomtext<<std::endl;
                        }
                            
                    }
                    ficmtl.close();
            }

            void clip( plan &P,std::vector<triangle> &visibles)
            {
                std::vector<triangle>aux;
                for (triangle &triangle : visibles)
                {
                    int count=count_hiden(triangle,P);
                    sf::Vector3f p1=pointscam[triangle.p1.ipos];
                    sf::Vector3f p2=pointscam[triangle.p2.ipos];
                    sf::Vector3f p3=pointscam[triangle.p3.ipos];
                    
                    if (count==0)
                    {
                        aux.push_back(triangle);
                    }
                    if (count==1 )
                    {
                        pointscam.push_back(near_projection(p2,p1,P));
                        pointscam.push_back(near_projection(p3,p1,P));
                        aux.push_back({triangle.p2,{pointscam.size()-2,triangle.p1.ivt},{pointscam.size()-1,triangle.p1.ivt},triangle.mat});
                        aux.push_back({triangle.p3,triangle.p2,{pointscam.size()-1,triangle.p1.ivt},triangle.mat});
                    }
                    if (count==2 )
                    {
                        pointscam.push_back(near_projection(p3,p1,P));
                        pointscam.push_back(near_projection(p3,p2,P));
                        aux.push_back({triangle.p3,{pointscam.size()-2,triangle.p1.ivt},{pointscam.size()-1,triangle.p2.ivt},triangle.mat});
                    }
                }
                visibles=aux;
            }
           

};

