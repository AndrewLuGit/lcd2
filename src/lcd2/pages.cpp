#include "pages.h"

#include "api.h"

#define MAX_LINE_LENGTH 39
#define PAGE_OFFSET 2

namespace lcd2::pages {
lv_obj_t* tab;
int page_count = 0;

void init(lv_obj_t* tabview, char** titles) {
    tab = tabview;

    while (titles[page_count][0] != '\0') {
        lv_obj_t* page = lv_tabview_add_tab(tabview, titles[page_count]);
        page_ext_t* ext = (page_ext_t*) lv_obj_allocate_ext_attr(page, sizeof(page_ext_t));
        lv_page_set_sb_mode(page, LV_SB_MODE_OFF);
        lv_style_copy(&ext->style, lv_theme_get_alien()->bg);
        ext->style.text.font = &pros_font_dejavu_mono_20;
        ext->style.body.padding.hor = 5;
        ext->style.body.padding.ver = 5;
        ext->style.body.padding.inner = 0;
        lv_obj_set_style(page, &ext->style);

        for (int i = 0; i < LINES; i++) {
            ext->lines[i] = lv_label_create(page, NULL);
            lv_obj_align(ext->lines[i], NULL, LV_ALIGN_IN_TOP_LEFT, 5, 20 * (i + 1));
            lv_label_set_align(ext->lines[i], LV_LABEL_ALIGN_LEFT);
            lv_label_set_long_mode(ext->lines[i], LV_LABEL_LONG_EXPAND);
            lv_label_set_text(ext->lines[i], "");
        }
    }
}

bool print_internal(int page, int line, const char* fmt, va_list args) {
    if (page < 0 || page >= page_count) {
        return false;
    }
    if (line < 0 || line >= LINES) {
        return false;
    }

    page_ext_t* ext = (page_ext_t*) lv_obj_get_ext_attr(lv_tabview_get_tab(tab, PAGE_OFFSET + page));
    char buf[MAX_LINE_LENGTH];
    vsnprintf(buf, MAX_LINE_LENGTH, fmt, args);

    lv_label_set_text(ext->lines[line], buf);
    return true;
}

bool print_line(int page, int line, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    bool res = print_internal(page, line, fmt, args);
    va_end(args);
    return res;
}

bool set_line(int page, int line, const char* text) {
    return print_line(page, line, "%s", text);
}

bool clear_line(int page, int line) {
    if (page < 0 || page >= page_count) {
        return false;
    }
    if (line < 0 || line >= LINES) {
        return false;
    }

    page_ext_t* ext = (page_ext_t*) lv_obj_get_ext_attr(lv_tabview_get_tab(tab, PAGE_OFFSET + page));
    lv_label_set_text(ext->lines[line], "");
    return true;
}

bool clear_page(int page) {
    for (int i = 0; i < LINES; i++) {
        clear_line(page, i);
    }
}

bool clear_all() {
    for (int i = 0; i < page_count; i++) {
        clear_page(i);
    }
}

bool set_background_color(int page, lv_color_t color) {
    if (page < 0 || page >= page_count) {
        return false;
    }
    page_ext_t* ext = (page_ext_t*) lv_obj_get_ext_attr(lv_tabview_get_tab(tab, PAGE_OFFSET + page));
    ext->style.body.main_color = color;
    ext->style.body.grad_color = color;
    return true;
}

bool set_text_color(int page, lv_color_t color) {
    if (page < 0 || page >= page_count) {
        return false;
    }
    page_ext_t* ext = (page_ext_t*) lv_obj_get_ext_attr(lv_tabview_get_tab(tab, PAGE_OFFSET + page));
    ext->style.text.color = color;
    return true;
}
}