#include "Soeur.hpp"


void Soeur::move(SoundManager & soundmanager)
{
    if (*this->actualState==State::Camera and *this->actualCam==this->position)
    {
        this->resetClock();
    }
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

Soeur::Soeur(std::string nom):Walker(nom) {}
