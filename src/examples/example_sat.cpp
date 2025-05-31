#include"../../include/external/raylib/raylib.h"
#include"../../include/external/raylib/raymath.h"
#include"../../include/engine/polygon.h"
#include"../../include/engine/polygon.h"

#define RAYGUI_IMPLEMENTATION
#include<raylib/raygui.h>
#include<vector>
#include<iostream>
#include<cmath>
int WIND_W = 400;
int WIND_H = 400;
int numbg_lines = 10;

Vector2 cam_pos = {0,0};
Vector2 real_cam_pos = {0,0};
float pan_speed = 0.025f;

Vector2 proj_vec = {0,0};
Vector2 proj_vec_rot = {0,0};
float proj_angle = 0;

using namespace std;
using namespace c2d;

void DrawPointWithCoords(Vector2 p, Color c){
    DrawCircleV({p.x,-p.y},5,c);
    DrawText(TextFormat("x: %f y: %f",p.x,p.y), p.x, -p.y+20, 10, c);
}

int main(){
    InitWindow(WIND_W,WIND_H,"raylib spworks - [ separating axis theorem ]");

    vector<polygon> polygons;
    polygon poly = c2d::polygon({50,30},{{-10,10},{-10,-10},{40,-10},{40,10}});  
    polygons.push_back({{20,20},{{-10,-10},{10,-10},{10,10},{-10,10}}});  
    polygons.push_back({{-25,30},{{-25,-10},{3,-7},{10,10},{-40,10}}});  
    polygons.push_back({{-30,70},{{-15,-14},{-6,-25},{21,-3},{10,14},{-10,28}}});  
    polygons[2].ang_vel = M_PI/10000.0f;

    Camera2D camera = { 0 };
    camera.target = (Vector2){ cam_pos.x, cam_pos.y };
    camera.offset = (Vector2){ WIND_W/2.0f, WIND_H/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // ---- Main Loop ----
    while(!WindowShouldClose()){
        proj_vec = {cos(proj_angle),sin(proj_angle)};
        proj_vec_rot = {cos(proj_angle+(float)M_PI/2),sin(proj_angle+(float)M_PI/2)};
        real_cam_pos = (cam_pos*Vec2(1,-1)).toRVec();

        // ---- Camera Movement ----
        if(IsKeyDown(KEY_W)){
            cam_pos.y+=pan_speed;
        }
        if(IsKeyDown(KEY_S)){
            cam_pos.y-=pan_speed;
        }
        if(IsKeyDown(KEY_A)){
            cam_pos.x-=pan_speed;
        }
        if(IsKeyDown(KEY_D)){
            cam_pos.x+=pan_speed;
        }
        // ---- Camera Movement ----

        camera.target = real_cam_pos;

        // ---- Drawing -----
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        DrawLineEx({0,real_cam_pos.y-WIND_H/2.0f},{0,real_cam_pos.y+WIND_H/2.0f},2.0f,LIGHTGRAY);
        DrawLineEx({real_cam_pos.x-WIND_W/2.0f,0},{real_cam_pos.x+WIND_W/2.0f,0},2.0f,LIGHTGRAY);
        poly.pos = (GetMousePosition()-Vec2(WIND_W/2.0f,WIND_H/2.0f))*Vec2(1,-1)+cam_pos;
        float rot_add = 0;
        switch ((int)GetMouseWheelMove()){
            case -1:
                rot_add = -0.1;
                break;
            case 0:
                break;
            case 1:
                rot_add = 0.1;
                break;
        };
        poly.rot += rot_add;
        poly.Update();
        poly.DrawDbg();
        bool collision = false;

        // ---- Polygon Update ----
        for(polygon& p : polygons){
            p.Update();
            p.DrawDbg();
            bool c = poly.CheckCollision(p);
            collision =  c > collision ? c : collision;
        }
        // ---- Polygon Update ----

        EndMode2D();

        // ---- UI ----
        DrawText(TextFormat("POSITION | x: %f y:%f ",cam_pos.x,cam_pos.y), 6, 6, 18, BLACK);

        string text = collision == 0 ? "false" : "true";
        Color col = collision == 0 ? RED : GREEN;
        DrawText(TextFormat("COLLISION | %s",text.c_str()), 6, 18+9, 18, col);
        // ---- UI ----

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
