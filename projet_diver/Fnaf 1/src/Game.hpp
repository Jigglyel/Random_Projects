#pragma once
#include"Button.hpp"
#include"TextureManager.hpp"
#include"FontManager.hpp"
#include"Bonnie.hpp"
#include"Chica.hpp"
#include "Foxy.hpp"
#include "Freddy.hpp"
#include<memory>


class Game
{
private:
    void addButton(State s,Button b);

public:
    Game(sf::RenderWindow&window,sf::View&camera,SoundManager &soundManager);
    int activeCam;
    State currentState=State::Idle;
    sf::Clock nightClock;
    int nightDuration=510;
    bool leftDoorClose=false;
    bool rightDoorClose=false;
    bool leftLightOn=false;
    bool rightLightOn=false;
    float batterie=100;
    std::unordered_map<State,std::vector<Button>> activableButtons;
    std::vector<std::unique_ptr<Animatronic>> animatronics;
};


