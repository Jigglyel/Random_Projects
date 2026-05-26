#include"Drawer.hpp"


void Drawer::draw(Game &game)
{
    
    if (game.currentState==State::Idle)
    {
        drawIdle(game);
    }
    else
    if (game.currentState==State::Camera)
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

void Drawer::drawCam(Game &game)
{
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    sf::RectangleShape background;
    background.setPosition(sf::Vector2f{0,0});
    background.setSize(sf::Vector2f(window->getSize()));
    background.setTexture(getTextureCamera(game));
    window->draw(background);
    drawAM(game);
    drawBatterie(game);
    window->setView(camera);

}
void Drawer::drawAM(Game &game)
{
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    sf::Text text(FM.getFont("Jersey15-Regular"),std::to_string((int(game.nightClock.getElapsedTime().asSeconds())/(game.nightDuration/6)+11)%12+1)+"AM",50);
    text.setCharacterSize(50);
    text.setPosition(sf::Vector2f{1700*this->windowRatio.x,50*this->windowRatio.y});
    window->draw(text);
    window->setView(camera);
}
void Drawer::drawBatterie(Game &game)
{
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    sf::Text text(FM.getFont("Jersey15-Regular"),std::to_string(int(game.batterie))+"%",50);
    text.setCharacterSize(50);
    text.setPosition(sf::Vector2f{150*this->windowRatio.x,900*this->windowRatio.y});
    window->draw(text);
    window->setView(camera);
}
sf::Texture* Drawer::getTextureCamera(Game &game)
{
    std::string textureName="Cam"+std::to_string(game.activeCam);
    if (game.activeCam==3)
    {
                
        return TM.getTexture("Foxy"+std::to_string(static_cast<Foxy*>(game.animatronics[2].get())->stage));
    }
    else
    {
        for (std::unique_ptr<Animatronic> & animatronic : game.animatronics)
        {    
            if (animatronic->position==game.activeCam)
            {
                if (animatronic->nom!="Freddy" or textureName=="Cam"+std::to_string(game.activeCam))
                {
                    textureName+="-"+animatronic->nom;
                }
                
                
            }
            
        }
        return TM.getTexture(textureName); 
    }
}

void Drawer::drawIdle(Game &game)
{
    sf::RectangleShape background;
    background.setPosition(sf::Vector2f{0,0});
    background.setSize(sf::Vector2f(window->getSize()));
    background.setTexture(TM.getTexture("Idle"));
    window->draw(background);
    sf::RectangleShape LeftDoor(sf::Vector2f(270*this->windowRatio.x,window->getSize().y-30*this->windowRatio.y));
    LeftDoor.setPosition(sf::Vector2f{200*this->windowRatio.x,30*this->windowRatio.y});
    sf::Color LeftDoorColor={0,0,0,0};
    if (game.leftDoorClose)
    {
        LeftDoorColor={255,0,0};
        LeftDoorColor.a=255;
    }
    if (game.leftLightOn)
    {
        LeftDoorColor.a=50;
        LeftDoorColor+={90,90,90};
        if (game.animatronics[0]->position==100)
        {
            LeftDoorColor+={0,0,255};
        }
    }
    LeftDoor.setFillColor(LeftDoorColor);
    window->draw(LeftDoor);
    sf::RectangleShape RightDoor(sf::Vector2f(270*this->windowRatio.x,window->getSize().y-30*this->windowRatio.y));
    RightDoor.setPosition(sf::Vector2f{1450*this->windowRatio.x,30*this->windowRatio.y});
    sf::Color RightDoorColor={0,0,0,0};
    if (game.rightDoorClose)    {
        RightDoorColor.a=255;
        RightDoorColor={255,0,0};
    }
    if (game.rightLightOn)
    {
        RightDoorColor.a=50;
        RightDoorColor+={90,90,90};
        if (game.animatronics[1]->position==101)
        {
            RightDoorColor+={100,100,0};
        }
        
    }
    RightDoor.setFillColor(RightDoorColor);
    window->draw(RightDoor);
    drawAM(game);
    drawBatterie(game);
    
}

Drawer::Drawer(sf::RenderWindow&window)
{
    this->window=&window;
    sf::Vector2u windowSize=window.getSize();
    this->windowRatio=sf::Vector2f(windowSize.x/1920.f,windowSize.y/1080.f);
}
void Drawer::drawMenu(Game &game)
{
    window->setView(window->getDefaultView());
    sf::Text text(FM.getFont("Jersey15-Regular"),"You Survived!",100);
    text.setPosition(sf::Vector2f{window->getSize().x/2-text.getGlobalBounds().size.x/2,window->getSize().y/2-text.getGlobalBounds().size.y/2});
    text.setFillColor(sf::Color(rand()%256,rand()%256,rand()%256)*sf::Color(255,255,255));
    window->draw(text);
}
void Drawer::drawLoose(Game &game){
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