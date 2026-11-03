#pragma once
#include <SFML/Graphics.hpp>



class Death_particules
{
    public :
    sf::RectangleShape tri;
    int durée=90;
    sf::Vector2f speed;
    Death_particules(const sf::Sprite &Sprite);
    void apply_forces();
    void rebondit(sf::RenderWindow &window);
    void move();
    void affiche(sf::RenderWindow &window);
};