#include <raylib.h>
#include <math.h>

#include "Bullet.hpp"
#include "Globals.hpp"

Bullet::Bullet(float x, float y, Texture2D* tex, float rots){
    rect.x = x;
    rect.y = y;
    rect.width = 16;
    rect.height = 16;
    texture = tex;
    rotation = rots;

    xVel = sinf(rotation * DEG2RAD) * 300.0f;
    yVel = -cosf(rotation * DEG2RAD) * 300.0f;
}

void Bullet::Draw(){
    DrawTexturePro(*texture, Rectangle{0, 0, (float)texture->width, (float)texture->height}, rect, Vector2{8, 8}, rotation, RAYWHITE);
}

void Bullet::Update(float& dt){
    
    travelTimer += dt;

    if (travelTimer > travelTime)
        dead = true;

    rect.x += xVel * dt;
    rect.y += yVel * dt;


    if (rect.x > glob::SCREEN_WIDTH)
        rect.x = -rect.width;
    else if (rect.x < -rect.width)
        rect.x = glob::SCREEN_WIDTH;

    if (rect.y > glob::SCREEN_HEIGHT)
        rect.y = -rect.height;
    else if (rect.y < -rect.height)
        rect.y = glob::SCREEN_HEIGHT;
}

//getters and setters
bool Bullet::GetDead(){ return dead; }