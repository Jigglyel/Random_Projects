#pragma once
#include<unordered_map>
#include<vector>
#include<cstdlib>
#include<SFML/Graphics.hpp>
#include<iostream>
#include"SoundManager.hpp"



class Animatronic
{
private:
    
protected:
    sf::Clock moveClock;
    
public:

    bool jumpScare=false;
    Animatronic(std::string nom);
    std::string nom;
    int lvl;
    void resetClock();
    ~Animatronic() = default;
    virtual void move(SoundManager &soundManager)=0;
    virtual void attack(SoundManager &soundManager)=0;
    int position;
};

