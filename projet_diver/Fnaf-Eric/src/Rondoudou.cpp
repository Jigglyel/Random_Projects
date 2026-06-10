#include "Rondoudou.hpp"


Rondoudou::Rondoudou() : Animatronic("Rondoudou")
{
    this->nom = "Rondoudou";
    this->pourcentage=0;
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