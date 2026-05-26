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
    sf::SoundBuffer T;
    if(!T.loadFromFile("../audio/Footsteps.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son Footsteps.mp3"<<std::endl;
    }
    else
    {
        setSound("footSteps",T);
    }
    if(!T.loadFromFile("../audio/fnaf-freddys-laugh.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son fnaf-freddys-laugh.mp3"<<std::endl;
    }
    else
    {
        setSound("freddyLaugh",T);
    }
    if(!T.loadFromFile("../audio/CameraOpen.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son CameraOpen.mp3"<<std::endl;
    }
    else
    {
        setSound("cameraOpen",T);
    }
    if(!T.loadFromFile("../audio/Fnaf1JumpScare.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son Fnaf1JumpScare.mp3"<<std::endl;
    }
    else
    {
        setSound("JumpScare",T);
    }
    if(!T.loadFromFile("../audio/Door.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son Door.mp3"<<std::endl;
    }
    else
    {
        setSound("Door",T);
    }
    if(!T.loadFromFile("../audio/fnaf-light-sound.mp3"))
    {
        std::cerr<<"Erreur lors du chargement du son fnaf-light-sound.mp3"<<std::endl;
    }
    else
    {
        setSound("light",T);
    }
}   

void SoundManager::playNoise(std::string noiseName)
{
    sf::Sound son(Map[noiseName]);
    sons.push_back(son);
    sons.back().play();
}