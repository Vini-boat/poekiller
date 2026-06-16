#include <iostream>
#include <vector>

#include "raylib.h"
#include "raymath.h"

constexpr struct {
    int Width = 800;
    int Height = 450;
} Screen;

struct Ball {
    float posX,posY;
    float velX,velY;
    float radius;
};

int main(void){
    std::cout << "Olá" << std::endl;

    InitWindow(Screen.Width, Screen.Height, "Teste");
    SetTargetFPS(60);
    
    std::vector<Ball> balls;
    balls.reserve(100);

    while(!WindowShouldClose()){
        float dt = GetFrameTime();
        Vector2 mouse_pos = GetMousePosition();


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            balls.push_back(
                Ball{
                    mouse_pos.x,
                    mouse_pos.y,
                    (float)GetRandomValue(-100,100)*2.0f,
                    (float)GetRandomValue(-100,100)*2.0f,
                    10.0f
                }
            );
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
            if(b.posX + b.radius >= (float)Screen.Width) {
                b.velX = -b.velX;
                b.posX = (float)Screen.Width - b.radius;
            }
            if(b.posY + b.radius >= (float)Screen.Height){
                b.velY = -b.velY;
                b.posY = (float)Screen.Height - b.radius;
            }
        }
    
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Draw Balls
            for(Ball& b : balls){
                DrawCircle(b.posX,b.posY,b.radius,RED);
            }

            DrawFPS(10.0f,10.0f);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}