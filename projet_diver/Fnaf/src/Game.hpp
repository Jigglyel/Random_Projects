#pragma once
#include"Animatronic.hpp"
#include"Button.hpp"
#include"CameraSystem.hpp"
#include"TextureManager.hpp"
#include"Walker.hpp"
#include<memory>

enum State{
    Camera,
    Idle,
    Behind,
    Door
};
class Game
{
private:
    void addButton(State s,Button b);

public:
    Game(sf::RenderWindow&window,sf::View&camera);
    State currentState=Idle;
    std::unordered_map<State,std::vector<Button>> activableButtons;
    CameraSystem cameras;
    std::vector<std::unique_ptr<Animatronic>> animatronics;
};


