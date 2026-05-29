#include "Animatronic.hpp"

Animatronic::Animatronic(std::string  nom)
{
    this->nom=nom;
}

void Animatronic::resetClock()
{
    this->moveClock.restart();
}