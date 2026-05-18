#include"Chica.hpp"

Chica::Chica(std::string nom) : Walker(nom)
{
    lvl=15;
    this->deplacements[0]={1};
    this->deplacements[1]={9,7,8};
    this->deplacements[9]={1,10};
    this->deplacements[10]={9,101};
    this->deplacements[7]={1};
    this->deplacements[8]={1};
}

void Chica::attack(SoundManager &soundManager)
{
    jumpScare=true;
    soundManager.playNoise("JumpScare");
}

void Chica::move(SoundManager &soundManager)
{
    if (this->moveClock.getElapsedTime().asSeconds()>2.5)
    {
        if (rand()%21<lvl)
        {
            if (position==101)
            {
                if (!*RightDoorClose)
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