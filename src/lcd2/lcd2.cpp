#include "lcd2/lcd2.h"

#include "api.h"

#define MAX_LINE_LENGTH 53
#define TEXT_LINES 8

namespace lcd2 {
lv_obj_t* tab_view;

lv_obj_t* text_view;
lv_obj_t* lines[TEXT_LINES];
lv_style_t text_style;

lv_obj_t* selector_view;
lv_obj_t* selector_btnm;
const char* map[] = {"Red", "\n", "Blue", "\n", "Skills", ""};
char auton[MAX_LINE_LENGTH] = "";

lv_res_t selector_btnm_action(lv_obj_t* btnm, const char* text) {
    strcpy(auton, text);
    if (!strcmp(text, "Red")) {
        lv_btnm_set_toggle(btnm, true, 0);
    } else if (!strcmp(text, "Blue")) {
        lv_btnm_set_toggle(btnm, true, 2);
    } else {
        lv_btnm_set_toggle(btnm, true, 4);
    }
    return LV_RES_OK;
}

void initialize() {
    tab_view = lv_tabview_create(lv_scr_act(), NULL);

    text_view = lv_tabview_add_tab(tab_view, "Text");
    lv_page_set_sb_mode(text_view, LV_SB_MODE_OFF);
    lv_style_copy(&text_style, &lv_style_plain);
    text_style.text.font = &pros_font_dejavu_mono_20;

    for (int i = 0; i < TEXT_LINES; i++) {
        lines[i] = lv_label_create(text_view, NULL);
        lv_obj_align(lines[i], NULL, LV_ALIGN_IN_TOP_LEFT, 5, 20 * (i + 1));
        lv_label_set_align(lines[i], LV_LABEL_ALIGN_LEFT);
        lv_label_set_long_mode(lines[i], LV_LABEL_LONG_EXPAND);
        lv_label_set_text(lines[i], "");
    }

    selector_view = lv_tabview_add_tab(tab_view, "Autons");
    lv_page_set_sb_mode(selector_view, LV_SB_MODE_OFF);
    selector_btnm = lv_btnm_create(selector_view, NULL);
    lv_btnm_set_map(selector_btnm, map);
    lv_btnm_set_action(selector_btnm, selector_btnm_action);
    lv_obj_set_size(selector_btnm, 450, 150);
    lv_obj_set_pos(selector_btnm, 0, 0);
    lv_obj_align(selector_btnm, NULL, LV_ALIGN_CENTER, 0, 0);
}

bool vprintf(int line, const char* fmt, va_list args) {
    if (line < 0 || line >= TEXT_LINES) {
        return false;
    }
    char buf[MAX_LINE_LENGTH];
    vsnprintf(buf, MAX_LINE_LENGTH, fmt, args);

    lv_label_set_text(lines[line], buf);
    return true;
}

bool printf(int line, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    bool res = vprintf(line, fmt, args);
    va_end(args);
    return res;
}

bool print(int line, const char* text) {
    return printf(line, "%s", text);
}
}