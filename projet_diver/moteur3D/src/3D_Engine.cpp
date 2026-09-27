#include"3D_Engine.hpp"


//Main of my 3D self Made Engine, with the only help of the SFML library


//first there is the input for the camera movements that require multiple buttons pressed at the same time
void input(Camera & camera,Objet3D* &selectedModel)
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
    // flying camera
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
    //grounded camera
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
    
        if (selectedModel!=nullptr)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                {
                    selectedModel->transformation.RotationAngleX+=0.5;
                }
                else
                {
                    selectedModel->transformation.position.x+=0.05;
                }
            }
            else
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    {
                        selectedModel->transformation.RotationAngleY+=0.5;
                    }
                    else
                    {
                        selectedModel->transformation.position.y+=0.05;
                    }
                }
                else
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                        {
                            selectedModel->transformation.RotationAngleZ+=0.5;
                        }
                        else
                        {
                            selectedModel->transformation.position.z+=0.05;
                        }
                    }
                    else
                    {
                        selectedModel->transformation.size+=0.05;
                    }
                }
            }
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (selectedModel!=nullptr)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                {
                    selectedModel->transformation.RotationAngleX-=0.5;
                }
                else
                {
                    selectedModel->transformation.position.x-=0.05;
                }
            }
            else
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    {
                        selectedModel->transformation.RotationAngleY-=0.5;
                    }
                    else
                    {
                        selectedModel->transformation.position.y-=0.05;
                    }
                }
                else
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                        {
                            selectedModel->transformation.RotationAngleZ-=0.5;
                        }
                        else
                        {
                            selectedModel->transformation.position.z-=0.05;
                        }
                    }
                    else
                    {
                        selectedModel->transformation.size-=0.05;
                    }
                }
            }
        }
    }
}



