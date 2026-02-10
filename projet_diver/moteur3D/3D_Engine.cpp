#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<cstdlib>
#include <SFML/Graphics.hpp>


void draw_line(sf::Vector2f p1,sf::Vector2f p2,sf::RenderWindow & window)
{
    sf::VertexArray line(sf::PrimitiveType::Lines,2);
    
    line[0].position=p1;
    line[1].position=p2;
    line[0].color=sf::Color::Green;
    line[1].color=sf::Color::Green;  
    window.draw(line);
}

void draw_connexions( std::vector<std::pair<int,int>> &connexions,sf::RenderWindow & window,const std::vector<sf::Vector3f> &points,sf::Vector3f décalage)
{
    
    for(std::pair<int,int> const &connexion : connexions)
    {
        sf::Vector3f p1=points[connexion.first]+décalage, p2=points[connexion.second]+décalage;
        draw_line(SFMLScale(Projection(p1),window),SFMLScale(Projection(p2),window),window);
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
    
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML window");
    
    sf::Vector3 center= getcenter(points[6],points[0]);
    sf::Vector3f décalage(0,0,25);
    sf::Vector3f décalage2(5,0,20);
    sf::Vector3f décalage3(-5,0,15);
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
        décalage.x-=dt;
        décalage2.z-=dt;
        décalage3.x+=dt;
        décalage.z-=dt;
        décalage3.z-=dt;
        Time.restart();
        
        window.clear(sf::Color::Black);
        
        sf::Vector3f rotation_axe =sf::Vector3f(0,1,0);
        for(sf::Vector3f &point : points)
        {
            point-=center;
            rotate_point(point,angle,rotation_axe);
            point+=center;
        }
        draw_connexions(connexions,window,points,décalage);
        draw_connexions(connexions,window,points,décalage2);
        draw_connexions(connexions,window,points,décalage3);
        window.display();
            
    }
    
    
}

