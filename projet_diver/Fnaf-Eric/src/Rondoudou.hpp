#include "Animatronic.hpp"

class Rondoudou : public Animatronic
{
private:
    
public:
    int stage=0;    
    Rondoudou(std::string nom);
    void move(SoundManager & soundManager) override;
    void attack(SoundManager &soundManager) override;
};

