#pragma once
#include<SFML/Audio.hpp>
#include<iostream>
#include<string>
#include<unordered_map>
class SoundManager
{
    private:
        std::unordered_map<std::string,sf::SoundBuffer> Map;
        
    public:
        SoundManager();
        std::vector<sf::Sound> sons;
        void setSound(std::string soundName,sf::SoundBuffer &T);
        sf::SoundBuffer* getSoundBuffer(std::string soundName);
        void playNoise(std::string noiseName);
};
