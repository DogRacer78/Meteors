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
#include "BGParticle.hpp"

Game::Game(){
    state = start;

    InitWindow(glob::SCREEN_WIDTH, glob::SCREEN_HEIGHT, "Asteroids");
    InitAudioDevice();

    playerTex = LoadTexture("../res/PlayerTex.png");
    laserTex = LoadTexture("../res/Laser.png");
    engineParticle = LoadTexture("../res/Particle.png");
    burnerTex = LoadTexture("../res/Burner.png");
    asteroidTex = LoadTexture("../res/Asteroid.png");
    deathParticle = LoadTexture("../res/Death Particle.png");
    shootParticle = LoadTexture("../res/Shoot Particle.png");
    spaceParticle = LoadTexture("../res/Space Particle.png");

    //load in sounds
    explosionFx = LoadSound("../res/Explosion.wav");
    shootFx = LoadSound("../res/Shoot.wav");
    engineFx = LoadSound("../res/Engine.wav");

    player = new Player(glob::SCREEN_WIDTH / 2 - 16, glob::SCREEN_HEIGHT / 2 - 16, &playerTex, &burnerTex);

    pManager = new ParticleManager();
    
    asteroidManager = new AsteroidManager(level + 4, &asteroidTex, &deathParticle, this);

    for (int i = 0; i < 100; i++){
        BGParticle* particle = new BGParticle(GetRandomValue(0, glob::SCREEN_WIDTH), GetRandomValue(0, glob::SCREEN_HEIGHT), 2.0f, 2.0f, &spaceParticle, 0.0f);
        particle->SetVelocity(GetRandomValue(-50, 50), GetRandomValue(-50, 50));
        pManager->AddParticles(particle);
    }

    playerLives = 3;

    dt = GetFrameTime();
}

void Game::StartScreen() {
    if (IsMouseButtonPressed(0) || IsKeyPressed(KEY_SPACE)){
        state = loading_screen;
    }

    if (IsKeyPressed(KEY_ENTER)){
        state = controls;
    }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Meteors", 133, 163, 96, WHITE);
        DrawText("Space to start", 133, 400, 20, WHITE);
        DrawText("Enter to see controls", 133, 450, 20, WHITE);

        EndDrawing();
}

void Game::GameOverScreen() {

    level = 0;
    playerLives = 3;

    if (IsMouseButtonPressed(0) || IsKeyPressed(KEY_SPACE)){
        state = load_new;
        score = 0;
    }

    BeginDrawing();

    ClearBackground(BLACK);
    // 292, 368
    DrawText("Game Over", 133, 163, 96, WHITE);
    DrawText(("Score: " + std::to_string(score)).c_str(), 292, 368, 18, WHITE);
    DrawText("Space to play again", 133, 400, 20, WHITE);

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
    
    for (int i = 0; i < 100; i++){
        BGParticle* particle = new BGParticle(GetRandomValue(0, glob::SCREEN_WIDTH), GetRandomValue(0, glob::SCREEN_HEIGHT), 2.0f, 2.0f, &spaceParticle, 0.0f);
        particle->SetVelocity(GetRandomValue(-50, 50), GetRandomValue(-50, 50));
        pManager->AddParticles(particle);
    }

    state = loading_screen;
}

void Game::LoadingState(){
    dt = GetFrameTime();

    loadInTimer += dt;

    if (loadInTimer > loadInTime){
        state = main_game;
        loadInTimer = 0.0f;
    }

    pManager->Update(dt);

    BeginDrawing();

    ClearBackground(BLACK);

    player->Draw();

    asteroidManager->Draw();

    pManager->Draw();

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

    //DrawFPS(0, 0);

    EndDrawing();
}

void Game::ControlsScreen(){

    if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(0))
        state = start;

    BeginDrawing();

    ClearBackground(BLACK);

    //264 67
    DrawText("Controls", 264, 67, 36, WHITE);
    DrawText("Arrow keys to move and space to shoot", 158, 201, 18, WHITE);
    DrawText("Press space to return", 241, 287, 18, WHITE);

    EndDrawing();
}

void Game::MainGame(){
        dt = GetFrameTime();

        int gesture = GetGestureDetected();


        if (IsKeyDown(KEY_UP) || IsGamepadButtonDown(0, 7)){
            player->AddThrust(dt, *pManager, &engineParticle);
            player->SetMoving(true);
            if (!IsSoundPlaying(engineFx))
                PlaySound(engineFx);
        }
        else if (!IsKeyDown(KEY_UP)){
            player->SetMoving(false);
            StopSound(engineFx);
        }
        if (IsKeyDown(KEY_RIGHT) || GetGamepadAxisMovement(0, 0) > 0)
            player->Rotate(1, dt);
        if (IsKeyDown(KEY_LEFT) || GetGamepadAxisMovement(0, 0) < 0)
            player->Rotate(-1, dt);
        if (IsKeyPressed(KEY_SPACE) || IsGamepadButtonPressed(0, 8)){
            player->Shoot(bullets, &laserTex, *pManager, &shootParticle);
            PlaySoundMulti(shootFx);
        }

        // update

        glob::offset[0] = 0.0f;
        glob::offset[1] = 0.0f;

        if (screenShake > 0){
            screenShake -= 1;
            glob::offset[0] = GetRandomValue(-4, 4);
            glob::offset[1] = GetRandomValue(-4, 4);
        }
            

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

        //DrawFPS(0, 0);

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
        case controls:
            ControlsScreen();
            break;
    }
}

void Game::SetScreenShake(int s) { screenShake = s; }