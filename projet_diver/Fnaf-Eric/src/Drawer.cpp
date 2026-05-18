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
    window->setView(camera);

}

sf::Texture* Drawer::getTextureCamera(Game &game)
{
    std::string textureName="Cam"+std::to_string(game.cameras.activeCam);
    if (game.cameras.activeCam==3)
    {
                
        return TM.getTexture("Foxy"+std::to_string(static_cast<Foxy*>(game.animatronics[2].get())->stage));
    }
    else
    {
        for (std::unique_ptr<Animatronic> & animatronic : game.animatronics)
        {    
            if (animatronic->position==game.cameras.activeCam)
            {
                if (animatronic->nom!="Freddy" or textureName=="Cam"+std::to_string(game.cameras.activeCam))
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
    sf::RectangleShape LeftDoor(sf::Vector2f(270,window->getSize().y-30));
    LeftDoor.setPosition(sf::Vector2f{200,30});
    sf::Color LeftDoorColor={0,0,0,0};
    if (game.leftDoorClose)
    {
        LeftDoorColor={255,0,0};
        LeftDoorColor.a=255;
    }
    if (game.leftLightOn)
    {
        LeftDoorColor.a=50;
        LeftDoorColor+={100,100,100};
        if (game.animatronics[0]->position==100)
        {
            LeftDoorColor+={0,0,255};
        }
    }
    LeftDoor.setFillColor(LeftDoorColor);
    window->draw(LeftDoor);
    sf::RectangleShape RightDoor(sf::Vector2f(270,window->getSize().y-30));
    RightDoor.setPosition(sf::Vector2f{1450,30});
    sf::Color RightDoorColor={0,0,0,0};
    if (game.rightDoorClose)    {
        RightDoorColor.a=255;
        RightDoorColor={255,0,0};
    }
    if (game.rightLightOn)
    {
        RightDoorColor.a=50;
        RightDoorColor+={100,100,100};
        if (game.animatronics[1]->position==101)
        {
            RightDoorColor+={150,150,0};
        }
        
    }
    RightDoor.setFillColor(RightDoorColor);
    window->draw(RightDoor);
}

Drawer::Drawer(sf::RenderWindow&window)
{
    this->window=&window;
}