int main()
{

    MatManager matManager;
    sf::Clock Time;
    //setting window and variables
    sf::RenderWindow window(sf::VideoMode(950, 950), "SFML window");
    
    float MouseSensivity=0.25;
    Camera camera;
    camera.speed=0.2;
    bool pause=false;
    Objet3D* selectedModel=nullptr;
    Renderer renderer(matManager);
    window.setFramerateLimit(60);
    sf::Mouse::setPosition(window.getPosition()+sf::Vector2i(window.getSize().x/2,window.getSize().y/2));
    sf::Vector2i oldPos=sf::Mouse::getPosition(window);
    std::vector<Light*>globalLights;
    globalLights.push_back(new Directional{{3,-1.3,-0.8},{255,255,255}});
    std::vector<Objet3D*>models;
    std::string path="";
    // Poll event of miscellanios which doesn't require multiple button pressed at the same time
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
                    case sf::Keyboard::C:
                        camera.lights=!camera.lights;
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
                    case sf::Keyboard::M:
                        std::cout<<"indiquez la vitesse de la caméra : "<<std::endl;
                        std::cin>>camera.speed;
                        break;

                    case sf::Keyboard::F:
                        path="";
                        std::cout<<"indiquez le nom du fichier obj à charger (sans le .obj) : "<<std::endl;
                        std::cin>>path;
                        path="../Assets/Model3D/"+path;
                        models.push_back(new Objet3D(path,matManager));
                        renderer.getTriangles(*models.back());
                        break;
                    case sf::Keyboard::G:
                        path="";
                        std::cout<<"indiquez le nom du fichier obj à détruire (sans le .obj) : "<<std::endl;
                        std::cin>>path;
                        renderer.removeMesh(path);
                        break;

                    case sf::Keyboard::Numpad0:
                        camera.position={0,0,0};
                        break;
                    case sf::Keyboard::L:
                        static_cast<Directional*>(globalLights[0])->couleur.r=rand()%255;
                        static_cast<Directional*>(globalLights[0])->couleur.g=rand()%255;
                        static_cast<Directional*>(globalLights[0])->couleur.b=rand()%255;
                        break;
                    case sf::Keyboard::Delete:

                       auto it = std::find(models.begin(), models.end(), selectedModel);

                        if (it != models.end())
                        {
                            models.erase(it);
                            renderer.removeMesh(selectedModel->getNom());
                            delete selectedModel;
                            selectedModel = nullptr;
                        }

                        break;
                    }
                // calculate the parcoured distance between two frame and then replace the mouse cursor at the center of the window
                case sf::Event::MouseMoved:
                    if (!pause)         
                    {   
                        
                        
                        
                        camera.offsetX+= (sf::Mouse::getPosition(window).x-oldPos.x)*MouseSensivity;
                        camera.offsetY+=(sf::Mouse::getPosition(window).y-oldPos.y)*MouseSensivity;
                        
                        if(Time.getElapsedTime().asSeconds()>0.05 and sf::Mouse::getPosition().x-window.getPosition().x>0 and sf::Mouse::getPosition().x-window.getPosition().x<window.getSize().x )
                        {
                            sf::Mouse::setPosition(window.getPosition()+sf::Vector2i(window.getSize().x/2,window.getSize().y/2));
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

                        
                            
                        
                    }
                    break; 
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    selectedModel = nullptr;
                }
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    for(Objet3D* &model : models)
                    {
                        sf::Vector3f pos = model->getTransfo()->position;
                        float size = model->getTransfo()->size;
                        sf::Vector3f topLeftNear=sf::Vector3f{model->left,model->top,model->near}*size+pos;
                        sf::Vector3f topRightNear=sf::Vector3f{model->right,model->top,model->near}*size+pos;
                        sf::Vector3f bottomLeftNear=sf::Vector3f{model->left,model->bottom,model->near}*size+pos;
                        sf::Vector3f bottomRightNear=sf::Vector3f{model->right,model->bottom,model->near}*size+pos;

                        sf::Vector3f topLeftFar=sf::Vector3f{model->left,model->top,model->far}*size+pos;
                        sf::Vector3f topRightFar=sf::Vector3f{model->right,model->top,model->far}*size+pos;
                        sf::Vector3f bottomLeftFar=sf::Vector3f{model->left,model->bottom,model->far}*size+pos;
                        sf::Vector3f bottomRightFar=sf::Vector3f{model->right,model->bottom,model->far}*size+pos;

                        topLeftNear=camera.switch_base(topLeftNear);
                        topRightNear=camera.switch_base(topRightNear);
                        bottomLeftNear=camera.switch_base(bottomLeftNear);
                        bottomRightNear=camera.switch_base(bottomRightNear);
                        topLeftFar=camera.switch_base(topLeftFar);
                        topRightFar=camera.switch_base(topRightFar);
                        bottomLeftFar=camera.switch_base(bottomLeftFar);
                        bottomRightFar=camera.switch_base(bottomRightFar);

                        float minX=std::min({topLeftNear.x,topRightNear.x,bottomLeftNear.x,bottomRightNear.x,topLeftFar.x,topRightFar.x,bottomLeftFar.x,bottomRightFar.x});
                        float maxX=std::max({topLeftNear.x,topRightNear.x,bottomLeftNear.x,bottomRightNear.x,topLeftFar.x,topRightFar.x,bottomLeftFar.x,bottomRightFar.x});
                        float minY=std::min({topLeftNear.y,topRightNear.y,bottomLeftNear.y,bottomRightNear.y,topLeftFar.y,topRightFar.y,bottomLeftFar.y,bottomRightFar.y});
                        float maxY=std::max({topLeftNear.y,topRightNear.y,bottomLeftNear.y,bottomRightNear.y,topLeftFar.y,topRightFar.y,bottomLeftFar.y,bottomRightFar.y});
                        float maxZ=std::max({topLeftNear.z,topRightNear.z,bottomLeftNear.z,bottomRightNear.z,topLeftFar.z,topRightFar.z,bottomLeftFar.z,bottomRightFar.z});
                        if ((maxX)>0 and (minX)<0 and (maxY)>0 and (minY)<0 and (maxZ)>0)
                        { 
                            selectedModel = model;
                            std::cout<<"model selected : "<<selectedModel->getNom()<<std::endl;
                            break;
                        }
                    }
                }
                break;
            }
        }

        //self explanatory
        input(camera,selectedModel);
        camera.apply_forces();
        camera.move();
        camera.Check_collisions();
        window.clear(sf::Color::Black);
        if(selectedModel!=nullptr)
            renderer.drawHitbox(selectedModel,camera,window);
        renderer.draw(window,camera,globalLights);
        
        
        
        

        window.display(); 

    }
}

