#include <raylib.h>

#include "Particle.hpp"
#include "BGParticle.hpp"
#include "Globals.hpp"

BGParticle::BGParticle(float x, float y, float w, float h, Texture2D* tex, float _lifetime) : Particle(x, y, w, h, tex, _lifetime){

}

void BGParticle::Update(float& dt){
    rect.x += xVel * dt;
    rect.y += yVel * dt;

    if (rect.x < -rect.width)
        rect.x = glob::SCREEN_WIDTH;
    else if (rect.x > glob::SCREEN_WIDTH)
        rect.x = -rect.width;

    if (rect.y < -rect.height)
        rect.y = glob::SCREEN_HEIGHT;
    else if (rect.y > glob::SCREEN_HEIGHT)
        rect.y = glob::SCREEN_HEIGHT;
        
}