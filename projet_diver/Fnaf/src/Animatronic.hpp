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
    Nom nom;
    int position;
    std::unordered_map<int,std::vector<int>> deplacements;
    int lvl;
    Animatronic(Nom nom);
    void resetClock();
    
    void move();
};

