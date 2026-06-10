#include "SoundManager.hpp"

void SoundManager::setSound(std::string soundName,sf::SoundBuffer &T)
{
    Map[soundName]=T; 
}

sf::SoundBuffer* SoundManager::getSoundBuffer(std::string soundName)
{
    return &Map[soundName];
}
SoundManager::SoundManager()
{

    sf::Vector3f gauche={-2,-1,-3};
    sf::Vector3f droite={2,-1,-3};
    this->posToVector[0]=gauche*5.f;
    this->posToVector[1]=gauche*5.f;
    this->posToVector[2]=droite*5.f;
    this->posToVector[3]={0,-5,-8};
    this->posToVector[4]=droite*4.f;
    this->posToVector[5]=droite*3.f;
    this->posToVector[6]=droite*2.5f;
    this->posToVector[7]=gauche*4.f;
    this->posToVector[8]=gauche*3.f;
    this->posToVector[9]=gauche*2.5f;
    sf::SoundBuffer T;
    if(!T.loadFromFile("../audio/sound/Footsteps.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son Footsteps.mp3"<<std::endl;
    }
    else
    {
        setSound("footSteps",T);
    }
    if(!T.loadFromFile("../audio/sound/fnaf-freddys-laugh.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son fnaf-freddys-laugh.mp3"<<std::endl;
    }
    else
    {
        setSound("freddyLaugh",T);
    }
    if(!T.loadFromFile("../audio/sound/CameraOpen.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son CameraOpen.mp3"<<std::endl;
    }
    else
    {
        setSound("cameraOpen",T);
    }
    if(!T.loadFromFile("../audio/sound/Fnaf1JumpScare.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son Fnaf1JumpScare.mp3"<<std::endl;
    }
    else
    {
        setSound("JumpScare",T);
    }
    if(!T.loadFromFile("../audio/sound/Door.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son Door.mp3"<<std::endl;
    }
    else
    {
        setSound("Door",T);
    }
    if(!T.loadFromFile("../audio/sound/Flash.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son Flash.mp3"<<std::endl;
    }
    else
    {
        setSound("Flash",T);
    }
    if(!T.loadFromFile("../audio/sound/PUFF.mpeg"))
    {
        std::cerr<<"Erreur lors du chargement du son PUFF.mpeg"<<std::endl;
    }
    else
    {
        setSound("PUFF",T);
    }
    if(!T.loadFromFile("../audio/sound/Lucas/Lucas_Skibidi.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son LucasSkibidi.mp3"<<std::endl;
    }
    else
    {
        setSound("LucasSkibidi",T);
    }
    if(!T.loadFromFile("../audio/Lucie/ThungThungThung.ogg"))
    {
        std::cerr<<"Erreur lors du chargement du son LucasSkibidi.mp3"<<std::endl;
    }
    else
    {
        setSound("LucieThung",T);
    }
    if(!T.loadFromFile("../audio/sound/waterFilling.wav"))
    {
        std::cerr<<"Erreur lors du chargement du son waterFilling.wav"<<std::endl;
    }
    else
    {
        setSound("waterFilling",T);
    }
    if(!T.loadFromFile("../audio/sound/waterFilled.wav"))
    {
        std::cerr<<"Erreur lors du chargement du son waterFilled.wav"<<std::endl;
    }
    else
    {
        setSound("waterFilled",T);
    }
    if(!T.loadFromFile("../audio/sound/Rondoudou/hit1.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son hit1.mp3"<<std::endl;
    }
    else
    {
        setSound("RondoudouHit1",T);
    }
    if(!T.loadFromFile("../audio/sound/Rondoudou/hit2.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son hit2.mp3"<<std::endl;
    }
    else
    {
        setSound("RondoudouHit2",T);
    }
    if(!T.loadFromFile("../audio/sound/Rondoudou/hit3.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son hit3.mp3"<<std::endl;
    }
    else
    {
        setSound("RondoudouHit3",T);
    }
    if(!T.loadFromFile("../audio/sound/Rondoudou/Death.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son Death.mp3"<<std::endl;
    }
    else
    {
        setSound("RondoudouDeath",T);
    }
    
}   

void SoundManager::playNoise(std::string noiseName,int pos)
{
    sf::Sound son(Map[noiseName]);
    son.setRelativeToListener(true);
    son.setPosition(this->posToVector[pos]);
    sons.push_back(son);
    sons.back().play();
}

void SoundManager::playNoise(std::string noiseName)
{
    sf::Sound son(Map[noiseName]);
    son.setRelativeToListener(false);
    sons.push_back(son);
    sons.back().play();
}