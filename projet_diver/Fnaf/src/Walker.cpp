#include "Walker.hpp"


void Walker::choose_room()
{
    std::vector<int>choix=deplacements[position];
    this->position=choix[rand()%choix.size()];
    std::cout<<this->nom<<" déplacement dans la salle "<<this->position<<std::endl;
}


void Walker::move()
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

Walker::Walker(std::string nom): Animatronic(nom) {}