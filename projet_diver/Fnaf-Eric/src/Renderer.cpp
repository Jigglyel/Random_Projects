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
    if (game.currentState==State::Door)
    {
        // drawDoor(animatronics);
    }
    else
    if (game.currentState==State::Behind)
    {
        // drawBehind(animatronics);
    }
}

void Renderer::drawCam(Game &game)
{
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    sf::RectangleShape background;
    background.setPosition(sf::Vector2f{0,0});
    background.setSize(sf::Vector2f(window->getSize()));
    background.setTexture(&manageCamera[game.activeCam](game));
    window->draw(background);
    drawAM(game);
    drawBatterie(game);
    window->setView(camera);

}
void Renderer::drawNightScreen(Game &game)
{
    if (this->animationFrames==0)
    {
        animationFrames=350;
    }
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    sf::Text text(FM.getFont("Jersey15-Regular"),"Night "+std::to_string(game.currentNight),100);
    text.setPosition(sf::Vector2f{window->getSize().x/2-text.getGlobalBounds().size.x/2,window->getSize().y/2-text.getGlobalBounds().size.y/2});
    text.setFillColor(sf::Color((std::clamp(350-animationFrames,0,255)),0,0));
    window->draw(text);
    animationFrames--;
    if (animationFrames==0)
    {
        game.currentState=State::Idle;
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
    window->setView(camera);
}
void Renderer::drawBatterie(Game &game)
{
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    sf::Text text(FM.getFont("Jersey15-Regular"),std::to_string(int(game.batterie))+"%",50);
    text.setCharacterSize(50);
    text.setPosition(sf::Vector2f{150*this->windowRatio.x,900*this->windowRatio.y});
    window->draw(text);
    window->setView(camera);
}

void Renderer::drawIdle(Game &game)
{
    sf::RectangleShape background;
    background.setPosition(sf::Vector2f{0,0});
    background.setSize(sf::Vector2f(window->getSize()));
    background.setTexture(&TM.getTexture("Chambre-PO-R"+std::to_string(static_cast<Rondoudou*>(game.animatronics[3].get())->stage)+"-C0"));
    window->draw(background);
    drawAM(game);
    drawBatterie(game);
    
}

Renderer::Renderer(sf::RenderWindow&window,Game&game)
{
    this->window=&window;
    sf::Vector2u windowSize=window.getSize();
    this->windowRatio=sf::Vector2f(windowSize.x/1920.f,windowSize.y/1080.f);

    this->manageCamera["Grille"]= [this](Game&game) -> sf::Texture& {
        std::string nomTexture="Grille";
        for (std::unique_ptr<Animatronic> &animatronic : game.animatronics)
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
        for (std::unique_ptr<Animatronic> &animatronic : game.animatronics)
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
        for (std::unique_ptr<Animatronic> &animatronic : game.animatronics)
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
        for (std::unique_ptr<Animatronic> &animatronic : game.animatronics)
        {
            if (animatronic->position==3)
            {
                if (animatronic->nom=="Lucie" and rand()%100==0)
                {
                    return TM.getTexture("67-1");
                }
                return TM.getTexture(nomTexture+"-"+animatronic->nom+"-"+std::to_string(static_cast<Walker*>(animatronic.get())->illustration));
            }
            
        }
        return TM.getTexture(nomTexture);
        
    };

    this->manageCamera["Cuisine"]= [this](Game&game) -> sf::Texture& {
        std::string nomTexture="Cuisine";
        for (std::unique_ptr<Animatronic> &animatronic : game.animatronics)
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
        for (std::unique_ptr<Animatronic> &animatronic : game.animatronics)
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
        for (std::unique_ptr<Animatronic> &animatronic : game.animatronics)
        {
            if (animatronic->position==7)
            {
                nomTexture+="-"+animatronic->nom;
            }
            
            if (animatronic->position==8)
            {
                nomTexture+="-Lucas-position2";
            }
            if (animatronic->nom=="Lucas" and (animatronic->position==7 or animatronic->position==8))
            {
                nomTexture+="-"+std::to_string(static_cast<Lucas*>(animatronic.get())->illustration);
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