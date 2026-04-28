#pragma once
#include"Calcules.hpp"
#include"Camera.hpp"
#include<fstream>
#include<iostream>
#include <filesystem>
#include <array>
#include <iostream>
#include "Light.hpp"
#include<cstdlib>
#include"MatManager.hpp"


class Objet3D;
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
Objet3D* proprietaire;
};
struct Transformation
{
Eigen::Vector3f position;
float size;
float RotationAngleX;
float RotationAngleY;
float RotationAngleZ;
};
struct Point
{

Eigen::Vector3f pos;
Eigen::Vector2f uv;
Eigen::Vector3f vn;
Point()
{}
Point(Eigen::Vector3f pos,Eigen::Vector2f uv,Eigen::Vector3f vn)
{
    this->pos=pos;
    this->uv=uv;
    this->vn=vn;
}
};
struct Mesh
{

std::vector<Eigen::Vector3f> points;
std::vector<Eigen::Vector3f> vns;
std::vector<Eigen::Vector2f> vts;
std::vector<triangle> triangles;
std::string nomModel;
};
struct Clipped_triangle
{
Point p1;
Point p2;
Point p3;
std::string mat;
Objet3D* proprietaire;
Clipped_triangle(Point p1,Point p2, Point p3, std::string mat,Objet3D* proprietaire)
{
    this->p1=p1;
    this->p2=p2;
    this->p3=p3;
    this->mat=mat;
    this->proprietaire=proprietaire;
}
};







class Objet3D
{
private:
    
            MatManager *matManager;
            std::string nomModel;
            std::vector<sf::Texture> loadTexturesFromFolder(const std::string& folderPath);
            void create_triangles(const std::string &mat);
            void parsemtl(const std::string &mtlname,const std::string &dirname);


protected:

    std::vector<std::vector<IndexPoint>>faces;

public:
    Objet3D();
    Objet3D(std::string dirname,MatManager&matManager);
    Mesh mesh;
    Transformation transformation;
    std::string getNom();
    Mesh* getMesh();
    Transformation* getTransfo();
    void load(std::string dirname,MatManager&matManager);
};

