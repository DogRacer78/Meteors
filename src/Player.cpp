#include <raylib.h>
#include <math.h>
#include <iostream>

#include "Player.hpp"
#include "Globals.hpp"
#include "Bullet.hpp"
#include "ParticleManager.hpp"
#include "Particle.hpp"
#include "SinParticle.hpp"

Player::Player(float x, float y, Texture2D* tex, Texture2D* _burnerTex){
    rect.x = x;
    rect.y = y;
    rect.width = 32;
    rect.height = 32;
    texture = tex;
    burnerTex = _burnerTex;
    lives = 3;
}

void Player::Draw(){
    //DrawTextureEx(*texture, Vector2 { rect.x, rect.y }, 0.0f, 1.0f, RAYWHITE);
    DrawTexturePro(*texture, Rectangle{0, 0, (float)texture->width, (float)texture->height}, Rectangle{rect.x + 16, rect.y + 16, rect.width, rect.height}, Vector2{16.0f, 16.0f}, rotation, RAYWHITE);
    //DrawRectangle(rect.x, rect.y, rect.width, rect.height, RED);

    if (moving)
        DrawTexturePro(*burnerTex, Rectangle{0, 0, (float)burnerTex->width, (float)burnerTex->height}, Rectangle{thrustLocation.x + 16, thrustLocation.y + 16, 32, 32}, Vector2{16, -16}, rotation, RAYWHITE);
}

void Player::Rotate(char dir, float& dt){
    rotation += dir * dt * rotationSpeed;
}

void Player::AddThrust(float& dt, ParticleManager& p, Texture2D* tex){
    engineParticleTimer += dt;

    xVel += sinf(rotation * DEG2RAD) * speed * dt;
    yVel += -cosf(rotation * DEG2RAD) * speed * dt;

    thrustLocation.x = (rect.x) - sinf(rotation * DEG2RAD);
    thrustLocation.y = (rect.y) + cosf(rotation * DEG2RAD);

    if (engineParticleTimer > engineParticleTime){
        float xMin = (rect.x + 16) - sinf(rotation * DEG2RAD) * 16;
        float yMin = (rect.y + 16) + cosf(rotation * DEG2RAD) * 16;

        for (int i = 0; i < 15; i++){
            float x = GetRandomValue(xMin - 10, xMin + 10);
            float y = GetRandomValue(yMin - 10, yMin + 10);
            p.AddParticles(new Particle(x, y, 4, 4, tex, 0.1f));
        }
        
        engineParticleTimer = 0.0f;
    }
}

void Player::Shoot(std::vector<Bullet>& bullets, Texture2D* tex){
    bullets.push_back(Bullet(rect.x + 16, rect.y + 16, tex, rotation));
}

void Player::Update(float& dt){

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

    std::cout << xVel << std::endl;

    if (abs(xVel) > maxSpeed){
        if (xVel > 0){
            //std::cout << maxSpeed * dt << std::endl;
            xVel = maxSpeed;
        }
        else if (xVel < 0){
            xVel = -maxSpeed;
        }
    }

    if (abs(yVel) > maxSpeed){
        if (yVel > 0){
            //std::cout << maxSpeed * dt << std::endl;
            yVel = maxSpeed;
        }
        else if (yVel < 0){
            yVel = -maxSpeed;
        }
    }

    rect.x += xVel * dt;
    rect.y += yVel * dt;

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

void Player::UnDead(){ 
    dead = false;
}

//getters and setters
void Player::SetMoving(bool move) { moving = move; }
Vector2 Player::GetVel() { return Vector2{xVel, yVel}; };