#pragma once

#include <raylib.h>

#include "Particle.hpp"
#include "Player.hpp"

// not currently used - might use in the future

class SinParticle : public Particle{
public:
    SinParticle(float x, float y, float w, float h, Texture2D* tex, float _lifetime, float _dir);
    //dir is an angle in degrees
    void Update(float& dt);
private:
    float dir;
    float step = 0.0f;
    float xVel, yVel;
};