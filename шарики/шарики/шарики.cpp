#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include <vector>

const int MAX_WIDTH = 800;
const int MAX_HEIGHT = 600;

struct Circle {
    Vector2 position;
    Vector2 velocity;
    float radius;
};
struct Wall {
    Vector2 position;
    float width;
    float height;
};
void GenerateWalls(std::vector<Wall>& walls) {
    walls.push_back({
      {MAX_WIDTH / 4,MAX_HEIGHT / 4},
      200,
      30,
        });
    walls.push_back({
      {MAX_WIDTH / 4,MAX_HEIGHT / 4},
      30,
      200,
        });
    walls.push_back({
      {MAX_WIDTH * 3 / 4,MAX_HEIGHT * 3 / 4 - 200},
      30,
      200,
        });
    walls.push_back({
      {MAX_WIDTH * 3 / 4 - 200,MAX_HEIGHT * 3 / 4},
      200,
      30,
        });
}
int main()
{
    InitWindow(MAX_WIDTH, MAX_HEIGHT, "Kruzhochki");
    SetTargetFPS(120);
    int ball_x = MAX_WIDTH / 2;
    int ball_y = MAX_HEIGHT / 2;
    int speed_x = 5;
    int speed_y = 5;
    int radius = 15;

    Circle circle = {
      {MAX_WIDTH / 4 + 80,MAX_HEIGHT / 2},
      {5,1.5},
      30.0f
    };
    std::vector<Wall> walls;
    GenerateWalls(walls);

    while (!WindowShouldClose()) {
        //Vector2 mouse = GetMousePosition();
        circle.position = Vector2Add(circle.position,
            circle.velocity);
        if (circle.position.y + circle.radius > MAX_HEIGHT
            || circle.position.y - circle.radius < 0) {
            circle.velocity.y *= -1;
        }
        if (circle.position.x + circle.radius > MAX_WIDTH
            || circle.position.x - circle.radius < 0) {
            circle.velocity.x *= -1;
        }
        for (const auto& wall : walls)
        {
            if (CheckCollisionCircleRec(circle.position, circle.radius,
                { wall.position.x,wall.position.y,wall.width,wall.height }))
            {
                if (circle.position.x < wall.position.x) {
                    circle.velocity.x *= -1;
                }
                if (circle.position.x > wall.position.x + wall.width) {
                    circle.velocity.x *= -1;
                }
                if (circle.position.y < wall.position.y) {
                    circle.velocity.y *= -1;
                }
                if (circle.position.y > wall.position.y + wall.height) {
                    circle.velocity.y *= -1;
                }
            }
        }
        BeginDrawing();
        ClearBackground(DARKBLUE);
        //DrawRectangle(mouse.x-50, mouse.y - 50, 100,100, RED);
        //DrawCircle(mouse.x, mouse.y, 50, WHITE);
        for (const auto& wall : walls)
        {
            DrawRectangle(wall.position.x, wall.position.y,
                wall.width, wall.height, RED);
        }
        DrawCircle(circle.position.x, circle.position.y,
            circle.radius, WHITE);
        EndDrawing();
    }
    CloseWindow();
  
}
//while (!WindowShouldClose()) {
//    //каждый кадр
//    //Vector2 mouse = GetMousePosition();
//
//    ball_x += speed_x;
//    ball_y += speed_y;
//    if (ball_y + radius > MAX_HEIGHT || ball_y - radius < 0) {
//        speed_y *= -1;
//    }
//    if (ball_x + radius > MAX_WIDTH || ball_x - radius < 0) {
//        speed_x *= -1;
//    }
//    BeginDrawing();
//    ClearBackground(DARKGREEN);
//    //DrawRectangle(mouse.x-50, mouse.y-50, 100, 100, BLUE);
//    //DrawCircle(mouse.x, mouse.y, 50,YELLOW);
//
//    DrawCircle(ball_x, ball_y, 15, YELLOW);
//    EndDrawing();
//
//}
//CloseWindow();
