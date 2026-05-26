#include"Game.hpp"


Game::Game(sf::RenderWindow &window,sf::View &camera,SoundManager &soundManager)
{

    sf::Vector2u windowSize=window.getSize();
    sf::Vector2f windowRatio=sf::Vector2f(windowSize.x/1920.f,windowSize.y/1080.f);
    std::unique_ptr<Bonnie> bonnie =std::make_unique<Bonnie>("Bonnie");
    bonnie->leftDoorClose=&leftDoorClose;


    std::unique_ptr<Chica> chica =std::make_unique<Chica>("Chica");
    chica->RightDoorClose=&rightDoorClose;
    std::unique_ptr<Foxy> foxy =std::make_unique<Foxy>("Foxy");
    foxy->actualState=&currentState;
    foxy->leftDoorClose=&leftDoorClose;
    std::unique_ptr<Freddy> freddy =std::make_unique<Freddy>("Freddy");
    freddy->actualCam=&activeCam;
    freddy->actualState=&currentState;
    
    animatronics.emplace_back(std::move(bonnie));
    animatronics.emplace_back(std::move(chica));
    animatronics.emplace_back(std::move(foxy));
    animatronics.emplace_back(std::move(freddy));
    
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(sf::Vector2f(0,windowSize.y-100.f),sf::Vector2f(windowSize.x,100)) ,[this,&soundManager](){currentState=State::Camera;soundManager.playNoise("cameraOpen");
    std::cout<<"je switch en state camera"<<std::endl;},true));
    this->addButton(State::Camera,Button(ButtonType::Switch, sf::FloatRect(sf::Vector2f{0,0},sf::Vector2f{100,100}) ,[this,&soundManager](){currentState=State::Idle;soundManager.playNoise("cameraOpen");
    std::cout<<"je switch en state Idle"<<std::endl;},true));
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(sf::Vector2f{0,0},sf::Vector2f(100*windowRatio.x,windowSize.y)) ,[&window,&camera](){Button::moveCamLeft(camera,window);},true));
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(sf::Vector2f(windowSize.x-100.f*windowRatio.x,0),sf::Vector2f(100*windowRatio.x,windowSize.y) ) ,[&window,&camera](){Button::moveCamRight(camera,window);},true));
    this->addButton(State::Idle,Button(ButtonType::Switch,sf::FloatRect(sf::Vector2f{90*windowRatio.x,550*windowRatio.y},sf::Vector2f{80*windowRatio.x,105*windowRatio.y}),[this,&soundManager]{if(batterie>0){this->leftLightOn=!this->leftLightOn;soundManager.playNoise("light");}},false));
    this->addButton(State::Idle,Button(ButtonType::Switch,sf::FloatRect(sf::Vector2f{90*windowRatio.x,400*windowRatio.y},sf::Vector2f{80*windowRatio.x,105*windowRatio.y}),[this,&soundManager]{if(batterie>0){this->leftDoorClose=!this->leftDoorClose;soundManager.playNoise("Door");}},false));
    this->addButton(State::Idle,Button(ButtonType::Switch,sf::FloatRect(sf::Vector2f{1750*windowRatio.x,550*windowRatio.y},sf::Vector2f{80*windowRatio.x,105*windowRatio.y}),[this,&soundManager]{if(batterie>0){this->rightLightOn=!this->rightLightOn;soundManager.playNoise("light");}},false));
    this->addButton(State::Idle,Button(ButtonType::Switch,sf::FloatRect(sf::Vector2f{1750*windowRatio.x,400*windowRatio.y},sf::Vector2f{80*windowRatio.x,105*windowRatio.y}),[this,&soundManager]{if(batterie>0){this->rightDoorClose=!this->rightDoorClose;soundManager.playNoise("Door");}},false));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1440*windowRatio.x,500*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam=0;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1410*windowRatio.x,586*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam=1;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1250*windowRatio.x,628*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam=2;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1362*windowRatio.x,703*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam=3;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1440*windowRatio.x,880*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam=4;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1313*windowRatio.x,850*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam=5;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1440*windowRatio.x,943*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam=6;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1760*windowRatio.x,628*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam=7;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1747*windowRatio.x,828*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam=8;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1600*windowRatio.x,880*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam=9;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1600*windowRatio.x,943*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam=10;},true));
    this->activeCam=0;
    this->currentState=State::Idle;
}

void Game::addButton(State s,Button  b)
{
    this->activableButtons[s].push_back(b);
}