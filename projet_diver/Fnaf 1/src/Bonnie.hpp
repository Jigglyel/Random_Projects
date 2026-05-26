#pragma once
#include "Walker.hpp"

class Bonnie : public Walker
{
private:
    
public:
    Bonnie(std::string nom);
    bool* leftDoorClose;
    void attack(SoundManager &soundManager) override;
    void move(SoundManager &soundManager) override;
};



