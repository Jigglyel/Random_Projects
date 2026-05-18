#include"Foxy.hpp"

Foxy::Foxy(std::string nom):Animatronic(nom)
{
    this->position=3;
}

void Foxy::move(SoundManager & soundManager)
{
    if (*actualState==State::Camera)
    {
       moveClock.restart();
    }
    
    if (this->moveClock.getElapsedTime().asSeconds()>20-lvl)
    {
        if (rand()%21<lvl)
        {
            this->stage++;
            if (stage==4 )
            {
                if (!*leftDoorClose)
                {
                    attack(soundManager);
                }
                else
                    stage=0;
                
                
            }
        }
        this->resetClock();
    }
}

void Foxy::attack(SoundManager &soundManager)
{
    jumpScare=true;
    soundManager.playNoise("JumpScare");
}  
