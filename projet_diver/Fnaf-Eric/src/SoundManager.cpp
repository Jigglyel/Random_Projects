#include "SoundManager.hpp"

void SoundManager::setSound(std::string soundName,std::string path)
{
    sf::SoundBuffer T;
    if(T.loadFromFile(path))
    {
        loadingMade++;
        std::cout<<"["<<loadingMade*100/66<<"%"<<"] Sound "<<soundName<<" loaded successfully"<<std::endl;
        Map[soundName]=std::move(T); 
    }
}
sf::SoundBuffer* SoundManager::getSoundBuffer(std::string soundName)
{
    return &Map[soundName];
}

void SoundManager::openMusic(std::string musicName)
{
    if(!music.openFromFile(musicName))
        std::cout<<"erreur de chargement de "+musicName<<std::endl;

}

SoundManager::SoundManager()
{

    this->controledSound.pause();
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
    setSound("footSteps", "../audio/sound/Footsteps.mp3");
    setSound("freddyLaugh", "../audio/sound/fnaf-freddys-laugh.mp3");
    setSound("cameraOpen","../audio/sound/CameraOpen.mp3");
    setSound("Door","../audio/sound/Door.mp3");
    setSound("Flash","../audio/sound/Flash/Flash.mp3");
    setSound("PUFF","../audio/sound/PUFF.mpeg");
    setSound("LucasSkibidi", "../audio/sound/Lucas/Lucas_Skibidi.mp3");
    setSound("waterFilling", "../audio/sound/waterFilling.wav");
    setSound("waterFilled", "../audio/sound/waterFilled.wav");
    setSound("LightFilled", "../audio/sound/Flash/LightFilled.wav");
    setSound("RondoudouHit1", "../audio/sound/Rondoudou/hit1.mp3");
    setSound("RondoudouHit2", "../audio/sound/Rondoudou/hit2.mp3");
    setSound("RondoudouHit3", "../audio/sound/Rondoudou/hit3.mp3");
    setSound("RondoudouDeath", "../audio/sound/Rondoudou/Death.mp3");
    setSound("Monkey", "../audio/sound/watch.mp3");
    setSound("RddSing", "../audio/sound/rddSing.mp3");
    setSound("Raphael-Jumpscare", "../audio/sound/Raphael/Jumpscare.wav");
    setSound("Leonie-Jumpscare", "../audio/sound/Léonie/LeonieJumpscare.wav");
    setSound("Lucie-Jumpscare", "../audio/sound/Lucie/LucieJumpscare.wav");
    setSound("Lucas-Jumpscare", "../audio/sound/Lucas/LucasJumpscare.wav");
    setSound("Rondoudou-Jumpscare", "../audio/sound/Rondoudou/Jumpscare.wav");
    setSound("Lucie:FakeLeonie", "../audio/sound/Lucie/FakeLéonie.wav");
    setSound("Leonie:WhyRDD", "../audio/sound/Léonie/WhyRDD.wav");
    setSound("Water", "../audio/sound/Water.mp3");
    setSound("Leonie:Peur", "../audio/sound/Léonie/peur.wav");
    setSound("Leonie:Massages", "../audio/sound/Léonie/massages.wav");
    setSound("Leonie:TicTac", "../audio/sound/Léonie/TicTac.wav");
    setSound("Leonie:Repos", "../audio/sound/Léonie/Tu_dev_rep.wav");
    setSound("Leonie:La?", "../audio/sound/Léonie/Tu_es_la.wav");
    setSound("Leonie:Detestes", "../audio/sound/Léonie/deteste.wav");
    setSound("Lucie:OpenDoor1", "../audio/sound/Lucie/Ouvre la porte.wav");
    setSound("Lucie:OpenDoor2", "../audio/sound/Lucie/OuvreLaporte2.wav");
    setSound("Lucie:singe", "../audio/sound/Lucie/singe.wav");
    setSound("Lucie:123", "../audio/sound/Lucie/123.wav");
    setSound("Lucie:OuvreMoi", "../audio/sound/Lucie/OuvreMoi.wav");
    setSound("NightBell", "../audio/sound/6AMbell.wav");
    setSound("Lucas-Moaning", "../audio/sound/Lucas/moaning.wav");
    
}   

void SoundManager::playNoise(std::string noiseName,int pos)
{
    deleteOldSounds();
    sf::Sound son(Map[noiseName]);
    son.setRelativeToListener(true);
    son.setPosition(this->posToVector[pos]);
    sons.emplace_back(son);
    sons.back().play();
    
}

void SoundManager::playNoise(std::string noiseName,sf::Vector3f pos)
{
    deleteOldSounds();
    sf::Sound son(Map[noiseName]);
    son.setRelativeToListener(true);
    son.setPosition(pos);
    sons.emplace_back(son);
    sons.back().play();
    
}

void SoundManager::playNoise(std::string noiseName)
{
    deleteOldSounds();
    sf::Sound son(Map[noiseName]);
    son.setRelativeToListener(false);
    sons.emplace_back(son);
    sons.back().play();
    
}

void SoundManager::deleteOldSounds()
{
    sons.erase(std::remove_if(sons.begin(),sons.end(),[](sf::Sound &son){
        return son.getStatus()==sf::Sound::Status::Stopped;
    }),sons.end());
}