#pragma once

#include <raylib.h>
#include <vector>

#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Player.hpp"

class AsteroidManager{
public:
    AsteroidManager(int _num, Texture2D* asteroidTex, Texture2D* _destroyTex);
    void Update(float& dt, std::vector<Bullet>& b, Player& p, int& score, ParticleManager& part);
    void Update(float& dt);
    void Draw();
    void Add(const Asteroid& asteroid);
    void SetupNewLevel(int _num);
    void Reset();
    bool CheckClear();
private:
    std::vector<Asteroid> asteroids;
    int numToSpawn;
    Texture2D* asteroidTexture;
    Texture2D* destroyTexture;
    void CheckCollideWithBulletOrPlayer(std::vector<Bullet>& bullets, Player& player, ParticleManager& p);
};