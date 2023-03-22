#ifndef _LCD2_PAGES_H_
#define _LCD2_PAGES_H_

#include "display/lvgl.h"

#define PAGE_LINES 8

namespace lcd2::pages {
typedef struct {
    lv_style_t style;
    lv_obj_t* lines[PAGE_LINES];
} page_ext_t;
void init(lv_obj_t* tabview, const char** titles);

bool print_line(int page, int line, const char* fmt, ...);
bool set_line(int page, int line, const char* text);

bool clear_line(int page, int line);
bool clear_page(int page);
bool clear_all();

bool set_background_color(int page, lv_color_t color);
bool set_text_color(int page, lv_color_t color);
}

#endif