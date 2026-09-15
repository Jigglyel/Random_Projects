#pragma once
#include "3D_object.hpp"



class Renderer
{
private:
    std::vector<Clipped_triangle> Triangle3D;
    std::vector<Mesh*> meshs; 
    std::unordered_map<std::string,Transformation*> Map;
    MatManager *matManager;
    int count_hiden(Clipped_triangle &tri,const plan &P);
    void clip( plan &P,std::vector<Clipped_triangle> &visibles);
    sf::Matrix4f getMatriceTransformation(Mesh* & mesh);
    sf::Matrix4f getMatriceView(Camera &camera,sf::Vector4f &point);
    void drawTriangle(sf::VertexArray &triangles,Clipped_triangle &triangle,matérieau* mat,Camera &camera,std::vector<Light*> &globalLights,sf::RenderTarget& target);

public :
    Renderer(MatManager &matManager);
    void getTriangles(Objet3D &Model);
    void removeMesh(std::string nom);
    void draw(sf::RenderTarget& target,Camera &camera,std::vector<Light*> &globalLights);
    


};

