#pragma once
#include "Walker.hpp"

class Chica : public Walker
{
private:
    
public:
    Chica(std::string nom);
    bool* RightDoorClose;
    void attack(SoundManager &soundManager) override;
    void move(SoundManager &soundManager) override;
};



