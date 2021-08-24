#pragma once

#include <raylib.h>

class Bullet{
public:
    Bullet(float x, float y, Texture2D* tex, float rots);
    void Draw();
    void Update(float& dt);
private:
    Rectangle rect;
    Texture2D* texture;
    float xVel = 0.0f, yVel = 0.0f;
    float travelTime;
    float rotation;
};