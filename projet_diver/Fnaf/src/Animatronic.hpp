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
    void choose_room();
    
    sf::Clock moveClock;
    
public:
    std::string nom;
    int position;
    std::unordered_map<int,std::vector<int>> deplacements;
    int lvl;
    Animatronic(std::string);
    void resetClock();
    
    void move();
};

