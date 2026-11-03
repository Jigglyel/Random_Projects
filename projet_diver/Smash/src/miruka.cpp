#include "miruka.hpp"
#include <iostream>



Miruka::Miruka(int id) :Perso(id){
    
    nom="Miruka";
    
    speed.x=0;
    speed.y=0;
    in_air=true;
    crouch=false;
    ground_speed=5;
    air_speedmax=4;
    air_acceleration=0.5;
    jump_height=11;
    pourcentage=0;
    
    if(!T.loadFromFile("../Assets/img/miruka.jpg"))
        std::cout<<"erreur"<<std::endl;
    Sprite.setTexture(T);
    Sprite.setScale(0.1,0.1);
    if(ID==0)
        Sprite.setPosition(200,50);
    else
        Sprite.setPosition(500,50);
    hitbox_perso.left = Sprite.getPosition().x;
    hitbox_perso.top = Sprite.getPosition().y;
    hitbox_perso.width = T.getSize().x*Sprite.getScale().x;
    hitbox_perso.height = T.getSize().y*Sprite.getScale().y;
    PositionMemory=Sprite.getPosition();
    
    
}

void Miruka::is_crouching()
{
    if (crouch)
    {
        Sprite.setScale(0.13,0.05);
    }
    else
    {
        
        Sprite.setScale(0.1,0.1);
    }
    
}

