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
#include "Game.hpp"

Game::Game(){
    state = start;

    InitWindow(glob::SCREEN_WIDTH, glob::SCREEN_HEIGHT, "Asteroids");

    playerTex = LoadTexture("../res/PlayerTex.png");
    laserTex = LoadTexture("../res/Laser.png");
    engineParticle = LoadTexture("../res/Particle.png");
    burnerTex = LoadTexture("../res/Burner.png");
    asteroidTex = LoadTexture("../res/Asteroid.png");
    deathParticle = LoadTexture("../res/Death Particle.png");
    shootParticle = LoadTexture("../res/Shoot Particle.png");

    player = new Player(glob::SCREEN_WIDTH / 2 - 16, glob::SCREEN_HEIGHT / 2 - 16, &playerTex, &burnerTex);

    pManager = new ParticleManager();
    
    asteroidManager = new AsteroidManager(level + 4, &asteroidTex, &deathParticle);

    playerLives = 3;

    dt = GetFrameTime();
}

void Game::StartScreen() {
    if (IsMouseButtonPressed(0) || IsKeyPressed(KEY_SPACE)){
        state = loading_screen;
    }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Meteors", 133, 163, 96, WHITE);

        EndDrawing();
}

void Game::GameOverScreen() {

    level = 0;
    playerLives = 3;

    if (IsMouseButtonPressed(0) || IsKeyPressed(KEY_ENTER)){
        state = load_new;
        score = 0;
    }

    BeginDrawing();

    ClearBackground(BLACK);
    // 292, 368
    DrawText("Game Over", 133, 163, 96, WHITE);
    DrawText(("Score: " + std::to_string(score)).c_str(), 292, 368, 18, WHITE);

    EndDrawing();
}

void Game::LoadNew(){
    bullets.clear();
    asteroidManager->Reset();
    pManager->Reset();

    delete player;
    player = new Player(glob::SCREEN_WIDTH / 2 - 16, glob::SCREEN_HEIGHT / 2 - 16, &playerTex, &burnerTex);

    asteroidManager->SetupNewLevel(level + 4);

    std::cout << "Setting up new" << std::endl;

    if (playerLives != 3)
        playerLives++;

    state = loading_screen;
}

void Game::LoadingState(){
    dt = GetFrameTime();

    loadInTimer += dt;

    if (loadInTimer > loadInTime){
        state = main_game;
        loadInTimer = 0.0f;
    }

    BeginDrawing();

    ClearBackground(BLACK);

    player->Draw();

    asteroidManager->Draw();

    DrawText(("Score: " + std::to_string(score)).c_str(), 26, 45, 20, WHITE);

    EndDrawing();
}

void Game::InBetweenLivesState(){
    dt = GetFrameTime();

    inBetweenLivesTimer += dt;

    if (inBetweenLivesTimer > inBetweenLivesTime){
        state = main_game;
        inBetweenLivesTimer = 0.0f;
        return;
    }


    for (uint32_t i = 0; i < bullets.size(); i++){
        if (!bullets[i].GetDead()){
            bullets[i].Update(dt);
        }
        else{
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }

    pManager->Update(dt);

    asteroidManager->Update(dt, score);


    BeginDrawing();

    ClearBackground(BLACK);

    for (Bullet& b : bullets)
        b.Draw();
    
    pManager->Draw();

    asteroidManager->Draw();

    for (int i = 0; i < playerLives; i++){
        DrawTextureEx(playerTex, Vector2{(float)livesDrawLocation + i * 23, 20}, 0.0f, 0.25f, RAYWHITE); 
    }

    DrawText(("Score: " + std::to_string(score)).c_str(), 26, 45, 20, WHITE);

    DrawFPS(0, 0);

    EndDrawing();
}

void Game::MainGame(){
        dt = GetFrameTime();


        if (IsKeyDown(KEY_UP)){
            player->AddThrust(dt, *pManager, &engineParticle);
            player->SetMoving(true);
        }
        else if (!IsKeyDown(KEY_UP))
            player->SetMoving(false);
        if (IsKeyDown(KEY_RIGHT))
            player->Rotate(1, dt);
        if (IsKeyDown(KEY_LEFT))
            player->Rotate(-1, dt);
        if (IsKeyPressed(KEY_SPACE))
            player->Shoot(bullets, &laserTex, *pManager, &shootParticle);

        // particle demonstration
        // if (IsMouseButtonDown(0)){
        //     Vector2 pos = GetMousePosition();
        //     //pos.x += GetRandomValue(-20, 20);
        //     //pos.y += GetRandomValue(-20, 20);
        //     pManager.AddParticles(new SinParticle(pos.x, pos.y, 4.0f, 4.0f, &engineParticle, 10.0f, 45));
        // }

        // update

        player->Update(dt);

        if (player->dead){
            if (playerLives > 0){
                playerLives -= 1;
                player->UnDead();
                bullets.clear();
                state = inbetween_lives;
            }
            else if (playerLives == 0){
                state = death;
            }
            return;
        }

        for (uint32_t i = 0; i < bullets.size(); i++){
            if (!bullets[i].GetDead()){
                bullets[i].Update(dt);
            }
            else{
                bullets.erase(bullets.begin() + i);
                i--;
            }
        }

        pManager->Update(dt);

        asteroidManager->Update(dt, bullets, *player, score, *pManager);

        if (asteroidManager->CheckClear()){
            level++;
            state = load_new;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        player->Draw();

        for (Bullet& b : bullets)
            b.Draw();

        pManager->Draw();

        asteroidManager->Draw();

        for (int i = 0; i < playerLives; i++){
            DrawTextureEx(playerTex, Vector2{(float)livesDrawLocation + i * 23, 20}, 0.0f, 0.25f, RAYWHITE); 
        }
        DrawText(("Score: " + std::to_string(score)).c_str(), 26, 45, 20, WHITE);

        DrawFPS(0, 0);

        EndDrawing();
}

void Game::StateSelect(){
    switch(state){
        case main_game:
            MainGame();
            break;
        case start:
            StartScreen();
            break;
        case death:
            GameOverScreen();
            break;
        case load_new:
            LoadNew();
            break;
        case loading_screen:
            LoadingState();
            break;
        case inbetween_lives:
            InBetweenLivesState();
            break;
    }
}