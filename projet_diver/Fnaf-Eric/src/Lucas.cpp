#include"Lucas.hpp"

Lucas::Lucas() : Walker("Lucas")
{
    this->deplacements[0]={1};
    this->deplacements[1]={3};
    this->deplacements[3]={8};
    this->deplacements[8]={9};
    this->deplacements[9]={10};
}

void Lucas::attack(SoundManager &soundManager)
{
    jumpScare=true;
    soundManager.playNoise("JumpScare",position);
}

void Lucas::move(SoundManager &soundManager)
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
            {
                if(rand()%10==0)
                {
                    soundManager.playNoise("LucasSkibidi",position);
                }
                    this->choose_room(); 

                if(position==10 and Raphael->position==10)
                {
                    this->position=6;    
                }
            }
        }
        this->resetClock();
    }
    
}