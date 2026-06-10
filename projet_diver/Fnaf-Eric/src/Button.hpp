#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
#include<functional>

enum ButtonType
{
    Hover,
    Click,
    Hold
};
class Button
{
private:
    ButtonType type;
    std::function<void()> action;
    
    float cooldown=0;
    sf::Clock innerClock;
public:
    Button(ButtonType type, sf::FloatRect hitbox,std::function<void()> f,bool hud);
    Button(ButtonType type, sf::FloatRect hitbox,std::function<void()> f,bool hud,sf::Mouse::Button bouton);
    Button(ButtonType type, sf::FloatRect hitbox,std::function<void()> f,bool hud,sf::Mouse::Button bouton,float cooldown);
    ButtonType getType();
    sf::FloatRect hitbox;
    bool is_activated=false;
    
    bool Hud;
    static void porte_gauche(sf::RenderWindow & window);
    static void porte_droite(sf::RenderWindow & window);
    static void moveCamRight(sf::View & camera,sf::RenderWindow & window);
    static void moveCamLeft(sf::View & camera,sf::RenderWindow & window);
    void draw(sf::RenderWindow & window);
    std::optional<sf::Mouse::Button> bouton;
    
    
    void activate();

};


