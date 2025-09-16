#pragma once

#include "../external/raylib/raylib.h"
#include "vec2.h"
#include <list>
#include <string>

namespace spworks {

namespace drawing{

struct ATexture {
    Texture* atlas;
    Rectangle dimensions;
};

struct ATextureZOrder{
    ATexture tex;
    
    c2d::Vec2 pos = {0,0};
    c2d::Vec2 scale = {1,1};
    c2d::Vec2 pivot = {0,0};
    float rotation = 0;
    Color color = WHITE;

    bool operator<(ATextureZOrder rhs){
        return pos.y<rhs.pos.y;
    }

    bool operator>(ATextureZOrder rhs){
        return pos.y>rhs.pos.y;
    }

    ATextureZOrder(ATexture tex,c2d::Vec2 pos,c2d::Vec2 scale,c2d::Vec2 pivot, float rotation, Color color) : 
        tex(tex),
        pos(pos), 
        scale(scale), 
        pivot(pivot), 
        rotation(rotation), 
        color(color) 
    {};
};

extern void DrawSquashText(RenderTexture2D* r,std::string text, float width_to_fit,Font font, float size,c2d::Vec2 pos, float spacing);

extern void DrawFromAtlas(ATexture texture, c2d::Vec2 pos, c2d::Vec2 scale, c2d::Vec2 pivot, float rotation, Color color);

extern void DrawFromAtlasZOrder(ATexture texture, c2d::Vec2 pos, c2d::Vec2 scale, c2d::Vec2 pivot, float rotation, Color color);

extern void DrawZOrderList();

extern std::list<ATextureZOrder> sprite_buffer;

}


}


