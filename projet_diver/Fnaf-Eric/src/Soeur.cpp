#include "Soeur.hpp"


void Soeur::move(SoundManager & soundmanager)
{
    
    if (this->moveClock.getElapsedTime().asSeconds()>25-lvl)
    {
        if (rand()%21<lvl)
        {
            if (position==0)
            {
                activesister=soeur(rand()%2);
                if (activesister==soeur::Lucie)
                {
                    nom="Lucie";
                }
                else
                    nom="Leonie";
            }
            
            position=deplacements[position][0];
            std::cout<<this->nom<<" déplacement dans la salle "<<this->position<<std::endl;
        }
        this->resetClock();
    }
    
    
}

Soeur::Soeur(std::string nom):Walker(nom) {this->nom="Lucie-Leonie";lvl=10;
    this->deplacements[0]={1};
    this->deplacements[1]={2};
    this->deplacements[2]={3};
    this->deplacements[3]={4};
    this->deplacements[4]={5};
    this->deplacements[5]={6};
    this->deplacements[6]={7};
    this->deplacements[7]={0};
}


void Soeur::attack(SoundManager &soundManager)
{
    jumpScare=true;
    soundManager.playNoise("JumpScare");
}