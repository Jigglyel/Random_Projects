#include <SFML/Graphics.hpp>
#include"Calcules.hpp"
#include"Camera.hpp"
#include<fstream>
#include<iostream>
class Objet3D { 
     public:
    std::vector<std::vector<int>>faces;
    std::vector<sf::Vector3f> points; 
    sf::Vector3f position;
    sf::Vector3f speed;
    float size;
    float RotationAngle;
    Objet3D()
    {

    }
    Objet3D(std::string filename)
    {
        
        std::ifstream fic;
        fic.open(filename);
        if (!fic.is_open())
        {
            std::cout<<"erreur d'ouverture de : "<<filename<<std::endl;
        }
        

        std::string donnee;
        sf::Vector3f vertex;
        std::vector<int> face;
        while (fic>>donnee)
        {   
            if (donnee=="v")  
            {
                fic>>vertex.x;
                fic>>vertex.y;
                fic>>vertex.z;
                points.push_back(vertex);
            }
            if (donnee=="f")
            {   
                
                getline(fic,donnee);
                std::vector<std::string> ligne=split(donnee," ");
                for (std::string &indice: ligne)
                {
                    {
                    if (indice!="" and indice!="\\")
                    {
                        indice= indice.substr(0,indice.find('/'));
                        face.push_back(stoi(indice)-1);
                    }
                    
                    

                    }
                }
                
                
                faces.push_back(face);
                face.clear();
            }
        }
        fic.close();

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

        sf::VertexArray lines(sf::Lines);
        for(std::vector<int> const &face : faces)
        {
            for (int i = 0; i < face.size(); i++)
            {
                sf::Vector3f  p1=points[face[i]]  ;
                sf::Vector3f  p2=points[face[(i+1)%face.size()]] ;
                p1*=size;
                p2*=size;
                
                p1+=position;
                p2+=position;
                
                p1=camera.switch_base(p1);
                p2=camera.switch_base(p2);
                if (p1.z>0 and p2.z>0)
                {
                    sf::Vector2f pr1=camera.Projection(p1);
                    sf::Vector2f pr2=camera.Projection(p2);
                    pr1=SFMLScale(pr1,target);
                    pr2=SFMLScale(pr2,target);
                    if (p1.z>255)
                    {
                        p1.z=255;
                    }
                    if (p2.z>255)
                    {
                        p2.z=255;
                    }
                    
                    sf::Color c1={255-p1.z,255-p1.z,255-p1.z};
                    sf::Color c2={255-p2.z,255-p2.z,255-p2.z};
                    lines.append(sf::Vertex(pr1,c1));
                    lines.append(sf::Vertex(pr2,c2));
                    
                }
            }
        }
        target.draw(lines);
    }



        void load(std::string filename)
        {
            std::ifstream fic;
            fic.open(filename);
            if (fic.is_open())
            {
                std::cout<<"fichier ouvert"<<std::endl;
            }
            

            std::string donnee;
            sf::Vector3f vertex;
            std::vector<int> face;
            while (fic>>donnee)
            {   
                if (donnee=="v")  
                {
                    fic>>vertex.x;
                    fic>>vertex.y;
                    fic>>vertex.z;
                    points.push_back(vertex);
                }
                if (donnee=="f")
                {   
                    
                    
                    while (fic.peek()!='\n')
                    {
                        fic>>donnee;
                        donnee= donnee.substr(0,donnee.find('/'));
                        face.push_back(stoi(donnee)-1);
                        
                    }
                    faces.push_back(face);
                    face.clear();
                }
            }
            fic.close();
            
        }

};

