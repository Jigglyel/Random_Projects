#include "FontManager.hpp"

void FontManager::setFont(std::string nomFont,sf::Font &F)
{
    Map[nomFont]=F; 
}

sf::Font& FontManager::getFont(std::string nomFont)
{
    return Map[nomFont];
}
FontManager::FontManager()
{
    sf::Font F("../Font/Jersey15-Regular.ttf");
    Map["Jersey15-Regular"] = F; 
}