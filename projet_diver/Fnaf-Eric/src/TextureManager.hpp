#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include<unordered_map>
#include<iostream>
#include<memory>
#include<thread>
class TextureManager
{
    private:
        std::unordered_map<std::string,sf::Texture> Map;
    public:
        TextureManager();
        void loadTextures();
        void setTexture(std::string nomTexture,std::string path);
        sf::Texture& getTexture(std::string nomTexture);
};