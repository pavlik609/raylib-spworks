#include "../../include/engine/drawing.h"
#include "../../include/engine/vec2.h"
#include "../../include/external/raylib/raylib.h"

std::list<spworks::drawing::ATextureZOrder> spworks::drawing::sprite_buffer = {};

void spworks::drawing::DrawSquashText(RenderTexture2D* r,std::string text, float width_to_fit,Font font, float size,c2d::Vec2 pos, float spacing){
    BeginTextureMode(*r);
    ClearBackground(BLANK);
    DrawTextEx(font, text.c_str(), {0,0}, size, spacing, GRAY);
    EndTextureMode();

    float squish_coeff = MeasureTextEx(font, text.c_str(), size, spacing).x/width_to_fit;
    DrawTexturePro(r->texture, {0,0,r->texture.width*squish_coeff,-r->texture.height*1.0f},{pos.x,pos.y,r->texture.width*1.0f,r->texture.height*1.0f}, {0,0}, 0, WHITE);
}

void spworks::drawing::DrawFromAtlas(spworks::drawing::ATexture texture, c2d::Vec2 pos, c2d::Vec2 scale, c2d::Vec2 pivot, float rotation, Color color){
    DrawTexturePro(*texture.atlas, texture.dimensions, {(float)pos.x,(float)pos.y,(float)texture.dimensions.width*scale.x,texture.dimensions.height*scale.y}, pivot.toRVec(), rotation, color);
}

void spworks::drawing::DrawFromAtlasZOrder(ATexture texture, c2d::Vec2 pos, c2d::Vec2 scale, c2d::Vec2 pivot, float rotation, Color color){
    sprite_buffer.push_back(ATextureZOrder(texture,pos, scale, pivot, rotation, color));
}

void spworks::drawing::DrawZOrderList(){
    if(sprite_buffer.size() == 0) { return; }
    sprite_buffer.sort();
    for(ATextureZOrder atexz : sprite_buffer){
        DrawTexturePro(*atexz.tex.atlas, atexz.tex.dimensions, {atexz.pos.x,atexz.pos.y,atexz.tex.dimensions.width*atexz.scale.x,atexz.tex.dimensions.height*atexz.scale.y}, atexz.pivot.toRVec(), atexz.rotation, atexz.color);
    }
    sprite_buffer.clear();
}

