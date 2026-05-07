#pragma once
#include"Animatronic.hpp"
#include"Button.hpp"
#include"CameraSystem.hpp"
#include"TextureManager.hpp"

enum State{
    Camera,
    Idle,
    Behind,
    Door
};
class Game
{
private:
    /* data */
public:
    Game(sf::RenderWindow&window,sf::View&camera);
    State currentState=Idle;
    std::unordered_map<State,std::vector<Button>> activableButtons;
    CameraSystem cameras;
    std::vector<Animatronic> animatronics;
    void addButton(State s,Button b);
};


