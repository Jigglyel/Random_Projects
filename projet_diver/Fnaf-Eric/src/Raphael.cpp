#include"Raphael.hpp"

Raphael::Raphael(std::string nom) : Walker(nom)
{
    lvl=10;
    deplacements[0]={2};
    deplacements[2]={3};
    deplacements[3]={4};
    deplacements[4]={5};
    deplacements[5]={6};
    deplacements[6]={0};
}

void Raphael::attack(SoundManager &soundManager)
{
    jumpScare=true;
    soundManager.playNoise("JumpScare");
}

void Raphael::move(SoundManager &soundManager)
{
    if (this->moveClock.getElapsedTime().asSeconds()>2.5)
    {
        if (rand()%21<lvl)
        {
                this->choose_room();
        }
        this->resetClock();
    }
    
}