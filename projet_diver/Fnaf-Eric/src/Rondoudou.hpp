#include "Animatronic.hpp"

class Rondoudou : public Animatronic
{
private:
    
public:
    int stage=0;    
    int pourcentage;
    Rondoudou();
    void move(SoundManager & soundManager) override;
    void attack(SoundManager &soundManager) override;
};

