#include"mob.h"
//fait spawn un zombie aléatoirement autour du joueur

void zombie_spawn(std::vector<Mob> &zombies,Perso joueur,int ID,sf::Texture &zombimage,sf::Texture& sorcimage)
{
    Mob zombie;
    zombie.ID=ID;
    int pif =rand()%1000;
    if (ID==0)
    {
        zombie.x=joueur.x+cos(pif)*200;
        zombie.y=joueur.y+sin(pif)*200;
    }
    else
    {
        zombie.x=joueur.x+cos(pif)*400;
        zombie.y=joueur.y+sin(pif)*400;
    }
    if(ID==0)
    {
        zombie.hp=20;
        zombie.v=1; 
        zombie.hitbox.setSize(sf::Vector2f(7,25));
        zombie.hitbox.setOrigin(zombimage.getSize().x/2,zombimage.getSize().y/2);
        zombie.hitbox.setPosition(zombie.x,zombie.y);
       
        zombie.sprite.setTexture(zombimage);
    }
    else{
        zombie.hp=50;
        zombie.v=0.5;
        zombie.hitbox.setSize(sf::Vector2f(20,30));
        zombie.hitbox.setOrigin(sorcimage.getSize().x/2,sorcimage.getSize().y/2);
        zombie.hitbox.setPosition(zombie.x,zombie.y);
        zombie.sprite.setTexture(sorcimage);
    }
    
    
    zombies.push_back(zombie);
}
void CheckMobSpawn(std::vector<Mob> &mobs,Perso joueur,sf::Clock &ZombieSpawnClock,sf::Clock &sorcièreSpawnClock,int spawn_rate,sf::Texture &zombimage,sf::Texture &sorcimage)
{
    if(mobs.size()<30)
    {
    if (ZombieSpawnClock.getElapsedTime().asMilliseconds()>spawn_rate+100)
        {
            ZombieSpawnClock.restart();
            zombie_spawn(mobs,joueur,0,zombimage,sorcimage);
        }
    if (sorcièreSpawnClock.getElapsedTime().asMilliseconds()>spawn_rate)
        {
            sorcièreSpawnClock.restart();
            zombie_spawn(mobs,joueur,1,zombimage,sorcimage);
        }
    }
    
}
//s'occupe d'accompagner un zombie
void zombie_accompagnement(Mob &zombie,Perso joueur)
{
    float dx,dy,distance;
    dx = joueur.x - zombie.x;
    dy =  joueur.y- zombie.y;
    distance = sqrt(dx*dx + dy*dy);

    zombie.vx = zombie.v * dx / distance;
    zombie.vy = zombie.v * dy / distance;
    zombie.x+=zombie.vx;
    zombie.y+=zombie.vy;
    zombie.hitbox.setPosition(zombie.x-3,zombie.y-10);
}
void sorcière_accompagnement(Mob &sorcière,Perso joueur,std::vector<Bullet> &balles,sf::Texture& TextureBalle)
{
    float dx,dy,distance;
    dx = joueur.x - sorcière.x;
    dy =  joueur.y- sorcière.y;
    distance = sqrt(dx*dx + dy*dy);
    Bullet balle;
    if (distance<200)
    {
        if (sorcière.shoot.getElapsedTime().asSeconds()>1)
        {
            sorcière.shoot.restart();
            
            balle.x=sorcière.x;
            balle.y=sorcière.y;
            balle.count=0;
            balle.v=1;
            balle.vx=0;
            balle.vy=0;
            balle.hitbox.setSize(sf::Vector2f(7,7));
            balle.sprite.setTexture(TextureBalle);
            balle.sprite.setColor(sf::Color(255,0,255));
            balles.push_back(balle);
            sorcière.vx=0;
            sorcière.vy=0;
        }
    }
    else
    {
        sorcière.vx = sorcière.v * dx / distance;
        sorcière.vy = sorcière.v * dy / distance;
        sorcière.x+=sorcière.vx;
        sorcière.y+=sorcière.vy;
        sorcière.hitbox.setPosition(sorcière.x-30,sorcière.y-40);
    }
}
void update_position_collisions(std::vector<Bullet> &bullets,std::vector<Mob>&mobs,Perso &joueur,sf::Clock &InvicibleClock,weapon arme,std::vector<Bullet> &witch_balls,sf::Texture &TextureBalle)
{
    int i=0;
    
    for ( Mob &mob:mobs)
    {
        if (mob.ID==0)
        {
            zombie_accompagnement(mob,joueur);
        }
        if (mob.ID==1)
        {
            sorcière_accompagnement(mob,joueur,witch_balls,TextureBalle);
        }
        
        
        
    }
    
    while (i<bullets.size())
    {   balle_accompagnement(bullets[i]);
        int j=0;
        bool bullet_destroyed=false;
        bool zombie_destroyed=false;
        while (j<mobs.size() and not bullet_destroyed)
        {
            if(bullets[i].hitbox.getGlobalBounds().intersects(mobs[j].hitbox.getGlobalBounds()))
            {
                
                bullets.erase(bullets.begin()+i);
                bullet_destroyed=true;
                mobs[j].hp=mobs[j].hp-arme.dégats;
                if (mobs[j].hp<=0)
                {
                    mobs.erase(mobs.begin()+j);
                }
                
            }
            if (not zombie_destroyed)
            { 
                ++j;
            }

            
                
        }
        if (not bullet_destroyed and bullets[i].count>200)
        {
            bullets.erase(bullets.begin()+i);
            bullet_destroyed=true;
        } 
        if (not bullet_destroyed)
        {
            ++i;
        }
    }
    if(not joueur.invincible)
    {
        for (int j = 0; j < mobs.size(); j++)
        {
            if(joueur.hitbox.getGlobalBounds().intersects(mobs[j].hitbox.getGlobalBounds()))
                {   
                    joueur.hp=joueur.hp-5;
                    joueur.invincible=true;
                    InvicibleClock.restart();   
                }
        }
    }
    i=0;
    while (i<witch_balls.size())
    {
        balle_sorcière_accompagnement(witch_balls[i],joueur);
        
        
        if(not joueur.invincible and witch_balls[i].hitbox.getGlobalBounds().intersects(joueur.hitbox.getGlobalBounds()))
        {
            joueur.hp-=5;
            joueur.invincible=true;
            InvicibleClock.restart();
            witch_balls.erase(witch_balls.begin()+i);
        }
        else
        if (witch_balls[i].count>200)
        {
            witch_balls.erase(witch_balls.begin()+i);
        } 
        else
        {
            ++i;
        }
        


    }
    
}
