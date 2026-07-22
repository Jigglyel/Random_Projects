#include"Fnaf.hpp"

int main(int argc, char const *argv[])
{
    //creation de la fenêtre
  sf::RenderWindow window(
    sf::VideoMode::getFullscreenModes()[0],"Fnaf", sf::State::Fullscreen);

    window.setFramerateLimit(60);
    sf::Vector2u windowSize=window.getSize();
    //creation de toutes les classes globales
    sf::View camera;
    SoundManager soundManager;
    window.clear(sf::Color::Black);
    window.display();
    srand(time(NULL));
    camera.setSize(sf::Vector2f(windowSize.x*1/3,windowSize.y));
    camera.setCenter(sf::Vector2f(windowSize.x-camera.getSize().x/2,windowSize.y/2));
    window.setView(camera);
    Game jeu(window,camera,soundManager);
    Renderer renderer(window,jeu,soundManager);
    jeu.renderer=&renderer;
    //creation des variables globales
    bool checkMove,checkReleased,checkPressed,drawButton=false;
    int powerUsage=0;
    if(soundManager.music.openFromFile("../audio/music/Menu fnaf eric v1.mp3"))
    {
        soundManager.music.play();
    }
    while (window.isOpen())
    {
        checkMove=false;
        checkPressed=false;
        checkReleased=false;
        sf::Mouse::Button boutonPressed;
        std::vector<Button>*currentButtons=&jeu.activableButtons[jeu.currentState];
        //test des clicks et recupération des inputs
        while (std::optional event=window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                checkPressed=true;
                boutonPressed=event->getIf<sf::Event::MouseButtonPressed>()->button;
                if(drawButton)
                    std::cout<<"souris pressée en "<<sf::Mouse::getPosition(window).x<<" "<<sf::Mouse::getPosition(window).y<<std::endl;
                
            }
            if (event->is<sf::Event::MouseButtonReleased>() and event->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left)
            {
                checkReleased=true;
            }
            if (event->is<sf::Event::KeyPressed>() and event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::B)
            {
                drawButton=!drawButton;
            }
            if (event->is<sf::Event::KeyPressed>() and event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::S)
            {
                if(drawButton)
                    jeu.startingNight(jeu.currentNight+1,soundManager);
            }
            if (event->is<sf::Event::KeyPressed>() and event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::P)
            {
                for(Walker* & animatronic : jeu.walkers)
                {
                    std::cout<<animatronic->nom<<" "<<animatronic->position<<std::endl;
                }
            }
            
            if (event->is<sf::Event::MouseMoved>())
            {
                
                checkMove=true;
            }
            
        }


        //traitement des inputs sur les boutons
        for (Button &bouton :*currentButtons)
        {
            sf::Vector2f sourisPos=sf::Vector2f(sf::Mouse::getPosition(window));
            if(!bouton.Hud)
                sourisPos=window.mapPixelToCoords(sf::Vector2i(sourisPos));
            if(bouton.hitbox.contains(sourisPos))
            {
                if(bouton.getType()==ButtonType::Hover)
                {
                    bouton.activate();
                }
                else
                if (bouton.bouton==boutonPressed or (bouton.bouton==std::nullopt and boutonPressed==sf::Mouse::Button::Left))
                {

                    if(bouton.getType()==ButtonType::Click and checkPressed)
                    {
                        bouton.activate();
                    }
                    else
                    if(bouton.getType()==ButtonType::Hold and checkPressed)
                    {
                        bouton.is_activated=true;
                    }
                }
                if(bouton.getType()==ButtonType::Hold and checkReleased)
                {
                    bouton.is_activated=false;
                }
            }
            else
            if(bouton.getType()!=ButtonType::Click)
                {
                    bouton.is_activated=false;
                }
        }



        //activation des boutons holds
        for (int i = 0; i < currentButtons->size(); i++)
        {
            if (currentButtons->at(i).is_activated)
            {
                currentButtons->at(i).activate();
            }
            
            
        }
        //boucle de jeu
        if (jeu.currentState!=Menu and jeu.currentState!=Loose and jeu.currentState!=StartingNight and jeu.currentState!=Credits)
        {
            if (soundManager.music.getStatus()==sf::SoundSource::Status::Stopped)
            {
                if(soundManager.music.openFromFile("../audio/music/nightMusic.mp3"))
                {
                    soundManager.music.play();
                }
            }
            
            for (std::unique_ptr<Animatronic> & animatronic : jeu.animatronics)
            {
                animatronic->move(soundManager);
                if (animatronic->jumpScare)
                {
                    jeu.currentState=State::Jumpscare;
                }
            }
            
            

            if (jeu.nightClock.getElapsedTime().asSeconds()>jeu.nightDuration)
            {
                jeu.startingNight(jeu.currentNight+1,soundManager);
            }
        }
        
        
        
        
        //dessin
        window.clear(sf::Color::Black);
        renderer.draw(jeu);
        if (drawButton)
            for (Button & bouton : *currentButtons)
                bouton.draw(window);
        

        window.display();
    }





    return 0;
}
