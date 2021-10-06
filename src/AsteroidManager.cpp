#include <raylib.h>
#include <vector>
#include <iostream>

#include "AsteroidManager.hpp"
#include "Asteroid.hpp"
#include "Globals.hpp"
#include "Game.hpp"

AsteroidManager::AsteroidManager(int _num, Texture2D* asteroidTex, Texture2D* _destroyTex, Game* _game){
    asteroidTexture = asteroidTex;
    destroyTexture = _destroyTex;
    game = _game;

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

void AsteroidManager::Update(float& dt, std::vector<Bullet>& b, Player& p, int& score, ParticleManager& part){
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

    CheckCollideWithBulletOrPlayer(b, p, part);
}

void AsteroidManager::SetupNewLevel(int _num){
    numToSpawn = _num;

    float x;
    float y;
    float randRots;

    asteroids.clear();

    for (int i = 0; i < _num; i++){
        if (GetRandomValue(0, -1) == -1){
            x = GetRandomValue(0, 100);
        }
        else{
            x = GetRandomValue(glob::SCREEN_WIDTH - 100, glob::SCREEN_WIDTH);
        }

        if (GetRandomValue(0, -1) == -1){
            y = GetRandomValue(0, 100);
        }
        else{
            y = GetRandomValue(glob::SCREEN_HEIGHT - 100, glob::SCREEN_HEIGHT);
        }

        randRots = GetRandomValue(0, 360);
        Add(Asteroid(x, y, 64, 64, randRots, 3, asteroidTexture));
    }
}

void AsteroidManager::CheckCollideWithBulletOrPlayer(std::vector<Bullet>& bullets, Player& player, ParticleManager& p){
    for (Asteroid& a : asteroids){
        for (Bullet& b : bullets){
            if (CheckCollisionRecs(a.rect, b.rect)){
                if (b.GetDead() || a.GetDead())
                    continue;
                else{
                    b.SetDead(true);
                    a.SetDead(true);
                    for (int i = 0; i < 10; i++){
                        Particle* particle = new Particle(a.rect.x, a.rect.y, 4.0f, 4.0f, destroyTexture, 5.0f);
                        particle->SetVelocity(GetRandomValue(-100, 100), GetRandomValue(-100, 100));
                        p.AddParticles(particle);
                    }
                    PlaySoundMulti(game->explosionFx);
                    game->SetScreenShake(30);
                }
            }
        }

        if (!a.GetDead()){
            if (CheckCollisionRecs(player.rect, a.rect)){
                std::cout << "dead" << std::endl;
                player.dead = true;
                a.SetDead(true);
                for (int i = 0; i < 10; i++){
                    Particle* particle = new Particle(player.rect.x, player.rect.y, 10.0f, 10.0f, destroyTexture, 2.8f);
                    particle->SetVelocity(GetRandomValue(-100, 100), GetRandomValue(-100, 100));
                    p.AddParticles(particle);
                }
                for (int i = 0; i < 10; i++){
                    Particle* particle = new Particle(a.rect.x, a.rect.y, 4.0f, 4.0f, destroyTexture, 5.0f);
                    particle->SetVelocity(GetRandomValue(-100, 100), GetRandomValue(-100, 100));
                    p.AddParticles(particle);
                    }
                PlaySoundMulti(game->explosionFx);
                break;
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

void AsteroidManager::Update(float& dt, int& score){
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
}