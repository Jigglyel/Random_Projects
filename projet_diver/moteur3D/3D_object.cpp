#include <SFML/Graphics.hpp>
#include"Calcules.hpp"
#include"Camera.hpp"
#include<fstream>
#include<iostream>
#include <filesystem>
#include<map>
struct IndexFace
{
    int ipos;
    int ivt;
    std::string mat;

    IndexFace(){}

    IndexFace(int ipos){
        this->ipos=ipos;
    }
    IndexFace(int ipos,int ivt,std::string mat){
        this->ipos=ipos;
        this->ivt=ivt;
        this->mat=mat;
    }
};

class Objet3D { 
     public:
    std::vector<std::vector<IndexFace>>faces;
    std::vector<sf::Vector3f> points;
    std::vector<sf::Vector2f> vts;
    sf::Vector3f position;
    sf::Vector3f speed;
    std::map<std::string,sf::Texture> Textures;
    float size;
    float RotationAngle;
    Objet3D()
    {

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

    void drawPoints(sf::RenderWindow & window,double dt,Camera & camera)
    {
        for(sf::Vector3f & point :points)
        {
            drawRectangle(SFMLScale(camera.Projection(point),window),window);
        }
    }
    
    void draw(sf::RenderTarget& target,Camera &camera) 
    {
        std::string newtex="";
        sf::VertexArray triangles(sf::Triangles);
        for(std::vector<IndexFace> const &face : faces)
        {

            sf::Vector3f  p1=points[face[0].ipos] ;
            sf::Vector3f  p2=points[face[1].ipos] ;
            sf::Vector3f  p3=points[face[2].ipos] ;
            p1*=size;
            p2*=size;
            p3*=size;
            
            p1+=position;
            p2+=position;
            p3+=position;
            
            p1=camera.switch_base(p1);
            p2=camera.switch_base(p2);
            p3=camera.switch_base(p3);
            if (p1.z>0 and p2.z>0 and p3.z>0)
            {
                sf::Vertex pr1=camera.Projection(p1);
                sf::Vertex pr2=camera.Projection(p2);
                sf::Vertex pr3=camera.Projection(p3);
                pr1=SFMLScale(pr1.position,target);
                pr2=SFMLScale(pr2.position,target);
                pr3=SFMLScale(pr3.position,target);
                sf::Vector2u size=Textures[face[0].mat].getSize();
                pr1.texCoords={vts[face[0].ivt].x*size.x,(1-vts[face[0].ivt].y)*size.y};
                pr2.texCoords={vts[face[1].ivt].x*size.x,(1-vts[face[1].ivt].y)*size.y};
                pr3.texCoords={vts[face[2].ivt].x*size.x,(1-vts[face[2].ivt].y)*size.y};
                triangles.append(pr1);
                triangles.append(pr2);
                triangles.append(pr3);
            }
            // si la texture est une nouvelle, alors on dessine tous les triangles déjà implémentés, on reset le tableau et on initialise la nouvelle texture
           if (newtex!=face[0].mat)
           {
            std::cout<<0<<std::endl;
                if(newtex!="")
                {
                    target.draw(triangles,&Textures[newtex]);
                    triangles.clear();
                }
                newtex=face[0].mat;
                
           }
           else
           if (newtex!=face[1].mat)
           {
            std::cout<<1<<std::endl;
                if(newtex!="")
                {
                    target.draw(triangles,&Textures[newtex]);
                    triangles.clear();
                }
                newtex=face[1].mat;
                
           }
           else
           if (newtex!=face[2].mat)
           {
            std::cout<<2<<std::endl;
                if(newtex!="")
                {
                    target.draw(triangles,&Textures[newtex]);
                    triangles.clear();
                }
                newtex=face[2].mat;
                
           }
        }
        target.draw(triangles,&Textures[newtex]);
        triangles.clear();
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
                    if(donneemtl=="newmtl") 
                    {   
                        ficmtl>>donneemtl;
                        nommat=donneemtl;
                        std::cout<<nommat<<std::endl;
                        while(donneemtl!="map_Kd" and donneemtl!="map_Ke" and donneemtl!="newmtl" and ficmtl>>donneemtl)
                        {
                            if(donneemtl=="map_Kd" or donneemtl=="map_Ke")
                            {
                                ficmtl>>nomtext;
                                sf::Texture Tex;
                                Tex.loadFromFile(dirname+"/textures/"+ nomtext);
                                std::cout<<" loading : "+dirname+"/textures/"+ nomtext<<std::endl;
                                Textures[nommat]=Tex;
                            }
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
                std::vector<IndexFace> face;
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
        }

        private :
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

};

