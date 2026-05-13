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
            this->choose_room();
    }
    
    
}
