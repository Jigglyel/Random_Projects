#pragma once
#include"Button.hpp"
#include"CameraSystem.hpp"
#include"TextureManager.hpp"
#include "Foxy.hpp"
#include "Freddy.hpp"
#include<memory>


class Game
{
private:
    void addButton(State s,Button b);

public:
    Game(sf::RenderWindow&window,sf::View&camera);
    State currentState=State::Idle;
    std::unordered_map<State,std::vector<Button>> activableButtons;
    CameraSystem cameras;
    std::vector<std::unique_ptr<Animatronic>> animatronics;
};


