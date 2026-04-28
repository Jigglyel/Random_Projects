#include"Calcules.h"
struct Mob{
    float x,y,v;
    float vx,vy;
    float hp;
    sf::RectangleShape hitbox;
    int ID;
    sf::Clock shoot;
    sf ::Sprite sprite;
};
void update_position_collisions(std::vector<Bullet> &bullets,std::vector<Mob>&zombies,Perso &joueur,sf::Clock &InvicibleClock,weapon arme,std::vector<Bullet> &witch_balls,sf::Texture& TextureBalle );
void zombie_spawn(std::vector<Mob> &zombies,Perso joueur,int ID,sf::Texture* &zombimage,sf::Texture*& sorcimage);
void zombie_accompagnement(Mob &zombie,Perso joueur);
void CheckMobSpawn(std::vector<Mob> &mobs,Perso joueur,sf::Clock &ZombieSpawnClock,sf::Clock &sorcièreSpawnClock,int spawn_rate,sf::Texture &zombimage,sf::Texture &sorcimage);
