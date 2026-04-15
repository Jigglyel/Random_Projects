#include <SFML/Graphics.hpp>
#include"Calcules.hpp"
#include"Camera.hpp"
#include<fstream>
#include<iostream>
#include <filesystem>
#include<map>
#include <array>
#include <iostream>
#include "Light.hpp"
#include<cstdlib>
struct matérieau
{
    sf::Vector3f kd={0,0,0},ke={0,0,0},ka={0,0,0},ks={0,0,0};
    float d=1;
    float Ns=-1;
    sf::Texture map_Kd;
    sf::Texture map_Ke;
    bool check_map_Kd=false,check_map_Ke=false;
    bool first=true;

};
struct IndexPoint
{
    long unsigned int ipos;
    long unsigned int ivt;
    long unsigned int ivn;

    IndexPoint(){}

    IndexPoint(long unsigned int ipos){
        this->ipos=ipos;
    }
    IndexPoint(long unsigned int ipos,long unsigned int ivt){
        this->ipos=ipos;
        this->ivt=ivt;
    }
    IndexPoint(long unsigned int ipos,long unsigned int ivt,long unsigned int ivn){
        this->ipos=ipos;
        this->ivt=ivt;
        this->ivn=ivn;
    }
};

struct triangle
{
    IndexPoint p1;
    IndexPoint p2;
    IndexPoint p3;
    std::string mat;
};

struct Point
{
    
    sf::Vector3f pos;
    sf::Vector2f uv;
    sf::Vector3f vn;
    Point()
    {}
    Point(sf::Vector3f pos,sf::Vector2f uv,sf::Vector3f vn)
    {
        this->pos=pos;
        this->uv=uv;
        this->vn=vn;
    }
};

struct Clipped_triangle
{
    Point p1;
    Point p2;
    Point p3;
    std::string mat;
    Clipped_triangle(Point p1,Point p2, Point p3, std::string mat)
    {
        this->p1=p1;
        this->p2=p2;
        this->p3=p3;
        this->mat=mat;
    }
};


class Objet3D { 
     public:
    std::vector<std::vector<IndexPoint>>faces;
    std::vector<sf::Vector3f> points;
    std::vector<sf::Vector3f> vns;
    std::vector<sf::Vector2f> vts;
    sf::Vector3f position;
    sf::Vector3f speed;
    std::map<std::string,matérieau> Materieaux;
    float size;
    float RotationAngleX;
    float RotationAngleY;
    
    
    Objet3D()
    {
        size=1;
        position={0,0,0};
        RotationAngleX=0;
        RotationAngleY=0;
        speed={0,0,0};
    }
    Objet3D(std::string dirname)
    {
        load(dirname);
        std::cout<<"Nombre de matérieaux chargées : "<<Materieaux.size()<<std::endl;
        size=1;
        position={0,0,0};
        RotationAngleX=0;
        RotationAngleY=0;
    }

    void move()
    {
        position+=speed;
    }

    
    
