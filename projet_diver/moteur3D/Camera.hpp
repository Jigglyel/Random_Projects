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
    Camera(/* args */);
    sf::Vector2f Projection(sf::Vector3f P);
    sf::Vector3f switch_base(sf::Vector3f P);
};