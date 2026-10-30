#pragma once
#include<SFML/Audio.hpp>
#include<iostream>
#include<string>
#include<unordered_map>
#include<algorithm>
class SoundManager
{
    private:
        std::unordered_map<std::string,sf::SoundBuffer> Map;
        
    public:
        SoundManager();
        std::vector<sf::Sound> sons;
        sf::Music music;
        sf::Music controledSound;
        std::unordered_map<int,sf::Vector3f> posToVector;
        void setSound(std::string soundName,std::string path);
        void openMusic(std::string musicName);
        sf::SoundBuffer* getSoundBuffer(std::string soundName);
        void playNoise(std::string noiseName,int pos);
        void playNoise(std::string noiseName);
        void playNoise(std::string noiseName,sf::Vector3f pos);
        void deleteOldSounds();
        int loadingMade=0;
};
