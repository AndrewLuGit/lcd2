#ifndef _LCD2_LOG_H_
#define _LCD2_LOG_H_

#include "display/lvgl.h"
#include <string>

namespace lcd2::log {
void init(lv_obj_t* page);
void print(std::string text);
}

#endif