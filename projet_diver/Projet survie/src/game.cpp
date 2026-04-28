#include "game.h"
//charge les textures
void charge(sf::Texture &mec,sf::Texture &bank,sf::Texture &feu,sf::Texture &bullet,sf::Texture &zombie,sf::Texture &etabli,sf::Texture &damage_stat,sf::Texture &rate_stat,sf::Texture &sorcière)
{
    mec.loadFromFile("../../sprites/mec.png");
    feu.loadFromFile("../../sprites/feu_de_camp.png");
    bank.loadFromFile("../../sprites/bank.png");
    bullet.loadFromFile("../../sprites/bullet.png");
    zombie.loadFromFile("../../sprites/zombie.png");
    etabli.loadFromFile("../../sprites/etabli.png");
    damage_stat.loadFromFile("../../sprites/tear_damage_stat.png");
    rate_stat.loadFromFile("../../sprites/tear_rate_stat.png");
    sorcière.loadFromFile("../../sprites/sorciere.png");

}
void init_text_pause(sf::RenderWindow &window,sf::Text &resu,sf::Font &font)
{
    resu.setFillColor(sf::Color::White);
    resu.setPosition(window.getSize().x/2.f,window.getSize().y/2.f);
    resu.setFont(font);
    resu.setString("PAUSE");
}
void dessine(Perso joueur,objet bank,objet feu,objet etabli,sf::RenderWindow &window,cercle_faim cercle_f,int money,std::vector<Bullet> bullets,sf::Texture image_balle,std::vector<Mob>zombies,sf::Texture image_zombie,sf::View &camera,sf::Font font,HUD &rate,HUD &damage,bool debug,std::vector<Bullet>witch_balls)
{
    sf::Sprite joueurImage(joueur.image),bankImage(bank.image),feuImage(feu.image),etabliImage(etabli.image);
    sf::Text text_faim, text_dollar,text_vie;
    text_faim.setPosition(1000,100);
    text_faim.setFillColor(sf::Color::Green);
    text_faim.setString(std::to_string(joueur.faim));
    text_faim.setFont(font);
    text_dollar.setPosition(600,800);
    text_dollar.setFillColor(sf::Color::Yellow);
    text_dollar.setString(std::to_string(money));
    text_dollar.setFont(font);
    text_vie.setPosition(200,100);
    text_vie.setFillColor(sf::Color::Red);
    text_vie.setString(std::to_string(static_cast<int>(joueur.hp)));
    text_vie.setFont(font);
    joueurImage.setPosition(joueur.x-16,joueur.y-16);
    bankImage.setPosition(bank.x-16,bank.y-16);
    feuImage.setPosition(feu.x-17,feu.y-20);
    etabliImage.setPosition(etabli.x-17,etabli.y-16);
    window.clear(sf::Color::Black);
    for (Bullet balle : bullets)
    {
        balle.sprite.setPosition(balle.x-17,balle.y-17);
        window.draw(balle.sprite);
        
    }
    for (Bullet balle : witch_balls)
    {
        balle.sprite.setPosition(balle.x-17,balle.y-17);
        window.draw(balle.sprite);
        
    }
    for (Mob zombie : zombies)
    {
        zombie.hitbox.setOutlineColor(sf::Color::Red);
        if (zombie.ID==0)
        {
            zombie.sprite.setPosition(zombie.x-13,zombie.y-18);
        }
        if (zombie.ID==1)
        {
            zombie.sprite.setPosition(zombie.x,zombie.y);
        }
        
        
        window.draw(zombie.sprite);
        if (debug)
        {
            window.draw(zombie.hitbox);
        }
        
        
        
    }
    joueur.hitbox.setOutlineColor(sf::Color::Red);
    for (size_t i = 0; i < (cercle_f.taille*2+1)*4; i++)
    {
        window.draw(cercle_f.pixels[i]);
    }
    sf::RectangleShape indicator_base=get_indicator_fire(feu,window,camera);
    indicator_base.setTexture(feuImage.getTexture());
    window.draw(bankImage);
    window.draw(etabliImage);
    window.draw(feuImage);
    window.draw(joueurImage);  
    if (debug)
    {
        window.draw(joueur.hitbox);
    }
    window.setView(window.getDefaultView());
    window.draw(indicator_base);
    window.draw(text_vie);
    window.draw(text_faim); 
    window.draw(text_dollar);
    window.draw(damage.rectganle);
    window.draw(rate.rectganle);
    window.draw(damage.text);
    window.draw(rate.text);
    window.setView(camera);
    
}
void init(Perso &joueur, objet &feu,objet &bank,objet &etabli,sf::View &camera,sf::RenderWindow &window,cercle_faim &cercle_f,sf::Texture &TextureBalle,sf::Text &text_pause,weapon &arme,HUD &rate,HUD &damage,sf::Font &neon,sf::Texture &TextureSorcière,sf::Texture &TextureZombie)
{
    joueur.invincible=false;
    joueur.x=300;
    joueur.y=500;
    joueur.hp=20000;
    joueur.faim=100;
    joueur.v=2;
    joueur.hitbox.setSize(sf::Vector2f(7,25));
    camera.setCenter(joueur.x,joueur.y);
    camera.setSize(sf::Vector2f(window.getSize()));
    window.setView(camera);
    cercle_f.taille=100;
    feu.x=300;
    feu.y=500;
    bank.x=500;
    bank.y=300;
    etabli.x=100;
    etabli.y=100;
    feu.x=300;
    feu.y=500;
    bank.x=500;
    bank.y=300;
    etabli.x=100;
    etabli.y=100;
    arme.dégats=10;
    arme.tear_rate=1000;
    arme.id=0;
    if(!neon.loadFromFile("../../font/Jersey15-Regular.ttf"))
        std::cout<<"erreur du chargement de la police";
    rate.rectganle.setSize(sf::Vector2f(50,50));
    damage.rectganle.setSize(sf::Vector2f(50,50));
    rate.rectganle.setPosition(sf::Vector2f(0,600));
    damage.rectganle.setPosition(sf::Vector2f(0,700));
    rate.text.setFont(neon);
    damage.text.setFont(neon);
    rate.text.setPosition(sf::Vector2f(100,625));
    damage.text.setPosition(sf::Vector2f(100,725));
    rate.text.setFillColor(sf::Color::White);
    damage.text.setFillColor(sf::Color::White);
    rate.text.setString(std::to_string(int(arme.tear_rate)));
    damage.text.setString(std::to_string(int(arme.dégats)));
    charge(joueur.image,bank.image,feu.image,TextureBalle,TextureZombie,etabli.image,damage.image,rate.image,TextureSorcière);
    rate.rectganle.setTexture(&rate.image);
    damage.rectganle.setTexture(&damage.image);
    cercle_f.pixels=get_cercle_faim(feu,cercle_f.taille,window);
    init_text_pause(window,text_pause,neon);
}
void dessine_craft(sf::RenderWindow &window,sf::Mouse &souris, bool &z,bool &q, bool &s, bool &d,HUD &rate, HUD &damage)
{
    sf::RectangleShape rectangleH,rectangleB,rectangleD,rectangleG,rectangleSouris;
    window.setView(window.getDefaultView());
    rectangleH.setSize(sf::Vector2f(40,40));
    rectangleB.setSize(sf::Vector2f(40,40));
    rectangleG.setSize(sf::Vector2f(40,40));
    rectangleD.setSize(sf::Vector2f(40,40));
    rectangleB.setFillColor(sf::Color::Red);

    rectangleH.setFillColor(sf::Color::Red);
    // rectangleB.setTexture(sf::Color::Red);
    rectangleG.setTexture(&rate.image);
    rectangleD.setTexture(&damage.image);
    // rectangleH.setTexture(sf::Color::Red);
    rectangleH.setPosition(window.getSize().x/2-rectangleH.getSize().x/2,window.getSize().y/2 -rectangleH.getSize().y/2-40);
    rectangleB.setPosition(window.getSize().x/2-rectangleB.getSize().x/2,window.getSize().y/2 -rectangleB.getSize().y/2+40);
    rectangleG.setPosition(window.getSize().x/2-rectangleG.getSize().x/2-20,window.getSize().y/2 -rectangleG.getSize().y/2);
    rectangleD.setPosition(window.getSize().x/2-rectangleD.getSize().x/2+20,window.getSize().y/2 -rectangleD.getSize().y/2);
    if(rectangleH.getGlobalBounds().contains(souris.getPosition(window).x,souris.getPosition(window).y))
    {
        rectangleH.setFillColor(sf::Color::Green);
        if (souris.isButtonPressed(sf::Mouse::Button::Left))
        {
            z=true;
        }
    }
    if(rectangleB.getGlobalBounds().contains(souris.getPosition(window).x,souris.getPosition(window).y))
    {
        rectangleB.setFillColor(sf::Color::Green);
        if (souris.isButtonPressed(sf::Mouse::Button::Left))
        {
            s=true;
        }
    }
    if(rectangleG.getGlobalBounds().contains(souris.getPosition(window).x,souris.getPosition(window).y))
    {
        rectangleG.setFillColor(sf::Color::Green);
        if (souris.isButtonPressed(sf::Mouse::Button::Left))
        {
            q=true;
        }
    }
    if(rectangleD.getGlobalBounds().contains(souris.getPosition(window).x,souris.getPosition(window).y))
    {
        rectangleD.setFillColor(sf::Color::Green);
        if (souris.isButtonPressed(sf::Mouse::Button::Left))
        {
            d=true;
        }
    }
    if (z)
    {
        rectangleH.setFillColor(sf::Color::Green);
    }
    if (s)
    {
        rectangleB.setFillColor(sf::Color::Green);
    }
    if (q)
    {
        rectangleG.setFillColor(sf::Color::Green);
    }
    if (d)
    {
        rectangleD.setFillColor(sf::Color::Green);
    }
    
    window.clear(sf::Color::Black);
    
    window.draw(rectangleH);
    window.draw(rectangleB);
    window.draw(rectangleG);
    window.draw(rectangleD);
    window.display();
    


    
}
void jeu(Perso joueur ,sf::RenderWindow &window)
{   
    //definition des classes
    objet feu, bank,etabli;
    std::vector<Bullet>bullets,witch_balls;
    Bullet balle;
    std::vector<Mob>mobs;
    Mob zombie; 
    sf::View camera;
    cercle_faim cercle_f;
    sf::Text text_pause ;
    HUD rate_stat,damage_stat;
    sf::Font neon;
    //mise en place des constantes
    float spawn_rate=5000; 
    int money=0;
    weapon arme;
    sf::Texture TextureSorcière ,TextureZombie,TextureBalle;
    bool z=false, q=false, s=false, d=false,debug=false, souris_pressee=false, sprint=false, loose= false, in_crafting=false, pause=false;
    init(joueur,feu,bank,etabli,camera,window,cercle_f,TextureBalle,text_pause,arme,rate_stat,damage_stat,neon,TextureSorcière,TextureZombie);
    int vitesse_de_base=joueur.v;
    dessine(joueur,bank,feu,etabli,window,cercle_f,money,bullets,TextureBalle,mobs,TextureZombie,camera,neon,rate_stat,damage_stat,debug,witch_balls);
    window.display();
    sf::Clock FoodGetClock,FoodLostClock,ZombieSpawnClock,InvicibilityClock,TearRateClock,buyClock,SorcièreSpawnClock;
    while (window.isOpen() and not loose)
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type==sf::Event::Resized)
            {
                camera.setSize(sf::Vector2f(window.getSize()));
                window.setView(camera);
            }






            if (event.type==sf::Event::KeyPressed)
            {
                if (event.key.code==sf::Keyboard::LControl)
                {
                    debug=!debug;
                }
                
                if(event.key.code==sf::Keyboard::Z)
                    z=true;
                if(event.key.code==sf::Keyboard::Q)
                    q=true;
                if(event.key.code==sf::Keyboard::S)
                    s=true;
                if(event.key.code==sf::Keyboard::D)
                    d=true;
                if(event.key.code==sf::Keyboard::LShift)
                {
                    sprint=true;
                }







                if(event.key.code==sf::Keyboard::Enter)
                    if (sqrt(abs(joueur.x-etabli.x)*abs(joueur.x-etabli.x)+abs(joueur.y-etabli.y)*abs(joueur.y-etabli.y))<20)
                    {
                        if (in_crafting)
                        {
                            buyClock.restart();
                            in_crafting=false;
                        }
                        else
                            in_crafting=true;
                    }







                if(event.key.code==sf::Keyboard::P)
                    pause=!pause;
                    

            }



