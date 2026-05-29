#include "Rondoudou.hpp"

Rondoudou::Rondoudou(std::string nom)
: Animatronic(nom) // ensure base class is initialized (no default constructor)
{
    this->nom = nom;
    this->position = 15;
    this->lvl = 5;
}


void Rondoudou::move(SoundManager & soundManager)
{
    
    if (this->moveClock.getElapsedTime().asSeconds()>20-lvl)
    {
        if (rand()%21<lvl)
        {
            soundManager.playNoise("PUFF");
            if (stage==3 )
                attack(soundManager);
            else
                this->stage++;
        }
        this->resetClock();
    }
}


void Rondoudou::attack(SoundManager &soundManager)
{
    jumpScare=true;
    soundManager.playNoise("PUFF");
}