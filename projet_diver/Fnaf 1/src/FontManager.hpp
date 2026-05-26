#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class FontManager
{
private:
    /* data */
public:
    private:
        std::unordered_map<std::string,sf::Font> Map;
    public:
        FontManager();
        void setFont(std::string nomFont,sf::Font &F);
        sf::Font& getFont(std::string nomFont);
};

