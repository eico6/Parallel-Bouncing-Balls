#include "raylib.h"
#include "SimulationSeq.hpp"
#include <vector>
#include <cstdlib>

Color getColor(int id) {
    switch (id % 6) {
        case 0: return RED;
        case 1: return GREEN;
        case 2: return BLUE;
        case 3: return YELLOW;
        case 4: return ORANGE;
        case 5: return PURPLE;
    }
    return WHITE;
}

int main() {
    InitWindow(1000, 800, "Ball Collision");
    SetTargetFPS(60);

    Rectangle bounds = {100, 100, 800, 600};

    std::vector<Ball> balls;
    for (int i = 0; i < 200; i++) {
        float x = bounds.x + rand() % (int)bounds.width;
        float y = bounds.y + rand() % (int)bounds.height;
        balls.emplace_back(i, x, y, 4, 1.0);
    }

    Grid<std::vector<Ball>> grid(20,20);
    SimulationSeq sim(bounds, balls, grid);

    while (!WindowShouldClose()) {

        sim.update();

        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangleLinesEx(bounds, 2, WHITE);

        DrawFPS(10, 10);
        DrawText(TextFormat("Balls: %d", (int)balls.size()), 10, 30, 20, WHITE);

        // balls
        for (auto &b : balls) {
            DrawCircle(b.position.x, b.position.y, b.radius, getColor(b.id));
        }

        EndDrawing();
    }

    CloseWindow();
}