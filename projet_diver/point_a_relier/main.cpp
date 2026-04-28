#include <SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<fstream>


std::vector<std::string> split(std::string s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}
void draw_line(sf::Vector2i p1,sf::Vector2i p2,sf::RenderTarget& target,sf::Color c)
{
    sf::VertexArray line(sf::PrimitiveType::Lines,2);
    
    line[0].position=sf::Vector2f(p1);
    line[1].position=sf::Vector2f(p2);
    line[0].color=c;
    line[1].color=c;  
    target.draw(line);
}
std::vector<std::vector<sf::Vector2i>> load(std::string path)
{
    std::ifstream fic;
    fic.open("../points/"+path);
    std::string str;
    std::vector<std::vector<sf::Vector2i>> traits;
    std::vector<sf::Vector2i> trait;
    sf::Vector2i ligne;
    if (fic.is_open())
    {
        while (std::getline(fic,str))
        {
            std::vector<std::string> points = split(str,"),");
            for(std::string &point :points)
            {
                if (point==points[points.size()-1])
                {
                    std::cout<<point<<std::endl;
                }
                
                std::string coo="";
                for (size_t i = 0; i < point.size(); i++)
                {
                    if (isdigit(point[i]))
                    {
                        coo+=point[i];
                    }
                    else
                    if (point[i]==',')
                    {
                        ligne.x=std::stoi(coo);
                        coo="";
                    }
                    if (point[i]==']')
                    break;
                    
                    
                }
                if (coo!="")
                {

                    ligne.y=std::stoi(coo);
                }
                std::cout<<ligne.x<<", "<<ligne.y<<std::endl;
                trait.push_back(ligne);
            }
            traits.push_back(trait);
            trait=std::vector<sf::Vector2i>();
        }
        
    }
    std::cout<<traits.size()<<std::endl;
    return traits;
}

sf::RenderWindow window(sf::VideoMode(950, 950), "SFML window");
int main(int argc, char const *argv[])
{
    
    std::vector<std::vector<sf::Vector2i>> traits;
    std::vector<sf::Vector2i> trait;
    bool texturedefined=false;
    bool afficheSprite=false;
    sf::Texture T;
    sf::Sprite S;
    S.setPosition({0,0});
    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            
            switch (event.type)
            {

                case sf::Event::Closed:
                    window.close();
                    break;



                
                case (sf::Event::MouseButtonPressed):
                    if (event.mouseButton.button==sf::Mouse::Button::Left)
                    {
               
                        trait.push_back(sf::Mouse::getPosition(window));
                    }
                    if (event.mouseButton.button==sf::Mouse::Button::Right)
                    {
                        if (trait.size()>0)
                        {
                            trait.pop_back();
                        }
                        
                        
                    }
                    break;
                case (sf::Event::KeyPressed):
                     
                    {
                        if (trait.size()>1 and event.key.code==sf::Keyboard::Enter)
                        {
                            traits.push_back(trait);
                            trait.clear();
                        }
                        if(event.key.code==sf::Keyboard::F)
                        {
                            std::string path;
                            std::cout<<"indiquez le nom du fichier image : "<<std::endl;
                            std::cin>>path;
                            path="../img/"+path;
                            if(T.loadFromFile(path))
                            {
                                S.setTexture(T);
                                texturedefined=true;
                            }
                            else
                                std::cout<<"erreur de chargement de "+path<<std::endl;
                        }
                        if(event.key.code==sf::Keyboard::L)
                        {
                            std::string path;
                            std::cout<<"indiquez le nom du fichier txt : "<<std::endl;
                            std::cin>>path;
                            std::vector<std::vector<sf::Vector2i>> test=load(path);
                            if (test!=std::vector<std::vector<sf::Vector2i>>())
                            {
                                traits=test;
                            }
                            
                            
                        }
                        if(event.key.code==sf::Keyboard::A)
                        {
                            for(std::vector<sf::Vector2i>& ligne : traits)
                            {
                                std::cout<<"[";
                                for (sf::Vector2i & segment : ligne)
                                {
                                    std::cout<<"("<<segment.x<<","<<segment.y<<") ";
                                    if (segment!=ligne.back())
                                    {
                                        std::cout<<", ";
                                    }
                                    
                                }
                                std::cout<<"],"<<std::endl;
                                
                            }
                        }
                        if(event.key.code==sf::Keyboard::D)
                        {
                            afficheSprite=!afficheSprite;
                        }
                        if(event.key.code==sf::Keyboard::Right)
                        {
                            S.setPosition(S.getPosition()+sf::Vector2f(1,0));
                        }
                        if(event.key.code==sf::Keyboard::Left)
                        {
                            S.setPosition(S.getPosition()+sf::Vector2f(-1,0));
                        }
                        if(event.key.code==sf::Keyboard::Up)
                        {
                            S.setPosition(S.getPosition()+sf::Vector2f(0,-1));
                        }
                        if(event.key.code==sf::Keyboard::Down)
                        {
                            S.setPosition(S.getPosition()+sf::Vector2f(0,1));
                        }
                    break;
                        
                        
                        
                    }
                    break;


                
                
            }
        }

        window.clear(sf::Color::White);

        if (texturedefined and afficheSprite)
        {
            window.draw(S);
        }
        

        for(std::vector<sf::Vector2i>& ligne : traits)
        {
            
            
                for(int i=1;i<ligne.size();++i)
                {
                    draw_line(ligne[i-1],ligne[i],window,sf::Color::Black);
                }
            
            
            
        }
        for(int i=1;i<trait.size();++i)
        {
                draw_line(trait[i-1],trait[i],window,sf::Color::Red);
            
        }

        
        window.display();
        
    }

    return 0;
}
