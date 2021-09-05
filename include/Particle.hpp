#pragma once

#include <raylib.h>

class Particle{
public:
    Particle(float x, float y, float w, float h, Texture2D* tex, float _lifetime);
    void Draw();
    virtual void Update(float& dt);
    bool GetDead();
    Vector2 SetSinVelocity();
    float xVel, yVel;
    void SetVelocity(float x, float y);
protected:
    Rectangle rect;
    Texture2D* texture;
    float lifetime; //lifetime of the particle in seconds
    float lifetimeTimer = 0.0f;
    bool dead = false;
    void UpdateLifeTimer(float& dt);
};