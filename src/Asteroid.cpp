#include <raylib.h>

#include "Asteroid.hpp"

Asteroid::Asteroid(float x, float y, float w, float h, Texture2D* tex){
    rect.x = x;
    rect.y = y;
    rect.width = w;
    rect.height = h;
    texture = tex;
}

void Asteroid::Draw(){
    DrawTexturePro(*texture, Rectangle{0, 0, (float)texture->width, (float)texture->height}, rect, Vector2{0, 0}, 0.0f, RAYWHITE);
}