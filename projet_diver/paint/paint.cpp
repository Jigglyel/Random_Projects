#include<iostream>
#include<array>
#include<cstdlib>
#include<ctime>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<string>
#include<cmath>
#include<vector>
#include<stack>
#include<fstream>
int NC=1280;
int NL=720;


struct action{
    sf::Color couleur;
    sf::Vector2i pos;
};
struct maillon{
    std::vector<action> val;
    maillon* suiv;
};

using pile=maillon*;

pile init_pile()
{
    return nullptr;
}

void empiler(pile& P, std::vector<action> a)
{
    if (P!=nullptr)
    {
        maillon *tier=P;
        P=new maillon;
        P->val=a;
        P->suiv=tier;
    }
    else
    {
        P=new maillon;
        P->val=a;
        P->suiv=nullptr;
    }
}
void supprimer(pile &P)
{
    if(P!=nullptr)
    {
        supprimer(P->suiv);
        delete P;
        P=nullptr;
    }
}
std::vector<action> pop(pile &P)
{
    pile resu=P;
    std::vector<action> resu2=resu->val;
    P=P->suiv;
    delete resu;
    return resu2;
}
std::vector<action> consulte(pile &P)
{
    return P->val;
}


void init (sf::VertexArray & pixels,int NC,int NL)
{
    pixels.setPrimitiveType(sf::Points);
    pixels.resize(NC * NL);
    for (size_t i = 50; i < NL; i++)
    {
        for (size_t j = 0; j < NC; j++)
        {
            pixels[i * NC + j].position = sf::Vector2f(j, i);
            pixels[i * NC + j].color = sf::Color(255,255,255);
        }
    }
}
void convertit(sf::VertexArray & pixels,sf::Vector2i taille_dessin, sf::Vector2i taille_fenetre)
{
    sf::VertexArray new_pixels;
    init(new_pixels,taille_fenetre.x,taille_fenetre.y);
    float x_scale= taille_fenetre.x/(taille_dessin.x*1.f);
    float y_scale= taille_fenetre.y/(taille_dessin.y*1.f);
    std::cout<<x_scale<<" "<<y_scale<<std::endl;
    std::cout<<taille_fenetre.x<<" "<<taille_fenetre.y<<std::endl;
    std::cout<<taille_dessin.x<<" "<<taille_dessin.y<<std::endl;
    for (int i = 0; i < taille_fenetre.y; i++)
    {
        for (int j = 0; j < taille_fenetre.x; j++)
        {
                    if(i*y_scale<taille_dessin.y and j*x_scale<taille_dessin.x)
                        new_pixels[i*taille_fenetre.x+j].color=pixels[static_cast<int>(i / y_scale)*taille_dessin.x + static_cast<int>(j/x_scale)].color;
                    new_pixels[i*taille_fenetre.x+j].position.x=j;
                    new_pixels[i*taille_fenetre.x+j].position.y=i;
        }
    }
    pixels=new_pixels;
}
void efface (sf::VertexArray & pixels,pile &P)
{
    action tache;
    std::vector<action> taches;
    for (size_t i = 50; i < NL; i++)
    {
        for (size_t j = 0; j < NC; j++)
        {
            tache.couleur=pixels[i * NC + j].color;
            tache.pos=sf::Vector2i(pixels[i * NC + j].position);
            if (tache.couleur!=sf::Color::White)
            {
                taches.push_back(tache);
            }  
            pixels[i * NC + j].color = sf::Color(255,255,255);
        }
    }
    empiler(P,taches);
}
void redo(sf::VertexArray &pixels,pile &PActions,pile&Pretour)
{
    if(PActions!=nullptr)
    {
    std::vector<action> taches=pop(PActions);
    std::vector<action> retours;
    action retour;
    for(action tache : taches)
    {
        retour.pos=tache.pos;
        retour.couleur=pixels[tache.pos.y*NC+tache.pos.x].color;
        pixels[tache.pos.y*NC+tache.pos.x].color=tache.couleur;
        retours.push_back(retour);
    }
    empiler(Pretour,retours);
    }
}
void peint_pixel(sf::VertexArray &pixels,int x,int y,int brushSize,sf::Color couleur,std::vector<action>& taches)
{
    action tache;
    for (int dy = -brushSize; dy <= brushSize; ++dy)
        for (int dx = -brushSize; dx <= brushSize; ++dx)
        {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < NC && ny >= 50 && ny < NL and pixels[ny * NC + nx].color!=couleur)
            {
                tache.couleur=pixels[ny * NC + nx].color;
                tache.pos=sf::Vector2i(nx,ny);
                pixels[ny * NC + nx].color = couleur;
                
                taches.push_back(tache);
            }
        }
}
void peint_ligne(sf::VertexArray &pixels,sf::Vector2f curent,sf::Vector2f old,int brushSize,sf::Color couleur,std::vector<action> &taches)
{
    float dx= curent.x-old.x;
    float dy= curent.y-old.y;
    float distance=std::sqrt(dx*dx+dy*dy);
    if(distance==0)
        distance=1;
    float x=old.x, y=old.y;
    for(int i=0 ;i<distance;++i)
    {
        peint_pixel(pixels,x,y,brushSize,couleur,taches);
        x+=dx/distance;
        y+=dy/distance;
    }
}
void sauvegarde(const sf::VertexArray &pixels)
{
    std::cout<<"où voulez vous sauvegarder ?"<<std::endl;
    std::cout<<"->:";
    std::string ch;
    std::cin>>ch;
    std::cout<<"quelle nom ?"<<std::endl;
    std::cout<<"->:";
    std::string nomfic;
    std::cin>>nomfic;
    
    std::ofstream fic;
    fic.open(ch+nomfic);
    if(fic.is_open())
    {
        for(int i=0;i<NC*NL;++i)
        fic<<pixels[i].position.x<<"  "<<pixels[i].position.y<<"  "<<(pixels[i].color.r)<<" "<<(pixels[i].color.g)<<" "<<(pixels[i].color.b)<<std::endl;  
    }
    else
        std::cout<<"Echec d'ouverture du fichier"<<std::endl;
}
void charge(sf::VertexArray &pixels)
{
    std::cout<<"chemin du chargement ?"<<std::endl;
    std::cout<<"->:";
    std::string ch;
    std::cin>>ch;
    std::ifstream fic;
    fic.open(ch);
    if(fic.is_open())
    {
        for(int i=0;i<NC*NL;++i)
        {
            fic>>pixels[i].position.x>>pixels[i].position.y>>pixels[i].color.r>>pixels[i].color.g>>pixels[i].color.b;
        }
    }
    else
        std::cout<<"Echec d'ouverture du fichier"<<std::endl;
}
void screenshot(sf::RenderWindow &window)
{
    sf::Texture texture;
    texture.create(window.getSize().x, window.getSize().y-50);
    texture.update(window,0,50);
    sf::Image image =texture.copyToImage();
    if (image.saveToFile("./capture.png"))
    {
        std::cout << "screenshot saved to " << "./capture" << std::endl;
    }
}
void touche(sf::Event event,sf::VertexArray & pixels,int &brushSize,pile &Back,pile &Forward,bool& full_mode,std::vector<action>& taches,sf::RenderWindow &window)
{
    if (event.key.code==sf::Keyboard::Space)
    {
        if (!taches.empty())
        {
            empiler(Back,taches);
        }

        efface(pixels,Back);
    } 
    else if (event.key.code==sf::Keyboard::Add)
    {
        brushSize++;
    }
    else if (event.key.code==sf::Keyboard::Subtract)
    {
        brushSize--;
    }
    else if (event.key.code==sf::Keyboard::LControl)
    {
        redo(pixels,Back,Forward);
        
    }
    else if (event.key.code==sf::Keyboard::RControl)
    {
        redo(pixels,Forward,Back);
    }
    else if (event.key.code==sf::Keyboard::R)
        full_mode=!full_mode;
    else if(event.key.code==sf::Keyboard::S)
        sauvegarde(pixels);
    else if(event.key.code==sf::Keyboard::C)
        charge(pixels);
    else if(event.key.code==sf::Keyboard::E)
        screenshot(window);
    
}
void remplissage(sf::VertexArray & pixels,sf::Color couleur,sf::Vector2i pos,std::vector<action> &taches)
{
    std::stack<action> P;
    action dou;
    dou.pos.x=pos.x;
    dou.pos.y=pos.y;
    dou.couleur=couleur;
    action redo;
    redo.couleur=pixels[(pos.y)*NC +pos.x].color;
    P.push(dou);
    
    
    while (!P.empty())
    {   dou=P.top();
        P.pop();
        if(dou.pos.x >= 0 && dou.pos.x < NC && dou.pos.y >= 50 && dou.pos.y < NL and pixels[dou.pos.y*NC +dou.pos.x].color==redo.couleur and redo.couleur!=couleur)
        {
            redo.pos.x=dou.pos.x;
            redo.pos.y=dou.pos.y;
            taches.push_back(redo);
            pixels[dou.pos.y*NC +dou.pos.x].color=dou.couleur;
            dou.pos.x=dou.pos.x+1;
            P.push(dou);
            dou.pos.x=dou.pos.x-2;
            P.push(dou);
            dou.pos.x=dou.pos.x+2;
            dou.pos.y=dou.pos.y+1;
            P.push(dou);
            dou.pos.y=dou.pos.y-2;
            P.push(dou);
        }
    }
    
}


