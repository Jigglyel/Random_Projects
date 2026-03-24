#include"Camera.hpp"

Camera::Camera(/* args */)
{
    position={0.4,0.1,-1};
    offsetX=0;
    offsetY=0;
    fov=1;
    speed=5;
    velocity={0,0,0};
    in_air=false;
    mode_survie=false;
    lights=false;
}

sf::Vector3f Camera::switch_base(sf::Vector3f P)
{
    
    P=P-position; 
    
    
    P=rotate_point( rotate_point(P,-offsetX,{0,1,0}),-offsetY,{1,0,0});

    return P;
}   
sf::Vector2f Camera::Projection(sf::Vector3f P)
{
    sf::Vector2f Proj;
    if (P.z==0)
    {
        P.z=0.0001;
    }
    
    Proj.x=fov*P.x/P.z;
    Proj.y=fov*P.y/P.z;
    
    
    return Proj;
}

void Camera::move()
{
    position+=velocity;
}

void Camera::apply_forces()
{
    if (mode_survie)
        velocity+={0,-0.5,0};
}

void Camera::Check_collisions()
{
    if (mode_survie and position.y<0)
    {
        position.y=0;
        in_air=false;
    }
    
}


