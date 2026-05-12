#pragma once
#include "Game.hpp"

class Freddy : public Walker
{
private:
    /* data */
public:
    int* actualCam;
    State* actualState;
    void move() override;
};


