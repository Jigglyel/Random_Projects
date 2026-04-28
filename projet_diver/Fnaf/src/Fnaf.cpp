#include"Fnaf.hpp"

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(800,600),"Fnaf");
    std::unordered_map<std::string,std::vector<Button>> activableButtons;
    std::vector<Button> buttons;
    buttons.push_back(Button(ButtonType::Switch,sf::FloatRect(0,0,100,100),[&window]{Button::porte_gauche(window);}));
    buttons.push_back(Button(ButtonType::Hover,sf::FloatRect(700,0,100,100),[&window]{Button::porte_droite(window);}));
    buttons.push_back(Button(ButtonType::Hold,sf::FloatRect(200,300,100,100),[&window]{Button::porte_droite(window);}));
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
                    
                    
                    if (buttons[i].hitbox.contains(event.mouseButton.x,event.mouseButton.y))
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
                if (buttons[i].getType()==ButtonType::Hover)
                {
                    if (buttons[i].hitbox.contains(event.mouseMove.x,event.mouseMove.y))
                    {
                        buttons[i].is_activated=true;
                    }
                    else
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
        
        for (Button & bouton : buttons)
        {
            sf::RectangleShape box(sf::Vector2f(bouton.hitbox.width,bouton.hitbox.height));
            box.setPosition(bouton.hitbox.getPosition());
            box.setFillColor(sf::Color::Green);
            window.draw(box);
        }
        
        
        window.display();
    }





    return 0;
}
