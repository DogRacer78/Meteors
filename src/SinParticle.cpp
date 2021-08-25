#include <raylib.h>
#include <math.h>
#include <iostream>

#include "Particle.hpp"
#include "SinParticle.hpp"
#include "Player.hpp"

SinParticle::SinParticle(float x, float y, float w, float h, Texture2D* tex, float _lifetime, float _dir, Player* player) : Particle(x, y, w, h, tex, _lifetime){
    dir = _dir + 90.0f;
    play = player;
}

void SinParticle::Update(float& dt){
    UpdateLifeTimer(dt);

    if (step >= 360){
        step = 0;
    }
    else{
        step += 10;
    }

    Vector2 vel = play->GetVel();
    xVel = 0 + vel.x;
    yVel = sinf(step * DEG2RAD) * dt * 500.0f + vel.y;

    float x = xVel * cosf(DEG2RAD * dir) - yVel * sinf(DEG2RAD * dir);
    float y = xVel * sinf(DEG2RAD * dir) + yVel * cosf(DEG2RAD * dir);

    rect.x += x;
    rect.y += y;
}