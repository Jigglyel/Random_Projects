#pragma once
#include <SFML/Graphics.hpp>
#include"Calcules.hpp"

class Camera
{
public:
    Eigen::Vector3f position;
    double offsetX;
    double offsetY;
    float fov;
    float speed;
    Eigen::Vector3f velocity;
    bool in_air;
    bool mode_survie;
    bool lights;
    Camera(/* args */);
    sf::Vector2f Projection(Eigen::Vector3f P);
    Eigen::Vector3f switch_base(Eigen::Vector3f P);
    void move();
    void apply_forces();
    void Check_collisions();
    Eigen::Matrix4f getMatriceView();
};