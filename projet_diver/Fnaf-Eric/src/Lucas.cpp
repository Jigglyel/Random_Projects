#include"Lucas.hpp"

Lucas::Lucas() : Walker("Lucas")
{
    this->deplacements[0]={1};
    this->deplacements[1]={3};
    this->deplacements[3]={1,7};
    this->deplacements[7]={8};
    this->deplacements[8]={9};
    this->deplacements[9]={10};
}

void Lucas::attack(SoundManager &soundManager)
{
    jumpScare=true;
    soundManager.playNoise("Lucas-Jumpscare",position);
}

void Lucas::move(SoundManager &soundManager)
{
    if (this->moveClock.getElapsedTime().asSeconds()>5)
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
                    if(rand()%2==0)
                    {
                        soundManager.playNoise("Lucas-Skibidi",position);
                    }
                    else
                    {
                        soundManager.playNoise("Lucas-Moaning",position);
                    }
                }
                    this->choose_room(); 

                if(position==10 and Raphael->position==10)
                {
                    this->position=9;    
                }
            }
        }
        this->resetClock();
    }
    
}