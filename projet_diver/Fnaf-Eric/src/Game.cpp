#include"Game.hpp"
#include"Renderer.hpp"
Game::Game(sf::RenderWindow &window,sf::View &camera,SoundManager &soundManager)
{

    sf::Vector2u windowSize=window.getSize();
    sf::Vector2f windowRatio=sf::Vector2f(windowSize.x/1920.f,windowSize.y/1080.f);
    animatronics.emplace_back(&raphael);
    animatronics.emplace_back(&lucas);
    animatronics.emplace_back(&soeur);
    animatronics.emplace_back(&rondoudou);
    walkers.emplace_back(dynamic_cast<Walker*>(animatronics[0].get()));
    walkers.emplace_back(dynamic_cast<Walker*>(animatronics[1].get()));
    walkers.emplace_back(dynamic_cast<Walker*>(animatronics[2].get()));
    raphael.Lucas=&lucas;
    lucas.Raphael=&raphael;
    this->addButton(State::Idle,Button(ButtonType::Click, sf::FloatRect(sf::Vector2f(1640*windowRatio.x,220*windowRatio.y),sf::Vector2f(250*windowRatio.x,800*windowRatio.y)) ,[this,&soundManager](){soundManager.playNoise("cameraOpen"); renderer->setAnimationZoom(20);
    std::cout<<"je Click en state camera"<<std::endl;},false));
    this->addButton(State::CameraState,Button(ButtonType::Click, sf::FloatRect(sf::Vector2f{0,0},sf::Vector2f{100*windowRatio.x,100*windowRatio.y}) ,[this,&soundManager,&window](){currentState=State::Idle;soundManager.playNoise("cameraOpen"); window.setView(renderer->cameraBackup);
    std::cout<<"je Click en state Idle"<<std::endl;},true));
    this->addButton(State::Tablette,Button(ButtonType::Click, sf::FloatRect(sf::Vector2f{0,0},sf::Vector2f{100*windowRatio.x,100*windowRatio.y}) ,[this,&soundManager,&window](){currentState=State::Idle;soundManager.playNoise("cameraOpen"); window.setView(renderer->cameraBackup);
    std::cout<<"je Click en state Idle"<<std::endl;},true));
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(sf::Vector2f{0,0},sf::Vector2f(100*windowRatio.x,windowSize.y)) ,[this,&window,&camera](){if(renderer->animationZoom==0){Button::moveCamLeft(camera,window);}},true));
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(sf::Vector2f(windowSize.x-100.f*windowRatio.x,0),sf::Vector2f(100*windowRatio.x,windowSize.y) ) ,[this,&window,&camera](){if(renderer->animationZoom==0){Button::moveCamRight(camera,window);}},true));
    this->addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(sf::Vector2f{0,windowSize.y-50.f*windowRatio.y},sf::Vector2f(windowSize.x,50*windowRatio.y)) ,[this,&window,&camera](){currentState=State::Tablette;},true));
    this->addButton(State::Idle,Button(ButtonType::Click,sf::FloatRect(sf::Vector2f(1290*windowRatio.x,0),sf::Vector2f(95*windowRatio.x,windowSize.y)),[this,&soundManager]{
        if(lightPourcentage>=30){
            lightPourcentage-=30;
            if(walkers[0]->position==10) 
                walkers[0]->position=0; 
            soundManager.playNoise("Flash");renderer->setAnimationFlash(255);  }
    },false,sf::Mouse::Button::Left,5));

    this->addButton(State::Idle,Button(ButtonType::Click,sf::FloatRect(sf::Vector2f(1290*windowRatio.x,0),sf::Vector2f(95*windowRatio.x,windowSize.y)),[this,&soundManager]{if(waterPourcentage>=30){
        waterPourcentage-=30; 
        if(walkers[1]->position==10) 
        walkers[1]->position=0; 
    }},false,sf::Mouse::Button::Right,5));
    this->addButton(State::CameraState,Button(ButtonType::Click,sf::FloatRect(sf::Vector2f{1617*windowRatio.x,600*windowRatio.y},sf::Vector2f{100*windowRatio.x,50*windowRatio.y}),[this]{activeCam="Grille";},true));
    this->addButton(State::CameraState,Button(ButtonType::Click,sf::FloatRect(sf::Vector2f{1518*windowRatio.x,695*windowRatio.y},sf::Vector2f{100*windowRatio.x,60*windowRatio.y}),[this]{activeCam="Billard";},true));
    this->addButton(State::CameraState,Button(ButtonType::Click,sf::FloatRect(sf::Vector2f{1716*windowRatio.x,695*windowRatio.y},sf::Vector2f{100*windowRatio.x,60*windowRatio.y}),[this]{activeCam="Laverie";},true));
    this->addButton(State::CameraState,Button(ButtonType::Hold,sf::FloatRect(sf::Vector2f{1300*windowRatio.x,800*windowRatio.y},sf::Vector2f{100*windowRatio.x,60*windowRatio.y}),[this,&soundManager]{
        if(activeCam=="Laverie" and waterPourcentage<100) 
            {waterPourcentage+=1; 
                if(waterPourcentage==100) 
                    {soundManager.playNoise("waterFilled");} 
                else {soundManager.playNoise("waterFilling");} 
            } },true,sf::Mouse::Button::Left,0.1));
    this->addButton(State::Idle,Button(ButtonType::Hover,sf::FloatRect(sf::Vector2f{0,0},sf::Vector2f(windowSize.x/5,windowSize.y)),[this,&soundManager]{
        if(lightPourcentage<100) 
            {lightPourcentage+=1; 
                if(lightPourcentage==100) 
                    {soundManager.playNoise("LightFilled");} 
            } },false,sf::Mouse::Button::Left,0.1));
    
    this->addButton(State::CameraState,Button(ButtonType::Click,sf::FloatRect(sf::Vector2f{1618*windowRatio.x,800*windowRatio.y},sf::Vector2f{100*windowRatio.x,60*windowRatio.y}),[this]{activeCam="Escalier";},true));
    this->addButton(State::CameraState,Button(ButtonType::Click,sf::FloatRect(sf::Vector2f{1760*windowRatio.x,840*windowRatio.y},sf::Vector2f{100*windowRatio.x,60*windowRatio.y}),[this]{activeCam="Cuisine Droite";},true));
    this->addButton(State::CameraState,Button(ButtonType::Click,sf::FloatRect(sf::Vector2f{1473*windowRatio.x,840*windowRatio.y},sf::Vector2f{100*windowRatio.x,60*windowRatio.y}),[this]{activeCam="Cuisine Gauche";},true));
    this->addButton(State::CameraState,Button(ButtonType::Click,sf::FloatRect(sf::Vector2f{1701*windowRatio.x,940*windowRatio.y},sf::Vector2f{100*windowRatio.x,60*windowRatio.y}),[this]{activeCam="Couloir droite";},true));
    this->addButton(State::CameraState,Button(ButtonType::Click,sf::FloatRect(sf::Vector2f{1563*windowRatio.x,940*windowRatio.y},sf::Vector2f{100*windowRatio.x,60*windowRatio.y}),[this]{activeCam="Couloir gauche";},true));
    this->addButton(State::Menu,Button(ButtonType::Click, sf::FloatRect(sf::Vector2f{750*windowRatio.x,600*windowRatio.y},sf::Vector2f{500*windowRatio.x,150*windowRatio.y}) ,[this,&soundManager](){this->startingNight(1,soundManager);},true));
    this->addButton(State::Loose,Button(ButtonType::Click, sf::FloatRect(sf::Vector2f{750*windowRatio.x,600*windowRatio.y},sf::Vector2f{500*windowRatio.x,150*windowRatio.y}) ,[this,&soundManager](){this->startingNight(1,soundManager);},true));
    this->addButton(State::Idle,Button(ButtonType::Hold, sf::FloatRect(sf::Vector2f{900*windowRatio.x,500*windowRatio.y},sf::Vector2f{100*windowRatio.x,400*windowRatio.y}) ,[this,&soundManager](){
        if(rondoudou.stage>0) 
        {
            rondoudou.pourcentage+=5;
            if((rondoudou.stage==1 and rondoudou.pourcentage>=30) or (rondoudou.stage==2 and rondoudou.pourcentage>=65) or (rondoudou.stage==3 and rondoudou.pourcentage>=100))
            {
                rondoudou.stage=0;
                rondoudou.pourcentage=0;
                soundManager.playNoise("RondoudouDeath");
            }
            else
            {
                soundManager.playNoise("RondoudouHit"+std::to_string(rand()%3+1));
            }
        }
        
    },false,sf::Mouse::Button::Left,0.5));
    this->addButton(State::Tablette,Button(ButtonType::Click,sf::FloatRect(sf::Vector2f{100,0},sf::Vector2f(windowSize.x/2.f-100,windowSize.y)),[this,&soundManager]{
        if(soundPlayClock.getElapsedTime().asSeconds()>10)
        {
            soundManager.playNoise("Monkey",sf::Vector3f{0,0,-4});
            if(this->soeur.activesister==soeur::Lucie) 
            {
                soeur.position=0; 
                soeur.nom="Lucie-Leonie";
            }
            soundPlayClock.restart();
        }
        
    },true,sf::Mouse::Button::Left,10));
    this->addButton(State::Tablette,Button(ButtonType::Click,sf::FloatRect(sf::Vector2f{windowSize.x/2.f,0},sf::Vector2f(windowSize.x/2.f,windowSize.y)),[this,&soundManager]{
        if(soundPlayClock.getElapsedTime().asSeconds()>10)
        {    
            soundManager.playNoise("RddSing",sf::Vector3f{0,0,-4});
            if(this->soeur.activesister==soeur::Leonie) 
                {
                    soeur.position=0; 
                    soeur.nom="Lucie-Leonie";
                }
                soundPlayClock.restart();
        }
    },true,sf::Mouse::Button::Left,10));
    this->activeCam="Grille";
    this->currentState=State::Menu;
}

void Game::addButton(State s,Button  b)
{
    this->activableButtons[s].emplace_back(b);
}


void Game::startingNight(int nbNight,SoundManager &soundManager)
{

    sf::View camera=renderer->window->getView();
    camera.setSize(sf::Vector2f(renderer->window->getSize().x*1/3,renderer->window->getSize().y));
    camera.setCenter(sf::Vector2f(renderer->window->getSize().x-camera.getSize().x/2,renderer->window->getSize().y/2));
    renderer->window->setView(camera);
    if (nbNight>5)
    {
        this->currentState=State::Credits;
        if(soundManager.music.openFromFile("../audio/music/credits.mp3"))
        {
            soundManager.music.play();
        }
    }
    else
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

        walkers[0]->position=0;
        walkers[1]->position=0;
        walkers[2]->position=0;
        animatronics[0]->jumpScare=false;
        animatronics[1]->jumpScare=false;
        animatronics[2]->jumpScare=false;
        animatronics[3]->jumpScare=false;
        rondoudou.stage=0;
        soeur.nom="Lucie-Leonie";
        this->waterPourcentage=100;
        this->lightPourcentage=100;
        this->nightClock.restart();
        
}
    
    
}