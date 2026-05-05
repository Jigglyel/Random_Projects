#include "TextureManager.hpp"

void TextureManager::setTexture(std::string &nomTexture,sf::Texture T);
{
    Map[nomTexture]=T; 
}

sf::Texture* TextureManager::getTexture(std::string &nomTexture)
{
    
    return &Map[nomTexture];
}