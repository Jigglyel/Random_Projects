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
struct matérieau
{
    sf::Color kd={0,0,0},ke={0,0,0},ka={0,0,0},ks={0,0,0};
    float d=1;
    float Ns=-1;
    sf::Texture map_Kd;
    sf::Texture map_Ke;
    bool check_map_Kd=false,check_map_Ke=false;

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

    
    
    void draw(sf::RenderTarget& target,Camera &camera) 
    {
        std::string newmat="";
        sf::VertexArray triangles(sf::Triangles);
        
        
        
        for(const sf::Vector3f & point : points)
            pointscam.push_back(camera.switch_base((rotate_point(rotate_point(point,RotationAngleX,{0,1,0}),RotationAngleY,{1,0,0})+position)*size));
        
        // traite les triangles, dessine ceux visibles, ignores ceux qui sont invisible et projette ceux qui sont entre les deux
        std::vector<triangle> visibles;
        
        for(const  triangle &tri:triangles3D)
        {
            if(prodscal3D(pointscam[tri.p1.ipos],prodvect3D(pointscam[tri.p2.ipos]-pointscam[tri.p1.ipos],pointscam[tri.p3.ipos]-pointscam[tri.p1.ipos]))<=0)
            visibles.push_back(tri);
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

        std::sort(visibles.begin(),visibles.end(),[this](const triangle & a,const triangle & b)
                                                        {
                                                            return (pointscam[a.p1.ipos].z+pointscam[a.p2.ipos].z+pointscam[a.p3.ipos].z)/3>(pointscam[b.p1.ipos].z+pointscam[b.p2.ipos].z+pointscam[b.p3.ipos].z)/3;
                                                        });
        for (const triangle &triangle : visibles)
        {
            matérieau mat=Materieaux[triangle.mat];

            sf::Vector3f p1=pointscam[triangle.p1.ipos];
            sf::Vector3f p2=pointscam[triangle.p2.ipos];
            sf::Vector3f p3=pointscam[triangle.p3.ipos];

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
                
                sf::Vertex pr1=camera.Projection(p1);
                sf::Vertex pr2=camera.Projection(p2);
                sf::Vertex pr3=camera.Projection(p3);
                pr1=SFMLScale(pr1.position,target);
                pr2=SFMLScale(pr2.position,target);
                pr3=SFMLScale(pr3.position,target);
                sf::Vector2u size=mat.map_Kd.getSize();
                pr1.texCoords={vts[triangle.p1.ivt].x*size.x,(1-vts[triangle.p1.ivt].y)*size.y};
                pr2.texCoords={vts[triangle.p2.ivt].x*size.x,(1-vts[triangle.p2.ivt].y)*size.y};
                pr3.texCoords={vts[triangle.p3.ivt].x*size.x,(1-vts[triangle.p3.ivt].y)*size.y};
                if (camera.lights)
                {
                    sf::Color diffuse1={0,0,0};
                    sf::Color diffuse2={0,0,0};
                    sf::Color diffuse3={0,0,0};
                    std::vector<Light*> globalLights;
                    sf::Color ambiantLight={50,50,50};
                    globalLights.push_back(new Directional{{0,-1,0.1},{255,0,255}});
                    globalLights.push_back(new Directional{{0,-1,-0.1},{0,255,255}});
                    globalLights.push_back(new Directional{{0,-1,-0.1},{255,255,255}});
                    for(Light* &light  :globalLights)
                    {
                        float dot1;
                        float dot2;
                        float dot3;
                        if(light->getType()==LightType::Directional)
                        {
                            sf::Vector3f L=-Normalize3D(static_cast<Directional*>(light)->direction);
                            sf::Vector3f N1=Normalize3D(vns[triangle.p1.ivn]);
                            sf::Vector3f N2=Normalize3D(vns[triangle.p2.ivn]);
                            sf::Vector3f N3=Normalize3D(vns[triangle.p3.ivn]);
                            dot1=prodscal3D(N1,L);
                            if(dot1>0)
                            {
                                diffuse1+=sf::Color(dot1*255,dot1*255,dot1*255)*light->couleur*mat.kd;
                            }
                            dot2=prodscal3D(N2,L);
                            if(dot2>0)
                            {
                                diffuse2+=sf::Color(dot2*255,dot2*255,dot2*255)*light->couleur*mat.kd;
                            }
                            dot3=prodscal3D(N3,L);
                            if(dot3>0)
                            {
                                diffuse3+=sf::Color(dot3*255,dot3*255,dot3*255)*light->couleur*mat.kd;
                            }

                            if (mat.Ns=-1)
                            {
                                sf::Vector3f R1=2.f*N1*dot1-L;
                                sf::Vector3f R2=2.f*N2*dot2-L;
                                sf::Vector3f R3=2.f*N3*dot3-L;
                                float dotr1=prodscal3D(Normalize3D(R1),Normalize3D(-p1));
                                double pow1=pow(dot1, mat.Ns);
                                if (dotr1>0)  {
                                    diffuse1 += light->couleur * sf::Color(pow1*255,pow1*255,pow1*255) *mat.ks;
                                }
                                float dotr2=prodscal3D(Normalize3D(R2),Normalize3D(-p2));
                                double pow2=pow(dot2, mat.Ns);
                                if (dotr2>0)  {
                                    diffuse2 += light->couleur * sf::Color(pow2*255,pow2*255,pow2*255) *mat.ks;
                                }
                                float dotr3=prodscal3D(Normalize3D(R3),Normalize3D(-p3));
                                double pow3=pow(dot3, mat.Ns);
                                if (dotr3>0)  {
                                    diffuse3 += light->couleur * sf::Color(pow3*255,pow3*255,pow3*255) *mat.ks;
                                }
                                
                            }

                        }
                            
                    }
                    
                    

                    for (Light* &light  :globalLights)
                    {
                        delete light;
                    }
                    
                    globalLights.clear();
                    
                    pr1.color=diffuse1+mat.ka*ambiantLight+mat.ke;
                    pr2.color=diffuse2+mat.ka*ambiantLight+mat.ke;
                    pr3.color=diffuse3+mat.ka*ambiantLight+mat.ke;
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
                            if (vertex!="" and vertex!="\\" and vertex!="\\\r" and vertex!="\\\n" and vertex!="\\\r\n") 
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

            std::cout<<triangles3D.size()<<" triangles ont été créés"<<std::endl;
            std::cout<<points.size()<<" points ont été créés"<<std::endl;
            faces.clear();
            if (vns.size()==0)
                {
                    std::cout<<"créations des normales"<<std::endl;
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
                std::cout<<faces.size()<<std::endl;
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


                return count;
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
                            float r,g,b;
                            ficmtl>>r;
                            ficmtl>>g;
                            ficmtl>>b;
                            Materieaux[nommat].kd.r = static_cast<sf::Uint8>(std::clamp(r * 255.f, 0.f, 255.f));
                            Materieaux[nommat].kd.g = static_cast<sf::Uint8>(std::clamp(g * 255.f, 0.f, 255.f));
                            Materieaux[nommat].kd.b = static_cast<sf::Uint8>(std::clamp(b * 255.f, 0.f, 255.f));
                        }

                        if(donneemtl=="Ke")
                        {
                            float r,g,b;
                            ficmtl>>r;
                            ficmtl>>g;
                            ficmtl>>b;
                            Materieaux[nommat].ke.r = static_cast<sf::Uint8>(std::clamp(r * 255.f, 0.f, 255.f));
                            Materieaux[nommat].ke.g = static_cast<sf::Uint8>(std::clamp(g * 255.f, 0.f, 255.f));
                            Materieaux[nommat].ke.b = static_cast<sf::Uint8>(std::clamp(b * 255.f, 0.f, 255.f));
                        }
                        if(donneemtl=="Ka")
                        {
                            float r,g,b;
                            ficmtl>>r;
                            ficmtl>>g;
                            ficmtl>>b;
                            Materieaux[nommat].ka.r = static_cast<sf::Uint8>(std::clamp(r * 255.f, 0.f, 255.f));
                            Materieaux[nommat].ka.g = static_cast<sf::Uint8>(std::clamp(g * 255.f, 0.f, 255.f));
                            Materieaux[nommat].ka.b = static_cast<sf::Uint8>(std::clamp(b * 255.f, 0.f, 255.f));
                        }
                        if(donneemtl=="Ks")
                        {
                            float r,g,b;
                            ficmtl>>r;
                            ficmtl>>g;
                            ficmtl>>b;
                            Materieaux[nommat].ks.r = static_cast<sf::Uint8>(std::clamp(r * 255.f, 0.f, 255.f));
                            Materieaux[nommat].ks.g = static_cast<sf::Uint8>(std::clamp(g * 255.f, 0.f, 255.f));
                            Materieaux[nommat].ks.b = static_cast<sf::Uint8>(std::clamp(b * 255.f, 0.f, 255.f));
                        }
                        if(donneemtl=="d")
                        {
                            float d;
                            ficmtl>>d;
                            Materieaux[nommat].kd.a = static_cast<sf::Uint8>(std::clamp(d * 255.f, 0.f, 255.f));
                            Materieaux[nommat].ke.a = static_cast<sf::Uint8>(std::clamp(d * 255.f, 0.f, 255.f));
                        }
                            
                        if(donneemtl=="map_Kd")
                        {
                            ficmtl>>nomtext;
                            Materieaux[nommat].map_Kd.loadFromFile(dirname+"/textures/"+ nomtext);
                            Materieaux[nommat].map_Kd.setRepeated(true);
                            Materieaux[nommat].check_map_Kd=true;
                            std::cout<<" loading : "+dirname+"/textures/"+ nomtext<<std::endl;
                        }
                        if(donneemtl=="map_Ke")
                        {
                            ficmtl>>nomtext;
                            Materieaux[nommat].map_Ke.loadFromFile(dirname+"/textures/"+ nomtext);
                            Materieaux[nommat].map_Kd.setRepeated(true);
                            Materieaux[nommat].check_map_Ke=true;
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
                        aux.push_back({triangle.p2,{pointscam.size()-2,triangle.p1.ivt,triangle.p1.ivn},{pointscam.size()-1,triangle.p1.ivt,triangle.p1.ivn},triangle.mat});
                        aux.push_back({triangle.p3,triangle.p2,{pointscam.size()-1,triangle.p1.ivt,triangle.p1.ivn},triangle.mat});
                    }
                    if (count==2 )
                    {
                        pointscam.push_back(near_projection(p3,p1,P));
                        pointscam.push_back(near_projection(p3,p2,P));
                        aux.push_back({triangle.p3,{pointscam.size()-2,triangle.p1.ivt,triangle.p1.ivn},{pointscam.size()-1,triangle.p2.ivt,triangle.p1.ivn},triangle.mat});
                    }
                }
                visibles=aux;
            }
           

};

