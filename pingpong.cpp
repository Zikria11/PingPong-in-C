#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Ping Pong - For My Love");
    SetTargetFPS(60);

    const float paddleWidth = 20.0f;
    const float paddleHeight = 100.0f;
    const float paddleSpeed = 400.0f;

    Rectangle leftPaddle = { 50, screenHeight / 2 - paddleHeight / 2, paddleWidth, paddleHeight };
    Rectangle rightPaddle = { screenWidth - 50 - paddleWidth, screenHeight / 2 - paddleHeight / 2, paddleWidth, paddleHeight };

    Vector2 ballPos = { screenWidth / 2.0f, screenHeight / 2.0f };
    Vector2 ballSpeed = { 300.0f, 300.0f };
    const float ballRadius = 10.0f;

    int leftScore = 0;
    int rightScore = 0;

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_W) && leftPaddle.y > 0)
            leftPaddle.y -= paddleSpeed * GetFrameTime();
        if (IsKeyDown(KEY_S) && leftPaddle.y < screenHeight - paddleHeight)
            leftPaddle.y += paddleSpeed * GetFrameTime();

        if (IsKeyDown(KEY_UP) && rightPaddle.y > 0)
            rightPaddle.y -= paddleSpeed * GetFrameTime();
        if (IsKeyDown(KEY_DOWN) && rightPaddle.y < screenHeight - paddleHeight)
            rightPaddle.y += paddleSpeed * GetFrameTime();

        ballPos.x += ballSpeed.x * GetFrameTime();
        ballPos.y += ballSpeed.y * GetFrameTime();

        if (ballPos.y <= ballRadius || ballPos.y >= screenHeight - ballRadius)
            ballSpeed.y = -ballSpeed.y;

        if (CheckCollisionCircleRec(ballPos, ballRadius, leftPaddle) ||
            CheckCollisionCircleRec(ballPos, ballRadius, rightPaddle))
            ballSpeed.x = -ballSpeed.x;

        if (ballPos.x < 0) {
            rightScore++;
            ballPos = { screenWidth / 2.0f, screenHeight / 2.0f };
            ballSpeed = { 300.0f, 300.0f };
        }
        if (ballPos.x > screenWidth) {
            leftScore++;
            ballPos = { screenWidth / 2.0f, screenHeight / 2.0f };
            ballSpeed = { -300.0f, 300.0f };
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangleRec(leftPaddle, WHITE);
        DrawRectangleRec(rightPaddle, WHITE);
        DrawCircleV(ballPos, ballRadius, WHITE);

        for (int i = 0; i < screenHeight; i += 20)
            DrawRectangle(screenWidth / 2 - 2, i, 4, 10, WHITE);

        DrawText(TextFormat("%d", leftScore), screenWidth / 4, 20, 40, WHITE);
        DrawText(TextFormat("%d", rightScore), 3 * screenWidth / 4, 20, 40, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
