#include "3D_object.hpp"

Objet3D::Objet3D()
{
    transformation.size=1;
    transformation.position={0,0,0};
    transformation.RotationAngleX=0;
    transformation.RotationAngleY=0;
}
Objet3D::Objet3D(std::string dirname,MatManager&matManager)
{
    load(dirname,matManager);
    transformation.size=1;
    transformation.position={0,0,0};
    transformation.RotationAngleX=0;
    transformation.RotationAngleY=0;
    transformation.RotationAngleZ=0;
    
}


std::string Objet3D::getNom()
{
    return nomModel;
}
Mesh* Objet3D::getMesh() 
{
    return &mesh;      
}
Transformation* Objet3D::getTransfo() 
{
    return &transformation;      
}
void Objet3D::load(std::string dirname,MatManager&matManager)
{
    this->matManager=&matManager;
    
    
    std::ifstream fic;
    std::string currentmat="";
    nomModel=split(dirname,"/")[3];
    mesh.nomModel=nomModel;
    std::string filename=nomModel+".obj";
    std::cout<<"chargement du model : "<<nomModel<<std::endl<<std::endl;
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
            mesh.points.push_back({x,y,z});
        }

        if (donnee=="vt")  
        {   float x,y;
            fic>>x;
            fic>>y;
            mesh.vts.push_back({x,y});
        }
        if (donnee=="vn")
        {   
            float x,y,z;
            fic>>x;
            fic>>y;
            fic>>z;
            mesh.vns.push_back({x,y,z});
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
    std::cout<<mesh.triangles.size()<<" triangles ont été fait"<<std::endl;
    std::cout<<mesh.points.size()<<" points ont été comptabilises"<<std::endl<<std::endl;
    faces.clear();
    if (mesh.vns.size()==0)
        {
            std::cout<<"creations des normales"<<std::endl;
            int index=0;
            for (triangle &tri : mesh.triangles)
            {
                mesh.vns.push_back(prodvect3D(Normalize3D(mesh.points[tri.p1.ipos]-mesh.points[tri.p2.ipos]),Normalize3D(mesh.points[tri.p1.ipos]-mesh.points[tri.p3.ipos])));
                tri.p1.ivn=index;
                tri.p2.ivn=index;
                tri.p3.ivn=index;
                index++;
            }
        }
}

        std::vector<sf::Texture> Objet3D::loadTexturesFromFolder(const std::string& folderPath)
        
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

        void Objet3D::create_triangles(const std::string &mat)
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
                    tri.proprietaire=this;
                    mesh.triangles.push_back(tri);
                    
                }
            }
            
            
        }


        void Objet3D::parsemtl(const std::string &mtlname,const std::string &dirname)
        {
            std::string donneemtl;
                std::string nommat="";
                std::string nomtext;
                matérieau mat;
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
                        if (nommat!="")
                        {
                            matManager->setMaterieau(nommat,mat,nomModel);
                            mat=matérieau();
                        }
                        
                        nommat=donneemtl;
                    }
                    if(donneemtl=="Kd")
                    {
                        ficmtl>>mat.kd.x();
                        ficmtl>>mat.kd.y();
                        ficmtl>>mat.kd.z();
                    }

                    if(donneemtl=="Ke")
                    {
                        ficmtl>>mat.ke.x();
                        ficmtl>>mat.ke.y();
                        ficmtl>> mat.ke.z();
                    }
                    if(donneemtl=="Ka")
                    {
                        ficmtl>>mat.ka.x();
                        ficmtl>>mat.ka.y();
                        ficmtl>> mat.ka.z();
                    }
                    if(donneemtl=="Ks")
                    {
                        ficmtl>>mat.ks.x();
                        ficmtl>>mat.ks.y();
                        ficmtl>> mat.ks.z();
                    }
                    if(donneemtl=="d")
                    {
                        float d;
                        ficmtl>>d;
                    }
                    if(donneemtl=="Ns")
                    {
                        ficmtl>> mat.Ns;
                    }
                    if(donneemtl=="map_Kd")
                    {
                        ficmtl>>nomtext;
                        mat.map_Kd.loadFromFile(dirname+"/textures/"+ nomtext);
                        mat.map_Kd.setRepeated(true);
                        mat.check_map_Kd=true;
                        std::cout<<" loading : "+dirname+"/textures/"+ nomtext<<std::endl<<std::endl;
                    }
                    if(donneemtl=="map_Ke")
                    {
                        ficmtl>>nomtext;
                        mat.map_Ke.loadFromFile(dirname+"/textures/"+ nomtext);
                        mat.map_Kd.setRepeated(true);
                        mat.check_map_Ke=true;
                        std::cout<<" loading : "+dirname+"/textures/"+ nomtext<<std::endl<<std::endl;
                    }
                        
                }
                matManager->setMaterieau(nommat,mat,nomModel);
                ficmtl.close();

        }

        
    

