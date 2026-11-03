#include "Perso.hpp"
    
    Perso::Perso(int id){
        ID=id;
        spaceRelease=false;
        mort=false;
        dbjump=true;
        in_air=true;
        pourcentage=0;
        crouch=false;
        hitstun=false;
        idle=false;
        direction=1;
        vies=3;
        
    }






void Perso::move(){
    PositionMemory=sf::Vector2f(Sprite.getPosition().x,Sprite.getPosition().y+Sprite.getGlobalBounds().height);
    Sprite.move(speed);
    if(std::sqrt(speed.x*speed.x+speed.y*speed.y*1)<15)
        hitstun=false;
    
}
void Perso::refresh_hitbox()
{
    hitbox_perso=Sprite.getGlobalBounds();
}

bool Perso::manage_hitbox_ejection(const Hitbox &hitbox){

    if (hitbox.hitbox.intersects(hitbox_perso))        
    {
        float distance=std::sqrt(hitbox.direction.x*hitbox.direction.x +hitbox.direction.y*hitbox.direction.y);
        sf::Vector2f normalized;
        if(distance==0)
                normalized=sf::Vector2f(0,0);
        else
            normalized=sf::Vector2f(hitbox.direction.x/distance,hitbox.direction.y/distance);
        speed.x= hitbox.puissance_ejec*(pourcentage+1)*normalized.x;
        speed.y= hitbox.puissance_ejec*(pourcentage+1)*normalized.y;
        pourcentage+=hitbox.damage;
        crouch=false;
        in_air=true;
        hitstun=true;
        return true;
    }
    return false;
}
void Perso::Check_touched(std::queue<Hitbox> Hitboxs_attaque_ennemis,std::vector<Arrow> &fleches)
{
        
    if(!Hitboxs_attaque_ennemis.empty())
    {
        manage_hitbox_ejection(Hitboxs_attaque_ennemis.front());
        
    }
    for (auto it = fleches.begin(); it != fleches.end(); )
    {
        if (ID!=it->belonging and manage_hitbox_ejection(it->hitbox))
            fleches.erase(it);   
        else
            ++it;    

    }
    
}
void Perso::draw_hitboxs(sf::RenderWindow &window)
{
        
    if(!Hitboxs_attaque.empty())
    {
        Hitbox &hitbox=Hitboxs_attaque.front();
        
            sf::RectangleShape rect(sf::Vector2f(hitbox.hitbox.width, hitbox.hitbox.height));
                rect.setPosition(hitbox.hitbox.left, hitbox.hitbox.top);
                rect.setFillColor(sf::Color::Transparent);
                rect.setOutlineThickness(2);
                rect.setOutlineColor(sf::Color::Red);
                window.draw(rect);
            hitbox.duration--;
            hitbox.hitbox.left-=Sprite.getPosition().x;
            hitbox.hitbox.top-=Sprite.getPosition().y;
            if (hitbox.duration<=0)
            {
                Hitboxs_attaque.pop();
            }
            
    }
}

void Perso::ground_collisions()
{
    if (Sprite.getPosition().y+Sprite.getGlobalBounds().height>400)
        {
            Sprite.setPosition(Sprite.getPosition().x,400-Sprite.getGlobalBounds().height);
            speed.y=0;
            in_air=false;
            dbjump=true;
            spaceRelease=false;
        }
}

void Perso::apply_forces()
{
    speed.y+=0.5;
    if(in_air)
    {
        if(hitstun)
        {
            if(speed.x<0)
                speed.x+=0.2;
            else
                speed.x-=0.2;
        }
        else
        {
            if(speed.x<0)
                speed.x+=0.1;
            else
                speed.x-=0.1;
            if(speed.y<0)
                speed.y+=0.2;
        }
    }
}
void Perso::create_death_particules()
{
    for (size_t i = 0; i < 20; i++)
        {
            Death_particules triangle(Sprite);
            
            triangles.push_back(triangle);
        }
}
void Perso::respawn()
{

    
        
        if(vies>1)
        {
            pourcentage=0;
            speed.x=0;
            speed.y=0;
            
            in_air=true;
            crouch=false;
            dbjump=true;
            idle=false;
            vies--;
            if(ID==0)
                Sprite.setPosition(200,50);
            else
                Sprite.setPosition(500,50);
                    
        }
        else
            vies--;
        
        
    }

void Perso::check_Death(sf::RenderWindow &window)
{
    if (vies>0)   
    {
        if(Sprite.getPosition().x>window.getSize().x or Sprite.getPosition().x<0 or Sprite.getPosition().y>window.getSize().y or (Sprite.getPosition().y<0 and hitstun))
        {
            create_death_particules();
            respawn();
        }
    }
    else
        {
            Sprite.setScale(0.01,0.01);
        }
}
void Perso::setActivesHitboxes()
{  
    if(!Hitboxs_attaque.empty())
    {
        Hitboxs_attaque.front().hitbox.left+=Sprite.getPosition().x;
        Hitboxs_attaque.front().hitbox.top+=Sprite.getPosition().y;
    }
} 
void Perso::move_triangles(sf::RenderWindow& window)
{
    for (Death_particules & triangle :  triangles)
    {
        triangle.apply_forces();
        triangle.move();
        triangle.rebondit(window);
        triangle.affiche(window);
        
    }
    if (!triangles.empty())
        if (triangles.back().durée==0)
        {
            triangles.clear();
        }
    
        
}