void init_constHUD(sf::RenderWindow &window,sf::RectangleShape* &Hud,sf::Texture &back,sf::Texture &forward)
{
    Hud= new sf::RectangleShape[12];
    Hud[0].setFillColor(sf::Color::Black);
    Hud[1].setFillColor(sf::Color::White);
    Hud[2].setFillColor(sf::Color::Blue);
    Hud[3].setFillColor(sf::Color::Red);
    Hud[4].setFillColor(sf::Color::Yellow);
    Hud[5].setFillColor(sf::Color::Green);
    Hud[6].setFillColor(sf::Color::Cyan);
    Hud[7].setFillColor(sf::Color::Magenta);
    Hud[8].setFillColor(sf::Color::Transparent);
    back.loadFromFile("../../assets/back.png");
    forward.loadFromFile("../../assets/forward.png");
    Hud[10].setTexture(&back);
    Hud[11].setTexture(&forward);
    for(int i=0;i<12;++i)
    {
        Hud[i].setSize(sf::Vector2f(30,30));
        Hud[i].setPosition(40*i,10);
    }
}
void DessineHUD(sf::RenderWindow &window,sf::RectangleShape* &Hud,pile& Pback,pile& Pforward)
{
    
    Hud[9].setFillColor(sf::Color(rand()%256,rand()%256,rand()%256));
    if(Pback==nullptr)
    {
        Hud[10].setFillColor(sf::Color(180,180,180));
    }
    else
        Hud[10].setFillColor(sf::Color::White);
    if(Pforward==nullptr)
    {
        Hud[11].setFillColor(sf::Color(180,180,180));
    }
    else
        Hud[11].setFillColor(sf::Color::White);

    for(int i=0;i<12;++i)
        window.draw(Hud[i]);
    
}

