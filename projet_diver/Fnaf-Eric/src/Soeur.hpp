#pragma once
#include "Enum.hpp"
#include "Walker.hpp"
enum soeur{
    Lucie,
    Leonie
};
class Soeur : public Walker
{
private:
    std::string* LucieSounds;
    std::string* LeonieSounds;

public:
    Soeur();
    soeur activesister;
    bool sixSeven;
    void move(SoundManager & soundmanager) override;
    void attack(SoundManager &soundManager) override;
};


