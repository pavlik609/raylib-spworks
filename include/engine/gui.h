#pragma once

#include <string>
#include "../external/raylib/raylib.h"
#include "aabb.h"
#include "drawing.h"
#include "vec2.h"

namespace spworks {

namespace gui {

extern bool button_hovering;
extern bool button_clicked;

struct gui_window{
    float width = 100;
    float height = 100;
    float x_offset = 50;
    float y_offset = 0;

    bool draw = false;

    void DrawBase(float w_width, float w_height){
        float r_x = (w_width-width)/2.0f;
        float r_y = (w_height-height)/2.0f;
        DrawRectangle(r_x-2-x_offset, r_y-2, width+4, height+4, BLACK);
        DrawRectangle(r_x-x_offset, r_y, width, height, WHITE);
    }

    gui_window(float width, float height) : width(width), height(height) {};
};

struct gui_panel{
    c2d::Vec2 pos = c2d::Vec2(0,0);
    float width = 100;
    float height = 100;
    float padding = 2;
    
    float upper_next = padding;
    float bottom_next = height-padding;

    gui_panel(c2d::Vec2 pos,float width, float height) : pos(pos), width(width), height(height) {
        upper_next = padding;
        bottom_next = height-padding;
    }

    void DrawBase(){
        upper_next = padding;
        bottom_next = height-padding;
        DrawRectangle(pos.x-2, pos.y-2, width+4, height+4, BLACK);
        DrawRectangle(pos.x, pos.y, width, height, WHITE);
    }

    c2d::Vec2 GetUpperNext(float _width, float _height){
        c2d::Vec2 retval = {pos.x+(this->width-_width)/2.0f,upper_next};
        upper_next+=_height+padding;
        return retval;
    }

    c2d::Vec2 GetBottomNext(float _width, float _height){
        c2d::Vec2 retval = {pos.x+(this->width-_width)/2.0f,bottom_next-_height};
        bottom_next-=(_height+padding);
        return retval;
    }
};

extern void DrawButton(spworks::drawing::ATexture* texture, c2d::Vec2 pos, void(*func)(),c2d::AABB aabb);
extern void DrawButton(Rectangle rec, void(*func)(),c2d::AABB aabb);

}
}
