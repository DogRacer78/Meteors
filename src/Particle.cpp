#include <raylib.h>

#include "Particle.hpp"
#include "Globals.hpp"

Particle::Particle(float x, float y, float w, float h, Texture2D* tex, float _lifetime){
    rect.x = x;
    rect.y = y;
    rect.width = w;
    rect.height = h;
    texture = tex;
    lifetime = _lifetime;
}

void Particle::Draw(){
    DrawTexturePro(*texture, Rectangle{0, 0, (float)texture->width, (float)texture->height}, Rectangle{rect.x - glob::offset[0], rect.y - glob::offset[1], rect.width, rect.height}, Vector2{0.0f, 0.0f}, 0.0f, RAYWHITE);
}

void Particle::Update(float& dt){
    if (lifetime != 0.0f){
        UpdateLifeTimer(dt);
    }
    rect.x += xVel * dt;
    rect.y += yVel * dt;
}

void Particle::UpdateLifeTimer(float& dt){
    lifetimeTimer += dt;

    if (lifetimeTimer > lifetime)
        dead = true;
}

void Particle::SetVelocity(float x, float y){
    xVel = x;
    yVel = y;
}

//getters and setters
bool Particle::GetDead() { return dead; }