#include <SFML/Graphics.hpp>
#include<cmath>

sf::Vector2f SFMLScale(sf::Vector2f P,sf::RenderTarget & window);
void drawRectangle(sf::Vector2f P,sf::RenderWindow & window);
float prodscal3D(sf::Vector3f v1,sf::Vector3f v2);
float prodscal2D(sf::Vector2f v1,sf::Vector2f v2);
sf::Vector3f prodvect3D(sf::Vector3f v1,sf::Vector3f v2);
float prodvect2D(sf::Vector2f v1,sf::Vector2f v2);
sf::Vector3f Normalize3D(sf::Vector3f v);
sf::Vector2f Normalize2D(sf::Vector2f v);
sf::Vector3f rotate_point(sf::Vector3f point,float angle,sf::Vector3f sens);
sf::Vector3f getcenter(sf::Vector3f v1,sf::Vector3f v2); //basgauchedevant et hautdroitederrière
void draw_line(sf::Vector2f p1,sf::Vector2f p2,sf::RenderTarget & window);
float getangle(sf::Vector2f v1,sf::Vector2f v2);
bool isint(std::string str);