#include "Walker.hpp"


void Walker::choose_room()
{
    std::vector<int>choix=deplacements[position];
    this->position=choix[rand()%choix.size()];
    this->illustration=rand()%2+1;
    std::cout<<this->nom<<" déplacement dans la salle "<<this->position<<std::endl;
}

Walker::Walker(std::string nom): Animatronic(nom) {}