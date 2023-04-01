#include "lcd2/base.h"

#include "display/lvgl.h"
#include "lcd2/selector.h"
#include "lcd2/log.h"
#include "lcd2/pages.h"

namespace lcd2 {

void initialize(lcd2_parameters parameters) {
    lv_obj_t* tab_view = lv_tabview_create(lv_scr_act(), NULL);
    if (strlen(parameters.autons[0]) != 0) {
        lv_obj_t* selector_page = lv_tabview_add_tab(tab_view, "Autons");
        lcd2::selector::init(selector_page, parameters.autons, parameters.default_auto);
        lv_page_set_sb_mode(selector_page, LV_SB_MODE_OFF);
    }
    if (parameters.enable_log) {
        lv_obj_t* log_page = lv_tabview_add_tab(tab_view, "Log");
        lcd2::log::init(log_page);
        lv_page_set_sb_mode(log_page, LV_SB_MODE_OFF);
    }
    lcd2::pages::init(tab_view, parameters.page_titles);
}
}