#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<cstdlib>
#include <SFML/Graphics.hpp>

sf::Vector2f SFMLScale(sf::Vector2f P,sf::RenderWindow & window)
{
    P.x=((P.x+1)/2.f)*window.getSize().x;
    P.y=(1-((P.y+1)/2.f))*window.getSize().y;
    return P;
}



sf::Vector2f Projection(sf::Vector3f P)
{
    sf::Vector2f Proj;
    Proj.x=P.x/P.z;
    Proj.y=P.y/P.z;
    return Proj;
}

void drawRectangle(sf::Vector2f P,sf::RenderWindow & window)
{
    int s=5;
    sf::RectangleShape R;
    R.setPosition(P.x-s/2,P.y-s/2);
    R.setFillColor(sf::Color::Green);
    R.setSize(sf::Vector2f(s,s));
    window.draw(R);
}
void drawPoints(std::vector<sf::Vector3f> &points,sf::RenderWindow & window,double dt)
{
    for(sf::Vector3f & point :points)
    {
        drawRectangle(SFMLScale(Projection(point),window),window);
    }
}
float prodscal3D(sf::Vector3f v1,sf::Vector3f v2)
{
    return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}
sf::Vector3f prodvect(sf::Vector3f v1,sf::Vector3f v2)
{
    sf::Vector3f ortho;
    ortho.x=v1.y*v2.z-v1.z*v2.y;
    ortho.x=v1.z*v2.x-v1.x*v2.z;
    ortho.x=v1.x*v2.y-v1.y*v2.x;
    return ortho;
}
sf::Vector3f Normalize(sf::Vector3f v)
{
    float distance=sqrt(v.x*v.x+v.y*v.y);
    return sf::Vector3f(v.x/distance,v.y/distance,v.z/distance);
}
void rotate_point(sf::Vector3f &point,float angle,sf::Vector3f sens)
{
        float c=cos(angle);
        float s=sin(angle);
        float x=point.x,y=point.y,z=point.z;
        sens=Normalize(sens);
        float scalaire=prodscal3D(point,sens);
        sf::Vector3f cross=prodvect(sens,point);
        point.x=x*c+(1-c)*scalaire*sens.x+s*cross.x;
        point.y=y*c+(1-c)*scalaire*sens.y+s*cross.y;
        point.z=z*c+(1-c)*scalaire*sens.z+s*cross.z;
}
sf::Vector3f getcenter(sf::Vector3f v1,sf::Vector3f v2) //basgauchedevant et hautdroitederrière
{
    
    return sf::Vector3f((v1.x+v2.x)/2,(v1.y+v2.y)/2,(v1.z+v2.z)/2);
}
void draw_line(sf::Vector2f p1,sf::Vector2f p2,sf::RenderWindow & window)
{
    sf::VertexArray line(sf::PrimitiveType::Lines,2);
    
    line[0].position=p1;
    line[1].position=p2;
    line[0].color=sf::Color::Green;
    line[1].color=sf::Color::Green;  
    window.draw(line);
}

void draw_connexions( std::vector<std::pair<int,int>> &connexions,sf::RenderWindow & window,const std::vector<sf::Vector3f> &points)
{
    
    for(std::pair<int,int> const &connexion : connexions)
    {
        draw_line(SFMLScale(Projection(points[connexion.first]),window),SFMLScale(Projection(points[connexion.second]),window),window);
    }
}
int main()
{
    float angle=0;
    sf::Clock Time;
    std::vector<sf::Vector3f> points;
    points.push_back(sf::Vector3f(0.5,0.5,2));
    points.push_back(sf::Vector3f(-0.5,0.5,2));
    points.push_back(sf::Vector3f(-0.5,-0.5,2));
    points.push_back(sf::Vector3f(0.5,-0.5,2));
    
    points.push_back(sf::Vector3f(0.5,0.5,1));
    points.push_back(sf::Vector3f(-0.5,0.5,1));
    points.push_back(sf::Vector3f(-0.5,-0.5,1));
    points.push_back(sf::Vector3f(0.5,-0.5,1));
    
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML window");
    std::vector<std::pair<int,int>> connexions{  
        {0,1},
        {1,2},
        {2,3},
        {3,0},
        {4,5},
        {5,6},
        {6,7},
        {7,4},
        {0,4},
        {1,5},
        {2,6},
        {3,7}
    };
    sf::Vector3 center= getcenter(points[6],points[0]);
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            // window closed
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        double dt=Time.getElapsedTime().asSeconds();
        angle=2 * M_PI*dt;
        Time.restart();
        
        window.clear(sf::Color::Black);
        
        sf::Vector3f rotation_axe =sf::Vector3f(0,1,0);
        for(sf::Vector3f &point : points)
        {
            point-=center;
            rotate_point(point,angle,rotation_axe);
            point+=center;
        }
        draw_connexions(connexions,window,points);
        window.display();
            
    }
    
    
}

