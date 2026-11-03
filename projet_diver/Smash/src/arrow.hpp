#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include "Hitbox.hpp"
#include "Death_Particules.hpp"
#include<iostream>
#include<cmath>


class Arrow
{
    private:

    public:
    sf::Sprite sprite;
    sf::Vector2f speed;
    Hitbox hitbox;
    int belonging;
    Arrow(sf::Texture &T);
    void move();
    void refresh_hitbox();
    void apply_forces();
    bool is_ground_collision();

};