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
    std::string nom;
    sf::Texture tex;

};

struct IndexPoint
{
    int ipos;
    int ivt;
    std::string mat; 

    IndexPoint(){}

    IndexPoint(int ipos){
        this->ipos=ipos;
    }
    IndexPoint(int ipos,int ivt,std::string mat){
        this->ipos=ipos;
        this->ivt=ivt;
        this->mat=mat;
    }
};
struct triangle
{
    IndexPoint p1;
    IndexPoint p2;
    IndexPoint p3;
    matérieau mat;
};
class Objet3D { 
     public:
    std::vector<std::vector<IndexPoint>>faces;
    std::vector<sf::Vector3f> points;
    std::vector<sf::Vector2f> vts;
    sf::Vector3f position;
    sf::Vector3f speed;
    std::map<std::string,sf::Texture> Textures;
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
        std::cout<<"Nombre de textures chargées : "<<Textures.size()<<std::endl;
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
        std::string newtex="";
        sf::VertexArray triangles(sf::Triangles);
        
        
        
        for(const sf::Vector3f & point : points)
            pointscam.push_back(camera.switch_base((point+position)*size));
            
        std::sort(triangles3D.begin(),triangles3D.end(),[this](const triangle & a,const triangle & b)
                                                            {
                                                                return (pointscam[a.p1.ipos].z+pointscam[a.p2.ipos].z+pointscam[a.p3.ipos].z)/3>(pointscam[b.p1.ipos].z+pointscam[b.p2.ipos].z+pointscam[b.p3.ipos].z)/3;
                                                            });
        for (const triangle &triangle : triangles3D)
        {
            sf::Vector3f p1=pointscam[triangle.p1.ipos];
            sf::Vector3f p2=pointscam[triangle.p2.ipos];
            sf::Vector3f p3=pointscam[triangle.p3.ipos];

            if (newtex!=triangle.mat.nom)
           {
                if(newtex!="")
                {
                    target.draw(triangles,&Textures[newtex]);
                    triangles.clear();
                }
                newtex=triangle.mat.nom;
                
           }
            if (p1.z>0 and p2.z>0 and p3.z>0)
            {
                sf::Vertex pr1=camera.Projection(p1);
                sf::Vertex pr2=camera.Projection(p2);
                sf::Vertex pr3=camera.Projection(p3);
                pr1=SFMLScale(pr1.position,target);
                pr2=SFMLScale(pr2.position,target);
                pr3=SFMLScale(pr3.position,target);
                sf::Vector2u size=Textures[triangle.mat.nom].getSize();
                pr1.texCoords={vts[triangle.p1.ivt].x*size.x,(1-vts[triangle.p1.ivt].y)*size.y};
                pr2.texCoords={vts[triangle.p2.ivt].x*size.x,(1-vts[triangle.p2.ivt].y)*size.y};
                pr3.texCoords={vts[triangle.p3.ivt].x*size.x,(1-vts[triangle.p3.ivt].y)*size.y};
                triangles.append(pr1);
                triangles.append(pr2);
                triangles.append(pr3);
            }
            // si la texture est une nouvelle, alors on dessine tous les triangles déjà implémentés, on reset le tableau et on initialise la nouvelle texture
        }
        target.draw(triangles,&Textures[newtex]);
        triangles.clear();
        pointscam.clear();
        
    }



        void load(std::string dirname)
        {
        std::ifstream fic;
        std::string currentmat;
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
                std::string donneemtl;
                std::string nommat;
                std::string nomtext;
                bool kd;
                std::string mtlname;
                fic>>mtlname;
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
                        kd=false;
                        std::cout<<nommat<<std::endl;
                    }
                        
                    if(donneemtl=="map_Kd" or donneemtl=="map_Ke" )
                    {
                        ficmtl>>nomtext;
                        sf::Texture Tex;
                        Tex.loadFromFile(dirname+"/textures/"+ nomtext);
                        std::cout<<" loading : "+dirname+"/textures/"+ nomtext<<std::endl;
                        Textures[nommat]=Tex;
                        kd=true;
                    }
                        
                }
                ficmtl.close();
                
                
            }

            if (donnee=="usemtl")
            {
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
                std::vector<IndexPoint> face;
                getline(fic,donnee);
                std::vector<std::string> ligne=split(donnee," ");
                for (std::string &indice: ligne)
                {
                    if (indice!="" and indice!="\\")
                    {
                        std::vector<std::string> vertex=split(indice,"/");
                        if(vertex[0]=="")vertex[0]="1";
                        if(vertex[1]=="")vertex[1]="1";
                        face.push_back({(stoi(vertex[0])-1),(stoi(vertex[1])-1),currentmat});
                    }
                    
                }
                
                
                faces.push_back(face);
                face.clear();
            }
        }
        fic.close();
        create_triangles();
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

            void create_triangles()
            {
                
                for (std::vector<IndexPoint> const &face : faces)
                {
                    triangle tri;
                    tri.p1=face[0];
                    tri.p2=face[1];
                    tri.p3=face[2];
                    tri.mat.nom=face[0].mat;
                    triangles3D.push_back(tri);
                    
                }
            }
           

};

