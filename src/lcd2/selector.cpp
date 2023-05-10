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
lv_style_t red_btnm_style;
lv_style_t red_btn_style;
lv_style_t blue_btnm_style;
lv_style_t blue_btn_style;
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
    lv_obj_set_pos(red_btnm, 0, 20);
    //lv_obj_align(red_btnm, NULL, LV_ALIGN_CENTER, 0, -50);
    /* lv_style_copy(&red_btnm_style, lv_theme_get_alien()->btnm.bg);
    red_btnm_style.body.border.color = lv_color_hsv_to_rgb(0, 60, 80);
    lv_btnm_set_style(red_btnm, LV_BTNM_STYLE_BG, &red_btnm_style);
    lv_style_copy(&red_btn_style, lv_theme_get_alien()->btnm.btn.tgl_rel);
    red_btn_style.body.border.color = lv_color_hsv_to_rgb(0, 80, 80);
    lv_btnm_set_style(red_btnm, LV_BTNM_STYLE_BTN_TGL_REL, &red_btn_style);

    blue_btnm = lv_btnm_create(page, NULL);
    lv_btnm_set_map(blue_btnm, map);
    lv_btnm_set_action(blue_btnm, blue_btnm_action);
    lv_obj_set_size(blue_btnm, 450, 50);
    lv_obj_set_pos(blue_btnm, 0, 70);
    //lv_obj_align(blue_btnm, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_style_copy(&blue_btnm_style, lv_theme_get_alien()->btnm.bg);
    blue_btnm_style.body.border.color = lv_color_hsv_to_rgb(240, 60, 80);
    lv_btnm_set_style(blue_btnm, LV_BTNM_STYLE_BG, &blue_btnm_style);
    lv_style_copy(&blue_btn_style, lv_theme_get_alien()->btnm.btn.tgl_rel);
    blue_btn_style.body.border.color = lv_color_hsv_to_rgb(240, 80, 80);
    lv_btnm_set_style(blue_btnm, LV_BTNM_STYLE_BTN_TGL_REL, &blue_btn_style); */

    skills_btnm = lv_btnmatrix_create(page);
    lv_btnmatrix_set_map(skills_btnm, skills_map);
    lv_obj_add_event_cb(skills_btnm, skills_btnm_action, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_set_size(skills_btnm, 450, 50);
    lv_obj_set_pos(skills_btnm, 0, 120);
    //lv_obj_align(skills_btnm, NULL, LV_ALIGN_CENTER, 0, 50);

    render();
    initialized = true;
}
}