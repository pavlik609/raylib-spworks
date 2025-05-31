#pragma once

#include "vec2.h"
#include <cassert>
#include <iostream>
#include "../external/raylib/raylib.h"
#include "../external/raylib/raymath.h"
#include<vector>

//Collision 2D
namespace c2d{

class polygon{
public:
    int num_vtx;
    std::vector<Vec2> verts;
    std::vector<Vec2> verts_ang_magn;
    std::vector<Vec2> face_norms;
    Vec2 pos;
    Vec2 draw_pos;
    Vec2 max_x, max_y;
    Vec2 min_x, min_y;
    float rot;

    Vector2 vel;
    float ang_vel;

    polygon(std::vector<Vec2> _verts){
        verts = _verts;
        num_vtx = _verts.size();
        pos = {0,0};
        rot = 0.0f;
        ang_vel = 0.0f;
        vel = {0,0};
        InitVertOffNMag();
        UpdateFaceNormals();
        GetMaxMin();
        GetDrawPos();
    };

    polygon(Vector2 _pos, std::vector<Vec2> _verts){
        verts = _verts;
        num_vtx = _verts.size();
        pos = _pos;
        rot = 0.0f;
        ang_vel = 0.0f;
        vel = {0,0};
        InitVertOffNMag();
        UpdateFaceNormals();
        GetMaxMin();
        GetDrawPos();
    };

    void InitVertOffNMag();
    void UpdateVertPos();
    void Update();
    void DrawDbg();
    void UpdateFaceNormals();
    void GetMaxMin();
    bool CheckCollision_part1(polygon);
    bool CheckCollision(polygon);
    Vec2 GetDrawPos();
};


}
