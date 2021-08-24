#include <raylib.h>
#include <math.h>
#include <iostream>

#include "Player.hpp"
#include "Globals.hpp"
#include "Bullet.hpp"
#include "ParticleManager.hpp"
#include "Particle.hpp"

Player::Player(float x, float y, Texture2D* tex){
    rect.x = x;
    rect.y = y;
    rect.width = 32;
    rect.height = 32;
    texture = tex;
}

void Player::Draw(){
    //DrawTextureEx(*texture, Vector2 { rect.x, rect.y }, 0.0f, 1.0f, RAYWHITE);
    DrawTexturePro(*texture, Rectangle{0, 0, (float)texture->width, (float)texture->height}, rect, Vector2{16.0f, 16.0f}, rotation, RAYWHITE);
}

void Player::Rotate(char dir, float& dt){
    rotation += dir * dt * 170.0f;
}

void Player::AddThrust(float& dt, ParticleManager& p, Texture2D* tex){
    xVel += sinf(rotation * DEG2RAD) * speed * dt;
    yVel += -cosf(rotation * DEG2RAD) * speed * dt;

    // randomly add particles to the back of the ship
    float xMin = (rect.x) - sinf(rotation * DEG2RAD) * 16;
    float yMin = (rect.y) + cosf(rotation * DEG2RAD) * 16;

    float x = GetRandomValue(xMin - 10, xMin + 10);
    float y = GetRandomValue(yMin - 10, yMin + 10);

    if (CheckCollisionPointRec(Vector2{x, y}, rect)){
        x = xMin;
        y = yMin;
    }

    p.AddParticles(Particle(x, y, 4, 4, tex, 0.05));
}

void Player::Shoot(std::vector<Bullet>& bullets, Texture2D* tex){
    bullets.push_back(Bullet(rect.x, rect.y, tex, rotation));
}

void Player::Update(float& dt){

    rect.x += xVel * dt;
    rect.y += yVel * dt;

    if (!moving){
        if (abs(xVel) < drag * dt)
            xVel = 0.0f;
        else{
            if (xVel > 0.0f)
                xVel -= drag * dt;
            else if (xVel < 0.0f)
                xVel += drag * dt;
        }


        if (abs(yVel) < drag * dt)
            yVel = 0.0f;
        else{
            if (yVel > 0.0f)
                yVel -= drag * dt;
            else if (yVel < 0.0f)
                yVel += drag * dt;
        }
    }

    if (rect.x > glob::SCREEN_WIDTH)
        rect.x = -32;
    else if (rect.x < -32)
        rect.x = glob::SCREEN_WIDTH;

    if (rect.y > glob::SCREEN_HEIGHT)
        rect.y = -32;
    else if (rect.y < -32)
        rect.y = glob::SCREEN_HEIGHT;

    //std::cout << rect.x << std::endl;
}

//getters and setters
void Player::SetMoving(bool move) { moving = move; }