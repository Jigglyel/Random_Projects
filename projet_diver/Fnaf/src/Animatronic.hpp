
enum Nom{
    Raphael,
    Lucie,
    Lucas,
    Leonie,
    Baptiste,
    Rondoudou
}


class Animatronic
{
private:
    /* data */
public:
    Nom nom;
    int position;
    Animatronic(Nom nom);
    std::unordered_map<int,std::vector<int>> deplacements;
    void (*move)();
    
};

