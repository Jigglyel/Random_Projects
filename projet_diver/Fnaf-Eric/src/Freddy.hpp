#pragma once
#include "Enum.hpp"
#include "Walker.hpp"

class Freddy : public Walker
{
private:
    /* data */
public:
    Freddy(std::string nom);
    int* actualCam;
    State* actualState;
    bool* RightDoorClose;
    void move(SoundManager &soundManager) override;
    void attack(SoundManager &soundManager) override;
};


