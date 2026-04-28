# include "Calcules.h"
//permet d'obtenir le cercle autour du feu de camp
sf::RectangleShape* get_cercle_faim(objet feu, int taille_cercle,sf::RenderWindow &window)
{
    sf::RectangleShape* cercle_faim_pixels;
    cercle_faim_pixels =new sf::RectangleShape[(taille_cercle*2+1)*4];
    int y;
    int x;
    int delta;
    int c;
    int i=0;
    for (int x=feu.x-taille_cercle;x<=feu.x+taille_cercle;++x)
    {
        c=feu.y*feu.y+(x-feu.x)*(x-feu.x)-taille_cercle*taille_cercle;
        delta= -2*feu.y*(-2)*feu.y-4*c;
        y=(2*feu.y-sqrt(delta))/2.0f;
        cercle_faim_pixels[i].setSize(sf::Vector2f(1,1));
        cercle_faim_pixels[i].setPosition(sf::Vector2f(x,y));
        cercle_faim_pixels[i].setFillColor(sf::Color::Green);
        ++i;
        y=(2*feu.y+sqrt(delta))/2.0f;
        cercle_faim_pixels[i].setSize(sf::Vector2f(1,1));
        cercle_faim_pixels[i].setPosition(sf::Vector2f(x,y));
        cercle_faim_pixels[i].setFillColor(sf::Color::Green);
        ++i;
    }
    
    for (int y=feu.y-taille_cercle;y<=feu.y+taille_cercle;++y)
    {
        c=feu.x*feu.x+(y-feu.y)*(y-feu.y)-taille_cercle*taille_cercle;
        delta= -2*feu.x*(-2)*feu.x-4*c;
        x=(2*feu.x-sqrt(delta))/2.0f;
        cercle_faim_pixels[i].setSize(sf::Vector2f(1,1));
        cercle_faim_pixels[i].setPosition(sf::Vector2f(x,y));
        cercle_faim_pixels[i].setFillColor(sf::Color::Green);
        ++i;
        x=(2*feu.x+sqrt(delta))/2.0f;
        cercle_faim_pixels[i].setSize(sf::Vector2f(1,1));
        cercle_faim_pixels[i].setPosition(sf::Vector2f(x,y));
        cercle_faim_pixels[i].setFillColor(sf::Color::Green);
        ++i;
    }
    return cercle_faim_pixels;
}

// permet d'initialiser la position de la balle
void get_balle(int x_joueur, int y_joueur,int x_souris,int y_souris,std::vector<Bullet> &balles,sf::View &camera,sf::RenderWindow &window,sf::Texture &Texture)
{
    Bullet balle;
    balle.v=5;
    sf::Vector2f coordonées_ecran_souris= window.mapPixelToCoords(sf::Vector2i(x_souris,y_souris),camera);
    x_souris=coordonées_ecran_souris.x;
    y_souris=coordonées_ecran_souris.y;
    float dx = x_souris - x_joueur;
    float dy = y_souris - y_joueur;
    float distance = sqrt(dx*dx + dy*dy);

    balle.vx = balle.v * dx / distance;
    balle.vy = balle.v * dy / distance;

    balle.x = x_joueur;
    balle.y = y_joueur;
    
    balle.count=0;
    balle.hitbox.setSize(sf::Vector2f(7,7));
    balle.sprite.setTexture(Texture);
    balles.push_back(balle);
    
}
void balle_sorcière_accompagnement(Bullet &balle,Perso joueur)
{
    float dx=(joueur.x-balle.x);
    float dy=(joueur.y-balle.y);
    float distance=dy*dy+dx*dx;
    balle.vx+=balle.v *5*dx/distance;
    balle.vy+=balle.v *5*dy/distance;
    balle.x+=balle.vx;
    balle.y+=balle.vy;
    balle.count++;
    balle.hitbox.setPosition(balle.x,balle.y);
    
}
//permet le mouvement de la balle une fois lancée
void balle_accompagnement(Bullet &balle)
{
    
    balle.x+=balle.vx;
    balle.y+=balle.vy;
    balle.count++;
    balle.hitbox.setPosition(balle.x,balle.y);
    
}
//s'occuppe d'update toutes les positions et collisions 

void update_pos_joueur(Perso & joueur, bool z,bool q,bool s,bool d,bool sprint,int vitesse_de_base)
{
    if (sprint)
        {
            joueur.v=vitesse_de_base*2;
        }
        else
            joueur.v=vitesse_de_base;
        
        if (z)
        {
            joueur.y-=joueur.v;
        }
        if (s)
        {
            joueur.y+=joueur.v;
        }
        if (q)
        {
            joueur.x-=joueur.v;
        }
        if (d)
        {
            joueur.x+=joueur.v;
        }
}
sf::RectangleShape get_indicator_fire(objet feu,sf::RenderWindow &window,sf::View &camera)
{
    sf::RectangleShape indicator_base;
    
    //position de l'objet par rapport au coin gauche de la camera
    sf::Vector2i pos_ObjetToCamera=window.mapCoordsToPixel(sf::Vector2f(feu.x,feu.y),camera);
    sf::Vector2i pos_ObjetToCentre;
    camera.setSize(window.getSize().x,window.getSize().y);
    //position de l'objet par rapport au centre de la camera
    pos_ObjetToCentre.y=pos_ObjetToCamera.y-window.getSize().y/2;
    pos_ObjetToCentre.x=pos_ObjetToCamera.x-window.getSize().x/2;
    //distance entre le coin gauche de la cam et l'objet
    float distance_centrecam_objet=sqrt(pos_ObjetToCentre.x*pos_ObjetToCentre.x+pos_ObjetToCentre.y*pos_ObjetToCentre.y);
    //taille de l'indicateur en fonction de la distance
    indicator_base.setSize(sf::Vector2f(30+100/distance_centrecam_objet,30+100/distance_centrecam_objet));
    
    if (pos_ObjetToCentre.x == 0) pos_ObjetToCentre.x = 0.001f;
    if (pos_ObjetToCentre.y == 0) pos_ObjetToCentre.y = 0.001f;
    //coeff directeur de la droite entre le centre de la cam et l'objet
    sf::Vector2f intersection;
    float rapport;
    //calcule du rapport entre la longeur et la largeur de la fenetre
    float rapport_fenetre=static_cast<float>(window.getSize().y)/window.getSize().x;
         rapport =static_cast<float>(pos_ObjetToCentre.y)/static_cast<float>(pos_ObjetToCentre.x);
    float ordonnee_a_lorigine=pos_ObjetToCamera.y-rapport*pos_ObjetToCamera.x;
    //calcul de l'intersection 
    if (rapport>=rapport_fenetre or rapport<=-rapport_fenetre)
    {
        //bas
        if (pos_ObjetToCentre.y>0)
        {
            intersection.y=window.getSize().y-indicator_base.getSize().y;
            intersection.x=(intersection.y-ordonnee_a_lorigine)/rapport;
        }
        //haut
        else
        {
            intersection.y=0;
            intersection.x=(intersection.y-ordonnee_a_lorigine)/rapport;
        }
        
    }
    else
    {
        //droite
        if (pos_ObjetToCentre.x>0)
        {
            intersection.x=window.getSize().x-indicator_base.getSize().x;
            intersection.y=intersection.x*rapport+ordonnee_a_lorigine;
        }
        //gauche
        else
        {
            intersection.x=0;
            intersection.y=intersection.x*rapport+ordonnee_a_lorigine;
        }
    }
    
    indicator_base.setPosition(intersection);
    
    return indicator_base;
}
