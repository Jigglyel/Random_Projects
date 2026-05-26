#pragma once
#include "Enum.hpp"
#include "Animatronic.hpp"
class Foxy : public Animatronic
{
private:
    /* data */
public:
    Foxy(std::string nom);
    State* actualState;
    bool* leftDoorClose;
    int stage=0;
    void move(SoundManager & soundManager) override;
    void attack(SoundManager &soundManager) override;
};


 