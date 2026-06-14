#include <iostream>
#include <vector>

#include "raylib.h"
#include "raymath.h"

constexpr struct {
    int Width = 800;
    int Height = 450;
} Screen;

struct Ball {
    Vector2 pos;
    Vector2 velocity;
    float radius;

    void draw(){
        DrawCircleV(pos,radius,RED);
    }
    void update(float dt) {
        pos = Vector2Add(
            pos,
            Vector2Scale(velocity, dt)
        );
    }
    friend std::ostream& operator<<(std::ostream& os, const Ball& b){
        os << "Ball:" << " x: " << b.pos.x << " y: " << b.pos.y  << "\n";
        os << "    : vx: " << b.velocity.x << " vy: " << b.velocity.y << "\n";
        os << "    : r: " << b.radius << "\n";
        return os;
    }

};

int main(void){
    std::cout << "Olá" << std::endl;

    InitWindow(Screen.Width, Screen.Height, "Teste");
    SetTargetFPS(60);
    
    std::vector<Ball> balls;

    while(!WindowShouldClose()){
        float dt = GetFrameTime();
        // std::cout << dt << std::endl;
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            balls.push_back(Ball{
                .pos = GetMousePosition(),
                .velocity = {
                    (float)GetRandomValue(-100,100),
                    (float)GetRandomValue(-100,100)
                },
                .radius = 10.0f
            });
        }
        for(Ball& b : balls) b.update(dt);
        // for(Ball& b : balls) std::cout << b;
    
        BeginDrawing();
            ClearBackground(RAYWHITE);
            for(Ball& b : balls) b.draw();
            DrawFPS(10.0f,10.0f);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}