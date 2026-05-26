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
    /* data */
public:
    Soeur(std::string nom);
    soeur activesister;

    void move(SoundManager & soundmanager) override;
    void attack(SoundManager &soundManager) override;
};


