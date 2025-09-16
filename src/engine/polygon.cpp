#include <cassert>
#include <cmath>
#include"../../include/external/raylib/raylib.h"
#include"../../include/external/raylib/raymath.h"
#include"../../include/engine/polygon.h"
#include"../../include/engine/vec2.h"

//IDEA: make vertical chunks, and sort the polygons by their low and high x or y values (all inbetweens too)

void c2d::polygon::InitVertOffNMag(){
    for(Vec2 v : verts){
        float angle = atan2(v.y,v.x);
        float magnitude = Vector2Length(v.toRVec());
        angle+=M_PI;
        verts_ang_magn.push_back({angle,magnitude});
    }
}

void c2d::polygon::UpdateVertPos(){
    for(int i=0;i<num_vtx;i++){
        float angle = rot+verts_ang_magn[i].x;
        float magnitude = verts_ang_magn[i].y;
        angle+=M_PI;
        verts[i] = (Vec2(cos(angle),sin(angle))*magnitude);
    }
}

//Update function
void c2d::polygon::Update(){
    //Ensure that we don't have an empty polygon
    if(this->num_vtx == 0){
        assert("POLYGON: number of verticies is zero!");
    }
    this->pos+=this->vel;
    this->rot+=this->ang_vel;

    UpdateVertPos();

    GetAABB();
    //aabb.DrawDbg();

    UpdateFaceNormals();
    GetMaxMin();
}

void c2d::polygon::DrawDbg(){
    Vec2 dpos = GetDrawPos();
    DrawLineV(((this->pos+this->verts[0])).toRVec(),((this->pos+this->verts[1])).toRVec(),BLACK);
    for(int i=0;i<this->num_vtx;i++){
        DrawCircleV(verts[i].GetWorldPos(*this).toRVec(), 2, BLACK);
        if(i != 0){
            DrawLineV(( (this->pos+this->verts[i-1])).toRVec(),((this->pos+this->verts[i])).toRVec(),BLACK);
        }
    }
    DrawLineV(((this->pos+this->verts[num_vtx-1])).toRVec(),((this->pos+this->verts[0])).toRVec(),BLACK);
}

void c2d::polygon::UpdateFaceNormals(){
    face_norms.clear();
    for(int i=1;i<num_vtx;i++){
        Vec2 pre_rot = verts[i-1]-verts[i];
        Vec2 pre_norm = {pre_rot.y,-pre_rot.x};
        face_norms.push_back(Vector2Normalize((pre_norm).toRVec()));
    }
}

void c2d::polygon::GetMaxMin(){
    Vec2 _max_x = Vec2(-1,-1);
    Vec2 _max_y = Vec2(-1,-1);
    Vec2 _min_x = Vec2(pow(10,9),pow(10,9));
    Vec2 _min_y = Vec2(pow(10,9),pow(10,9));

    for(Vec2 vertex : verts){
        if(vertex.x > _max_x.x){ _max_x = vertex;
                                  max_x = (vertex+pos); }

        if(vertex.x < _min_x.x){ _min_x = vertex;
                                  min_x = (vertex+pos); }

        if(vertex.y > _max_y.y){ _max_y = vertex;
                                  max_y = (vertex+pos); }

        if(vertex.y < _min_y.y){ _min_y = vertex;
                                  min_y = (vertex+pos); }
    }
}

c2d::Vec2 c2d::polygon::GetDrawPos(){
    return pos*Vec2(1,-1);
}


bool c2d::polygon::CheckCollision_part1(polygon other){
    int i = 0;
    for(Vec2 f : face_norms){
        float min_0 = pow(10,9);
        float max_0 = -pow(10,9);
        for(Vec2 v : verts){
            float dot = (v.GetWorldPos(*this)).Dot(f);
            min_0 = dot < min_0 ? dot : min_0;
            max_0 = dot > max_0 ? dot : max_0;
        }
        
        float min_1 = pow(10,9);
        float max_1 = -pow(10,9);
        for(Vec2 v : other.verts){
            //Vec2 l = Vec2(v.x+other.pos.x,v.y+other.pos.y);
            Vec2 l = v.GetWorldPos(other);
            float dot = l.Dot(f);
            min_1 = dot < min_1 ? dot : min_1;
            max_1 = dot > max_1 ? dot : max_1;
        }
        if( (max_1 < min_0) || (min_1 > max_0)){
            return false;
        }
        /*if(i==0){
        DrawLine(f.x*-500,f.y*-500,f.x*50,f.y*50,MAROON);
        DrawCircle(max_0,0, 3,GREEN);
        DrawCircle(min_0,0, 3,DARKGREEN);
        DrawCircle(max_1,0, 3,BLUE);
        DrawCircle(min_1,0, 3,DARKBLUE);
        }*/
    }

    return true;
}
bool c2d::polygon::CheckCollision(polygon p){
    if (!aabb.CheckCollision(p.aabb)) { return false; }
    if (!this->CheckCollision_part1(p)) { return false; }
    return p.CheckCollision_part1(*this);
}

c2d::AABB c2d::polygon::GetAABB(){
    float max_x = NAN;
    float min_x = NAN;
    
    float max_y = NAN;
    float min_y = NAN;

    for(Vec2 v : verts){
        if (v.x > max_x || std::isnan(max_x)) { max_x = v.x; }
        if (v.x < min_x || std::isnan(min_x)) { min_x = v.x; }
        
        if (v.y > max_y || std::isnan(max_y)) { max_y = v.y; }
        if (v.y < min_y || std::isnan(min_y)) { min_y = v.y; }
    }

    //Due to the annoying coordinate flip
    return AABB(Vec2(min_x,min_y).GetWorldPos(*this),Vec2(max_x,max_y).GetWorldPos(*this));
}
