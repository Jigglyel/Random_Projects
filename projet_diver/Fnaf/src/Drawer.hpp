#pragma once
#include"Game.hpp"


class Drawer
{
private:
    sf::RenderWindow *window;
    void drawCam(CameraSystem &cameraSystem,std::vector<Animatronic>&animatronics);
    void drawIdle(std::vector<Animatronic>&animatronics);
    // void drawDoor(std::vector<Animatronic>&animatronics);
    // void drawBehind(std::vector<Animatronic>&animatronics);
    sf::Texture* getTextureCamera(CameraSystem &cameraSystem,std::vector<Animatronic>&animatronics);
public:
    TextureManager TM;
    void draw(State s,CameraSystem &cameraSystem,std::vector<Animatronic>&animatronics);
    Drawer(sf::RenderWindow&window);

    
    
};

