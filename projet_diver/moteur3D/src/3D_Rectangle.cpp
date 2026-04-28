#include "3D_object.cpp" 


class Rectangle3D : public Objet3D
{
private:
    float width;
    float height;
    float depth;
    
public:

    

    Rectangle3D(float width, float height,float depth,sf::Vector3f position)
    {
        mesh.points={
            {sf::Vector3f(0,0,0)}, // 0
            {sf::Vector3f(0,-height,0)}, // 1
            {sf::Vector3f(0,0,depth)}, // 2
            {sf::Vector3f(0,-height,depth)}, // 3
            {sf::Vector3f(width,0,0)}, // 4
            {sf::Vector3f(width,-height,0)}, // 5
            {sf::Vector3f(width,0,depth)}, // 6
            {sf::Vector3f(width,-height,depth)} // 7
        };
        faces={
            {0,1},
            {0,2},
            {0,4},
            {1,3},
            {1,5},
            {2,3},
            {2,6},
            {4,5},
            {6,4},
            {3,7},
            {5,7},
            {6,7}
        };
        this->transformation.position=position;
        this->width=width;
        this->height=height;
        this->depth=depth;
        this->transformation.size=1;
    }

    Rectangle3D()
    {
        Rectangle3D(0,0,0,{0,0,0});
    }

    virtual void Construct(float width, float height,float depth,sf::Vector3f position)
    {
        mesh.points={
            {sf::Vector3f(0,0,0)}, // 0
            {sf::Vector3f(0,-height,0)}, // 1
            {sf::Vector3f(0,0,depth)}, // 2
            {sf::Vector3f(0,-height,depth)}, // 3
            {sf::Vector3f(width,0,0)}, // 4
            {sf::Vector3f(width,-height,0)}, // 5
            {sf::Vector3f(width,0,depth)}, // 6
            {sf::Vector3f(width,-height,depth)} // 7
        };
        faces={
            {0,1},
            {0,2},
            {0,4},
            {1,3},
            {1,5},
            {2,3},
            {2,6},
            {4,5},
            {6,4},
            {3,7},
            {5,7},
            {6,7}
        };
        this->transformation.position=position;
        this->width=width;
        this->height=height;
        this->depth=depth;
        this->transformation.size=1;
    }
    
};

