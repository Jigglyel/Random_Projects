#include"Fnaf.hpp"

int main(int argc, char const *argv[])
{
  sf::RenderWindow window(
    sf::VideoMode::getFullscreenModes()[0],
    "Fnaf",
    sf::Style::Fullscreen
);
    sf::Vector2u windowSize=window.getSize();
    sf::View camera;
    camera.setSize(windowSize.x*2/3,windowSize.y);
    camera.setCenter(windowSize.x/2,windowSize.y/2);
    window.setView(camera);
    
    std::vector<Button> buttons;
    buttons.push_back(Button(ButtonType::Switch,sf::FloatRect(50,630,80,120),[]{},false));
    buttons.push_back(Button(ButtonType::Hover,sf::FloatRect(windowSize.x-150,0,150,windowSize.y),[&camera,&window]{Button::moveCamRight(camera,window);},true));
    buttons.push_back(Button(ButtonType::Hover,sf::FloatRect(0,0,150,windowSize.y),[&camera,&window]{Button::moveCamLeft(camera,window);},true));
    sf::Texture base, light, bonnie,jumpscare,longue;
    base.loadFromFile("../img/BaseOffice.png");
    light.loadFromFile("../img/OfficeLight.png");
    bonnie.loadFromFile("../img/OfficeAnimatronic.png");
    jumpscare.loadFromFile("../img/BonnieJumpscare.png");
    longue.loadFromFile("../img/OfficeBaseLong.jpg");
    sf::RectangleShape fond;
    fond.setSize(sf::Vector2f(window.getSize()));
    bool* lightOn=&buttons[0].is_activated;
    Animatronic Bonnie(Nom::Raphael);
        Bonnie.deplacements[0]={1};
        Bonnie.deplacements[1]={2,3};
        Bonnie.deplacements[2]={1,3};
        Bonnie.deplacements[3]={4,2,1};
        Bonnie.deplacements[4]={5};
        Bonnie.lvl=10;
    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button==sf::Mouse::Left)
            {
                for (int i = 0; i < buttons.size(); i++)
                {
                    sf::Vector2f sourisPos;
                    if (!buttons[i].Hud)
                    {
                        sourisPos=window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x,event.mouseButton.y));
                    }
                    else
                        sourisPos=sf::Vector2f(event.mouseButton.x,event.mouseButton.y);
                    
                    if (buttons[i].hitbox.contains(sourisPos))
                    {
                        if (buttons[i].getType()==ButtonType::Switch)
                        {
                            buttons[i].is_activated=!buttons[i].is_activated;
                        }
                        else
                        if (buttons[i].getType()==ButtonType::Hold)
                        {
                            buttons[i].is_activated=true;
                        }
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased and event.mouseButton.button==sf::Mouse::Left)
            {
                for (int i = 0; i < buttons.size(); i++)
                {
                    if (buttons[i].getType()==ButtonType::Hold)
                        {
                            buttons[i].is_activated=false;
                        }
                }
            }
            if (event.type==sf::Event::MouseMoved)
            {
                
                for (int i = 0; i < buttons.size(); i++)
                {
                    sf::Vector2f sourisPos;
                    if (!buttons[i].Hud)
                    {
                        sourisPos=window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y));
                    }
                    else
                    {
                        sourisPos=sf::Vector2f(event.mouseMove.x,event.mouseMove.y);
                        
                    }


                    if (buttons[i].hitbox.contains(sourisPos))
                    {
                        if (buttons[i].getType()==ButtonType::Hover)
                        {
                            buttons[i].is_activated=true;
                        }
                            
                    }
                    else
                    if (buttons[i].getType()==ButtonType::Hover or buttons[i].getType()==ButtonType::Hold)
                        buttons[i].is_activated=false;
                    
                }
            }
            
        }








        
        window.clear();
        for (int i = 0; i < buttons.size(); i++)
        {
            if (buttons[i].is_activated)
            {
                buttons[i].action();
            }
            
        }
        Bonnie.move();
        if (Bonnie.position==5)
        {
            fond.setTexture(&jumpscare);
        }
        else
        if (*lightOn)
        {
            if (Bonnie.position==4)
            {
                fond.setTexture(&bonnie);
            }
            else
                fond.setTexture(&light);
            
        }
        else
            fond.setTexture(&base);
        
        
        
        
        window.draw(fond);
        sf::RectangleShape box;
        box.setPosition(buttons[0].hitbox.getPosition());
        box.setSize(buttons[0].hitbox.getSize());
        box.setOutlineColor(sf::Color::Red);
        window.draw(box);
        window.display();
    }





    return 0;
}
