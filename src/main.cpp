#include <raylib.h>
#include <iostream>
#include <vector>

#include "Bullet.hpp"
#include "Player.hpp"
#include "Globals.hpp"
#include "Particle.hpp"
#include "ParticleManager.hpp"
#include "SinParticle.hpp"

int main(void)
{

    InitWindow(glob::SCREEN_WIDTH, glob::SCREEN_HEIGHT, "Asteroids");

    //loading in textures

    Texture2D playerTex = LoadTexture("../res/PlayerTex.png");
    Texture2D laserTex = LoadTexture("../res/Laser.png");
    Texture2D engineParticle = LoadTexture("../res/Particle.png");

    Player player = Player(100.0f, 100.0f, &playerTex);

    ParticleManager pManager = ParticleManager();

    std::vector<Bullet> bullets;

    SetTargetFPS(144);

    float dt = GetFrameTime();


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        dt = GetFrameTime();


        if (IsKeyDown(KEY_UP)){
            player.AddThrust(dt, pManager, &engineParticle);
            player.SetMoving(true);
        }
        else if (!IsKeyDown(KEY_UP))
            player.SetMoving(false);
        if (IsKeyDown(KEY_RIGHT))
            player.Rotate(1, dt);
        if (IsKeyDown(KEY_LEFT))
            player.Rotate(-1, dt);
        if (IsKeyPressed(KEY_SPACE))
            player.Shoot(bullets, &laserTex);

        // particle demonstration
        // if (IsMouseButtonDown(0)){
        //     Vector2 pos = GetMousePosition();
        //     //pos.x += GetRandomValue(-20, 20);
        //     //pos.y += GetRandomValue(-20, 20);
        //     pManager.AddParticles(new SinParticle(pos.x, pos.y, 4.0f, 4.0f, &engineParticle, 10.0f, 45));
        // }

        // update

        player.Update(dt);

        for (uint32_t i = 0; i < bullets.size(); i++){
            if (!bullets[i].GetDead()){
                bullets[i].Update(dt);
            }
            else{
                bullets.erase(bullets.begin() + i);
                i--;
            }
        }

        pManager.Update(dt);

        BeginDrawing();

        ClearBackground(BLACK);

        player.Draw();

        for (Bullet& b : bullets)
            b.Draw();

        pManager.Draw();

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}