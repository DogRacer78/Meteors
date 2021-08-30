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
    Rectangle rect;
    bool dead = false;
    void Reset();
private:
    Texture2D* texture;
    Texture2D* burnerTex;
    float xVel = 0.0f, yVel = 0.0f;
    float rotation;
    float drag = 150.0f;
    float speed = 350.0f;
    bool moving = false;
    Vector2 thrustLocation = {0.0f, 0.0f};
    float engineParticleTimer = 0.0f;
    //can not be too high a number or will not look correct
    float engineParticleTime = 1.0f / 30.0f;
    float rotationSpeed = 220.0f;
    float maxSpeed = 500.0f;
};