//  check de touches de déplacements et de touche de sprint
            if (event.type==sf::Event::KeyReleased)
            {
                if(event.key.code==sf::Keyboard::Z)
                    z=false;
                if(event.key.code==sf::Keyboard::Q)
                    q=false;
                if(event.key.code==sf::Keyboard::S)
                    s=false;
                if(event.key.code==sf::Keyboard::D)
                    d=false;
                if(event.key.code==sf::Keyboard::LShift)
                {
                    sprint=false;
                }
                    
            }





// check souris
            if(event.type==sf::Event::MouseButtonPressed)
                souris_pressee=true;
            if(event.type==sf::Event::MouseButtonReleased)
                souris_pressee=false;
        }




// boucle de craft
        if (in_crafting)
        {
            sf::Mouse souris;
            dessine_craft(window,souris,z,q,s,d,rate_stat,damage_stat);
            if(q and buyClock.getElapsedTime().asMilliseconds()>20)
            {
                if (money>=100)
                {
                    std::cout<<"j'ai acheté du tear rate"<<std::endl;
                    arme.tear_rate-=300;
                    money-=100;
                }
                else
                    std::cout<<"pas assez d'argent"<<std::endl;
                
                buyClock.restart();
                
                
            }
            if(d and buyClock.getElapsedTime().asMilliseconds()>20)
            {
            if (money>=100)
                {
                    std::cout<<"j'ai acheté des dégats rate"<<std::endl;
                    arme.dégats+=1;
                    money-=100;
                }
                else
                    std::cout<<"pas assez d'argent"<<std::endl;

                buyClock.restart();
            }
            
            z=false;q=false;s=false;d=false;
            rate_stat.text.setString(std::to_string(int(arme.tear_rate)));
            damage_stat.text.setString(std::to_string(int(arme.dégats))); 
        }




