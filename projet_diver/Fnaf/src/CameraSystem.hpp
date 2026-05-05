#include<vector>
#include<iostream>
#include"Camera.hpp"
class CameraSystem
{
private:
    
public:
    std::vector<Camera> cameras;
    int activeCam;
    void setActiveCamera(int id);

    
};



