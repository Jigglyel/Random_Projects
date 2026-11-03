#pragma once
#include "Perso.hpp"
#include <SFML/Graphics.hpp>


class Itsuyo : public Perso {
    public:
    Itsuyo(int id);

    void Jab() override;
    void Ftilt() override;
    void Utilt() override;
    void Dtilt() override;
    void Fair() override;
    void Bair() override;
    void Nair() override;
    void Upair() override;
    void Dair() override;
    void NeutralB(std::vector<Arrow> &Arrows,sf::Texture &T) override;

    void is_crouching() ;

};