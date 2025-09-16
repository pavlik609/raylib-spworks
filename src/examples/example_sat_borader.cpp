#include"../../include/external/raylib/raylib.h"
#include"../../include/external/raylib/raymath.h"
#include"../../include/engine/polygon.h"
#include"../../include/engine/random.h"

//#define RAYGUI_IMPLEMENTATION
//#include"../../include/external/raylib/raygui.h"
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
    InitWindow(WIND_W,WIND_H,"raylib spworks - [ SAT w/ AABB checking]");

    vector<polygon> polygons;
    polygon poly = c2d::polygon({50,30},{{-10,10},{-10,-10},{40,-10},{40,10}});
    for(int i=0;i<100;i++){
        vector<Vec2> points;
        Vec2 pos = {G_RAND.GetFloat(-100,100),G_RAND.GetFloat(-100,100)};
        float size = G_RAND.GetFloat(-30,30);
        if (size < 3) { size = 20; }
        float angle = 2*M_PI/(i+3);
        for(int j=1;j<(8+4);j++){
            points.push_back(Vec2(cos(angle*j),sin(angle*j))*size);
        }
        polygon p(points);
        p.pos=pos;
        p.ang_vel = G_RAND.GetFloat(-M_PI/5000.0f, M_PI/5000.0f);
        polygons.push_back(p); 
    }

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
        poly.pos = (GetMousePosition()-Vec2(WIND_W/2.0f,WIND_H/2.0f))+Vec2(cam_pos.x,-cam_pos.y);
        float rot_add = 0;
        switch ((int)GetMouseWheelMove()){
            case -1:
                rot_add = 0.1;
                break;
            case 0:
                break;
            case 1:
                rot_add = -0.1;
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

        //collision = poly.aabb.CheckCollision(polygons[2].aabb);
        // ---- Polygon Update ----
    //todo : just aabb check before collision check, then compare heavy polygon count fps
        EndMode2D();

        // ---- UI ----
        DrawText(TextFormat("POSITION | x: %f y:%f ",cam_pos.x,cam_pos.y), 6, 6, 18, BLACK);

        DrawFPS(6,40);
        string text = collision == 0 ? "false" : "true";
        Color col = collision == 0 ? RED : GREEN;
        DrawText(TextFormat("COLLISION | %s",text.c_str()), 6, 18+9, 18, col);
        // ---- UI ----

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
