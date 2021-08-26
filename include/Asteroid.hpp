#pragma once

#include <raylib.h>

class Asteroid{
public:
    Asteroid(float x, float y, float w, float h, Texture2D* tex);
    void Draw();
    void Update(float& dt);
private:
    Texture2D* texture;
    Rectangle rect;
    float xVel = 0.0f, yVel = 0.0f;
};