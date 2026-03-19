#include"Calcules.hpp"
#include"Camera.hpp"


sf::Vector2f SFMLScale(sf::Vector2f P,sf::RenderTarget & window)
{
    P.x=((P.x+1)/2.f)*window.getSize().x;
    P.y=(1-((P.y+1)/2.f))*window.getSize().y;
    return P;
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

float prodscal3D(sf::Vector3f v1,sf::Vector3f v2)
{
    return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}
float prodscal2D(sf::Vector2f v1,sf::Vector2f v2)
{
    return v1.x*v2.x+v1.y*v2.y;
}
sf::Vector3f prodvect3D(sf::Vector3f v1,sf::Vector3f v2)
{
    sf::Vector3f ortho;
    ortho.x=v1.y*v2.z-v1.z*v2.y;
    ortho.y=v1.z*v2.x-v1.x*v2.z;
    ortho.z=v1.x*v2.y-v1.y*v2.x;
    return ortho;
}
float prodvect2D(sf::Vector2f v1,sf::Vector2f v2)
{
    return v1.x*v2.y-v1.y*v2.x;
}
sf::Vector3f Normalize3D(sf::Vector3f v)
{
    float distance=sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
    return sf::Vector3f(v.x/distance,v.y/distance,v.z/distance);
}
sf::Vector2f Normalize2D(sf::Vector2f v)
{
    float distance=sqrt(v.x*v.x+v.y*v.y);
    return sf::Vector2f(v.x/distance,v.y/distance);
}
sf::Vector3f rotate_point(sf::Vector3f point,float angle,sf::Vector3f sens)
{
    angle=(angle*M_PI*2)/360;
        float c=cos(angle);
        float s=sin(angle);
        float x=point.x,y=point.y,z=point.z;
        sens=Normalize3D(sens);
        float scalaire=prodscal3D(point,sens);
        sf::Vector3f cross=prodvect3D(sens,point);
        point.x=x*c+(1-c)*scalaire*sens.x+s*cross.x;
        point.y=y*c+(1-c)*scalaire*sens.y+s*cross.y;
        point.z=z*c+(1-c)*scalaire*sens.z+s*cross.z;
        return point;
}
sf::Vector3f getcenter(sf::Vector3f v1,sf::Vector3f v2) //basgauchedevant et hautdroitederrière
{
    
    return sf::Vector3f((v1.x+v2.x)/2,(v1.y+v2.y)/2,(v1.z+v2.z)/2);
}

void draw_line(sf::Vector2f p1,sf::Vector2f p2,sf::RenderTarget& target)
{
    sf::VertexArray line(sf::PrimitiveType::Lines,2);
    
    line[0].position=p1;
    line[1].position=p2;
    line[0].color=sf::Color::Green;
    line[1].color=sf::Color::Green;  
    target.draw(line);
}

float getangle(sf::Vector2f v1,sf::Vector2f v2)
{
    v1=Normalize2D(v1);
    v2=Normalize2D(v2);
    float dot=prodscal2D(v1,v2);
    float cross=prodvect2D(v1,v2);
    return atan2(cross,dot);
}

bool isint(std::string str)
{
    if (str.empty())
    {
        return false;
    }

    for(char c : str)
    {
        if (!isdigit(c))
        {
           return false;
        }
        
    }
    return true;
    
}
std::vector<std::string> split(std::string s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}

sf::Vector3f near_projection(const sf::Vector3f &A,const sf::Vector3f &B,plan &P)
{
    float t=(P.D-prodscal3D(P.N,A))/prodscal3D(P.N,B-A);
    return A + t * (B - A);
}

void affiche_couleur(sf::Color couleur)
{
    std::cout<<int(couleur.r)<<" "<<int(couleur.g)<<" "<<int(couleur.b)<<std::endl;
}

