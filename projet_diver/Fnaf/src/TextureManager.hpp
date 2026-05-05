class TextureManager
{
private:
    std::unordered_map<std::string,sf::Texture> Map;
public:
    void setTexture(std::string &nomTexture,sf::Texture &T);
    Texture* getTexture(std::string &nomTexture);
};