#include "itsuyo.hpp"
#include<iostream>

Itsuyo::Itsuyo(int id) :Perso(id){

    nom="Itsuyo";
    
    speed.x=0;
    speed.y=0;
    in_air=true;
    crouch=false;
    ground_speed=5;
    air_speedmax=4;
    air_acceleration=0.5;
    jump_height=11;
    pourcentage=0;
    
    if(!T.loadFromFile("../Assets/img/itsuyo.jpeg"))
        std::cout<<"erreur"<<std::endl;
    Sprite.setTexture(T);
    Sprite.setScale(0.1,0.1);
    Sprite.setPosition(100,50);
    hitbox_perso.left = Sprite.getPosition().x;
    hitbox_perso.top = Sprite.getPosition().y;
    hitbox_perso.width = T.getSize().x*Sprite.getScale().x;
    hitbox_perso.height = T.getSize().y*Sprite.getScale().y;
    PositionMemory=Sprite.getPosition();
}


void Itsuyo::Jab() {
    int dir;
    if(direction==1)
        dir=30;
    else
        dir=-30;
    {
        sf::FloatRect jabHitbox(dir,0,30,30);
        Hitbox jab;
        jab.hitbox=jabHitbox;
        jab.duration=5;
        jab.damage=5;
        jab.puissance_ejec=0.4;
        jab.direction=sf::Vector2f(2.5*direction,-1.5);
        Hitboxs_attaque.push(jab);
        Hitbox lent;
        lent.duration=0;
        Hitboxs_attaque.push(lent);
        speed.x=0;
        speed.y=0;
    }
}

void Itsuyo::Ftilt() {
    int dir;
    if(direction==1)
        dir=30;
    else
        dir=-48;
    {
        
        Hitbox coup;
        

        coup.damage=10;
        coup.puissance_ejec=0.3;
        coup.hitbox=sf::FloatRect(dir,0,40,15); 
        coup.direction=sf::Vector2f(2.5*direction,-1.5);
        Hitboxs_attaque.push(coup);


        
        Hitbox lent;
        lent.duration=15;
        Hitboxs_attaque.push(lent);
        
        speed.x=0;
        speed.y=0;
    }
}


void Itsuyo::Utilt() {
    {

        Hitbox lent;
        lent.duration=15;
        Hitboxs_attaque.push(lent);


        sf::FloatRect coupHitbox(1,-5,40,60);
        Hitbox coup;
        coup.hitbox=coupHitbox;
        coup.duration=6;
        coup.damage=2;
        coup.puissance_ejec=0.1;
        
        lent;
        lent.duration=20;
        Hitboxs_attaque.push(lent);
        speed.x=0;
        speed.y=0;
    }
}


void Itsuyo::Dtilt() {
    int dir;
    if(direction==1)
        dir=30;
    else
        dir=-25;
    {



        Hitbox lent;
        lent.duration=10;
        Hitboxs_attaque.push(lent);
        Hitbox coup;
        coup.hitbox=sf::FloatRect(dir,5,10,10);
        coup.duration=6;
        coup.damage=15;
        coup.puissance_ejec=0.4;
        coup.direction=sf::Vector2f(0.5,-1);
        Hitboxs_attaque.push(coup);
        coup.hitbox.width=10;
        Hitboxs_attaque.push(coup);
        coup.hitbox.width=15;
        Hitboxs_attaque.push(coup);
        coup.hitbox.width=20;
        Hitboxs_attaque.push(coup);
        coup.hitbox.width=23;
        Hitboxs_attaque.push(coup);
        
    
        
        
        lent;
        lent.duration=20;
        Hitboxs_attaque.push(lent);
        speed.x=0;
        speed.y=0;
    }
}


