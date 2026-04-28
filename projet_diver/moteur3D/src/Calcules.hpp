#pragma once
#include <SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<Eigen/Dense>

struct plan{
    Eigen::Vector3f N;
    float D;
};

sf::Vector2f SFMLScale(sf::Vector2f P,sf::RenderTarget & window);
void drawRectangle(sf::Vector2f P,sf::RenderWindow & window);
float prodscal3D(Eigen::Vector3f v1,Eigen::Vector3f v2);
float prodscal2D(Eigen::Vector2f v1,Eigen::Vector2f v2);
Eigen::Vector3f prodvect3D(Eigen::Vector3f v1,Eigen::Vector3f v2);
float prodvect2D(Eigen::Vector2f v1,Eigen::Vector2f v2);
Eigen::Vector3f Normalize3D(Eigen::Vector3f v);
Eigen::Vector2f Normalize2D(Eigen::Vector2f v);
Eigen::Vector3f rotate_point(Eigen::Vector3f point,float angle,Eigen::Vector3f sens);
Eigen::Vector3f getcenter(Eigen::Vector3f v1,Eigen::Vector3f v2); //basgauchedevant et hautdroitederrière
void draw_line(sf::Vector2f p1,sf::Vector2f p2,sf::RenderTarget & window);
float getangle(Eigen::Vector2f v1,Eigen::Vector2f v2);
bool isint(std::string str);
std::vector<std::string> split( std::string s, const std::string& delimiter) ;
float near_projection(const Eigen::Vector3f &A,const Eigen::Vector3f &B,plan &P);
void affiche_couleur(sf::Color couleur);
Eigen::Vector3f multvect(Eigen::Vector3f v1,Eigen::Vector3f v2);