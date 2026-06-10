#include"Raphael.hpp"

Raphael::Raphael() : Walker("Raphael")
{
    deplacements[0]={2};
    deplacements[2]={3};
    deplacements[3]={4};
    deplacements[4]={5};
    deplacements[5]={6};
    deplacements[6]={10};
}

void Raphael::attack(SoundManager &soundManager)
{
    jumpScare=true;
    soundManager.playNoise("JumpScare",position);
}

void Raphael::move(SoundManager &soundManager)
{
    if (this->moveClock.getElapsedTime().asSeconds()>2.5)
    {
        if (rand()%21<lvl)
        {
            if(position==10)
            {
                attack(soundManager);
            }
            else
                this->choose_room();
        }
        this->resetClock();
    }
    
}