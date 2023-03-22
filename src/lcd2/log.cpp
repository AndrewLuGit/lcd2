#include "log.h"

#include "api.h"
#include <list>

#define LOG_LINES 5

namespace lcd2::log {
std::list<std::string> history = {};
auto pointer = history.begin();
int index = 0;
lv_obj_t* btnm;
lv_obj_t* lines[LOG_LINES];
const char* btnmap[] = {SYMBOL_UP, SYMBOL_DOWN, ""};

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

lv_res_t btnm_action(lv_obj_t* btnm, const char* text) {
    if (!strcmp(text, SYMBOL_UP) && index > 0) { // up
        index--;
        pointer--;
    } else if (!strcmp(text, SYMBOL_DOWN) && index < history.size() - 1) { // down
        index++;
        pointer++;
    }

    render();
    return LV_RES_OK;
}

void init(lv_obj_t* page) {
    btnm = lv_btnm_create(page, NULL);
    lv_btnm_set_map(btnm, btnmap);
    lv_btnm_set_action(btnm, btnm_action);
    lv_obj_set_size(btnm, 450, 50);
    lv_obj_set_pos(btnm, 0, 20);
    lv_obj_align(btnm, NULL, LV_ALIGN_CENTER, 0, 0);

    for (int i = 0; i < LOG_LINES; i++) {
        lines[i] = lv_label_create(page,NULL);
        lv_obj_align(lines[i], NULL, LV_ALIGN_IN_TOP_LEFT, 5, 70 + 20 * i);
        lv_label_set_align(lines[i], LV_LABEL_ALIGN_LEFT);
        lv_label_set_long_mode(lines[i], LV_LABEL_LONG_EXPAND);
        lv_label_set_text(lines[i], "");
    }
}

void print(std::string text) {
    history.push_back(text);
    if (history.size() == 1) {
        index = 0;
        pointer = history.begin();
    } else {
        index++;
        pointer++;
    }
    render();
}
}