#include "Freddy.hpp"


void Freddy::move()
{
    if (*this->actualState==State::Camera and *this->actualCam==this->position)
    {
        this->resetClock();
    }
    if (this->moveClock.getElapsedTime().asSeconds()>25-lvl)
    {
        if (rand()%21<lvl)
        {
            position=deplacements[position][0];
            std::cout<<this->nom<<" déplacement dans la salle "<<this->position<<std::endl;
        }
        this->resetClock();
    }
    
    
    
}

Freddy::Freddy(std::string nom):Walker(nom) {}
