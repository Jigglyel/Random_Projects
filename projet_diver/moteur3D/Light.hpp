#pragma once
#include <SFML/Graphics.hpp>


enum class LightType { Directional, Point, Spot };
class Light
{
private:
    /* data */
public:
    LightType type;
    sf::Vector3f position;
    sf::Vector3f direction;
    float intensity;

    Light(LightType type,sf::Vector3f position,sf::Vector3f direction,float intensity);
    Light(LightType type,sf::Vector3f directpos,float intensity);
};








