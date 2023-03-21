#ifndef _LCD2_PAGES_H_
#define _LCD2_PAGES_H_

#include "display/lvgl.h"

#define LINES 8

namespace lcd2::pages {
typedef struct {
    lv_style_t style;
    lv_obj_t* lines[LINES];
} page_ext_t;
void init(lv_obj_t* tabview, char** titles);
}

#endif