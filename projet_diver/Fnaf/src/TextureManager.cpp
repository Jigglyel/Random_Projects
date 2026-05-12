#include "TextureManager.hpp"

void TextureManager::setTexture(std::string nomTexture,sf::Texture &T)
{
    Map[nomTexture]=T; 
}

sf::Texture* TextureManager::getTexture(std::string nomTexture)
{
    return &Map[nomTexture];
}
TextureManager::TextureManager()
{
    sf::Texture T;
    T.loadFromFile("../img/Camera/Camera0/Cam0BonnieChicaFreddy.png");
    setTexture("Cam0-Bonnie-Chica",T);
    T.loadFromFile("../img/Camera/Camera0/Cam0FreddyLooking.png");
    setTexture("Cam0",T);
    T.loadFromFile("../img/Camera/Camera0/Cam0Chica.png");
    setTexture("Cam0-Chica",T);
    T.loadFromFile("../img/Camera/Camera1/Cam1Bonnie.png");
    setTexture("Cam1-Bonnie",T);
    T.loadFromFile("../img/Camera/Camera1/Cam1Chica.png");
    setTexture("Cam1-Chica",T);
    setTexture("Cam1-Bonnie-Chica",T);
    T.loadFromFile("../img/Camera/Camera1/Cam1Vide.png");
    setTexture("Cam1",T);
    T.loadFromFile("../img/Camera/Camera2/Cam2Bonnie.png");
    setTexture("Cam2-Bonnie",T);
    T.loadFromFile("../img/Camera/Camera2/Cam2Vide.png");
    setTexture("Cam2",T);
    T.loadFromFile("../img/Camera/Camera4/Cam4Vide.png");
    setTexture("Cam4",T);
    T.loadFromFile("../img/Camera/Camera4/Cam4Bonnie.png");
    setTexture("Cam4-Bonnie",T);
    T.loadFromFile("../img/Camera/Camera9/Cam9Chica.png");
    setTexture("Cam9-Chica",T);
    T.loadFromFile("../img/Camera/Camera9/Cam9Vide.png");
    setTexture("Cam9",T);
    T.loadFromFile("../img/Camera/Camera10/Cam10Chica.png");
    setTexture("Cam10-Chica",T);
    T.loadFromFile("../img/Camera/Camera10/Cam10Vide.png");
    setTexture("Cam10",T);
    T.loadFromFile("../img/OfficeBaseLong.jpg");
    setTexture("Idle",T);
}