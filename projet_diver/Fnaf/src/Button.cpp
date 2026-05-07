#include "Button.hpp"




Button::Button(ButtonType type, sf::FloatRect hitbox,std::function<void()> f,bool hud)
{
    this->action=f;
    this->type = type;
    this->hitbox = hitbox;
    this->Hud=hud;
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
void Button::moveCamLeft(sf::View & camera,sf::RenderWindow & window)
{
     
    if (camera.getCenter().x-camera.getSize().x/2>0)
    {
        camera.setCenter(camera.getCenter()+sf::Vector2f(-5,0));
        window.setView(camera);
    }
    
}

void Button::moveCamRight(sf::View & camera,sf::RenderWindow & window)
{
    if (camera.getCenter().x+camera.getSize().x/2<window.getSize().x)
    {
        camera.setCenter(camera.getCenter()+sf::Vector2f(5,0));
        window.setView(camera);
    }
    
    
}

void Button::draw(sf::RenderWindow & window)
{
    sf::RectangleShape box;
    box.setPosition(hitbox.left,hitbox.top);
    box.setSize(sf::Vector2f(hitbox.width,hitbox.height));
    box.setFillColor(sf::Color::Red);
    box.setOutlineColor(sf::Color::White);
    if(Hud)
    {
        sf::View camera =window.getView();
        window.setView(window.getDefaultView());
        window.draw(box);
        window.setView(camera);
    }
    else
        window.draw(box);
        
}