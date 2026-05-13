#include"Fnaf.hpp"


int main(int argc, char const *argv[])
{
  sf::RenderWindow window(
    sf::VideoMode::getFullscreenModes()[0],
    "Fnaf",
    sf::Style::Fullscreen
);
    window.setFramerateLimit(60);
    sf::Vector2u windowSize=window.getSize();
    sf::View camera;
    camera.setSize(windowSize.x*2/3,windowSize.y);
    camera.setCenter(windowSize.x/2,windowSize.y/2);
    window.setView(camera);
    Game jeu(window,camera);
    Drawer drawer(window);
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
        for (std::unique_ptr<Animatronic> & animatronic : jeu.animatronics)
        {
            animatronic->move();
            
        }
        

        drawer.draw(jeu.currentState,jeu.cameras,jeu.animatronics);
        //  for (Button & bouton : currentButtons)
        //      bouton.draw(window);
        

        window.display();
    }





    return 0;
}
