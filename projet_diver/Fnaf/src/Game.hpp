#include"Animatronic.hpp"
#include"Button.hpp"
#include"CameraSystem.hpp"

enum State{
    Camera,
    Idle,
    Behind,
    Door
};
class Game
{
private:
    /* data */
public:
    State currentState;
    std::unordered_map<State,std::vector<Button>> activableButtons;
};


