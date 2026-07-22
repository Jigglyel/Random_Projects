#include"Renderer.hpp"

std::vector<std::string> split(std::string s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}
void Renderer::draw(Game &game)
{
    if (loading)
    {
        loadingScreen();
    }
    if(game.currentState==State::Jumpscare)
    {
        if(this->animationShake==0)
        {
            this->animationShake=60;
            this->cameraBackup=window->getView();
        }
        
        drawJumpscare(game);
    }
    else
    if (game.currentState==State::Idle)
    {
        drawIdle(game);
    }
    else
    if (game.currentState==State::CameraState)
    {
        drawCam(game);
    }
    else
    if (game.currentState==State::Menu)
    {
        drawMenu(game);
    }
    else
    if (game.currentState==State::Loose)
    {
        drawLoose(game);
    }
    else
    if (game.currentState==State::StartingNight)
    {
        drawNightScreen(game);
    }
    else
    if (game.currentState==State::Tablette)
    {
        drawTablette(game);
    }
    else
    if (game.currentState==State::Credits)
    {
        drawCredits(game);
    }
}

void Renderer::drawCam(Game &game)
{
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    sf::RectangleShape background;
    background.setPosition(sf::Vector2f{0,0});
    background.setSize(sf::Vector2f(window->getSize()));
    if(game.activeCam=="Cuisine Gauche")
    {
        background.setFillColor(sf::Color::Black);
        window->draw(background);
        sf::Text text(FM.getFont("Jersey15-Regular"),"Camera Disabled sound only ",70);
        text.setPosition(sf::Vector2f{500*this->windowRatio.x,window->getSize().y-200*this->windowRatio.y});
        text.setFillColor(sf::Color::White);
        window->draw(text);
        
    }else
    {
        
        background.setTexture(&manageCamera[game.activeCam](game));
        window->draw(background);
        
    }
    
    sf::RectangleShape HUD({500*this->windowRatio.x,500*this->windowRatio.y});
    HUD.setPosition({window->getSize().x-500*this->windowRatio.x,window->getSize().y-500*this->windowRatio.y});
    HUD.setTexture(&TM.getTexture("CamHUD"));
    if(HUD.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
    {
        HUD.setFillColor(sf::Color(255,255,255,255));
    }
    else
        HUD.setFillColor(sf::Color(255,255,255,40));

    window->draw(HUD);
    sf::RectangleShape Cross({100*this->windowRatio.x,100*this->windowRatio.y});
    Cross.setPosition({0,0});
    Cross.setTexture(&TM.getTexture("Croix"));
    window->draw(Cross);
    drawAM(game);
    window->setView(camera);

    drawWaterLevel(game);
    drawLightLevel(game);

}
void Renderer::drawNightScreen(Game &game)
{
    if (this->animationNight==0)
    {
        animationNight=350;
    }
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    sf::Text text(FM.getFont("Jersey15-Regular"),"Nuit "+std::to_string(game.currentNight),100);
    text.setPosition(sf::Vector2f{window->getSize().x/2-text.getGlobalBounds().size.x/2,window->getSize().y/2-text.getGlobalBounds().size.y/2});
    text.setFillColor(sf::Color((std::clamp(350-animationNight,0,255)),0,0));
    window->draw(text);
    
    animationNight--;
    if (animationNight==0)
    {
        game.nightClock.restart();
        game.currentState=State::Idle;
        std::cout<<"Nuit "<<game.currentNight<<" commencée"<<std::endl;
        if(SM->music.openFromFile("../audio/appels/nuit"+std::to_string(game.currentNight)+"-phoneCall.mp3"));
            SM->music.play(); 
    }
    window->setView(camera);
}

void Renderer::drawAM(Game &game)
{
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    sf::Text text(FM.getFont("Jersey15-Regular"),std::to_string((int(game.nightClock.getElapsedTime().asSeconds())/(game.nightDuration/6)+11)%12+1)+"AM",50);
    text.setCharacterSize(50);
    text.setPosition(sf::Vector2f{1700*this->windowRatio.x,50*this->windowRatio.y});
    window->draw(text);
    text.setString("Nuit "+std::to_string(game.currentNight));
    text.setPosition({text.getPosition().x,text.getPosition().y+50*this->windowRatio.y});
    window->draw(text);
    window->setView(camera);
}

void Renderer::drawIdle(Game &game)
{
    if (this->animationZoom>0)
    {
        if (this->animationZoom==20)
        {
            this->cameraBackup=window->getView();
            this->moveCenter=sf::Vector2f(1750*this->windowRatio.x,616*this->windowRatio.y)-this->cameraBackup.getCenter();
        }
       Zoom(game);
    }
    sf::RectangleShape background;
    background.setPosition(sf::Vector2f{0,0});
    background.setSize(sf::Vector2f(window->getSize()));
    std::string nomTexture="Chambre-R"+std::to_string(static_cast<Rondoudou*>(game.animatronics[3].get())->stage);
    if(game.walkers[0]->position==10)
    {
        nomTexture+="-Raphael";
    }
    if(game.walkers[1]->position==10)
    {
        nomTexture+="-Lucas";
    }
    background.setTexture(&TM.getTexture(nomTexture));
    window->draw(background);
    if(this->animationFlash>0)
        drawFlash();
    drawAM(game);
    drawWaterLevel(game);
    drawLightLevel(game);
}

Renderer::Renderer(sf::RenderWindow&window,Game&game,SoundManager &soundManager)
{
    this->window=&window;
    sf::Vector2u windowSize=window.getSize();
    this->windowRatio=sf::Vector2f(windowSize.x/1920.f,windowSize.y/1080.f);
    this->SM=&soundManager;

    this->manageCamera["Grille"]= [this](Game&game) -> sf::Texture& {
        std::string nomTexture="Grille";
        for (Walker* &animatronic : game.walkers)
        {
            if (animatronic->position==0)
            {
                nomTexture+="-"+animatronic->nom;
            }
            
        }
        return TM.getTexture(nomTexture);
        
    };

    this->manageCamera["Billard"]= [this](Game&game) -> sf::Texture& {
        std::string nomTexture="Billard";
        for (Walker* &animatronic : game.walkers)
        {
            if (animatronic->position==1)
            {
                nomTexture+="-"+animatronic->nom;
            }
            
        }
        if (nomTexture=="Billard-Lucas")
        {
                return TM.getTexture(nomTexture+"-"+std::to_string(static_cast<Lucas*>(game.animatronics[1].get())->illustration));
        }
        
        return TM.getTexture(nomTexture);
        
    };
    this->manageCamera["Laverie"]= [this](Game&game) -> sf::Texture& {
        std::string nomTexture="Laverie";
        for (Walker* &animatronic : game.walkers)
        {
            if (animatronic->position==2)
            {
                nomTexture+="-"+animatronic->nom;
            }
            
        }
        if (nomTexture=="Laverie-Raphael")
        {
                return TM.getTexture(nomTexture+"-"+std::to_string(static_cast<Raphael*>(game.animatronics[0].get())->illustration));
        }
        
        return TM.getTexture(nomTexture);
        
    };

    this->manageCamera["Escalier"]= [this](Game&game) -> sf::Texture& {
        std::string nomTexture="Escalier";
        for (Walker* &animatronic : game.walkers)
        {
            if (animatronic->position==3)
            {
                if (animatronic->nom=="Lucie" and game.soeur.sixSeven)
                {
                    if(sixSevenClock.getElapsedTime().asSeconds()>0.8)
                    {
                        sixseven=!sixseven;
                        sixSevenClock.restart();
                    }
                    return TM.getTexture("67-"+(sixseven+1));
                }
                return TM.getTexture(nomTexture+"-"+animatronic->nom+"-"+std::to_string(animatronic->illustration));
            }
            
        }
        return TM.getTexture(nomTexture);
        
    };

    this->manageCamera["Cuisine Droite"]= [this](Game&game) -> sf::Texture& {
        std::string nomTexture="Cuisine Droite";
        for (Walker* &animatronic : game.walkers)
        {
            if (animatronic->position==4)
            {
                nomTexture+="-"+animatronic->nom;
            }
            
        }
        auto splitName=split(nomTexture,"-");
        if (splitName.size()==2)
        {
            if (splitName[1]=="Raphael")
            {
                int illu=static_cast<Raphael*>(game.animatronics[0].get())->illustration;
                if (illu==2)
                {
                    if (rand()%5==0)
                    {
                        return TM.getTexture(nomTexture+"-3");
                    }
                    
                    return TM.getTexture(nomTexture+"-2");
                }
                else
                    return TM.getTexture(nomTexture+"-1");
            }
            else
                return TM.getTexture(nomTexture+"-"+std::to_string(static_cast<Walker*>(game.animatronics[2].get())->illustration)); 

        }
            
            
        
        return TM.getTexture(nomTexture);
        
    };

    this->manageCamera["Couloir droite"]= [this](Game&game) -> sf::Texture& {
        std::string nomTexture="Couloir droite";
        for (Walker* &animatronic : game.walkers)
        {
            if (animatronic->position==5)
            {
                nomTexture+="-"+animatronic->nom;
            }
            if (animatronic->position==6)
            {
                return TM.getTexture("Couloir droite-Raphael-position2");
            }
            
        }
        return TM.getTexture(nomTexture);
        
    };
    this->manageCamera["Couloir gauche"]= [this](Game&game) -> sf::Texture& {
        std::string nomTexture="Couloir gauche";
        for (Walker* &animatronic : game.walkers)
        {
            if (animatronic->position==8)
            {
                nomTexture+="-"+animatronic->nom;
            }
            
            if (animatronic->position==9)
            {
                nomTexture+="-Lucas-position2";
            }
            if (animatronic->nom=="Lucas" and (animatronic->position==8 or animatronic->position==9))
            {
                nomTexture+="-"+std::to_string(animatronic->illustration);
            }
            
        }
        return TM.getTexture(nomTexture);
        
    };
    loading=true;
    std::thread t1([this](){
        
        TM.loadTextures();
        loading=false;
    });
    while(loading)
    {
       while (std::optional event=window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        loadingScreen();
        window.display();
    }
    t1.join();




}
void Renderer::loadingScreen()
{
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    
    std::string dots=".";
    for (int i = 0; i < loadingState; i++)
    {
        dots+=".";
    }
    sf::Text text(FM.getFont("Jersey15-Regular"),"Loading"+dots,100);
    text.setPosition(sf::Vector2f{window->getSize().x/2-150.f,window->getSize().y/2-text.getGlobalBounds().size.y/2});
    text.setFillColor(sf::Color::White);
    if (loadingClock.getElapsedTime().asSeconds()>1)
    {
        loadingState=(loadingState+1)%3;
        loadingClock.restart();
    }
    window->clear(sf::Color::Black);
        window->draw(text);
        window->setView(camera);
    
    
}
void Renderer::drawMenu(Game &game)
{
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    sf::Text text(FM.getFont("Jersey15-Regular"),"Jouer",200);
    text.setPosition(sf::Vector2f{window->getSize().x/2-text.getGlobalBounds().size.x/2,window->getSize().y/2-text.getGlobalBounds().size.y/2});
    text.setFillColor(sf::Color(255,255,0));
    window->draw(text);
    window->setView(camera);
}
void Renderer::drawLoose(Game &game){
    sf::RectangleShape background;
    window->setView(window->getDefaultView());
    background.setPosition(sf::Vector2f{0,0});
    background.setSize(sf::Vector2f(window->getSize()));
    background.setFillColor(sf::Color::Red);
    window->draw(background);
    sf::Text text(FM.getFont("Jersey15-Regular"),"You Died",100);
    text.setPosition(sf::Vector2f{window->getSize().x/2-text.getGlobalBounds().size.x/2,window->getSize().y/2-text.getGlobalBounds().size.y/2});
    text.setFillColor(sf::Color::White);
    window->draw(text);
}

void Renderer::drawFlash(){
    sf::RectangleShape background(sf::Vector2f(window->getSize()));
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    background.setPosition(sf::Vector2f{0,0});
    
    background.setFillColor(sf::Color(255,255,255,std::clamp(0,255,this->animationFlash)));
    
    window->draw(background);
    animationFlash--;
    window->setView(camera);
}

void Renderer::setAnimationFlash(int flashNumber){
    this->animationFlash=flashNumber;
}

void Renderer::drawWaterLevel(Game &game)
{
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    sf::RectangleShape background({100*windowRatio.x,300*windowRatio.y});
    background.setPosition(sf::Vector2f{100*windowRatio.x,700*windowRatio.y});
    background.setFillColor(sf::Color::White);
    float taille_eau=285*windowRatio.y*(game.waterPourcentage/100.f);
    sf::RectangleShape water({90*windowRatio.x,taille_eau});
    water.setPosition({105*windowRatio.x,710*windowRatio.y+285-taille_eau});
    water.setFillColor(sf::Color::Blue);
    window->draw(background);
    window->draw(water);
    window->setView(camera);
}

void Renderer::drawLightLevel(Game &game)
{
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    sf::RectangleShape background({100*windowRatio.x,300*windowRatio.y});
    background.setPosition(sf::Vector2f{250*windowRatio.x,700*windowRatio.y});
    background.setFillColor(sf::Color::White);
    float taille_eau=285*windowRatio.y*(game.lightPourcentage/100.f);
    sf::RectangleShape water({90*windowRatio.x,taille_eau});
    water.setPosition({255*windowRatio.x,710*windowRatio.y+285-taille_eau});
    water.setFillColor(sf::Color::Yellow);
    window->draw(background);
    window->draw(water);
    window->setView(camera);
}
void Renderer::setAnimationZoom(int zoomNumber)
{
    this->animationZoom=zoomNumber;
}
void Renderer::Zoom(Game&game)
{
    sf::View camera=window->getView();
    camera.setCenter(camera.getCenter()+moveCenter/20.f);
        camera.zoom(0.90f);
    animationZoom--;
    window->setView(camera);
    if (animationZoom==0)
    {
        game.currentState=State::CameraState;
    }
    
}

void Renderer::drawTablette(Game &game)
{
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    sf::RectangleShape backgroundLeft(sf::Vector2f(window->getSize().x/2,window->getSize().y));
    backgroundLeft.setPosition({0,0});
    if(game.soundPlayClock.getElapsedTime().asSeconds()<=10)
    {
        backgroundLeft.setFillColor(sf::Color(150,150,0));
    }
    else
    {
        backgroundLeft.setFillColor(sf::Color::Yellow);
    }
    window->draw(backgroundLeft);
    sf::RectangleShape backgroundRight(sf::Vector2f(window->getSize().x/2,window->getSize().y));
    backgroundRight.setPosition(sf::Vector2f(window->getSize().x/2,0));
    if(game.soundPlayClock.getElapsedTime().asSeconds()<=10)
    {
        backgroundRight.setFillColor(sf::Color(255*0.7,150*0.7,150*0.7));
    }
    else
    {
        backgroundRight.setFillColor(sf::Color(255,150,150));
    }
    window->draw(backgroundRight);
    sf::RectangleShape monkey({210*windowRatio.x,142*windowRatio.y});
    monkey.setPosition({window->getSize().x/4-105*windowRatio.x,window->getSize().y/2-71*windowRatio.y});
    monkey.setTexture(&TM.getTexture("singe"));
    sf::RectangleShape rondoudou({150*windowRatio.x,150*windowRatio.y});
    rondoudou.setPosition({window->getSize().x*3/4-75*windowRatio.x,window->getSize().y/2-75*windowRatio.y});
    rondoudou.setTexture(&TM.getTexture("rondoudou"));
    window->draw(monkey);
    window->draw(rondoudou);
    drawAM(game);
    window->setView(camera);
}



void drawText(sf::Text &text,sf::RenderWindow& window,sf::Vector2f position,int size,std::string textString)
{
    text.setCharacterSize(size);
    text.setString(textString);
    text.setPosition(position-sf::Vector2f(text.getGlobalBounds().size.x/2,0));
    
    
    window.draw(text);
}
void Renderer::drawCredits(Game &game)
{
    if(!credits)
    {
        credits=true;
        sf::View camera=window->getView();
        camera.setSize(sf::Vector2f(window->getSize()));
        camera.setCenter(sf::Vector2f{window->getSize().x/2.f,0});
        window->setView(camera);
    }
    sf::Text  text(FM.getFont("Jersey15-Regular"));
    drawText(text,*window,sf::Vector2f{window->getSize().x/2.f,100},100,"Merci d'avoir joué !");

    drawText(text,*window,sf::Vector2f{window->getSize().x/2.f,300},90,"programmer :");
    drawText(text,*window,sf::Vector2f{window->getSize().x/2.f-100,500},70,"Raphaël Croix");

    drawText(text,*window,sf::Vector2f{window->getSize().x/2.f,700},90,"acteurs :");
    drawText(text,*window,sf::Vector2f{window->getSize().x/2.f-100,800},70,"Raphaël Croix, Lucas Hall, Lucie Avrillaud, Léonie Avrillaud");

    drawText(text,*window,sf::Vector2f{window->getSize().x/2.f,1000},90,"réalisateur :");
    drawText(text,*window,sf::Vector2f{window->getSize().x/2.f-100,1200},70,"Baptiste Marie");
    sf::View camera=window->getView();
    camera.setCenter(camera.getCenter()+sf::Vector2f{0,1});
    window->setView(camera);
    if (camera.getCenter().y>1400)
    {
        game.currentState=State::Menu;
        credits=false;
    }
    
}

void Renderer::setAnimationShake(int shakeNumber)
{
    this->animationShake=shakeNumber;
}

sf::View Renderer::shakeCamera(sf::View &camera)
{
    if (this->animationShake>55)
    {
        camera.setCenter(camera.getCenter()+sf::Vector2f{1.4,1.4}*2.f);
    }
    else
    if (this->animationShake>50)
    {
        camera.setCenter(camera.getCenter()+sf::Vector2f{-1,0}*2.f);
    }
    else
    if (this->animationShake>45)
    {
        camera.setCenter(camera.getCenter()+sf::Vector2f{1.4,-1.4}*2.f);
    }
    else
    if (this->animationShake>40)
    {
        camera.setCenter(camera.getCenter()+sf::Vector2f{-1.4,1.4}*2.f);
    }
    else
    if (this->animationShake>35)
    {
        camera.setCenter(camera.getCenter()+sf::Vector2f{0,-1}*2.f);
    }
    else
    if (this->animationShake>30)
    {
        camera.setCenter(camera.getCenter()+sf::Vector2f{0,1}*2.f);
    }
    else
    if (this->animationShake>25)
    {
        camera.setCenter(camera.getCenter()+sf::Vector2f{-2,1}*2.f);
    }
    else
    if (this->animationShake>25)
    {
        camera.setCenter(camera.getCenter()+sf::Vector2f{1,-1}*2.f);
    }
    else
    if (this->animationShake>20)
    {
        camera.setCenter(camera.getCenter()+sf::Vector2f{0,1}*2.f);
    }
    else
    if (this->animationShake>15)
    {
        camera.setCenter(camera.getCenter()+sf::Vector2f{1.4,-1}*2.f);
    }
    else
    if (this->animationShake>10)
    {
        camera.setCenter(camera.getCenter()+sf::Vector2f{0.2,1}*2.f);
    }
    else
    if (this->animationShake>5)
    {
        camera.setCenter(camera.getCenter()+sf::Vector2f{-0.5,-1}*2.f);
    }
    else
    if (this->animationShake>0)
    {
        camera.setCenter(camera.getCenter()+sf::Vector2f{-0.6,1}*2.f);
    }
    return camera;
}

void Renderer::drawJumpscare(Game &game)
{
    sf::View camera=window->getView();
    window->setView(cameraBackup);
    sf::RectangleShape background(sf::Vector2f(window->getSize()));
    background.setPosition(sf::Vector2f{0,0});
    background.setTexture(&TM.getTexture("idle"));
    window->draw(background);
    window->setView(this->shakeCamera(camera));
    sf::RectangleShape jumpscare(sf::Vector2f(window->getSize().x/2,window->getSize().y/2));
    jumpscare.setPosition(sf::Vector2f{500,500});
    jumpscare.setTexture(&TM.getTexture("singe"));
    // if(game.raphael.jumpScare)
    // {
    //     jumpscare.setTexture(&TM.getTexture("Jumpscare-Raphael"));
    // }
    // else
    // if(game.lucas.jumpScare)
    // {
    //     jumpscare.setTexture(&TM.getTexture("Jumpscare-Lucas"));
    // }
    // else
    // if(game.rondoudou.jumpScare)
    // {
    //     jumpscare.setTexture(&TM.getTexture("Jumpscare-Rondoudou"));
    // }
    // else
    // if(game.soeur.jumpScare )
    // {
    //     if(game.soeur.activesister==soeur::Lucie)
    //     {
    //         jumpscare.setTexture(&TM.getTexture("Jumpscare-Lucie"));
    //     }
    //     else
    //     {
    //     jumpscare.setTexture(&TM.getTexture("Jumpscare-Leonie"));
    //     }
    // } 
    window->draw(jumpscare);
    animationShake--;
    if(animationShake==0)
    {
        game.currentState=State::Loose;
    }
}