void selectColors(sf::RenderWindow &window, sf::Color &couleur,int x,int y,sf::RectangleShape* Hud)
{
    for(int i=0;i<10;++i)
    {
        if(Hud[i].getGlobalBounds().contains(sf::Vector2f(x,y)))
            switch(i)
            {

                case 0:
                    couleur=sf::Color::Black;
                    break;
                case 1:
                    couleur=sf::Color::White;
                    break;
                case 2:
                    couleur=sf::Color::Blue;
                    break;
                case 3:
                    couleur=sf::Color::Red;
                    break;
                case 4:
                    couleur=sf::Color::Yellow;
                    break;
                case 5:
                    couleur=sf::Color::Green;
                    break;
                case 6:
                    couleur=sf::Color::Cyan;
                    break;
                case 7:
                    couleur=sf::Color::Magenta;
                    break;
                case 8:
                    couleur=sf::Color::Transparent;
                    break;
                case 9:
                    couleur=Hud[i].getFillColor();
                    break;
            }
        
    }
}
void selectRedo(sf::RenderWindow &window,int x,int y,sf::RectangleShape* Hud,sf::VertexArray & pixels,pile &Pback,pile & Pforward)
{
    for(int i=10;i<12;++i)
    {
        if(Hud[i].getGlobalBounds().contains(sf::Vector2f(x,y)))
            switch(i)
        {
            case 10:
                redo(pixels,Pback,Pforward);
                break;
            case 11:
                redo(pixels,Pforward,Pback);
                break;
        }
    }
    
}



