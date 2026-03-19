#include <SFML/Graphics.hpp>
#include"Calcules.hpp"
#pragma once
class Camera
{
public:
    sf::Vector3f position;
    double offsetX;
    double offsetY;
    float fov;
    float speed;
    sf::Vector3f velocity;
    bool in_air;
    bool mode_survie;
    bool lights;
    Camera(/* args */);
    sf::Vector2f Projection(sf::Vector3f P);
    sf::Vector3f switch_base(sf::Vector3f P);
    void move();
    void apply_forces();
    void Check_collisions();
};