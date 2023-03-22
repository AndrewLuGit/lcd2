#include "lcd2/lcd2.h"

#include "api.h"
#include "lcd2/selector.h"
#include "lcd2/log.h"
#include "lcd2/pages.h"

namespace lcd2 {
lv_obj_t* tab_view;
const char* autons[] = {"Front", "Back", "Do Nothing", ""};
const char* titles[] = {"Page 1", "Page 2", ""};

void initialize() {
    tab_view = lv_tabview_create(lv_scr_act(), NULL);
    lv_obj_t* selector_page = lv_tabview_add_tab(tab_view, "Autons");
    lcd2::selector::init(selector_page, autons, 0);
    lv_obj_t* log_page = lv_tabview_add_tab(tab_view, "Log");
    lcd2::log::init(log_page);
    lv_tabview_set_tab_act(tab_view, 1, true);
    lcd2::pages::init(tab_view, titles);
}
}