//boucle de pause
        else
        if (pause)
        {   window.setView(window.getDefaultView());
            window.draw(text_pause);
            window.display();
            window.setView(camera);
        }
        else
        {

        //uptade de la position du joueur en fonction des touches pressées ou non
        update_pos_joueur(joueur,z,q,s,d,sprint,vitesse_de_base);
        //update de la hitbox et de la cam
        joueur.hitbox.setPosition(joueur.x-7,joueur.y-8);
        camera.setCenter(joueur.x,joueur.y);
        //enlève l'incincibilité du joueur au bout de deux secondes
        if (joueur.invincible)
        {
            if (InvicibilityClock.getElapsedTime().asSeconds()>=2)
            {
                joueur.invincible=false;
            }
            
        }
        // récupère la trajectoire de la balle quand on clic
        if(souris_pressee and TearRateClock.getElapsedTime().asMilliseconds()>arme.tear_rate)
        {
            TearRateClock.restart();
            get_balle(joueur.x,joueur.y,sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y,bullets,camera,window,TextureBalle);
        }
        //donne de la nourriture au joueur dans le cercle de faim
        if (sqrt(abs(joueur.x-feu.x)*abs(joueur.x-feu.x)+abs(joueur.y-feu.y)*abs(joueur.y-feu.y))<cercle_f.taille)
        {
            if (joueur.faim<100 and FoodGetClock.getElapsedTime().asMilliseconds()>100)
            {
                FoodGetClock.restart();
                FoodLostClock.restart();
                joueur.faim++;
            }
        }
        else

        // perte de nourriture
            if (FoodLostClock.getElapsedTime().asMilliseconds()>1000)
            {
                FoodGetClock.restart();
                FoodLostClock.restart();
                joueur.faim--;
                if (sprint)
                {
                    joueur.faim--;
                }
            }
            
            
        // donne de la thune au joueur si il est près de la banque
        if (sqrt(abs(joueur.x-bank.x)*abs(joueur.x-bank.x)+abs(joueur.y-bank.y)*abs(joueur.y-bank.y))<cercle_f.taille)
        {
            money++;
        }
        
        // Clear screen
        window.clear(sf::Color::Black);
 
        // Draw the sprites
        dessine(joueur,bank,feu,etabli,window,cercle_f,money,bullets,TextureBalle,mobs,TextureZombie,camera,neon,rate_stat,damage_stat,debug,witch_balls);
        //update les elements
        update_position_collisions(bullets,mobs,joueur,InvicibilityClock,arme,witch_balls,TextureBalle);
        //regade s'il y a des mobs à faire spawn
        CheckMobSpawn(mobs,joueur,ZombieSpawnClock,SorcièreSpawnClock,spawn_rate,TextureZombie,TextureSorcière);
        if (joueur.hp<=0 or joueur.faim<=0)
        {
            loose=true;
        }
         spawn_rate=spawn_rate-10;
        //(1/std::log(spawn_rate-spawn_rate*0.1));
        window.setView(camera);
        window.display();
        
    }
}
    //quand le joueur perd
    while (window.isOpen() and loose)
    {
        window.setView(window.getDefaultView());
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type==sf::Event::KeyPressed)
            {
                if (event.key.code==sf::Keyboard::R)
                {
                    jeu(joueur,window);
                }
                
            }
            
        }
   
        sf::Text text_défaite;
        text_défaite.setPosition(window.getSize().x/2,window.getSize().y/2);
        text_défaite.setFillColor(sf::Color::Red);
        text_défaite.setString("mort");
        text_défaite.setFont(neon);
        window.clear(sf::Color::Black);
        window.draw(text_défaite);
        window.display();
    }
}







