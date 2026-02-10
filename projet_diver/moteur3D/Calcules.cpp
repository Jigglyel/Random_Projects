sf::Vector2f SFMLScale(sf::Vector2f P,sf::RenderWindow & window)
{
    P.x=((P.x+1)/2.f)*window.getSize().x;
    P.y=(1-((P.y+1)/2.f))*window.getSize().y;
    return P;
}



sf::Vector2f Projection(sf::Vector3f P)
{
    sf::Vector2f Proj;
    Proj.x=P.x/P.z;
    Proj.y=P.y/P.z;
    return Proj;
}

void drawRectangle(sf::Vector2f P,sf::RenderWindow & window)
{
    int s=5;
    sf::RectangleShape R;
    R.setPosition(P.x-s/2,P.y-s/2);
    R.setFillColor(sf::Color::Green);
    R.setSize(sf::Vector2f(s,s));
    window.draw(R);
}
void drawPoints(std::vector<sf::Vector3f> &points,sf::RenderWindow & window,double dt)
{
    for(sf::Vector3f & point :points)
    {
        drawRectangle(SFMLScale(Projection(point),window),window);
    }
}
float prodscal3D(sf::Vector3f v1,sf::Vector3f v2)
{
    return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}
sf::Vector3f prodvect(sf::Vector3f v1,sf::Vector3f v2)
{
    sf::Vector3f ortho;
    ortho.x=v1.y*v2.z-v1.z*v2.y;
    ortho.y=v1.z*v2.x-v1.x*v2.z;
    ortho.z=v1.x*v2.y-v1.y*v2.x;
    return ortho;
}
sf::Vector3f Normalize(sf::Vector3f v)
{
    float distance=sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
    return sf::Vector3f(v.x/distance,v.y/distance,v.z/distance);
}
void rotate_point(sf::Vector3f &point,float angle,sf::Vector3f sens)
{
        float c=cos(angle);
        float s=sin(angle);
        float x=point.x,y=point.y,z=point.z;
        sens=Normalize(sens);
        float scalaire=prodscal3D(point,sens);
        sf::Vector3f cross=prodvect(sens,point);
        point.x=x*c+(1-c)*scalaire*sens.x+s*cross.x;
        point.y=y*c+(1-c)*scalaire*sens.y+s*cross.y;
        point.z=z*c+(1-c)*scalaire*sens.z+s*cross.z;
}
sf::Vector3f getcenter(sf::Vector3f v1,sf::Vector3f v2) //basgauchedevant et hautdroitederrière
{
    
    return sf::Vector3f((v1.x+v2.x)/2,(v1.y+v2.y)/2,(v1.z+v2.z)/2);
}