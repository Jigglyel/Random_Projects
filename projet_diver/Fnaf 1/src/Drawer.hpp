#pragma once
#include"Game.hpp"


class Drawer
{
private:
    sf::RenderWindow *window;
    int animationFrames=0;
    std::string currentAnimation="";
    void drawCam(Game &game);
    void drawMenu(Game &game);
    void drawIdle(Game &game);
    // void drawDoor(std::vector<std::unique_ptr<Animatronic>> &animatronics);
    // void drawBehind(std::vector<std::unique_ptr<Animatronic>> &animatronics);
    sf::Texture* getTextureCamera(Game &game);
    void drawAM(Game &game);
    void drawLoose(Game &game);
    void drawBatterie(Game &game);
    FontManager FM;
    TextureManager TM;
    sf::Vector2f windowRatio;
public:
    

    void draw(Game &game);
    Drawer(sf::RenderWindow&window);

    
    
};

