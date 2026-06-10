#pragma once
#include"Game.hpp"


class Renderer
{
private:
    sf::RenderWindow *window;
    int animationFlash=0;
    int animationZoom=0;
    int animationNight=0;
    std::string currentAnimation="";
    bool loading=false;
    int loadingState=0;
    sf::Clock loadingClock;
    std::unordered_map<std::string,std::function<sf::Texture&(Game&game)>>manageCamera;
    void drawCam(Game &game);
    void drawMenu(Game &game);
    void drawIdle(Game &game);
    void drawNightScreen(Game &game);
    void drawFlash();
    void loadingScreen();
    void drawWaterLevel(Game &game);
    void drawLightLevel(Game &game);
    // void drawDoor(std::vector<std::unique_ptr<Animatronic>> &animatronics);
    // void drawBehind(std::vector<std::unique_ptr<Animatronic>> &animatronics);
    void drawAM(Game &game);
    void drawLoose(Game &game);
    sf::View CameraBackup;
    FontManager FM;
    TextureManager TM;
    sf::Vector2f windowRatio;
public:
    

    void draw(Game &game);
    void setAnimationFlash(int flashNumber);
    void setAnimationZoom(int zoomNumber);
    Renderer(sf::RenderWindow&window,Game&game);
    void Zoom(Game &game);

    
    
};

