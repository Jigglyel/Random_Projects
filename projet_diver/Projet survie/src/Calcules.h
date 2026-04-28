#include "SFML/Graphics.hpp"
#include <cmath>
#include <iostream>
struct objet{
    float x, y;
    sf::Texture image;
};
struct Perso{
    int faim;
    float x, y,v;
    sf::Texture image;
    float hp;
    sf::RectangleShape hitbox;
    bool invincible;
    
};
struct Bullet{
    float x,y,v;
    float vx,vy;
    sf::Sprite sprite;
    bool on_screen;
    int count;
    sf::RectangleShape hitbox;
};

struct cercle_faim{
    int taille;
    sf::RectangleShape* pixels;
};
struct weapon{
    float dégats;
    float tear_rate;
    int id;

};
struct HUD
{
    sf::RectangleShape rectganle;
    sf::Text text;
    sf::Texture image;
};
sf::RectangleShape* get_cercle_faim(objet feu, int taille_cercle,sf::RenderWindow &window);
void get_balle(int x_joueur, int y_joueur,int x_souris,int y_souris,std::vector<Bullet> &balles,sf::View &camera,sf::RenderWindow &window,sf::Texture &TextureBalle);
void balle_accompagnement(Bullet &balle);
void update_pos_joueur(Perso & joueur, bool z,bool q,bool s,bool d,bool sprint,int vitesse_de_base);
sf::RectangleShape get_indicator_fire(objet feu,sf::RenderWindow &window,sf::View &camera);
void balle_sorcière_accompagnement(Bullet &balle,Perso joueur);
