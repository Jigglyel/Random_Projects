#pragma once
#include"Game.hpp"


class Renderer
{
private:
    
    int animationFlash=0;
    
    int animationNight=0;
    std::string currentAnimation="";
    bool loading=false;
    int loadingState=0;
    sf::Clock loadingClock, sixSevenClock;
    bool sixseven;
    std::unordered_map<std::string,std::function<sf::Texture&(Game&game)>>manageCamera;
    void drawCam(Game &game);
    void drawMenu(Game &game);
    void drawIdle(Game &game);
    void drawNightScreen(Game &game);
    void drawFlash();
    void loadingScreen();
    void drawWaterLevel(Game &game);
    void drawTablette(Game &game);
    void drawLightLevel(Game &game);
    void drawAM(Game &game);
    void drawLoose(Game &game);
    void drawCredits(Game &game);
    sf::Vector2f moveCenter;
    sf::View shakeCamera(sf::View &camera);
    void drawJumpscare(Game &game);
    
    FontManager FM;
    TextureManager TM;
    SoundManager* SM;
    sf::Vector2f windowRatio;
    bool credits=false;
public:
    int animationZoom=0;
    int animationShake=0;
    sf::View cameraBackup;
    void draw(Game &game);
    void setAnimationFlash(int flashNumber);
    void setAnimationZoom(int zoomNumber);
    void setAnimationShake(int shakeNumber);
    Renderer(sf::RenderWindow&window,Game&game,SoundManager &soundManager);
    void Zoom(Game &game);
    sf::RenderWindow *window;
    

    
    
};

