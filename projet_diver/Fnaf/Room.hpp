#include<unordered_map>
#include<vector>
#include"Animatronic.hpp"

class Room{

    static std::unordered_map<Nom nom,int* position>;
    public :
    int id;
    sf::Texture* textures;
    
}