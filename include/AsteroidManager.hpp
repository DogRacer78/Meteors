#include <raylib.h>
#include <vector>

#include "Asteroid.hpp"

class AsteroidManager{
public:
    void Update(float& dt);
    void Draw();
private:
    std::vector<Asteroid> asteroids;
};