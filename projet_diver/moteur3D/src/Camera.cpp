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

Eigen::Vector3f Camera::switch_base(Eigen::Vector3f P)
{
    
    P=P-position; 
    
    
    P=rotate_point( rotate_point(P,-offsetX,{0,1,0}),-offsetY,{1,0,0});

    return P;
}   
sf::Vector2f Camera::Projection(Eigen::Vector3f P)
{
    sf::Vector2f Proj;
    if (P.z()==0)
    {
        P.z()=0.0001;
    }
    
    Proj.x=fov*P.x()/P.z();
    Proj.y=fov*P.y()/P.z();
    
    
    return Proj;
}

void Camera::move()
{
    position+=velocity;
}

void Camera::apply_forces()
{
    if (mode_survie)
        velocity+=Eigen::Vector3f{0,-0.5,0};
}

void Camera::Check_collisions()
{
    if (mode_survie and position.y()<0)
    {
        position.y()=0;
        in_air=false;
    }
    
}

Eigen::Matrix4f Camera::getMatriceView()
{

   
   float c,s;
    Eigen::Matrix4f T;
    T<<1,0,0,position.x(),
       0,1,0,position.y(),
       0,0,1,position.z(),
       0,0,0,1;


    Eigen::Matrix4f Rx;
    
    c=cos(-offsetX);
    s=sin(-offsetX);
    Rx<<1,0,0,0,
        0,c,-s,0,
        0,s,c,0,
        0,0,0,1;

    Eigen::Matrix4f Ry;
    
    c=cos(-offsetY);
    s=sin(-offsetY);
    Ry<<c,0,s,0,
        0,1,0,0,
        -s,0,c,0,
        0,0,0,1;
    return Rx*Ry*T;
}


