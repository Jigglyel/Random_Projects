#include"Lucas.hpp"

Lucas::Lucas(std::string nom) : Walker(nom)
{
    lvl=10;
    this->deplacements[0]={1};
    this->deplacements[1]={3};
    this->deplacements[3]={7};
    this->deplacements[7]={8};
    this->deplacements[8]={0};
}

void Lucas::attack(SoundManager &soundManager)
{
    jumpScare=true;
    soundManager.playNoise("JumpScare");
}

void Lucas::move(SoundManager &soundManager)
{
    if (this->moveClock.getElapsedTime().asSeconds()>2.5)
    {
        if (rand()%21<lvl)
        {
                this->choose_room(); 
        }
        this->resetClock();
    }
    
}