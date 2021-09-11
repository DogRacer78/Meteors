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

class AsteroidManager;

class Game{
public:
    enum GameState : unsigned char { main_game, start, death, load_new, loading_screen, inbetween_lives, controls };
    Game();
    void MainGame();
    void StartScreen();
    void StateSelect();
    void GameOverScreen();
    void LoadNew();
    void LoadingState();
    void InBetweenLivesState();
    void ControlsScreen();
    Sound explosionFx;
private:
    GameState state;
    
    //Textures
    Texture2D playerTex;
    Texture2D laserTex;
    Texture2D engineParticle;
    Texture2D burnerTex;
    Texture2D asteroidTex;
    Texture2D deathParticle;
    Texture2D shootParticle;
    Texture2D spaceParticle;

    //sounds
    Sound shootFx;
    Sound engineFx;

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
    int playerLives;

    float inBetweenLivesTimer = 0.0;
    int inBetweenLivesTime = 3;
};