#pragma once
#include"Button.hpp"
#include"TextureManager.hpp"
#include"FontManager.hpp"
#include "Soeur.hpp"
#include "Raphael.hpp"
#include "Lucas.hpp"
#include "Rondoudou.hpp"
#include<windows.h>

class Renderer;
class Game
{
private:
    void addButton(State s,Button b);

public:
    Game(sf::RenderWindow&window,sf::View&camera,SoundManager &soundManager);
    std::string activeCam;
    void startingNight(int nbNight,SoundManager &soundManager);
    State currentState;
    sf::Clock nightClock;
    int nightDuration=100;
    int currentNight=0;
    int waterPourcentage=100; 
    int lightPourcentage=100;
    Renderer* renderer;
    std::unordered_map<State,std::vector<Button>> activableButtons;
    std::vector<Walker*> walkers;
    Rondoudou rondoudou;
    Raphael raphael;
    Lucas lucas;
    Soeur soeur;
    std::vector<std::unique_ptr<Animatronic>> animatronics;
};


