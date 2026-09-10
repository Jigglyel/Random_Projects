#include "Soeur.hpp"


void Soeur::move(SoundManager & soundmanager)
{
    
    if (this->moveClock.getElapsedTime().asSeconds()>5)
    {
        if (rand()%21<lvl)
        {
            if (position==0)
            {
                activesister=soeur(rand()%2);
                if (activesister==soeur::Lucie)
                {
                    nom="Lucie";
                }
                else
                    nom="Leonie";
            }
            if (position==10)
            {
                if(rand()%2==0)
                {
                    attack(soundmanager);
                }
            }
            else
            {
                position=deplacements[position][0];
                if (position==3 and rand()%100==0)
                {
                    sixSeven=true;
                }
                else
                    sixSeven=false;
                
                if (position==10)
                {
                    if (activesister==soeur::Lucie)
                        soundmanager.playNoise(LucieSounds[rand()%LucieSounds.size()]);
                    else
                        soundmanager.playNoise(LeonieSounds[rand()%LeonieSounds.size()]);
                }
            }
        }
        this->resetClock();
    }
    
    
}

Soeur::Soeur():Walker("Lucie-Leonie") {
    this->deplacements[0]={1};
    this->deplacements[1]={2};
    this->deplacements[2]={3};
    this->deplacements[3]={4,7};
    this->deplacements[4]={5};
    this->deplacements[5]={10};
    this->deplacements[7]={10};
    this->LeonieSounds.emplace_back("Leonie:WhyRDD");
    this->LucieSounds.emplace_back("Lucie:FakeLeonie");
}


void Soeur::attack(SoundManager &soundManager)
{
    jumpScare=true;
    soundManager.playNoise("Leonie-Jumpscare");
}