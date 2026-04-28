#include "Button.hpp"




Button::Button(ButtonType type, sf::FloatRect hitbox,std::function<void()> f)
{
    this->action=f;
    this->type = type;
    this->hitbox = hitbox;
}
ButtonType Button::getType()
{
    return this->type;
}
void Button::porte_gauche(sf::RenderWindow &window)
{
    sf::RectangleShape porte_gauche(sf::Vector2f(100,200));
    porte_gauche.setPosition(0,400);
    porte_gauche.setFillColor(sf::Color::Red);
    window.draw(porte_gauche);
}
void Button::porte_droite(sf::RenderWindow &window)
{
    sf::RectangleShape porte_droite(sf::Vector2f(100,200));
    porte_droite.setPosition(700,400);
    porte_droite.setFillColor(sf::Color::Red);
    window.draw(porte_droite);
}   