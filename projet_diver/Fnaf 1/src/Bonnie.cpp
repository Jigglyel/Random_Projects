#include"Bonnie.hpp"

Bonnie::Bonnie(std::string nom) : Walker(nom)
{
    lvl=10;
    deplacements[0]={1};
    deplacements[1]={2,4};
    deplacements[2]={1};
    deplacements[4]={1,5,6};
    deplacements[5]={4};
    deplacements[6]={5,100};
}

void Bonnie::attack(SoundManager &soundManager)
{
    jumpScare=true;
    soundManager.playNoise("JumpScare");
}

void Bonnie::move(SoundManager &soundManager)
{
    if (this->moveClock.getElapsedTime().asSeconds()>2.5)
    {
        if (rand()%21<lvl)
        {
            if (position==100)
            {
                if (!*leftDoorClose)
                {
                    attack(soundManager);
                }
                else
                position=1;
                
                
            }
            else
            {
                soundManager.playNoise("footSteps");
                this->choose_room();
            }
        }
        this->resetClock();
    }
    
}