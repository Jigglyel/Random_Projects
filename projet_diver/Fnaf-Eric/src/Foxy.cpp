#include"Foxy.hpp"

Foxy::Foxy(std::string nom):Animatronic(nom)
{
    this->position=3;
    this->lvl=10;
}

void Foxy::move(SoundManager & soundManager)
{
    if (stage!=3 and *actualState==State::Camera)
    {
       moveClock.restart();
    }
    
    if (this->moveClock.getElapsedTime().asSeconds()>20-lvl)
    {
        if (rand()%21<lvl)
        {
            
            if (stage==3 )
            {
                if (!*leftDoorClose)
                {
                    attack(soundManager);
                }
                else
                    stage=0;
                
                
            }
            else
                this->stage++;
        }
        this->resetClock();
    }
}

void Foxy::attack(SoundManager &soundManager)
{
    jumpScare=true;
    soundManager.playNoise("JumpScare");
}  
