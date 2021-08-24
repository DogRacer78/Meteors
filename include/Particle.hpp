#pragma once

#include <raylib.h>

class Particle{
public:
    Particle(float x, float y, float w, float h, Texture2D* tex, float _lifetime);
    void Draw();
    void Update(float& dt);
    bool GetDead();
private:
    Rectangle rect;
    Texture2D* texture;
    float lifetime; //lifetime of the particle in seconds
    float xVel = 0.0f, yVel = 0.0f;
    float lifetimeTimer = 0.0f;
    bool dead = false;
};