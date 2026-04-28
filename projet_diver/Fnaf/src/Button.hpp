#include<SFML/Graphics.hpp>
#include<iostream>
#include<functional>

enum ButtonType
{
    Hover,
    Switch,
    Hold
};
class Button
{
private:
    ButtonType type;
public:
    Button(ButtonType type, sf::FloatRect hitbox,std::function<void()> f);
    ButtonType getType();
    std::function<void()> action;
    bool is_activated=false;
    sf::FloatRect hitbox;
    static void porte_gauche(sf::RenderWindow & window);
    static void porte_droite(sf::RenderWindow & window);

};

