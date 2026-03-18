#include"3D_Engine.hpp"

void input(Camera & camera)
{
    float angleXz;
    float angleYz;
    sf::Keyboard::Key Forward,Backward,Left,Right,NormalAttack,UP,Down,SwitchMode;
            Forward=sf::Keyboard::Z;
            Backward=sf::Keyboard::S;
            Left=sf::Keyboard::Q;
            Right=sf::Keyboard::D;
            UP=sf::Keyboard::Space;
            Down=sf::Keyboard::LControl;
            SwitchMode=sf::Keyboard::R;

    if(sf::Keyboard::isKeyPressed(SwitchMode))
        camera.mode_survie=!camera.mode_survie;

    if (!camera.mode_survie)
    {

        camera.velocity={0,0,0};
        if(sf::Keyboard::isKeyPressed(Forward))
        {
            angleXz=(camera.offsetX*2*M_PI/360);
            angleYz=(camera.offsetY*2*M_PI/360);
            camera.velocity+=sf::Vector3f(sin(angleXz)*cos(angleYz),-sin(angleYz),cos(angleXz)*cos(angleYz))*camera.speed;
        }
        if(sf::Keyboard::isKeyPressed(Backward))
        {
            angleXz=((camera.offsetX+180)*2*M_PI/360);
            camera.velocity+=sf::Vector3f(sin(angleXz)*camera.speed,0,cos(angleXz)*camera.speed);
        }
        if(sf::Keyboard::isKeyPressed(Right))
        {
            angleXz=((camera.offsetX+90)*2*M_PI/360);
            camera.velocity+=sf::Vector3f(sin(angleXz)*camera.speed,0,cos(angleXz)*camera.speed);
        }
        if(sf::Keyboard::isKeyPressed(Left))
        {
            angleXz=((camera.offsetX-90)*2*M_PI/360);
            camera.velocity+=sf::Vector3f(sin(angleXz)*camera.speed,0,cos(angleXz)*camera.speed);
        }
        if(sf::Keyboard::isKeyPressed(UP))
        {
            camera.velocity+=sf::Vector3f(0,camera.speed,0);
        }
            if(sf::Keyboard::isKeyPressed(Down))
        {
            camera.velocity+=sf::Vector3f(0,-camera.speed,0);
        }
    }
    else
    {
        camera.velocity.x=0;
        camera.velocity.z=0;
        if(sf::Keyboard::isKeyPressed(Forward))
        {
            angleXz=(camera.offsetX*2*M_PI/360);
            camera.velocity+=sf::Vector3f(sin(angleXz)*camera.speed,0,cos(angleXz)*camera.speed);
        }
        if(sf::Keyboard::isKeyPressed(Backward))
        {
            angleXz=((camera.offsetX+180)*2*M_PI/360);
            camera.velocity+=sf::Vector3f(sin(angleXz)*camera.speed,0,cos(angleXz)*camera.speed);
        }
        if(sf::Keyboard::isKeyPressed(Right))
        {
            angleXz=((camera.offsetX+90)*2*M_PI/360);
            camera.velocity+=sf::Vector3f(sin(angleXz)*camera.speed,0,cos(angleXz)*camera.speed);
        }
        if(sf::Keyboard::isKeyPressed(Left))
        {
            angleXz=((camera.offsetX-90)*2*M_PI/360);
            camera.velocity+=sf::Vector3f(sin(angleXz)*camera.speed,0,cos(angleXz)*camera.speed);
        }
        if(sf::Keyboard::isKeyPressed(UP) and !camera.in_air)
        {
            camera.velocity=sf::Vector3f(0,7,0);
            camera.in_air=true;
        }
    }
    
   
    // if(sf::Keyboard::isKeyPressed(Down))
    // {
    //     camera.velocity=sf::Vector3f(0,-camera.speed,0);
    // }
}



