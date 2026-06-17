#include <iostream>
#include <vector>

#include "raylib.h"
#include "raymath.h"

#include <tracy\Tracy.hpp>

struct ScreenConfig{
    int Width = 800;
    int Height = 450;
    int target_fps = 60;
};

constexpr ScreenConfig Screen{};

struct UiConfig{
    Color background_color = RAYWHITE;
    struct {
        const int x = 10;
        const int y = 10;
    } FPS;

    struct {
        const int x = 10;
        const int y = 30;
        const int font_size = 20; 
        const Color color = GREEN;
    } BallCount;

};
constexpr UiConfig Ui{};

struct Ball {
    float posX,posY;
    float velX,velY;
    float radius;
    static constexpr Color color = RED;
};

auto addBall(std::vector<Ball>& balls, Vector2 pos) -> void{
    Vector2 vel = Vector2Rotate(
        {.x=0.0f,.y=100.0f},
        static_cast<float>(GetRandomValue(0,360))
    );
    balls.push_back(
        Ball{
            .posX   = pos.x,
            .posY   = pos.y,
            .velX   = vel.x,
            .velY   = vel.y,
            .radius = 10.0f
        }
    );
}

auto main() -> int{
    InitWindow(Screen.Width, Screen.Height, "Teste");
    SetTargetFPS(Screen.target_fps);
    
    std::vector<Ball> balls;
    balls.reserve(10000);

    while(!WindowShouldClose()){
        FrameMark;
        float dt = GetFrameTime();
        Vector2 mouse_pos = GetMousePosition();


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            for(int i=0;i<100;i++) {
                addBall(balls,mouse_pos);
            }
        }

        // Update Balls
        for(Ball& b : balls){
            b.posX += b.velX * dt;
            b.posY += b.velY * dt;



            if(b.posX - b.radius <= 0.0f){
                b.velX = -b.velX;
                b.posX = b.radius;
            }
            if(b.posY - b.radius <= 0.0f){
                b.velY = -b.velY;
                b.posY = b.radius;
            } 
            if(b.posX + b.radius >= static_cast<float>(Screen.Width)) {
                b.velX = -b.velX;
                b.posX = static_cast<float>(Screen.Width) - b.radius;
            }
            if(b.posY + b.radius >= static_cast<float>(Screen.Height)){
                b.velY = -b.velY;
                b.posY = static_cast<float>(Screen.Height) - b.radius;
            }
        }
    
        BeginDrawing();
            ClearBackground(Ui.background_color);

            // Draw Balls
            for(Ball& b : balls){
                DrawCircle(
                    static_cast<int>(b.posX),
                    static_cast<int>(b.posY),
                    b.radius,
                    b.color
                );
            }

            DrawFPS(Ui.FPS.x,Ui.FPS.y);
            DrawText(
                TextFormat("%d",balls.size()),
                Ui.BallCount.x,
                Ui.BallCount.y,
                Ui.BallCount.font_size,
                Ui.BallCount.color
            );
        EndDrawing();
    }
    CloseWindow();
    return 0;
}