    void draw(sf::RenderTarget& target,Camera &camera,std::vector<Light*> globalLights) 
    {
        std::string newmat="";
        sf::VertexArray triangles(sf::Triangles);
        
        
        
        
        // traite les triangles, dessine ceux visibles, ignores ceux qui sont invisible et projette ceux qui sont entre les deux
        std::vector<Clipped_triangle> visibles;
        pointscam.reserve(points.size());
        int n=0;
        for(const  sf::Vector3f& point : points)
        {
            pointscam[n]=camera.switch_base(rotate_point(rotate_point(point,RotationAngleX,{0,1,0}),RotationAngleY,{1,0,0})*size+position);
            n++;
        }
        for(const triangle & tri : triangles3D)
        {
                Point P1={pointscam[tri.p1.ipos],vts[tri.p1.ivt],vns[tri.p1.ivn]};
                Point P2={pointscam[tri.p2.ipos],vts[tri.p2.ivt],vns[tri.p2.ivn]};
                Point P3={pointscam[tri.p3.ipos],vts[tri.p3.ivt],vns[tri.p3.ivn]};
            if(prodscal3D(P1.pos,prodvect3D(P2.pos-P1.pos,P3.pos-P1.pos))<=0) //back culling
                visibles.push_back({P1,P2,P3,tri.mat});
        }


        float M_1_sqrt2=1/sqrt(2);
        plan P;


        P.N={0,0,1};
        P.D=-1;
        clip(P,visibles);//plan sur l'axe de la cam

        P.D=0;
        P.N={M_1_sqrt2,0,M_1_sqrt2};
        clip(P,visibles);//plan sur l'axe gauche

        P.N={-1*M_1_sqrt2,0,M_1_sqrt2};
        clip(P,visibles);//plan sur l'axe droit

        P.N={0,M_1_sqrt2,M_1_sqrt2};
        clip(P,visibles);//plan sur l'axe bas

        P.N={0,-1*M_1_sqrt2,M_1_sqrt2};
        clip(P,visibles);//plan sur l'axe haut

        void load(std::string dirname)
        {
            std::ifstream fic;
            std::string currentmat="";
            std::string filename=split(dirname,"/")[3]+".obj";
            std::cout<<"ouverture de "+dirname+"/source/"+filename<<std::endl<<std::endl;
            fic.open(dirname+"/source/"+filename);
            if (!fic.is_open())
            {
                std::cout<<"erreur d'ouverture de : "<<dirname+"/source/"+filename<<std::endl<<std::endl;
            }
            

            std::string donnee;
            
            while (fic>>donnee)
            {   
                if (donnee=="mtllib")
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
                if (donnee=="vn")
                {   
                    float x,y,z;
                    fic>>x;
                    fic>>y;
                    fic>>z;
                    vns.push_back({x,y,z});
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
                            if (vertex!="" and vertex!="\\" and vertex!="\\\r" and vertex!="\\\n" and vertex!="\\\r\n" ) 
                            {
                                std::vector<std::string> index=split(vertex,"/");
                                if(index[1]=="")index[1]="1";
                                if (index.size()!=2)
                                {
                                
                                    face.push_back({unsigned(stoi(index[0])-1),unsigned(stoi(index[1])-1),unsigned(stoi(index[2])-1)});
                                }
                                else
                                {
                                    face.push_back({unsigned(stoi(index[0])-1),unsigned(stoi(index[1])-1)});
                                }
                                
                                
                               
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

            std::cout<<triangles3D.size()<<" triangles ont été fait"<<std::endl;
            std::cout<<points.size()<<" points ont été comptabilises"<<std::endl<<std::endl;
            faces.clear();
            if (vns.size()==0)
                {
                    std::cout<<"creations des normales"<<std::endl;
                    int index=0;
                    for (triangle &tri : triangles3D)
                    {
                        vns.push_back(prodvect3D(Normalize3D(points[tri.p1.ipos]-points[tri.p2.ipos]),Normalize3D(points[tri.p1.ipos]-points[tri.p3.ipos])));
                        tri.p1.ivn=index;
                        tri.p2.ivn=index;
                        tri.p3.ivn=index;
                        index++;
                    }
                }
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
            std::vector<sf::Vector3f>pointscam;
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
                                std::cout<<"erreur chargement texture"<<std::endl<<std::endl;
                        }
                    }
                }

                return textures;
            }

            void create_triangles(const std::string &mat)
            {
                std::cout<<"je cree les triangles du mat : "<<mat<<std::endl<<std::endl;
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

            int count_hiden(Clipped_triangle &tri,const plan &P)
            {
                Point aux;
                int count=0;
                if(prodscal3D(tri.p1.pos-P.N*P.D,P.N)<0)
                {
                    count++;
                }
                if(prodscal3D(tri.p2.pos-P.N*P.D,P.N)<0)
                {
                    count++;
                }
                if(prodscal3D(tri.p3.pos-P.N*P.D,P.N)<0)
                {
                    count++;
                }
                if (prodscal3D(tri.p1.pos-P.N*P.D,P.N)>prodscal3D(tri.p2.pos-P.N*P.D,P.N))
                {
                    aux=tri.p1;
                    tri.p1=tri.p2;
                    tri.p2=aux;
                }
                if (prodscal3D(tri.p1.pos-P.N*P.D,P.N)>prodscal3D(tri.p3.pos-P.N*P.D,P.N))
                {
                    aux=tri.p1;
                    tri.p1=tri.p3;
                    tri.p3=aux;
                }
                if (prodscal3D(tri.p2.pos-P.N*P.D,P.N)>prodscal3D(tri.p3.pos-P.N*P.D,P.N))
                {
                    aux=tri.p2;
                    tri.p2=tri.p3;
                    tri.p3=aux;
                }


                return count;
            }

            void parsemtl(const std::string &mtlname,const std::string &dirname)
            {
                std::string donneemtl;
                    std::string nommat;
                    std::string nomtext;
                    
                    std::cout<<dirname+"/source/"+mtlname<<std::endl<<std::endl;
                    std::ifstream ficmtl;
                    ficmtl.open(dirname+"/source/"+mtlname);
                    if (!ficmtl.is_open())
                    {
                        std::cout<<"erreur d'ouverture de : "<<dirname+"/source/"+mtlname<<std::endl<<std::endl;
                    }
                    while(ficmtl>>donneemtl)
                    {
                        if(donneemtl=="newmtl") 
                        {   
                            ficmtl>>donneemtl;
                            nommat=donneemtl;
                        }
                        if(donneemtl=="Kd")
                        {
                            ficmtl>>Materieaux[nommat].kd.x;
                            ficmtl>>Materieaux[nommat].kd.y;
                            ficmtl>> Materieaux[nommat].kd.z;
                        }

                        if(donneemtl=="Ke")
                        {
                            ficmtl>>Materieaux[nommat].ke.x;
                            ficmtl>>Materieaux[nommat].ke.y;
                            ficmtl>> Materieaux[nommat].ke.z;
                        }
                        if(donneemtl=="Ka")
                        {
                            ficmtl>>Materieaux[nommat].ka.x;
                            ficmtl>>Materieaux[nommat].ka.y;
                            ficmtl>> Materieaux[nommat].ka.z;
                        }
                        if(donneemtl=="Ks")
                        {
                            ficmtl>>Materieaux[nommat].ks.x;
                            ficmtl>>Materieaux[nommat].ks.y;
                            ficmtl>> Materieaux[nommat].ks.z;
                        }
                        if(donneemtl=="d")
                        {
                            float d;
                            ficmtl>>d;
                        }
                        if(donneemtl=="Ns")
                        {
                            ficmtl>> Materieaux[nommat].Ns;
                        }
                        if(donneemtl=="map_Kd")
                        {
                            ficmtl>>nomtext;
                            Materieaux[nommat].map_Kd.loadFromFile(dirname+"/textures/"+ nomtext);
                            Materieaux[nommat].map_Kd.setRepeated(true);
                            Materieaux[nommat].check_map_Kd=true;
                            std::cout<<" loading : "+dirname+"/textures/"+ nomtext<<std::endl<<std::endl;
                        }
                        if(donneemtl=="map_Ke")
                        {
                            ficmtl>>nomtext;
                            Materieaux[nommat].map_Ke.loadFromFile(dirname+"/textures/"+ nomtext);
                            Materieaux[nommat].map_Kd.setRepeated(true);
                            Materieaux[nommat].check_map_Ke=true;
                            std::cout<<" loading : "+dirname+"/textures/"+ nomtext<<std::endl<<std::endl;
                        }
                            
                    }
                    ficmtl.close();
            }

            void clip( plan &P,std::vector<Clipped_triangle> &visibles)
            {
                std::vector<Clipped_triangle>aux;
                for (Clipped_triangle &triangle : visibles)
                {
                    int count=count_hiden(triangle,P);                  
                    if (count==0)
                    {
                        aux.push_back(triangle);
                    }
                    if (count==1 )
                    {
                        float t21=near_projection(triangle.p2.pos,triangle.p1.pos,P);
                        float t31=near_projection(triangle.p3.pos,triangle.p1.pos,P);

                        sf::Vector3f p21=triangle.p2.pos+t21*(triangle.p1.pos-triangle.p2.pos);
                        sf::Vector3f p31=triangle.p3.pos+t31*(triangle.p1.pos-triangle.p3.pos);

                        sf::Vector2f uv21=triangle.p2.uv+t21*(triangle.p1.uv-triangle.p2.uv);
                        sf::Vector2f uv31=triangle.p3.uv+t31*(triangle.p1.uv-triangle.p3.uv);

                        aux.push_back({triangle.p2,{p21,uv21,triangle.p1.vn},{p31,uv31,triangle.p1.vn},triangle.mat});
                        aux.push_back({triangle.p3,triangle.p2,{p31,uv31,triangle.p1.vn},triangle.mat});
                    }
                    if (count==2 )
                    {
                        float t31=near_projection(triangle.p3.pos,triangle.p1.pos,P);
                        float t32=near_projection(triangle.p3.pos,triangle.p2.pos,P);

                        sf::Vector3f p31=triangle.p3.pos+t31*(triangle.p1.pos-triangle.p3.pos);
                        sf::Vector3f p32=triangle.p3.pos+t32*(triangle.p2.pos-triangle.p3.pos);

                        sf::Vector2f uv31=triangle.p3.uv+t31*(triangle.p1.uv-triangle.p3.uv);
                        sf::Vector2f uv32=triangle.p3.uv+t32*(triangle.p2.uv-triangle.p3.uv);
                        
                        aux.push_back({triangle.p3,{p31,uv31,triangle.p1.vn},{p32,uv32,triangle.p1.vn},triangle.mat});
                    }
                }
                visibles=aux;
            }
           

};

