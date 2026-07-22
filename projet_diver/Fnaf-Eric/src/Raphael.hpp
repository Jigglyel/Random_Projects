#pragma once
#include "Walker.hpp"

class Raphael : public Walker
{
private:
    
public:
    Raphael();
    Walker* Lucas;
    void attack(SoundManager &soundManager) override;
    void move(SoundManager &soundManager) override;
};



