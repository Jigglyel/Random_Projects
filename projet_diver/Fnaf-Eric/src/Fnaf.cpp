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
    window.clear(sf::Color::Black);
    window.display();
    srand(time(NULL));
    camera.setSize(sf::Vector2f(windowSize.x*3/4,windowSize.y));
    camera.setCenter(sf::Vector2f(windowSize.x/2,windowSize.y/2));
    window.setView(camera);
    Game jeu(window,camera,soundManager);
    Renderer renderer(window,jeu);
    bool checkMove,checkReleased,checkPressed;
    int powerUsage=0;
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




        
        for (int i = 0; i < currentButtons.size(); i++)
        {
            if (currentButtons[i].is_activated)
            {
                currentButtons[i].action();
            }
            
            
        }
        if (jeu.currentState!=Menu and jeu.currentState!=Loose)
        {

            if (jeu.batterie<0)
            {
                jeu.leftDoorClose=false;
                jeu.leftLightOn=false;
                jeu.rightDoorClose=false;
                jeu.rightLightOn=false;
            }
            for (std::unique_ptr<Animatronic> & animatronic : jeu.animatronics)
            {
                animatronic->move(soundManager);
                if (animatronic->jumpScare)
                {
                    jeu.currentState=State::Loose;
                }
            }
            
            
            powerUsage=jeu.leftLightOn+jeu.rightLightOn+jeu.leftDoorClose+jeu.rightDoorClose+(jeu.currentState==State::CameraState)+(jeu.batterie>0);
            jeu.batterie-=(powerUsage)*0.002;

            if (jeu.nightClock.getElapsedTime().asSeconds()>jeu.nightDuration)
            {
                jeu.currentState=State::Menu;
            }
        }
        
        
        
        
        
        window.clear(sf::Color::Black);
        renderer.draw(jeu);
            for (Button & bouton : currentButtons)
                bouton.draw(window);
        

        window.display();
    }





    return 0;
}
