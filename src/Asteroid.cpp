#include <raylib.h>

#include "Asteroid.hpp"
#include "Globals.hpp"

Asteroid::Asteroid(float x, float y, float w, float h, float rot, int astStage, Texture2D* tex){
    rect.x = x;
    rect.y = y;
    rect.width = w;
    rect.height = h;
    rotation = rot;
    asteroidStage = astStage;
    texture = tex;

    if (GetRandomValue(0, 1) == 1){
        xVel = GetRandomValue(-maxSpeed, -minSpeed);
    }
    else{
        xVel = GetRandomValue(minSpeed, maxSpeed);
    }

    if (GetRandomValue(0, 1) == 1){
        yVel = GetRandomValue(-maxSpeed, -minSpeed);
    }
    else{
        yVel = GetRandomValue(minSpeed, maxSpeed);
    }
}

void Asteroid::Draw(){
    DrawTexturePro(*texture, Rectangle{0, 0, (float)texture->width, (float)texture->height}, Rectangle{rect.x + rect.width / 2 - glob::offset[0], rect.y + rect.height / 2 - glob::offset[1], rect.width, rect.height},
    Vector2{rect.width / 2, rect.height / 2}, rotation, RAYWHITE);
    //DrawRectangle(rect.x, rect.y, rect.width, rect.height, RED);
}

void Asteroid::Update(float& dt){
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
bool Asteroid::GetDead(){ return dead; }
void Asteroid::SetDead(bool d) { dead = d; }