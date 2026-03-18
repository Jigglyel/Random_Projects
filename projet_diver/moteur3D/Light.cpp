#include"Light.hpp"

Light::Light(LightType type,sf::Vector3f position,sf::Vector3f direction,float intensity)
{
    this->type=type;
    this->position=position;
    this->direction=direction;
    this->intensity=intensity;
}

Light::Light(LightType type,sf::Vector3f directpos,float intensity)
{
    if (type==LightType::Directional)
    {
        this->direction=directpos;
        this->type=type;
        this->intensity=intensity;
    }
    else if(type==LightType::Point)
    {
        this->position=directpos;
        this->type=type;
        this->intensity=intensity;
    }
    
}