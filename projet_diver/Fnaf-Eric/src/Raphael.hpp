#pragma once
#include "Walker.hpp"

class Raphael : public Walker
{
private:
    
public:
    Raphael();
    bool* leftDoorClose;
    void attack(SoundManager &soundManager) override;
    void move(SoundManager &soundManager) override;
};



