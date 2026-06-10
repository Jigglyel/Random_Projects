#pragma once
#include "Walker.hpp"

class Lucas : public Walker
{
private:
    
public:
    Lucas();
    bool* RightDoorClose;
    void attack(SoundManager &soundManager) override;
    void move(SoundManager &soundManager) override;
};



