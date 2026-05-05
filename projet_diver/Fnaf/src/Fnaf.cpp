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
    
    Game jeu;
    TextureManager textureManager;
    sf::Texture base, light, bonnie,jumpscare,longue,monitor;
    longue.loadFromFile("../img/OfficeBaseLong.jpg");
    TextureManager.setTexture("Idle",longue);
    monitor.loadFromFile("../img/monitor.webp");
    TextureManager.setTexture("monitor",monitor);
    jeu.addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(0,windowSize.y-100,windowSize.x,100) ,[&jeu](){jeu.currentState=State::Camera;
    std::cout<<"je switch en state camera"<<std::endl;},true));
    jeu.addButton(State::Camera,Button(ButtonType::Switch, sf::FloatRect(0,0,100,100) ,[&jeu](){jeu.currentState=State::Idle;
    std::cout<<"je switch en state Idle"<<std::endl;},true));
    jeu.addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(0,0,100,windowSize.y) ,[&window,&camera](){Button::moveCamLeft(camera,window);},true));
    jeu.addButton(State::Idle,Button(ButtonType::Hover, sf::FloatRect(windowSize.x-100,0,100,windowSize.y) ,[&window,&camera](){Button::moveCamRight(camera,window);},true));
    jeu.addButton(State::Idle,Button(ButtonType::Switch,sf::FloatRect(90,550,80,105),[]{std::cout<<"lightActivated"<<std::endl;},false));
    
    sf::RectangleShape fond;
    fond.setSize(sf::Vector2f(window.getSize()));
    fond.setTexture(&longue);
    Animatronic Bonnie(Nom::Raphael);
        Bonnie.deplacements[0]={1};
        Bonnie.deplacements[1]={2,3};
        Bonnie.deplacements[2]={1,3};
        Bonnie.deplacements[3]={4,2,1};
        Bonnie.deplacements[4]={5};
        Bonnie.lvl=10;


    bool checkMove,checkReleased,checkPressed;
    while (window.isOpen())
    {
        checkMove=false;
        checkPressed=false;
        checkReleased=false;
        sf::Event event;
        std::vector<Button>currentButtons=jeu.activableButtons[jeu.currentState];
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button==sf::Mouse::Left)
            {
                checkPressed=true;
            }
            if (event.type == sf::Event::MouseButtonReleased and event.mouseButton.button==sf::Mouse::Left)
            {
                checkReleased=true;
            }
            if (event.type==sf::Event::MouseMoved)
            {
                
                checkMove=true;
            }
            
        }



        for (Button &bouton :currentButtons)
        {
            sf::Vector2f sourisPos=sf::Vector2f(sf::Mouse::getPosition());
            if(!bouton.Hud)
                sourisPos=window.mapPixelToCoords(sf::Vector2i(sourisPos));
            if(bouton.hitbox.contains(sourisPos))
            {
                if(bouton.getType()==ButtonType::Hover)
                {
                    bouton.is_activated=true;
                }
                else
                if(bouton.getType()==ButtonType::Switch and checkPressed)
                {
                    bouton.is_activated=!bouton.is_activated;
                }
                else
                if(bouton.getType()==ButtonType::Hold and checkPressed)
                {
                    bouton.is_activated=true;
                }
                else
                if(bouton.getType()==ButtonType::Hold and checkReleased)
                {
                    bouton.is_activated=false;
                }
            }
            else
            if(bouton.getType()!=ButtonType::Switch)
                {
                    bouton.is_activated=false;
                }
        }




        
        window.clear(sf::Color::Black);
        for (int i = 0; i < currentButtons.size(); i++)
        {
            
            if (currentButtons[i].is_activated)
            {
                currentButtons[i].action();
            }
            
            
        }

        window.draw(fond);
        for (Button & bouton : currentButtons)
            bouton.draw(window);

        window.display();
    }





    return 0;
}
