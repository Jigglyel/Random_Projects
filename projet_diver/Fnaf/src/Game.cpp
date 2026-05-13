#include"Game.hpp"


Game::Game(sf::RenderWindow &window,sf::View &camera)
{

    sf::Vector2u windowSize=window.getSize();
    sf::Vector2f windowRatio=sf::Vector2f(windowSize.x/1920.f,windowSize.y/1080.f);

    std::unique_ptr<Walker> Bonnie =std::make_unique<Walker>("Bonnie");
    Bonnie->deplacements[0]={1};
    Bonnie->deplacements[1]={2,4};
    Bonnie->deplacements[2]={1};
    Bonnie->deplacements[4]={1,5,6};
    Bonnie->deplacements[5]={4,1};
    Bonnie->deplacements[6]={5};


    std::unique_ptr<Walker> Chica =std::make_unique<Walker>("Chica");
    Chica->deplacements[0]={1};
    Chica->deplacements[1]={9,7,8};
    Chica->deplacements[9]={1,10};
    Chica->deplacements[10]={9};
    Chica->deplacements[7]={1};
    Chica->deplacements[8]={1};
    std::unique_ptr<Foxy> foxy =std::make_unique<Foxy>("Foxy");
    std::unique_ptr<Freddy> freddy =std::make_unique<Freddy>("Freddy");
    freddy->deplacements[0]={1};
    freddy->deplacements[1]={7};
    freddy->deplacements[7]={9};
    freddy->deplacements[9]={10};
    freddy->deplacements[10]={9};
    freddy->actualCam=&cameras.activeCam;
    freddy->actualState=&currentState;
    foxy->actualState=&currentState;
    animatronics.emplace_back(std::move(Bonnie));
    animatronics.emplace_back(std::move(Chica));
    animatronics.emplace_back(std::move(foxy));
    animatronics.emplace_back(std::move(freddy));
    
    
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(0,windowSize.y-100,windowSize.x,100) ,[this](){currentState=State::Camera;
    std::cout<<"je switch en state camera"<<std::endl;},true));
    this->addButton(State::Camera,Button(ButtonType::Switch, sf::FloatRect(0,0,100,100) ,[this](){currentState=State::Idle;
    std::cout<<"je switch en state Idle"<<std::endl;},true));
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(0,0,100*windowRatio.x,windowSize.y) ,[&window,&camera](){Button::moveCamLeft(camera,window);},true));
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(windowSize.x-100*windowRatio.x,0,100*windowRatio.x,windowSize.y) ,[&window,&camera](){Button::moveCamRight(camera,window);},true));
    this->addButton(State::Idle,Button(ButtonType::Switch,sf::FloatRect(90*windowRatio.x,550*windowRatio.y,80*windowRatio.x,105*windowRatio.y),[]{std::cout<<"lightActivated"<<std::endl;},false));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(1440*windowRatio.x,500*windowRatio.y,90*windowRatio.x,62*windowRatio.y),[this]{cameras.activeCam=0;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(1410*windowRatio.x,586*windowRatio.y,90*windowRatio.x,62*windowRatio.y),[this]{cameras.activeCam=1;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(1250*windowRatio.x,628*windowRatio.y,90*windowRatio.x,62*windowRatio.y),[this]{cameras.activeCam=2;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(1362*windowRatio.x,703*windowRatio.y,90*windowRatio.x,62*windowRatio.y),[this]{cameras.activeCam=3;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(1440*windowRatio.x,880*windowRatio.y,90*windowRatio.x,62*windowRatio.y),[this]{cameras.activeCam=4;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(1313*windowRatio.x,850*windowRatio.y,90*windowRatio.x,62*windowRatio.y),[this]{cameras.activeCam=5;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(1440*windowRatio.x,943*windowRatio.y,90*windowRatio.x,62*windowRatio.y),[this]{cameras.activeCam=6;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(1760*windowRatio.x,628*windowRatio.y,90*windowRatio.x,62*windowRatio.y),[this]{cameras.activeCam=7;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(1747*windowRatio.x,828*windowRatio.y,90*windowRatio.x,62*windowRatio.y),[this]{cameras.activeCam=8;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(1600*windowRatio.x,880*windowRatio.y,90*windowRatio.x,62*windowRatio.y),[this]{cameras.activeCam=9;},true));
    this->addButton(State::Camera,Button(ButtonType::Hold,sf::FloatRect(1600*windowRatio.x,943*windowRatio.y,90*windowRatio.x,62*windowRatio.y),[this]{cameras.activeCam=10;},true));
    this->cameras.activeCam=0;
    this->currentState=State::Idle;
}

void Game::addButton(State s,Button  b)
{
    this->activableButtons[s].push_back(b);
}