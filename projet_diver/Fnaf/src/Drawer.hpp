#pragma once
#include"Game.hpp"


class Drawer
{
private:
    sf::RenderWindow *window;
    void drawCam(CameraSystem &cameraSystem,std::vector<std::unique_ptr<Animatronic>> &animatronics);
    void drawIdle(std::vector<std::unique_ptr<Animatronic>> &animatronics);
    // void drawDoor(std::vector<std::unique_ptr<Animatronic>> &animatronics);
    // void drawBehind(std::vector<std::unique_ptr<Animatronic>> &animatronics);
    sf::Texture* getTextureCamera(CameraSystem &cameraSystem,std::vector<std::unique_ptr<Animatronic>> &animatronics);
public:
    TextureManager TM;
    void draw(State s,CameraSystem &cameraSystem,std::vector<std::unique_ptr<Animatronic>> &animatronics);
    Drawer(sf::RenderWindow&window);

    
    
};

