#include<unordered_map>
#include<vector>
#include"Animatronic.hpp"

class Camera{

    static std::unordered_map<Nom ,int* > pos;
    public :
    int id;
    sf::Texture* textures;
    
};