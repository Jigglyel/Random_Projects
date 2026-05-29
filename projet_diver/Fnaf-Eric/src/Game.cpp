#include"Game.hpp"

void shellExecute( std::string lien) {
    ShellExecuteA(NULL, "open",lien.c_str(), NULL, NULL, SW_SHOWNOACTIVATE);
}
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
    animatronics.emplace_back(std::make_unique<Rondoudou>("Rondoudou"));
    
    

    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(sf::Vector2f(0,windowSize.y-100.f*windowRatio.y),sf::Vector2f(windowSize.x,100*windowRatio.y)) ,[this,&soundManager](){currentState=State::CameraState;soundManager.playNoise("cameraOpen");
    std::cout<<"je switch en state camera"<<std::endl;},true));
    this->addButton(State::CameraState,Button(ButtonType::Switch, sf::FloatRect(sf::Vector2f{0,0},sf::Vector2f{100*windowRatio.x,100*windowRatio.y}) ,[this,&soundManager](){currentState=State::Idle;soundManager.playNoise("cameraOpen");
    std::cout<<"je switch en state Idle"<<std::endl;},true));
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(sf::Vector2f{0,0},sf::Vector2f(100*windowRatio.x,windowSize.y)) ,[&window,&camera](){Button::moveCamLeft(camera,window);},true));
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(sf::Vector2f(windowSize.x-100.f*windowRatio.x,0),sf::Vector2f(100*windowRatio.x,windowSize.y) ) ,[&window,&camera](){Button::moveCamRight(camera,window);},true));
    this->addButton(State::Idle,Button(ButtonType::Switch,sf::FloatRect(sf::Vector2f{1550*windowRatio.x,550*windowRatio.y},sf::Vector2f{40*windowRatio.x,80*windowRatio.y}),[this,&soundManager]{shellExecute("https://www.youtube.com/watch?v=dQw4w9WgXcQ");},false));
    this->addButton(State::Idle,Button(ButtonType::Switch,sf::FloatRect(sf::Vector2f{1550*windowRatio.x,750*windowRatio.y},sf::Vector2f{40*windowRatio.x,80*windowRatio.y}),[this,&soundManager]{std::system("\"C:/Program Files (x86)/Steam/steamapps/common/Overwatch/Overwatch.exe\"");},false));
    this->addButton(State::CameraState,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1440*windowRatio.x,500*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam="Grille";},true));
    this->addButton(State::CameraState,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1410*windowRatio.x,586*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam="Billard";},true));
    this->addButton(State::CameraState,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1250*windowRatio.x,628*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam="Laverie";},true));
    this->addButton(State::CameraState,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1362*windowRatio.x,703*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam="Escalier";},true));
    this->addButton(State::CameraState,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1440*windowRatio.x,880*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam="Cuisine";},true));
    this->addButton(State::CameraState,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1313*windowRatio.x,850*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam="Couloir droite";},true));
    this->addButton(State::CameraState,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1440*windowRatio.x,943*windowRatio.y},sf::Vector2f{90*windowRatio.x,62*windowRatio.y}),[this]{activeCam="Couloir gauche";},true));
    this->addButton(State::Menu,Button(ButtonType::Switch, sf::FloatRect(sf::Vector2f{750*windowRatio.x,600*windowRatio.y},sf::Vector2f{150*windowRatio.x,500*windowRatio.y}) ,[this,&soundManager](){this->startingNight(1,soundManager);},true));
    this->activeCam="Grille";
    this->currentState=State::Menu;
}

void Game::addButton(State s,Button  b)
{
    this->activableButtons[s].push_back(b);
}


void Game::startingNight(int nbNight,SoundManager &soundManager)
{
    this->currentState=State::StartingNight;
    this->currentNight=nbNight;
    if (nbNight==1)
    {
        animatronics[0]->lvl=1;
        animatronics[1]->lvl=1; 
        animatronics[2]->lvl=1;
        animatronics[3]->lvl=1;
        animatronics[3]->lvl=1;
    }
    else    if (nbNight==2)
    {
        animatronics[0]->lvl=5;
        animatronics[1]->lvl=5; 
        animatronics[2]->lvl=5;
        animatronics[3]->lvl=5;
        animatronics[3]->lvl=1;
    }
    else    if (nbNight==3)
    {
        animatronics[0]->lvl=8;
        animatronics[1]->lvl=8; 
        animatronics[2]->lvl=8;
        animatronics[3]->lvl=8;
        animatronics[3]->lvl=8;
    }
    else if (nbNight==4)
    {
        animatronics[0]->lvl=10;
        animatronics[1]->lvl=10; 
        animatronics[2]->lvl=10;
        animatronics[3]->lvl=10;
        animatronics[3]->lvl=10;
    }
    else if (nbNight==5)
    {
        animatronics[0]->lvl=15;
        animatronics[1]->lvl=15; 
        animatronics[2]->lvl=15;
        animatronics[3]->lvl=15;
        animatronics[3]->lvl=15;
    }

    animatronics[0]->position=0;
    animatronics[1]->position=0;
    animatronics[2]->position=0;
    animatronics[3]->position=0;
    animatronics[0]->jumpScare=false;
    animatronics[1]->jumpScare=false;
    animatronics[2]->jumpScare=false;
    animatronics[3]->jumpScare=false;
    static_cast<Rondoudou*>(animatronics[3].get())->stage=0;
    this->nightClock.restart();
    soundManager.music.stop();
    this->batterie=100;
}