int main()
{




    // Objet3D Tournevis("../tournevis.obj");
    Objet3D Bastion("../Assets/Model3D/Bastion");
    Objet3D Castle("../Assets/Model3D/Peach_Castle");
      Objet3D zelda("../Assets/Model3D/links_awakening_64");
      Objet3D turevoi("../Assets/Model3D/Voiture");
    Objet3D road("../Assets/Model3D/RR64");
     Objet3D link("../Assets/Model3D/Link Adult");
    // // Objet3D Minecastle("../Assets/Model3D/Minecraft_castle");
    // Objet3D mcplains("../Assets/Model3D/mcPlains");

    Objet3D cassidy("../Assets/Model3D/low_poly_mccree");

    Objet3D amelie("../Assets/Model3D/amelie");
    Objet3D TPZ("../Assets/Model3D/TPzelda");
    // Objet3D escalier("../Assets/Model3D/escalierColimacon.obj");
    // Bastion.position={50,32,60};
    // escalier.position={20,50,62};
    // Objet3D sonique("../Assets/Model3D/sonique.obj");
    // Objet3D Evoli("../Assets/Model3D/Evoli.obj");
    // Objet3D pichu("../Assets/Model3D/Pichu.obj");
    // Objet3D gardien("../Assets/Model3D/Guardian.obj");
     Objet3D Jiggliano("../Assets/Model3D/Jiggliano");
    
    // Objet3D Monkey("../Assets/Model3D/Monkey.obj");
    // Objet3D Mario("../Assets/Model3D/Mario.obj");
    // Objet3D scary_face("../Assets/Model3D/scary-face.obj");
    // Jiggliano.position={0,0,0};
    // Evoli.position={-100,40,25};
    // pichu.position={-150,40,25};
    // gardien.position={0,0,0};
    // Jigglypuff.size=0.05;
    // Mario.position={12,45,78};
    // scary_face.position={-50,0,43};














    float angle=0;
    sf::Clock Time;

    sf::RenderWindow window(sf::VideoMode(950, 950), "SFML window");
    
    float MouseSensivity=0.25;


    Camera camera;
    std::vector<Light>lights;
    lights.push_back({LightType::Directional,{0,0,1},255});
    camera.speed=1;
    turevoi.position={200,20,10};
    cassidy.position={2,0,1};
    bool pause=false;
    window.setFramerateLimit(60);
    sf::Vector2i oldPos=sf::Mouse::getPosition(window);
    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::P:
                        pause=!pause;
                        break;
                    case sf::Keyboard::Add:
                        camera.fov+=0.01;
                        break;
                    case sf::Keyboard::Subtract:
                        camera.fov-=0.01;
                        if (camera.fov<0)
                        {
                            camera.fov=0;
                        }
                        
                        break;
                    case sf::Keyboard::Left:
                        cassidy.RotationAngleX-=5;
                        break;
                    case sf::Keyboard::Right:
                        cassidy.RotationAngleX+=5;
                        break;
                    case sf::Keyboard::M:
                        std::cout<<"indiquez la vitesse de la caméra : "<<std::endl;
                        std::cin>>camera.speed;
                        break;
                    }
                    
                    
                case sf::Event::MouseMoved:
                if (!pause)         
                {   
                    sf::Mouse souris;
                    
                    
                    camera.offsetX+= (sf::Mouse::getPosition(window).x-oldPos.x)*MouseSensivity;
                    camera.offsetY+=(sf::Mouse::getPosition(window).y-oldPos.y)*MouseSensivity;

                    if(Time.getElapsedTime().asSeconds()>0.05)
                    {
                        souris.setPosition(window.getPosition()+sf::Vector2i(window.getSize().x/2,window.getSize().y/2));
                        Time.restart();
                    }
                    
                    oldPos=sf::Mouse::getPosition(window);

                    if (camera.offsetX>=360 or camera.offsetX<=-360)
                    {
                        camera.offsetX=0;
                    }
                    
                    if (camera.offsetY>90)
                    {
                        camera.offsetY=90;
                    }
                    if (camera.offsetY<-90)
                    {
                        camera.offsetY=-90;
                    }

                    
                        
                    break; 
                }
                    
                
            }
        }


        input(camera);
        camera.apply_forces();
        camera.move();
        camera.Check_collisions();

        window.clear(sf::Color::Black);
        
        Cube cube1(5,{10,5,8});
        Cube cube2(3,{8,7,3});
        Cube cube3(6,{9,12,2});       
        amelie.size=0.005;
        amelie.position={100,0,60};
        amelie.RotationAngleX=-70;
        Castle.RotationAngleY=-90;
        Jiggliano.size=3;
        TPZ.RotationAngleX+=30;
        TPZ.RotationAngleY+=2;
        Jiggliano.draw(window, camera,lights);
        window.display();

    }
}

