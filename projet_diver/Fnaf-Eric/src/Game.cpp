#include"Game.hpp"


Game::Game(sf::RenderWindow &window,sf::View &camera,SoundManager &soundManager)
{

    sf::Vector2u windowSize=window.getSize();
    sf::Vector2f windowRatio=sf::Vector2f(windowSize.x/1920.f,windowSize.y/1080.f);
    std::unique_ptr<Animatronic> sister=std::make_unique<Soeur>("Lucie-Leonie");
    std::unique_ptr<Animatronic> raphael=std::make_unique<Raphael>("Raphael");
    std::unique_ptr<Animatronic> lucas=std::make_unique<Lucas>("Lucas");
    animatronics.emplace_back(std::move(raphael));
    animatronics.emplace_back(std::move(lucas));
    animatronics.emplace_back(std::move(sister));
    
    

    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(sf::Vector2f(0,windowSize.y-100.f*windowRatio.y),sf::Vector2f(windowSize.x,100*windowRatio.y)) ,[this,&soundManager](){currentState=State::CameraState;soundManager.playNoise("cameraOpen");
    std::cout<<"je switch en state camera"<<std::endl;},true));
    this->addButton(State::CameraState,Button(ButtonType::Switch, sf::FloatRect(sf::Vector2f{0,0},sf::Vector2f{100*windowRatio.x,100*windowRatio.y}) ,[this,&soundManager](){currentState=State::Idle;soundManager.playNoise("cameraOpen");
    std::cout<<"je switch en state Idle"<<std::endl;},true));
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(sf::Vector2f{0,0},sf::Vector2f(100*windowRatio.x,windowSize.y)) ,[&window,&camera](){Button::moveCamLeft(camera,window);},true));
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(sf::Vector2f(windowSize.x-100.f*windowRatio.x,0),sf::Vector2f(100*windowRatio.x,windowSize.y) ) ,[&window,&camera](){Button::moveCamRight(camera,window);},true));
    this->addButton(State::Idle,Button(ButtonType::Switch,sf::FloatRect(sf::Vector2f{90*windowRatio.x,550*windowRatio.y},sf::Vector2f{80*windowRatio.x,105*windowRatio.y}),[this,&soundManager]{if(batterie>0){this->leftLightOn=!this->leftLightOn;soundManager.playNoise("light");}},false));
    this->addButton(State::Idle,Button(ButtonType::Switch,sf::FloatRect(sf::Vector2f{90*windowRatio.x,400*windowRatio.y},sf::Vector2f{80*windowRatio.x,105*windowRatio.y}),[this,&soundManager]{if(batterie>0){this->leftDoorClose=!this->leftDoorClose;soundManager.playNoise("Door");}},false));
    this->addButton(State::Idle,Button(ButtonType::Switch,sf::FloatRect(sf::Vector2f{1750*windowRatio.x,550*windowRatio.y},sf::Vector2f{80*windowRatio.x,105*windowRatio.y}),[this,&soundManager]{if(batterie>0){this->rightLightOn=!this->rightLightOn;soundManager.playNoise("light");}},false));
    this->addButton(State::Idle,Button(ButtonType::Switch,sf::FloatRect(sf::Vector2f{1750*windowRatio.x,400*windowRatio.y},sf::Vector2f{80*windowRatio.x,105*windowRatio.y}),[this,&soundManager]{if(batterie>0){this->rightDoorClose=!this->rightDoorClose;soundManager.playNoise("Door");}},false));
    this->addButton(State::Idle,Button(ButtonType::Switch,sf::FloatRect(sf::Vector2f{1550*windowRatio.x,550*windowRatio.y},sf::Vector2f{40*windowRatio.x,80*windowRatio.y}),[this,&soundManager]{std::system("start https://www.youtube.com/watch?v=dQw4w9WgXcQ");},false));
    this->addButton(State::Idle,Button(ButtonType::Switch,sf::FloatRect(sf::Vector2f{1550*windowRatio.x,750*windowRatio.y},sf::Vector2f{40*windowRatio.x,80*windowRatio.y}),[this,&soundManager]{std::system("\"C:/Program Files (x86)/Steam/steamapps/common/Overwatch/Overwatch.exe\"");},false));
    this->addButton(State::CameraState,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1440*windowRatio.x,500*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam="Grille";},true));
    this->addButton(State::CameraState,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1410*windowRatio.x,586*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam="Billard";},true));
    this->addButton(State::CameraState,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1250*windowRatio.x,628*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam="Laverie";},true));
    this->addButton(State::CameraState,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1362*windowRatio.x,703*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam="Escalier";},true));
    this->addButton(State::CameraState,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1440*windowRatio.x,880*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam="Cuisine";},true));
    this->addButton(State::CameraState,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1313*windowRatio.x,850*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam="Couloir droite";},true));
    this->addButton(State::CameraState,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1440*windowRatio.x,943*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam="Couloir gauche";},true));
    this->addButton(State::Menu,Button(ButtonType::Switch, sf::FloatRect(sf::Vector2f{800*windowRatio.x,500*windowRatio.y},sf::Vector2f{100*windowRatio.x,100*windowRatio.y}) ,[this,&soundManager](){currentState=State::Idle; this->nightClock.restart(); this->batterie=100;soundManager.music.stop();},true));
    this->activeCam="Grille";
    this->currentState=State::Menu;
}

void Game::addButton(State s,Button  b)
{
    this->activableButtons[s].push_back(b);
}