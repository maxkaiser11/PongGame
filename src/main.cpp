#include <iostream>
#include <random>
#include <cmath>
#include "raylib.h"

// TODO: Refactor into classes

struct Player
{
    float x;
    float y;
    float height;
    float width;
};

// Function to check collision between circle (ball) and rectangle (paddle)
bool checkBallPaddleCollision(Vector2 ballPos, float ballRadius, Rectangle paddle)
{
    return CheckCollisionCircleRec(ballPos, ballRadius, paddle);
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    bool showFPS = false;

    InitWindow(screenWidth, screenHeight, "Raylib Pong");

    Vector2 ballPosition = {(float)screenWidth / 2, (float)screenHeight / 2};
    float ballRadius = 10.f;

    Player player = {10.f, screenHeight / 2 - 50.f, 100.f, 25.f};
    Player enemyPlayer = {765.f, screenHeight / 2 - 50.f, 100.f, 25.f};

    float ballDirectionY = 2.f;
    float ballDirectionX = 3.f;

    // AI variables
    float aiSpeed = 1.5f;

    // Score variables
    int playerScore = 0;
    int enemyScore = 0;

    SetTargetFPS(120);

    while (!WindowShouldClose())
    {
        // Update player rectangles each frame
        Rectangle playerRec = {player.x, player.y, player.width, player.height};
        Rectangle enemyRec = {enemyPlayer.x, enemyPlayer.y, enemyPlayer.width, enemyPlayer.height};

        // Player controls
        if (player.y >= 5.f)
            if (IsKeyDown(KEY_UP))
                player.y -= 4.0f;
        if (player.y <= screenHeight - 105.f)
            if (IsKeyDown(KEY_DOWN))
                player.y += 4.0f;

        // Toggle FPS
        if (IsKeyPressed(KEY_F))
            showFPS = !showFPS;

        // Reset game
        if (IsKeyPressed(KEY_R))
        {
            ballPosition.x = screenWidth / 2;
            ballPosition.y = screenHeight / 2;
            ballDirectionX = 3.f;
            ballDirectionY = 2.f;
            playerScore = 0;
            enemyScore = 0;
        }

        // TODO: Implement proper AI logic thats not too hard but also not super easy
        enemyPlayer.y = ballPosition.y;

        float ballCenterY = ballPosition.y;
        float paddleCenterY = enemyPlayer.y + enemyPlayer.height / 2;

        // Keep enemy paddle on screen
        if (enemyPlayer.y < 0)
            enemyPlayer.y = 0;
        if (enemyPlayer.y > screenHeight - enemyPlayer.height)
            enemyPlayer.y = screenHeight - enemyPlayer.height;

        // Update ball position
        ballPosition.y += ballDirectionY;
        ballPosition.x += ballDirectionX;

        // Ball collision with top and bottom walls
        if (ballPosition.y - ballRadius <= 0)
        {
            ballDirectionY = -ballDirectionY;
            ballPosition.y = ballRadius;
        }
        else if (ballPosition.y + ballRadius >= screenHeight)
        {
            ballDirectionY = -ballDirectionY;
            ballPosition.y = screenHeight - ballRadius;
        }

        // Ball collision with player paddle
        if (checkBallPaddleCollision(ballPosition, ballRadius, playerRec) && ballDirectionX < 0)
        {
            ballDirectionX = -ballDirectionX;
            ballPosition.x = playerRec.x + playerRec.width + ballRadius;

            float hitPos = (ballPosition.y - (playerRec.y + playerRec.height / 2)) / (playerRec.height / 2);
            ballDirectionY += hitPos * 1.5f;
        }

        // Ball collision with enemy paddle
        if (checkBallPaddleCollision(ballPosition, ballRadius, enemyRec) && ballDirectionX > 0)
        {
            ballDirectionX = -ballDirectionX;
            ballPosition.x = enemyRec.x - ballRadius;

            if (ballPosition.x >= screenWidth - ballRadius)
            {
                ballPosition.x = screenWidth - ballRadius - 1;
            }

            float hitPos = (ballPosition.y - (enemyRec.y + enemyRec.height / 2)) / (enemyRec.height / 2);
            ballDirectionY += hitPos * 1.5f;
        }

        // Limit ball Y speed
        if (ballDirectionY > 5.f)
            ballDirectionY = 5.f;
        if (ballDirectionY < -5.f)
            ballDirectionY = -5.f;

        // Scoring
        if (ballPosition.x < -ballRadius)
        {
            enemyScore++;
            ballPosition.x = screenWidth / 2;
            ballPosition.y = screenHeight / 2;
            ballDirectionX = 3.f;
            ballDirectionY = (GetRandomValue(0, 1) == 0) ? 2.f : -2.f;
        }
        else if (ballPosition.x > screenWidth + ballRadius)
        {
            playerScore++;
            ballPosition.x = screenWidth / 2;
            ballPosition.y = screenHeight / 2;
            ballDirectionX = -3.f;
            ballDirectionY = (GetRandomValue(0, 1) == 0) ? 2.f : -2.f;
        }

        // Drawing
        BeginDrawing();

        ClearBackground(WHITE);

        // Instructions
        DrawText("Move with UP/DOWN Keys", 10, 10, 20, DARKGRAY);
        DrawText("Press F to toggle FPS, R to reset", 10, 35, 16, DARKGRAY);

        // Score
        DrawText(TextFormat("Player: %d", playerScore), 50, screenHeight - 50, 20, DARKBLUE);
        DrawText(TextFormat("Enemy: %d", enemyScore), screenWidth - 150, screenHeight - 50, 20, MAROON);

        // Draw paddles
        DrawRectangle(player.x, player.y, player.width, player.height, MAROON);
        DrawRectangle(enemyPlayer.x, enemyPlayer.y, enemyPlayer.width, enemyPlayer.height, MAROON);

        // Draw ball
        DrawCircleV(ballPosition, ballRadius, BLACK);

        // Draw center line
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, LIGHTGRAY);

        if (showFPS)
            DrawFPS(700, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}