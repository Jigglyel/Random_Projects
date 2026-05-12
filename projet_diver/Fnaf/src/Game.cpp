#include"Game.hpp"


Game::Game(sf::RenderWindow &window,sf::View &camera)
{

    sf::Vector2u windowSize=window.getSize();
    
    std::unique_ptr<Walker> Bonnie =std::make_unique<Walker>("Bonnie");
    Bonnie->deplacements[0]={1};
    Bonnie->deplacements[1]={0,2};
    Bonnie->deplacements[2]={1};
    Bonnie->lvl=10;


    std::unique_ptr<Walker> Chica =std::make_unique<Walker>("Chica");
    Chica->deplacements[0]={1};
    Chica->deplacements[1]={0};
    Chica->lvl=10;

    animatronics.emplace_back(std::move(Bonnie));
    animatronics.emplace_back(std::move(Chica));

    
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(0,windowSize.y-100,windowSize.x,100) ,[this](){currentState=State::Camera;
    std::cout<<"je switch en state camera"<<std::endl;},true));
    this->addButton(State::Camera,Button(ButtonType::Switch, sf::FloatRect(0,0,100,100) ,[this](){currentState=State::Idle;
    std::cout<<"je switch en state Idle"<<std::endl;},true));
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(0,0,100,windowSize.y) ,[&window,&camera](){Button::moveCamLeft(camera,window);},true));
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(windowSize.x-100,0,100,windowSize.y) ,[&window,&camera](){Button::moveCamRight(camera,window);},true));
    this->addButton(State::Idle,Button(ButtonType::Switch,sf::FloatRect(90,550,80,105),[]{std::cout<<"lightActivated"<<std::endl;},false));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(1440,500,90,62),[this]{cameras.activeCam=0;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(1410,586,90,62),[this]{cameras.activeCam=1;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(1250,628,90,62),[this]{cameras.activeCam=2;},true));
    this->cameras.activeCam=0;
    this->currentState=State::Idle;
}
void Game::addButton(State s,Button  b)
{
    this->activableButtons[s].push_back(b);
}