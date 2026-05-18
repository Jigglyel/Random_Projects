#pragma once
#include"Button.hpp"
#include"CameraSystem.hpp"
#include"TextureManager.hpp"
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
    State currentState=State::Idle;
    bool leftDoorClose=false;
    bool rightDoorClose=false;
    bool leftLightOn=false;
    bool rightLightOn=false;
    std::unordered_map<State,std::vector<Button>> activableButtons;
    CameraSystem cameras;
    std::vector<std::unique_ptr<Animatronic>> animatronics;
};


