#include <raylib.h>
#include <vector>
#include <iostream>

#include "AsteroidManager.hpp"
#include "Asteroid.hpp"
#include "Globals.hpp"

AsteroidManager::AsteroidManager(int _num, Texture2D* asteroidTex){
    asteroidTexture = asteroidTex;

    SetupNewLevel(_num);
}

void AsteroidManager::Draw(){
    for (Asteroid& a : asteroids){
        a.Draw();
    }
}

void AsteroidManager::Add(const Asteroid& asteroid){
    asteroids.push_back(asteroid);
}

void AsteroidManager::Update(float& dt, std::vector<Bullet>& b, Player& p, int& score){
    for (int i = 0; i < asteroids.size(); i++){
        if (!asteroids[i].GetDead())
            asteroids[i].Update(dt);
        else{
            if (asteroids[i].asteroidStage == 3){
                Add(Asteroid(asteroids[i].rect.x, asteroids[i].rect.y, 32, 32, GetRandomValue(0, 360), 2, asteroidTexture));
                Add(Asteroid(asteroids[i].rect.x, asteroids[i].rect.y, 32, 32, GetRandomValue(0, 360), 2, asteroidTexture));
                score += 50;
            }
            else if (asteroids[i].asteroidStage == 2){
                Add(Asteroid(asteroids[i].rect.x, asteroids[i].rect.y, 24, 24, GetRandomValue(0, 360), 1, asteroidTexture));
                Add(Asteroid(asteroids[i].rect.x, asteroids[i].rect.y, 24, 24, GetRandomValue(0, 360), 1, asteroidTexture));
                score += 30;
            }
            else{
                score += 100;
            }

            asteroids.erase(asteroids.begin() + i);
            i--;
        }
    }

    CheckCollideWithBulletOrPlayer(b, p);
}

void AsteroidManager::SetupNewLevel(int _num){
    numToSpawn = _num;

    float x;
    float y;
    float randRots;

    asteroids.clear();

    for (int i = 0; i < _num; i++){
        x = GetRandomValue(0, glob::SCREEN_WIDTH);
        y = GetRandomValue(0, glob::SCREEN_HEIGHT);
        randRots = GetRandomValue(0, 360);
        Add(Asteroid(x, y, 64, 64, randRots, 3, asteroidTexture));
    }
}

void AsteroidManager::CheckCollideWithBulletOrPlayer(std::vector<Bullet>& bullets, Player& player){
    for (Asteroid& a : asteroids){
        for (Bullet& b : bullets){
            if (CheckCollisionRecs(a.rect, b.rect)){
                if (b.GetDead() || a.GetDead())
                    continue;
                else{
                    b.SetDead(true);
                    a.SetDead(true);
                }
            }
        }

        if (!a.GetDead()){
            if (CheckCollisionRecs(player.rect, a.rect)){
                std::cout << "dead" << std::endl;
                player.dead = true;
            }
        }
    }
}

void AsteroidManager::Reset(){ 
    asteroids.clear();
}

bool AsteroidManager::CheckClear(){ 
    if (asteroids.size() == 0)
        return true;
    else
        return false;
}