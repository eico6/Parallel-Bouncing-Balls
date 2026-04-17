#include <iostream>
#include <raylib.h>
#include "ball.h"
#include "vector.h"

int main() {
    InitWindow(1000, 800, "Bouncing Ball");
    SetTargetFPS(60);

    Vector pos = {400, 300};
    Vector vel = {3, 2};
    float radius = 20;

    while (!WindowShouldClose()) {
        // update
        pos.x += vel.x;
        pos.y += vel.y;

        if (pos.x < radius || pos.x > 800 - radius) vel.x *= -1;
        if (pos.y < radius || pos.y > 600 - radius) vel.y *= -1;

        // draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(pos, radius, RED);
        EndDrawing();
    }

    CloseWindow();
}