#pragma once

#include"../external/raylib/raylib.h"

namespace c2d{

class polygon;

//Wrapper class
class Vec2{
public:
    float x,y;

    Vec2& operator+=(Vec2 const& rhs)& {
        x+=rhs.x;
        y+=rhs.y;
        return *this;
    }
    //Why does the friend have to be here???? i don't understand c++ oop...
    friend Vec2 operator+(Vec2 lhs, Vec2 const& rhs){
        lhs+=rhs;
        return lhs;
    }

    Vec2& operator-=(Vec2 const& rhs)& {
        x-=rhs.x;
        y-=rhs.y;
        return *this;
    }
    //Why does the friend have to be here???? i don't understand c++ oop...
    friend Vec2 operator-(Vec2 lhs, Vec2 const& rhs){
        lhs-=rhs;
        return lhs;
    }

    Vec2& operator*=(Vec2 const& rhs)& {
        x*=rhs.x;
        y*=rhs.y;
        return *this;
    }
    //Why does the friend have to be here???? i don't understand c++ oop...
    friend Vec2 operator*(Vec2 lhs, Vec2 const& rhs){
        lhs*=rhs;
        return lhs;
    }

    Vec2& operator*=(float const& rhs)& {
        x*=rhs;
        y*=rhs;
        return *this;
    }
    //Why does the friend have to be here???? i don't understand c++ oop...
    friend Vec2 operator*(Vec2 lhs,float  rhs){
        lhs*=rhs;
        return lhs;
    }

    Vec2(){
        x=0;
        y=0;
    }
    Vec2(float _x, float _y){
        x=_x;
        y=_y;
    }
    Vec2(Vector2 v){
        x=v.x;
        y=v.y;
    }

    Vector2 toRVec();
    Vec2 GetWorldPos(polygon);
    float Dot(Vec2);
};

}
