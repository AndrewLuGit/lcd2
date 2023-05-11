#include "selector.h"

#include "api.h"

#define MAX_AUTONS 10

namespace lcd2::selector {
bool initialized = false;
int auton = 0;
int auton_count = 0;
lv_obj_t* red_btnm;
lv_obj_t* blue_btnm;
lv_obj_t* skills_btnm;
const char* map[MAX_AUTONS + 1] = {};
const char* skills_map[] = {"Skills", ""};

void render() {
    lv_btnmatrix_clear_btn_ctrl_all(red_btnm, LV_BTNMATRIX_CTRL_CHECKED);
    lv_btnmatrix_clear_btn_ctrl_all(blue_btnm, LV_BTNMATRIX_CTRL_CHECKED);
    lv_btnmatrix_clear_btn_ctrl_all(skills_btnm, LV_BTNMATRIX_CTRL_CHECKED);
    if (auton == 0) { // skills
        lv_btnmatrix_set_btn_ctrl(skills_btnm, 0, LV_BTNMATRIX_CTRL_CHECKED);
    } else if (auton > 0) { // red
        lv_btnmatrix_set_btn_ctrl(red_btnm, auton - 1, LV_BTNMATRIX_CTRL_CHECKED);
    } else { // blue
        lv_btnmatrix_set_btn_ctrl(blue_btnm, -auton - 1, LV_BTNMATRIX_CTRL_CHECKED);
    }
}

void red_btnm_action(lv_event_t *event) {
    auton = lv_btnmatrix_get_selected_btn(red_btnm) + 1;
    render();
}

void blue_btnm_action(lv_event_t *event) {
    auton = -lv_btnmatrix_get_selected_btn(blue_btnm) - 1;
    render();
}

void skills_btnm_action(lv_event_t *event) {
    auton = 0;
    render();
}

int get_auton() {
    return auton;
}

void init(lv_obj_t* page, const char** autons, int default_auton) {
    lv_obj_clear_flag(page, LV_OBJ_FLAG_SCROLLABLE);
    while (autons[auton_count][0] != '\0' && auton_count < MAX_AUTONS) {
        map[auton_count] = autons[auton_count];
        auton_count++;
    }
    map[auton_count] = "";
    auton = default_auton;

    red_btnm = lv_btnmatrix_create(page);
    lv_btnmatrix_set_map(red_btnm, map);
    lv_obj_add_event_cb(red_btnm, red_btnm_action, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_set_size(red_btnm, 450, 50);
    lv_obj_align(red_btnm, LV_ALIGN_CENTER, 0, -50);
    lv_obj_set_style_pad_all(red_btnm, 6, 0);
    lv_obj_set_style_pad_row(red_btnm, 6, 0);
    lv_obj_set_style_pad_column(red_btnm, 6, 0);
    lv_obj_set_style_bg_color(red_btnm, lv_palette_main(LV_PALETTE_RED), LV_PART_ITEMS | LV_STATE_CHECKED);

    blue_btnm = lv_btnmatrix_create(page);
    lv_btnmatrix_set_map(blue_btnm, map);
    lv_obj_add_event_cb(blue_btnm, blue_btnm_action, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_set_size(blue_btnm, 450, 50);
    lv_obj_align(blue_btnm, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(blue_btnm, 6, 0);
    lv_obj_set_style_pad_row(blue_btnm, 6, 0);
    lv_obj_set_style_pad_column(blue_btnm, 6, 0);
    lv_obj_set_style_bg_color(blue_btnm, lv_palette_main(LV_PALETTE_BLUE), LV_PART_ITEMS | LV_STATE_CHECKED);

    skills_btnm = lv_btnmatrix_create(page);
    lv_btnmatrix_set_map(skills_btnm, skills_map);
    lv_obj_add_event_cb(skills_btnm, skills_btnm_action, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_set_size(skills_btnm, 450, 50);
    lv_obj_set_style_pad_all(skills_btnm, 6, 0);
    lv_obj_set_style_pad_row(skills_btnm, 6, 0);
    lv_obj_set_style_pad_column(skills_btnm, 6, 0);
    lv_obj_set_style_bg_color(skills_btnm, lv_palette_main(LV_PALETTE_YELLOW), LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_align(skills_btnm, LV_ALIGN_CENTER, 0, 50);

    render();
    initialized = true;
}
}