void Miruka::Jab() {
    int dir;
    if(direction==1)
        dir=30;
    else
        dir=-30;
    {
        sf::FloatRect jabHitbox(dir,0,20,20);
        Hitbox jab;
        jab.hitbox=jabHitbox;
        jab.duration=5;
        jab.damage=5;
        jab.puissance_ejec=0.2;
        jab.direction=sf::Vector2f(2.5*direction,-1.5);
        Hitboxs_attaque.push(jab);
        // Hitbox lent;
        // lent.duration=0;
        // Hitboxs_attaque.push(lent);
        // speed.x=0;
        // speed.y=0;
    }

}
void Miruka::Ftilt() {
    int dir;
    if(direction==1)
        dir=30;
    else
        dir=-48;
    {
        sf::FloatRect coupHitbox(dir,0,40,15);
        Hitbox coup;
        coup.hitbox=coupHitbox;
        coup.duration=1;
        coup.damage=10;
        coup.puissance_ejec=0.3;
        coup.direction=sf::Vector2f(2.5*direction,-1.5);
        Hitboxs_attaque.push(coup);
        Hitbox lent;
        lent.duration=15;
        Hitboxs_attaque.push(lent);
        
        speed.x=0;
        speed.y=0;
    }
}
void Miruka::Utilt() {
    {
        sf::FloatRect coupHitbox(1,-13,20,15);
        Hitbox coup;
        coup.hitbox=coupHitbox;
        coup.duration=6;
        coup.damage=2;
        coup.puissance_ejec=0.1;
        

        coup.direction=sf::Vector2f(0,-1);
        Hitboxs_attaque.push(coup);

        coupHitbox =sf::FloatRect(-10,-20,40,17);
        coup.hitbox=coupHitbox;
        coup.duration=5;
        coup.damage=1;
        coup.puissance_ejec=0.3;
        

        coup.direction=sf::Vector2f(0,-1);
        Hitboxs_attaque.push(coup);
        Hitbox lent;
        lent.duration=10;
        Hitboxs_attaque.push(lent);
        speed.x=0;
        speed.y=0;
    }
}
void Miruka::Dtilt() {
    int dir;
    if(direction==1)
        dir=30;
    else
        dir=-25;
    {
        sf::FloatRect coupHitbox(dir,5,15,10);
        Hitbox coup;
        coup.hitbox=coupHitbox;
        coup.duration=1;
        coup.damage=2;
        coup.puissance_ejec=0.1;
        coup.direction=sf::Vector2f(0,-1);
        Hitboxs_attaque.push(coup);
        coup.hitbox.height=20;
        coup.hitbox.top=-5;
        Hitboxs_attaque.push(coup);
        coup.hitbox.height=30;
        coup.hitbox.top=-15;
        Hitboxs_attaque.push(coup);
        coup.hitbox.height=40;
        coup.damage=15;
        coup.puissance_ejec=0.3;
        coup.hitbox.top=-25;
        Hitboxs_attaque.push(coup);
    
        
        
        Hitbox lent;
        lent.duration=20;
        Hitboxs_attaque.push(lent);
        speed.x=0;
        speed.y=0;
    }
}
void Miruka::Fair() {
    int dir;
    if(direction==1)
        dir=30;
    else
        dir=-25;
    {
        sf::FloatRect coupHitbox(dir,-15,15,30);
        Hitbox coup;
        coup.hitbox=coupHitbox;
        coup.duration=2;
        coup.damage=4;
        coup.puissance_ejec=0.1;
        coup.direction=sf::Vector2f(1*direction,1.75);
        Hitboxs_attaque.push(coup);


        coup.hitbox= sf::FloatRect(dir,0,28,15);
        coup.direction=sf::Vector2f(1*direction,-2);
        coup.damage=8;
        coup.puissance_ejec=0.2;
        Hitboxs_attaque.push(coup);
        Hitbox lent;
        lent.duration=5;
        Hitboxs_attaque.push(lent);
    }
}
void Miruka::Bair() {
    int dir;
    if(direction==1)
        dir=30;
    else
        dir=-25;
    
    {
        sf::FloatRect coupHitbox(-dir,-5,30,15);
        Hitbox coup;
        coup.hitbox=coupHitbox;
        coup.duration=2;
        coup.damage=2;
        coup.puissance_ejec=0.08;
        coup.direction=sf::Vector2f(0,1);
        Hitboxs_attaque.push(coup);
        for (int i = coup.hitbox.top+5; i < 20; i=i+5)
        {
           coup.hitbox.top=i;
           Hitboxs_attaque.push(coup);
        }
        coup.hitbox.top=25;
        coup.damage=6;
        coup.puissance_ejec=0.3;
        Hitboxs_attaque.push(coup);

        
        
        Hitbox lent;
        lent.duration=8;
        Hitboxs_attaque.push(lent);
    }
}
void Miruka::Nair() {
    int dir;
    if(direction==1)
        dir=30;
    else
        dir=-25;
    
        for (size_t i = 0; i < 15; i++)
        {
            sf::FloatRect coupHitbox(-12,-12,45,45);
            Hitbox coup;
            coup.hitbox=coupHitbox;
            coup.duration=1;
            coup.damage=2;
            coup.puissance_ejec=0.2;
            coup.direction=sf::Vector2f(speed.x,-1.25);
            Hitboxs_attaque.push(coup);
        }
        Hitboxs_attaque.back().puissance_ejec=0.6;
        
        
        Hitbox lent;
        lent.duration=15;
        Hitboxs_attaque.push(lent);
    
}
void Miruka::Upair() {
    {
        sf::FloatRect coupHitbox(-5,-10,20,20);
        Hitbox coup;
        coup.hitbox=coupHitbox;
        coup.duration=1;
        coup.damage=2;
        coup.puissance_ejec=0.1;
        coup.direction=sf::Vector2f(1,-0.2);
        Hitboxs_attaque.push(coup);


        coup.hitbox.top=-12;
        coup.hitbox.left=-2;
        Hitboxs_attaque.push(coup);
        coup.hitbox.top=-14;
        coup.hitbox.left=1;
        Hitboxs_attaque.push(coup);
        coup.hitbox.top=-16;
        coup.hitbox.left=4;
        coup.direction=sf::Vector2f(1,0.2);
        Hitboxs_attaque.push(coup);
        coup.hitbox.top=-14;
        coup.hitbox.left=7;
        Hitboxs_attaque.push(coup);
        coup.hitbox.top=-12;
        coup.hitbox.left=10;
        coup.duration=2;
        coup.damage=10;
        coup.puissance_ejec=0.3;
        coup.direction=sf::Vector2f(0.1,-1);
        Hitboxs_attaque.push(coup);
        Hitbox lent;
        lent.duration=10;
        Hitboxs_attaque.push(lent);
    }
}
void Miruka::Dair() {
    {
        
            sf::FloatRect coupHitbox(5,30,10,25);
            Hitbox coup;
            coup.hitbox=coupHitbox;
            coup.damage=3;
            coup.duration=15;
            coup.puissance_ejec=0.3;
            coup.direction=sf::Vector2f(0,1);
            Hitboxs_attaque.push(coup);
            speed.y=10;

        
        
        
        
        Hitbox lent;
        lent.duration=10;
        Hitboxs_attaque.push(lent);
    }
}

void Miruka::NeutralB(std::vector<Arrow> &Arrows,sf::Texture &T)
{
    Arrow fleche(T);
    fleche.sprite.setPosition(direction*22+Sprite.getPosition().x,Sprite.getPosition().y);
    fleche.hitbox.direction=sf::Vector2f(direction,-2);
    fleche.speed.x=20*direction;
    fleche.belonging=ID;
    Arrows.push_back(fleche);
    Hitbox lent;
    lent.duration=15;
    Hitboxs_attaque.push(lent);
}

void Miruka::UpB()
{
    sf::FloatRect coupHitbox(2,30,20,20);
    Hitbox coup;
    coup.hitbox=coupHitbox;
    coup.damage=3;
    coup.duration=15;
    coup.puissance_ejec=0.3;
    coup.direction=sf::Vector2f(0,1);
    Hitboxs_attaque.push(coup); 
    Hitbox lent;
    lent.duration=10;
    Hitboxs_attaque.push(lent);
    speed.y=-20; 
    idle=true;
}