#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include<Eigen/Dense>



struct matérieau
{
    Eigen::Vector3f kd={0,0,0},ke={0,0,0},ka={0,0,0},ks={0,0,0};
    float d=1;
    float Ns=-1;
    sf::Texture map_Kd;
    sf::Texture map_Ke;
    bool check_map_Kd=false,check_map_Ke=false;
    bool first=true;

};




class MatManager
{
private:
    std::unordered_map<std::string,matérieau> Map;
public:
    void setMaterieau(std::string &nomMat,matérieau &mat,std::string &nomModel);
    matérieau* getMaterieau(std::string &nomMat,std::string &nomModel);
};

