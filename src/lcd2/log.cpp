#include "log.h"

#include "api.h"
#include <list>

#define LOG_LINES 6

namespace lcd2::log {
bool initialized = false;
std::list<std::string> history = {};
auto pointer = history.begin();
int index = 0;
lv_obj_t* btnm;
lv_obj_t* lines[LOG_LINES];
const char* btnmap[] = {LV_SYMBOL_UP, LV_SYMBOL_DOWN, ""};

void render() {
    if (index < LOG_LINES || history.size() <= LOG_LINES) {
        auto iter = history.begin();
        for (int i = 0; i < LOG_LINES && iter != history.end(); i++, iter++) {
            lv_label_set_text(lines[i], (*iter).c_str());
        }
    } else {
        auto iter = pointer;
        for (int i = LOG_LINES - 1; i >= 0; i--, iter--) {
            lv_label_set_text(lines[i], (*iter).c_str());
        }
    }
}

void btnm_action(lv_event_t *event) {
    if (lv_btnmatrix_get_selected_btn(btnm) == 0 && index >= LOG_LINES) { // up
        index--;
        pointer--;
    } else if (lv_btnmatrix_get_selected_btn(btnm) == 1 && index < history.size() - 1) { // down
        index++;
        pointer++;
    }

    render();
}

void init(lv_obj_t* page) {
    lv_obj_set_style_pad_all(page, 6, 0);
    lv_obj_set_style_pad_row(page, 6, 0);
    lv_obj_set_style_pad_column(page, 6, 0);
    lv_obj_clear_flag(page, LV_OBJ_FLAG_SCROLLABLE);
    
    btnm = lv_btnmatrix_create(page);
    lv_obj_set_style_pad_all(btnm, 6, 0);
    lv_obj_set_style_pad_row(btnm, 6, 0);
    lv_obj_set_style_pad_column(btnm, 6, 0);
    lv_btnmatrix_set_map(btnm, btnmap);
    lv_obj_add_event_cb(btnm, btnm_action, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_set_size(btnm, 450, 50);
    lv_obj_align(btnm, LV_ALIGN_TOP_MID, 0, 0);

    for (int i = 0; i < LOG_LINES; i++) {
        lines[i] = lv_label_create(page);
        lv_obj_set_width(lines[i], 450);
        lv_obj_align(lines[i], LV_ALIGN_TOP_MID, 0, 60 + 20 * i);
        lv_label_set_long_mode(lines[i], LV_LABEL_LONG_CLIP);
        lv_label_set_text(lines[i], "");
    }
    initialized = true;
}

bool print(std::string text) {
    if (!initialized) {
        return false;
    }
    history.push_back(text);
    if (history.size() == 1) {
        index = 0;
        pointer = history.begin();
    } else {
        index++;
        pointer++;
    }
    render();
    return true;
}
}