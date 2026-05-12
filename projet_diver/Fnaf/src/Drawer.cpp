#include"Drawer.hpp"


void Drawer::draw(State s,CameraSystem &cameraSystem,std::vector<std::unique_ptr<Animatronic>> &animatronics)
{
    if (s==State::Idle)
    {
        drawIdle(animatronics);
    }
    else
    if (s==State::Camera)
    {
        drawCam(cameraSystem,animatronics);
    }
    else
    if (s==State::Door)
    {
        // drawDoor(animatronics);
    }
    else
    if (s==State::Behind)
    {
        // drawBehind(animatronics);
    }
}

void Drawer::drawCam(CameraSystem &cameraSystem,std::vector<std::unique_ptr<Animatronic>> &animatronics)
{
    sf::View camera=window->getView();
    window->setView(window->getDefaultView());
    sf::RectangleShape background;
    background.setPosition(0,0);
    background.setSize(sf::Vector2f(window->getSize()));
    background.setTexture(getTextureCamera(cameraSystem,animatronics));
    window->draw(background);
    window->setView(camera);

}

sf::Texture* Drawer::getTextureCamera(CameraSystem &cameraSystem,std::vector<std::unique_ptr<Animatronic>> &animatronics)
{
    std::string textureName="Cam"+std::to_string(cameraSystem.activeCam);
    
    for (std::unique_ptr<Animatronic> & animatronic : animatronics)
    {    
        if (animatronic->position==cameraSystem.activeCam)
        {
            
            textureName+="-"+animatronic->nom;
        }
        
    }
    return TM.getTexture(textureName); 
}

void Drawer::drawIdle(std::vector<std::unique_ptr<Animatronic>> &animatronics)
{
    sf::RectangleShape background;
    background.setPosition(0,0);
    background.setSize(sf::Vector2f(window->getSize()));
    background.setTexture(TM.getTexture("Idle"));
    window->draw(background);
}

Drawer::Drawer(sf::RenderWindow&window)
{
    this->window=&window;
}