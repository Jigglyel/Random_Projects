#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<cstdlib>
#include <SFML/Graphics.hpp>

sf::Vector2f SFMLSclale(sf::Vector2f P,sf::RenderWindow & window)
{
    std::cout<<"window"<<window.getSize().x<<std::endl;
    P.x=((P.x+1)/2.f)*window.getSize().x;
    P.y=(1-((P.y+1)/2.f))*window.getSize().y;
    std::cout<<P.x<<" "<<P.y<<std::endl;
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
    int s=10;
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
        drawRectangle(SFMLSclale(Projection(point),window),window);
        point.z+=1*dt;
    }
}
int main()
{
    sf::Clock Time;
    std::vector<sf::Vector3f> points;
    points.push_back(sf::Vector3f(0.5,0.5,1));
    points.push_back(sf::Vector3f(-0.5,0.5,1));
    points.push_back(sf::Vector3f(0.5,-0.5,1));
    points.push_back(sf::Vector3f(-0.5,-0.5,1));
    points.push_back(sf::Vector3f(0.5,0.5,-1));
    points.push_back(sf::Vector3f(-0.5,0.5,-1));
    points.push_back(sf::Vector3f(0.5,-0.5,-1));
    points.push_back(sf::Vector3f(-0.5,-0.5,-1));
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

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
        Time.restart();
        
        window.clear(sf::Color::Black);
        drawPoints(points,window,dt);
        window.display();
            
    }
    
    
}