int main()
{    
    sf::VertexArray pixels(sf::Points,NC*NL);
    sf::Color couleur = sf::Color::Black;
    init(pixels,NC,NL);
    int brushSize = 3;
    sf::RenderWindow window(sf::VideoMode(NC, NL), "SFML window");
    sf::RectangleShape* Hud;
    sf::Vector2f oldPos;
    std::vector<action> taches;
    sf::Texture back_png,forward_png;
    sf::View camera(sf::Vector2f(window.getSize().x/2,window.getSize().y/2),sf::Vector2f(window.getSize().x,window.getSize().y));
    window.setView(camera);
    pile Back =init_pile();
    pile Forward =init_pile();
    bool first_time=true;
    bool full_mode=false;
    bool availiable_release=false;




    //clear et initialise le hud qui doit rester constant
    window.clear(sf::Color::White);
    init_constHUD(window,Hud,back_png,forward_png);
    window.setFramerateLimit(300);
    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Arrow))
        window.setMouseCursor(cursor);
    
        while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type==sf::Event::Resized)
            {
                //convertit(pixels,sf::Vector2i(NC,NL),sf::Vector2i(event.size.width,event.size.height));
                //NC=event.size.width;
                //NL=event.size.height;
            }


            if (event.type==sf::Event::KeyPressed)
            {
                touche(event,pixels,brushSize,Back,Forward,full_mode,taches,window);
                if (full_mode)
                {
                     if (cursor.loadFromSystem(sf::Cursor::Cross))
                            window.setMouseCursor(cursor);
                }
                else
                {
                    if (cursor.loadFromSystem(sf::Cursor::Arrow))
                        window.setMouseCursor(cursor);
                }
            }
        }
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {   
                float x=sf::Mouse::getPosition(window).x;
                float y=sf::Mouse::getPosition(window).y;
                x=window.mapPixelToCoords(sf::Vector2i(x,y)).x;
                y=window.mapPixelToCoords(sf::Vector2i(x,y)).y;
                

                
                if (full_mode)
                {
                    remplissage(pixels,couleur,sf::Vector2i(x,y),taches);
                }
                else
                {
                    if(first_time)
                    {
                        peint_ligne(pixels,sf::Vector2f(x,y),sf::Vector2f(x,y),brushSize,couleur,taches);
                        first_time=false;
                    }
                    else
                        peint_ligne(pixels,sf::Vector2f(x,y),oldPos,brushSize,couleur,taches);
                    oldPos={x,y};
                }
                availiable_release=true;
            }
            else
            if (availiable_release and event.type==sf::Event::MouseButtonReleased)
            {
                float x=sf::Mouse::getPosition(window).x;
                float y=sf::Mouse::getPosition(window).y;
                selectColors(window,couleur,x,y,Hud);
                selectRedo(window,x,y,Hud,pixels,Back,Forward);
                availiable_release=false;
            }
            else
            {
                first_time=true;
                if (!taches.empty())
                {
                    empiler(Back,taches);
                    taches.clear();
                    supprimer(Forward);
                }
                
            }
            
            window.clear(sf::Color::White);
            
            window.draw(pixels);
            DessineHUD(window,Hud,Back,Forward);
            window.display();
        
 
        
    }
    return 0;
}