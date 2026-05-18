#include"Fnaf.hpp"


int main(int argc, char const *argv[])
{
  sf::RenderWindow window(
    sf::VideoMode::getFullscreenModes()[0],
    "Fnaf",
    sf::State::Fullscreen
);
    window.setFramerateLimit(60);
    sf::Vector2u windowSize=window.getSize();
    sf::View camera;
    SoundManager soundManager;
    srand(time(NULL));
    camera.setSize(sf::Vector2f(windowSize.x*2/3,windowSize.y));
    camera.setCenter(sf::Vector2f(windowSize.x/2,windowSize.y/2));
    window.setView(camera);
    Game jeu(window,camera,soundManager);
    Drawer drawer(window);
    bool checkMove,checkReleased,checkPressed;
    while (window.isOpen())
    {
        checkMove=false;
        checkPressed=false;
        checkReleased=false;
        std::vector<Button>currentButtons=jeu.activableButtons[jeu.currentState];
        while (std::optional event=window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::MouseButtonPressed>() and event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
            {
                checkPressed=true;
            }
            if (event->is<sf::Event::MouseButtonReleased>() and event->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left)
            {
                checkReleased=true;
            }
            if (event->is<sf::Event::MouseMoved>())
            {
                
                checkMove=true;
            }
            
        }



        for (Button &bouton :currentButtons)
        {
            sf::Vector2f sourisPos=sf::Vector2f(sf::Mouse::getPosition(window));
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
            animatronic->move(soundManager);
            
        }
        

        drawer.draw(jeu);
        //   for (Button & bouton : currentButtons)
        //       bouton.draw(window);
        

        window.display();
    }





    return 0;
}
