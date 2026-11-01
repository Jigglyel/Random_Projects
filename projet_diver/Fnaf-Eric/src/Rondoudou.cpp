#include "Rondoudou.hpp"


Rondoudou::Rondoudou() : Animatronic("Rondoudou")
{
    this->nom = "Rondoudou";
    this->pourcentage=0;
}


void Rondoudou::move(SoundManager & soundManager)
{
    
    if (this->moveClock.getElapsedTime().asSeconds()>7- lvl*0.2)
    {
        if (rand()%21<lvl)
        {
            if (stage==3 )
                attack(soundManager);
            else
            {
                this->stage++;
                if(rand()%5==0)
                {
                    soundManager.playNoise("PUFF");
                }
            }

        }
        this->resetClock();
    }
}


void Rondoudou::attack(SoundManager &soundManager)
{
    jumpScare=true;
    soundManager.playNoise("Rondoudou-Jumpscare");
}