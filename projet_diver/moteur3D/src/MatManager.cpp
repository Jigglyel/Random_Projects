#include "MatManager.hpp"

void MatManager::setMaterieau(std::string &nomMat,matérieau &mat,std::string &nomModel)
{
    Map[nomModel+":"+nomMat]=mat; 
}

matérieau* MatManager::getMaterieau(std::string &nomMat,std::string &nomModel)
{
    
    
    return &Map[nomModel+":"+nomMat];
}

