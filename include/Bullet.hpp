#pragma once

#include <raylib.h>

class Bullet{
public:
    Bullet(float x, float y, Texture2D* tex, float rots);
    void Draw();
    void Update(float& dt);
    bool GetDead();
    void SetDead(bool d);
    Rectangle rect;
private:
    Texture2D* texture;
    float xVel = 0.0f, yVel = 0.0f;
    float travelTime = 2.0f;
    float travelTimer = 0.0f;
    float rotation;
    bool dead = false;
};