#include "Freddy.hpp"


void Freddy::move(SoundManager &soundManager)
{
    if (*this->actualState==State::CameraState and *this->actualCam==this->position)
    {
        this->resetClock();
    }
    if (this->moveClock.getElapsedTime().asSeconds()>25-lvl)
    {
        if (rand()%21<lvl)
        {
            soundManager.playNoise("freddyLaugh");
            
            position=deplacements[position][0];
            std::cout<<this->nom<<" déplacement dans la salle "<<this->position<<std::endl;
        }
        this->resetClock();
    }
}

Freddy::Freddy(std::string nom):Walker(nom) {
    lvl=15;
    this->deplacements[0]={1};
    this->deplacements[1]={7};
    this->deplacements[7]={9};
    this->deplacements[9]={10};
    this->deplacements[10]={9};
}

void Freddy::attack(SoundManager &soundManager)
{
    jumpScare=true;
    soundManager.playNoise("JumpScare");
}