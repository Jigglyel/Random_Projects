#pragma once
#include<SFML/Graphics.hpp>


class Hitbox{
    public: 
    sf::FloatRect hitbox;
    float duration;
    float damage;
    float puissance_ejec;
    sf::Vector2f direction;
    sf::Vector2f decalage;
    Hitbox();

};