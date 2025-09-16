#pragma once

#include "vec2.h"

namespace c2d{

class AABB{
public:
    Vec2 pos;
    Vec2 ul; //Up Left
    Vec2 dr; //Down Right
    
    AABB(){
        ul = Vec2(-1,1);
        dr = Vec2(1,-1);
    }

    AABB(Vec2 _ul, Vec2 _dr){
        ul = _ul;
        dr = _dr;
    }
    Vec2 GetDownLeft();
    Vec2 GetUpRight();
    bool CheckCollision(AABB);
    void DrawDbg();
};

}
