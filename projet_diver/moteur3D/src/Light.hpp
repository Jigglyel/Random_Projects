#pragma once
#include <SFML/Graphics.hpp>
#include<cmath>
#include<iostream>



enum class LightType{Directional,Positionnal};


class Light{
    
    protected:
    LightType type;
    public:
    
    sf::Color couleur;
    virtual ~Light() = default;
    LightType getType()
    {
        return this->type;
    }
    
    
};



class Directional : public Light{
    
    public:
        Eigen::Vector3f direction;
        Directional(const Eigen::Vector3f &direction, const sf::Color &couleur)
        {
            this->direction=direction;
            this->couleur=couleur;
            this->type=LightType::Directional;
        }

        Directional(Eigen::Vector3f &direction)
        {
            this->direction=direction;
            this->type=LightType::Directional;
        }
        Directional()
        {
            this->type=LightType::Directional;
        }
};


class Positionnal : public Light{
    public:
        Eigen::Vector3f position;

        Positionnal(const Eigen::Vector3f &position,const sf::Color &couleur)
        {
            this->position=position;
            this->couleur=couleur;
            this->type=LightType::Positionnal;
        }

        Positionnal(Eigen::Vector3f &position)
        {
            this->position=position;
            this->type=LightType::Positionnal;
        }

        Positionnal(){
            this->type=LightType::Positionnal;
        }
};

