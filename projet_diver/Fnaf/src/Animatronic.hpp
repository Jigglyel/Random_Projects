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
    int lvl;
    void resetClock();
    ~Animatronic() = default;
    virtual void move()=0;
    int position;
};

