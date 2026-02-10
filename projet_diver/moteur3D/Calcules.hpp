#include <SFML/Graphics.hpp>


sf::Vector2f SFMLScale(sf::Vector2f P,sf::RenderWindow & window);
sf::Vector2f Projection(sf::Vector3f P);
void drawRectangle(sf::Vector2f P,sf::RenderWindow & window);
void drawPoints(std::vector<sf::Vector3f> &points,sf::RenderWindow & window,double dt);
float prodscal3D(sf::Vector3f v1,sf::Vector3f v2);
sf::Vector3f prodvect(sf::Vector3f v1,sf::Vector3f v2);
sf::Vector3f Normalize(sf::Vector3f v);
void rotate_point(sf::Vector3f &point,float angle,sf::Vector3f sens);
sf::Vector3f getcenter(sf::Vector3f v1,sf::Vector3f v2); //basgauchedevant et hautdroitederrière