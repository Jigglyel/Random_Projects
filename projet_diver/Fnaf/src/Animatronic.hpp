#pragma once
#include<unordered_map>
#include<vector>
#include<cstdlib>
#include<SFML/Graphics.hpp>
#include<iostream>
enum Nom{
    Raphael,
    Lucie,
    Lucas,
    Leonie,
    Baptiste,
    Rondoudou
};


class Animatronic
{
private:
    
protected:
    sf::Clock moveClock;
    
public:
    Animatronic(std::string nom);
    std::string nom;
    int position;
    int lvl;
    void resetClock();
    
    virtual void move()=0;
};

