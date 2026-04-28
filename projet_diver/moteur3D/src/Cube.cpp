#include "3D_Rectangle.cpp" 
#include<iostream>


class Cube : public Rectangle3D
{
private:

    
public:
    

    Cube(float size,sf::Vector3f position) : Rectangle3D(size,size,size,position){}
    
        
    
    Cube() : Rectangle3D(0,0,0,{0,0,0}){}

        void Construct(float size,sf::Vector3f position)
        {
            Rectangle3D::Construct(size,size,size,position);
        }
    
};

