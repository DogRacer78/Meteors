#pragma once

#include <raylib.h>
#include <vector>

#include "Bullet.hpp"
#include "ParticleManager.hpp"
#include "Particle.hpp"

class ParticleManager;

class Player{
public:
    Player(float x, float y, Texture2D* tex, Texture2D* _burnerTex);
    void Draw();
    void Rotate(char dir, float& dt);
    void AddThrust(float& dt, ParticleManager& p, Texture2D* tex);
    void Update(float& dt);
    void Shoot(std::vector<Bullet>& bullets, Texture2D* tex);
    void SetMoving(bool move);
    Vector2 GetVel();
private:
    Rectangle rect;
    Texture2D* texture;
    Texture2D* burnerTex;
    float xVel = 0.0f, yVel = 0.0f;
    float rotation;
    float drag = 150.0f;
    float speed = 300.0f;
    bool moving = false;
    Vector2 thrustLocation = {0.0f, 0.0f};
    float engineParticleTimer = 0.0f;
    float engineParticleTime = 0.01f;
};