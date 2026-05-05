#include "Animatronic.hpp"

Animatronic::Animatronic(Nom  nom)
{
    this->nom=nom;
    this->lvl=5;
    this->position=0;
}


void Animatronic::choose_room()
{
    std::vector<int>choix=deplacements[position];
    position=choix[rand()%choix.size()];
    
    std::cout<<"déplacement dans la salle "<<position<<std::endl;
}

void Animatronic::move()
{
    if (moveClock.getElapsedTime().asSeconds()>2)
    {
        if (rand()%21<lvl)
        {
            std::cout<<"succès du déplacement"<<std::endl;
            Animatronic::choose_room();
        }
        else
            std::cout<<"echec du déplacement "<<std::endl;
        moveClock.restart();
    }
    
    
    
    
}

void Animatronic::resetClock()
{
    this->moveClock.restart();
}