#pragma once
#include "Walker.hpp"

class Lucas : public Walker
{
private:
    
public:
    Lucas(std::string nom);
    bool* RightDoorClose;
    void attack(SoundManager &soundManager) override;
    void move(SoundManager &soundManager) override;
};



