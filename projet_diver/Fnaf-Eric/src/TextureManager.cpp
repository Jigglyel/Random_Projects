#include "TextureManager.hpp"

void TextureManager::setTexture(std::string nomTexture,std::string path)
{
    sf::Texture T;
    if(T.loadFromFile(path))
    {
        loadingMade++;
        std::cout<<"["<<loadingMade*100/66<<"%"<<"] Texture "<<nomTexture<<" loaded successfully"<<std::endl;
        Map[nomTexture]=std::move(T); 
    }
}

sf::Texture& TextureManager::getTexture(std::string nomTexture)
{
    return Map[nomTexture];
}
TextureManager::TextureManager()
{
}

void TextureManager::loadTextures()
{
    setTexture("Couloir droite","../img/Camera/Couloir_droite/CD_Vide.jpg");

    setTexture("Couloir droite-Raphael","../img/Camera/Couloir_droite/CD_Raph1.jpg");
    setTexture("Couloir droite-Raphael-position2","../img/Camera/Couloir_droite/CD_Raph2.jpg");
    setTexture("Couloir droite-Lucie","../img/Camera/Couloir_droite/CD_Lucie1.jpg");
    setTexture("Couloir droite-Leonie","../img/Camera/Couloir_droite/CD_Léonie1.jpg");
    setTexture("Couloir gauche","../img/Camera/Couloir_gauche/CG_Vide.jpg");
    setTexture("Couloir gauche-Lucas-1","../img/Camera/Couloir_gauche/CG_Lucas1.jpg");
    setTexture("Couloir gauche-Lucas-2","../img/Camera/Couloir_gauche/CG_Lucas2.jpg");
    setTexture("Couloir gauche-Lucas-position2-1","../img/Camera/Couloir_gauche/CG_Lucas3.jpg");
    setTexture("Couloir gauche-Lucas-position2-2","../img/Camera/Couloir_gauche/CG_Lucas4.jpg");
    setTexture("Couloir gauche-Lucie","../img/Camera/Couloir_gauche/CG_Lucie1.jpg");
    setTexture("Couloir gauche-Leonie","../img/Camera/Couloir_gauche/CG_Léonie1.jpg");
    setTexture("Cuisine Droite","../img/Camera/Cuisine/Cu_Vide.jpg");
    setTexture("Cuisine Droite-Raphael-1","../img/Camera/Cuisine/Cu_Raph1.jpg");
    setTexture("Cuisine Droite-Raphael-2","../img/Camera/Cuisine/Cu_Raph2.jpg");
    setTexture("Cuisine Droite-Raphael-3","../img/Camera/Cuisine/Cu_Raph3.jpg");
    setTexture("Cuisine Droite-Lucie-1","../img/Camera/Cuisine/Cu_Lucie1.jpg");
    setTexture("Cuisine Droite-Lucie-2","../img/Camera/Cuisine/Cu_Lucie2.jpg");
    setTexture("Cuisine Droite-Leonie-1","../img/Camera/Cuisine/Cu_Léonie1.jpg");
    setTexture("Cuisine Droite-Leonie-2","../img/Camera/Cuisine/Cu_Léonie2.jpg");
    setTexture("Cuisine Droite-Raphael-Lucie","../img/Camera/Cuisine/Cu_Lucie-Raph1.jpg");
    setTexture("Cuisine Droite-Raphael-Leonie","../img/Camera/Cuisine/Cu_Léonie-Raph1.jpg");
    setTexture("Escalier","../img/Camera/Escalier/Es_Vide.jpg");
    setTexture("Escalier-Raphael-1","../img/Camera/Escalier/Es_Raph1.jpg");
    setTexture("Escalier-Lucas-1","../img/Camera/Escalier/Es_Lucas1.jpg");
    setTexture("Escalier-Lucie-1","../img/Camera/Escalier/Es_Lucie1.jpg");
    setTexture("Escalier-Leonie-1","../img/Camera/Escalier/Es_Léonie1.jpg");
    setTexture("Escalier-Raphael-2","../img/Camera/Escalier/Es_Raph2.jpg");
    setTexture("Escalier-Lucas-2","../img/Camera/Escalier/Es_Lucas2.jpg");
    setTexture("Escalier-Lucie-2","../img/Camera/Escalier/Es_Lucie2.jpg");
    setTexture("Escalier-Leonie-2","../img/Camera/Escalier/Es_Léonie2.jpg");
    setTexture("67-1","../img/Camera/Escalier/Es_Lucie67-1.jpg");
    setTexture("67-2","../img/Camera/Escalier/Es_Lucie67-2.jpg");
    setTexture("Grille","../img/Camera/Grille/Gr_0-Vide.jpg");
    setTexture("Grille-Raphael","../img/Camera/Grille/Gr_1-Raph.jpg");
    setTexture("Grille-Lucas","../img/Camera/Grille/Gr_1-Lucas.jpg");
    setTexture("Grille-Lucie-Leonie","../img/Camera/Grille/Gr_2-Léonie-Lucie.jpg");
    setTexture("Grille-Raphael-Lucas","../img/Camera/Grille/Gr_2-Lucas-Raph.jpg");
    setTexture("Grille-Lucas-Lucie-Leonie","../img/Camera/Grille/Gr_3-Lucas-Léonie-Lucie.jpg");
    setTexture("Grille-Raphael-Lucie-Leonie","../img/Camera/Grille/Gr_3-Raph-Léonie-Lucie.jpg");
    setTexture("Grille-Raphael-Lucas-Lucie-Leonie","../img/Camera/Grille/Gr_4-Lucas-Raph-Léonie-Lucie.jpg");
    setTexture("Laverie","../img/Camera/Laverie/La_Vide.jpg");
    setTexture("Laverie-Raphael-1","../img/Camera/Laverie/La_Raph1.jpg");
    setTexture("Laverie-Raphael-2","../img/Camera/Laverie/La_Raph2.jpg");
    setTexture("Laverie-Lucie","../img/Camera/Laverie/La_Lucie1.jpg");
    setTexture("Laverie-Leonie","../img/Camera/Laverie/La_Léonie1.jpg");
    setTexture("Laverie-Raphael-Lucie","../img/Camera/Laverie/La_Raph-Lucie1.jpg");
    setTexture("Laverie-Raphael-Leonie","../img/Camera/Laverie/La_Raph-Léonie1.jpg");
    setTexture("Billard","../img/Camera/Billard/Bi_Vide.jpg");
    setTexture("Billard-Lucas-1","../img/Camera/Billard/Bi_Lucas1.jpg");
    setTexture("Billard-Lucas-2","../img/Camera/Billard/Bi_Lucas2.jpg");
    setTexture("Billard-Lucie","../img/Camera/Billard/Bi_Lucie1.jpg");
    setTexture("Billard-Leonie","../img/Camera/Billard/Bi_Léonie1.jpg");
    setTexture("Billard-Lucas-Lucie","../img/Camera/Billard/Bi_Lucas-Lucie1.jpg");
    setTexture("Billard-Lucas-Leonie","../img/Camera/Billard/Bi_Lucas-Léonie1.jpg");
    setTexture("Chambre-R0","../img/Office/Bu R0.jpg");
    setTexture("Chambre-R1","../img/Office/Bu R1.jpg");
    setTexture("Chambre-R2","../img/Office/Bu R2.jpg");
    setTexture("Chambre-R3","../img/Office/Bu R3.jpg");
    setTexture("Chambre-R0-Raphael","../img/Office/Bu RAPH-R0.jpg");
    setTexture("Chambre-R1-Raphael","../img/Office/Bu RAPH-R1.jpg");
    setTexture("Chambre-R2-Raphael","../img/Office/Bu RAPH-R2.jpg");
    setTexture("Chambre-R3-Raphael","../img/Office/Bu RAPH-R3.jpg");
    setTexture("Chambre-R0-Lucas","../img/Office/Bu LUCAS-R0.jpg");
    setTexture("Chambre-R1-Lucas","../img/Office/Bu LUCAS-R1.jpg");
    setTexture("Chambre-R2-Lucas","../img/Office/Bu LUCAS-R2.jpg");
    setTexture("Chambre-R3-Lucas","../img/Office/Bu LUCAS-R3.jpg");
    setTexture("CamHUD","../img/Camera/CAM.png");
    setTexture("Croix","../img/cross.jpg");
    setTexture("singe","../img/singe.png");
    setTexture("rondoudou","../img/rdd.jpg");
}