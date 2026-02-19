#include"Camera.hpp"

Camera::Camera(/* args */)
{
    position={0,0,0};
    offsetX=0;
    offsetY=0;
    fov=1;
    speed=0.2;
}

sf::Vector3f Camera::switch_base(sf::Vector3f P)
{
    
    float angleX=offsetX*2*M_PI/360;
    float angleY=offsetY*2*M_PI/360;
    P=P-position; 
    
    
    P=rotate_point( rotate_point(P,-angleX,{0,1,0}),-angleY,{1,0,0});

    return P;
}   
sf::Vector2f Camera::Projection(sf::Vector3f P)
{
    sf::Vector2f Proj;
    
    Proj.x=fov*P.x/P.z;
    Proj.y=fov*P.y/P.z;
    return Proj;
}


