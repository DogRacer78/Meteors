#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include "Bullet.hpp"
#include "Player.hpp"
#include "Globals.hpp"
#include "Particle.hpp"
#include "ParticleManager.hpp"
#include "SinParticle.hpp"
#include "Asteroid.hpp"
#include "AsteroidManager.hpp"

class Game{
public:
    enum GameState : unsigned char { main_game, start, death, load_new, loading_screen };
    Game();
    void MainGame();
    void StartScreen();
    void StateSelect();
    void DeathScreen();
    void LoadNew();
    void LoadingState();
private:
    GameState state;
    Texture2D playerTex;
    Texture2D laserTex;
    Texture2D engineParticle;
    Texture2D burnerTex;
    Texture2D asteroidTex;

    Player* player;
    ParticleManager* pManager;
    AsteroidManager* asteroidManager;
    std::vector<Bullet> bullets;
    int score = 0;
    float dt;

    int level = 0;
    float loadInTimer = 0.0f;
    int loadInTime = 3;
    int livesDrawLocation = 500;
};