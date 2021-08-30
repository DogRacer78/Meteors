#pragma once

#include <raylib.h>

class Asteroid{
public:
    Asteroid(float x, float y, float w, float h, float rot, int astStage, Texture2D* tex);
    void Draw();
    void Update(float& dt);
    bool GetDead();
    void SetDead(bool d);
    Rectangle rect;
    int asteroidStage;
private:
    Texture2D* texture;
    float xVel = 0.0f, yVel = 0.0f;
    float rotation = 0.0f;
    int minSpeed = 50;
    int maxSpeed = 150;
    // 1 is last 3 is big so 2 is then in the middle
    bool dead = false;
};