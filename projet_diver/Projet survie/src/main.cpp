#include"main.h"
int main()
{
    Perso joueur;
    sf::RenderWindow window(sf::VideoMode(1200, 900), "TEST");
    window.setFramerateLimit(120);
    jeu(joueur,window);
    return 0;
}