#include"../../include/external/raylib/raylib.h"
#include"../../include/engine/vec2.h"
#include"../../include/engine/polygon.h"

Vector2 c2d::Vec2::toRVec(){
    return (Vector2){this->x,this->y};
}

c2d::Vec2 c2d::Vec2::GetWorldPos(polygon p){
    return Vec2(this->x+p.pos.x,this->y+p.pos.y);
}

float c2d::Vec2::Dot(Vec2 v){
    return x*v.x+y*v.y;
}