void Itsuyo::Fair() {
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


        coup.hitbox= sf::FloatRect(dir+5*direction,5,15,30);
        coup.direction=sf::Vector2f(1*direction,-2);
        coup.damage=8;
        coup.puissance_ejec=0.2;
        Hitboxs_attaque.push(coup);
        coup.hitbox= sf::FloatRect(dir+8*direction,8,15,30);
        coup.direction=sf::Vector2f(1*direction,-2);
        coup.damage=8;
        coup.puissance_ejec=0.2;
        Hitboxs_attaque.push(coup);
        coup.hitbox= sf::FloatRect(dir+5*direction,10,15,30);
        coup.direction=sf::Vector2f(1*direction,-2);
        coup.damage=8;
        coup.puissance_ejec=0.2;
        Hitboxs_attaque.push(coup);
        coup.hitbox= sf::FloatRect(dir+3*direction,13,15,30);
        coup.direction=sf::Vector2f(1*direction,-2);
        coup.damage=8;
        coup.puissance_ejec=0.2;
        Hitboxs_attaque.push(coup);
        Hitbox lent;
        lent.duration=5;
        Hitboxs_attaque.push(lent);
    }
}



void Itsuyo::Bair() {
    int dir;
    if(direction==1)
        dir=30;
    else
        dir=-25;
    
    {


        Hitbox lent;
        lent.duration=3;
        Hitboxs_attaque.push(lent);
        sf::FloatRect coupHitbox(-dir,5,30,15);
        Hitbox coup;
        coup.hitbox=coupHitbox;
        coup.duration=2;
        coup.damage=8;
        coup.puissance_ejec=0.2;
        coup.direction=sf::Vector2f(direction*-5,1);
        Hitboxs_attaque.push(coup);
        coup.hitbox=sf::FloatRect(-dir-3*direction,4,10,10);
        coup.damage=15;
        coup.puissance_ejec=0.4;

        lent;
        lent.duration=12;
        Hitboxs_attaque.push(lent);
    }
}

void Itsuyo::Nair() {
    int dir;
    if(direction==1)
        dir=25;
    else
        dir=-22;
    

        Hitbox lent;
        lent.duration=4;
        Hitboxs_attaque.push(lent);
        sf::FloatRect coupHitbox(dir,5,30,15);
        Hitbox coup;
        coup.hitbox=coupHitbox;
        coup.duration=3;
        coup.damage=6;
        coup.puissance_ejec=0.05;
        coup.direction=sf::Vector2f(direction*4,1);
        Hitboxs_attaque.push(coup);
        lent;
        lent.duration=8;
        Hitboxs_attaque.push(lent);
        coup.hitbox=sf::FloatRect(-dir-1*direction,2,10,10);
        coup.damage=10;
        coup.puissance_ejec=0.3;
        Hitboxs_attaque.push(coup);
        
        
        lent;
        lent.duration=15;
        Hitboxs_attaque.push(lent);
    
}


void Itsuyo::Upair() {
    {
        sf::FloatRect coupHitbox(-15,-10,30,30);
        Hitbox coup;
        coup.hitbox=coupHitbox;
        coup.duration=6;
        coup.damage=2;
        coup.puissance_ejec=0.1;
        coup.direction=sf::Vector2f(0,-1);
        Hitboxs_attaque.push(coup);


 
        Hitbox lent;
        lent.duration=10;
        Hitboxs_attaque.push(lent);
        speed.y=8;
    }
}

void Itsuyo::Dair() {
    {
        Hitbox lent;
        lent.duration=8;
        Hitboxs_attaque.push(lent);
        sf::FloatRect coupHitbox(-4,28,25,25);
        Hitbox coup;
        coup.hitbox=coupHitbox;
        coup.damage=10;
        coup.duration=5;
        coup.puissance_ejec=0.3;
        coup.direction=sf::Vector2f(0,1);
        Hitboxs_attaque.push(coup);

        
        
        
        
        lent;
        lent.duration=10;
        Hitboxs_attaque.push(lent);
    }
}

void Itsuyo::NeutralB(std::vector<Arrow> &Arrows,sf::Texture &T)
{
    int dir;
    if(direction==1)
        dir=25;
    else
        dir=-22;
    Hitbox lent;
    lent.duration=15;
    Hitboxs_attaque.push(lent);
    sf::FloatRect coupHitbox(dir,5,20,20);
    Hitbox coup;
    coup.hitbox=coupHitbox;
    coup.damage=32;
    coup.duration=5;
    coup.puissance_ejec=0.8;
    coup.direction=sf::Vector2f(direction,4);
    Hitboxs_attaque.push(coup);
    
    lent;
    lent.duration=15;
    Hitboxs_attaque.push(lent);
}



void Itsuyo::is_crouching()
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