#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include "Hitbox.hpp"
#include "Death_Particules.hpp"
#include<iostream>
#include<cmath>
#include"arrow.hpp"


class Perso
{
    private:

    public:
    Perso(int id);
    bool spaceRelease;
    sf::Sprite Sprite;
    bool mort;
    std::string nom;
    bool dbjump;
    bool in_air;
    int pourcentage;
    sf::Vector2f speed;
    float ground_speed;
    float air_speedmax;
    float air_acceleration;
    bool crouch;
    float jump_height;
    bool hitstun;
    int direction;
    sf::Texture T;
    sf::FloatRect hitbox_perso;
    int ID;
    int vies;
    std::queue<Hitbox> Hitboxs_attaque;
    std::vector<Death_particules> triangles;
    sf::Vector2f PositionMemory;
    bool idle;
    
    
    virtual void Jab()=0;
    virtual void Ftilt()=0;
    virtual void Utilt()=0;
    virtual void Dtilt()=0;
    // virtual void Fsmash()=0;
    // virtual void Usmash()=0;
    // virtual void Dsmash()=0;
    virtual void Fair()=0;
    virtual void Dair()=0;
    virtual void Nair()=0;
    virtual void Upair()=0;
    virtual void Bair()=0;

    // virtual void DownB()=0;
    virtual void NeutralB(std::vector<Arrow> &Arrows,sf::Texture &T)=0;
    virtual void UpB()=0;
    // virtual void SideB()=0;

    void move();
    void refresh_hitbox();
    
    void Check_touched(std::queue<Hitbox> Hitboxs_attaque_ennemis,std::vector<Arrow> &fleches);
    void draw_hitboxs(sf::RenderWindow &window);
    void ground_collisions();
    void apply_forces();
    void create_death_particules();
    void respawn();
    bool manage_hitbox_ejection(const Hitbox &hitbox);
    void check_Death(sf::RenderWindow &window);
    void setActivesHitboxes();
    void move_triangles(sf::RenderWindow& window);

};