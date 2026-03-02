#include <SFML/Graphics.hpp>
#include"Calcules.hpp"
#include"Camera.hpp"
#include<fstream>
#include<iostream>
#include <filesystem>
struct IndexFace
{
    int ipos;
    int ivt;
    int itex;

    IndexFace(){}

    IndexFace(int iposs){
        ipos=iposs;
    }
    IndexFace(int iposs,int ivtt,int itexx){
        ipos=iposs;
        ivt=ivtt;
        itex=itexx;
    }
};

class Objet3D { 
     public:
    std::vector<std::vector<IndexFace>>faces;
    std::vector<sf::Vector3f> points;
    std::vector<sf::Vector2f> vts;
    sf::Vector3f position;
    sf::Vector3f speed;
    std::vector<sf::Texture> Textures;
    float size;
    float RotationAngle;
    Objet3D()
    {

    }
    Objet3D(std::string dirname)
    {
        int indiceTexture=-1;
        std::ifstream fic;
        std::string mtlname;
        std::string Texturename;
        std::string filename=split(dirname,"/")[3]+".obj";
        std::cout<<dirname+"/sources/"+filename<<std::endl;
        fic.open(dirname+"/source/"+filename);
        if (!fic.is_open())
        {
            std::cout<<"erreur d'ouverture de : "<<dirname+"/source/"+filename<<std::endl;
        }
        

        std::string donnee;
        
        while (fic>>donnee)
        {   if (donnee=="mtllib")
            {
                fic>>mtlname;
            }

            if (donnee=="usemtl")
            {
                fic>>donnee;
                std::string donneemtl;
                std::ifstream ficmtl;
                std::cout<<dirname+"/source/"+mtlname<<std::endl;
                ficmtl.open(dirname+"/source/"+mtlname);
                if (!ficmtl.is_open())
                {
                    std::cout<<"erreur d'ouverture de : "<<dirname+"/source/"+mtlname<<std::endl;
                }
                //cherche le nom de la section mtl
                while (ficmtl>>donneemtl and donneemtl!=donnee) 
                {   
                }
                //cherche la section map_kd qui correspond à la texture
                while (ficmtl>>donneemtl and donneemtl!="map_Kd") 
                {  
                }

                //récupère la texture, la charge et la met dans l'objet;
                ficmtl>>Texturename;
                sf::Texture Tex;
                Tex.loadFromFile(dirname+"/textures/"+ Texturename);
                std::cout<<" loading : "+dirname+"/textures/"+ Texturename<<std::endl;
                Textures.push_back(Tex);
                indiceTexture++;
                ficmtl.close();
                
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
                        face.push_back({(stoi(vertex[0])-1),(stoi(vertex[1])-1),indiceTexture});
                    }
                    
                }
                
                
                faces.push_back(face);
                face.clear();
            }
        }
        fic.close();
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
        int newtex=0;
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
                sf::Vector2u size=Textures[face[0].itex].getSize();
                pr1.texCoords={vts[face[0].ivt].x*size.x,(1-vts[face[0].ivt].y)*size.y};
                pr2.texCoords={vts[face[1].ivt].x*size.x,(1-vts[face[1].ivt].y)*size.y};
                pr3.texCoords={vts[face[2].ivt].x*size.x,(1-vts[face[2].ivt].y)*size.y};
                triangles.append(pr1);
                triangles.append(pr2);
                triangles.append(pr3);
            }
           if (newtex!=face[0].itex)
           {
                
                target.draw(triangles,&Textures[newtex]);
                newtex=face[0].itex;
                triangles.clear();
           }
        }
        target.draw(triangles,&Textures[newtex+1]);
        triangles.clear();
    }



        void load(std::string dirname)
        {
            int indiceTexture=-1;
        std::ifstream fic;
        std::string mtlname;
        std::string Texturename;
        std::string filename=split(dirname,"/")[3]+".obj";
        std::cout<<dirname+"/sources/"+filename<<std::endl;
        fic.open(dirname+"/sources/"+filename);
        if (!fic.is_open())
        {
            std::cout<<"erreur d'ouverture de : "<<dirname<<std::endl;
        }
        

        std::string donnee;
        
        while (fic>>donnee)
        {   if (donnee=="mtllib")
            {
                fic>>mtlname;
            }

            if (donnee=="usemtl")
            {
                fic>>donnee;
                std::string donneemtl;
                std::ifstream ficmtl;
                ficmtl.open(dirname+"/sources/"+mtlname);
                //cherche le nom de la section mtl
                while (ficmtl>>donneemtl and donneemtl!=donnee) 
                {   
                }
                //cherche la section map_kd qui correspond à la texture
                while (ficmtl>>donneemtl and donneemtl!="map_kd") 
                {  
                }

                //récupère la texture, la charge et la met dans l'objet;
                ficmtl>>Texturename;
                sf::Texture Tex;
                Tex.loadFromFile(Texturename);
                Textures.push_back(Tex);
                indiceTexture++;
                ficmtl.close();
                
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
                        face.push_back({(stoi(vertex[0])-1),(stoi(vertex[1])-1),indiceTexture});
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

