#pragma once
#include "3d_object.hpp"



class Renderer
{
private:
    std::vector<Clipped_triangle> Triangle3D;
    std::vector<Mesh*> meshs; 
    std::unordered_map<std::string,Transformation*> Map;
    MatManager *matManager;
    int count_hiden(Clipped_triangle &tri,const plan &P);
    void clip( plan &P,std::vector<Clipped_triangle> &visibles);
    Eigen::Matrix4f getMatriceTransformation(Mesh* & mesh);
    Eigen::Matrix4f getMatriceView(Camera &camera,Eigen::Vector4f &point);

public :
    Renderer(MatManager &matManager);
    void getTriangles(Objet3D &Model);
    void removeMesh(std::string nom);
    void draw(sf::RenderTarget& target,Camera &camera,std::vector<Light*> &globalLights);


};

