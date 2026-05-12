#include "Animatronic.hpp"

Animatronic::Animatronic(std::string  nom)
{
    this->nom=nom;
    this->lvl=5;
    this->position=0;
}

void Animatronic::resetClock()
{
    this->moveClock.restart();
}