#include "../../include/engine/vec2.h"
#include "../../include/engine/aabb.h"

#include<iostream>

c2d::Vec2 c2d::AABB::GetDownLeft(){
    return Vec2(ul.x,dr.y);
}


c2d::Vec2 c2d::AABB::GetUpRight(){
    return Vec2(dr.x,ul.y);
}

bool c2d::AABB::CheckCollision(AABB other){
    if( (other.dr.x < ul.x) || (other.ul.x > dr.x)){
            return false;
    }
    if( (other.dr.y < ul.y) || (other.ul.y > dr.y)){
            return false;
    }
    return true;
}

void c2d::AABB::DrawDbg(){
    DrawCircleV(dr.toRVec(),4,RED);
    DrawCircleV(ul.toRVec(),4,BLUE);
    DrawLineV(ul.toRVec(),GetDownLeft().toRVec(),DARKBLUE);
    DrawLineV(ul.toRVec(),GetUpRight().toRVec(),DARKBLUE);
    DrawLineV(dr.toRVec(),GetDownLeft().toRVec(),MAROON);
    DrawLineV(dr.toRVec(),GetUpRight().toRVec(),MAROON);
}
