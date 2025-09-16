#include "../../include/engine/gui.h"
#include "../../include/engine/drawing.h"

bool spworks::gui::button_hovering = false;
bool spworks::gui::button_clicked = false;

void spworks::gui::DrawButton(spworks::drawing::ATexture* texture, c2d::Vec2 pos, void(*func)(),c2d::AABB aabb){ 
    Color c = WHITE;
    c2d::AABB button_coll = {pos,pos+c2d::Vec2(texture->dimensions.width,texture->dimensions.height)};
    if(button_coll.CheckCollision(aabb)){
        button_hovering = true;
        c = YELLOW;
        if(IsMouseButtonPressed(0)){
            button_clicked = true;
            func();
            c = DARKGRAY;
        }
    }
    spworks::drawing::DrawFromAtlas(*texture, pos, {1,1}, {0,0}, 0, c);
}

void spworks::gui::DrawButton(Rectangle rec, void(*func)(),c2d::AABB aabb){ 
    Color c = GRAY;
    c2d::AABB button_coll = {{rec.x,rec.y},c2d::Vec2(rec.x,rec.y)+c2d::Vec2(rec.width,rec.height)};
    if(button_coll.CheckCollision(aabb)){
        button_hovering = true;
        c = YELLOW;
        if(IsMouseButtonPressed(0)){
            func();
            c = DARKGRAY;
        }
    }
    DrawRectangleLinesEx(rec,2,c);
}
