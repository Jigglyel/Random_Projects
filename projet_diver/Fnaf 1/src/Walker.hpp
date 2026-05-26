#pragma once
#include "Animatronic.hpp"
class Walker : public Animatronic
{
private:

protected:
    void choose_room();

public:
    std::unordered_map<int,std::vector<int>> deplacements;
    Walker(std::string);
    
    
};

