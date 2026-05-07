#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include<unordered_map>

class TextureManager
{
    private:
        std::unordered_map<std::string,sf::Texture> Map;
    public:
        TextureManager();
        void setTexture(std::string nomTexture,sf::Texture &T);
        sf::Texture* getTexture(std::string nomTexture);
};