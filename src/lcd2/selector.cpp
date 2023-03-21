#include "selector.h"

#define MAX_AUTONS 10

namespace lcd2::selector {
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

lv_res_t red_btnm_action(lv_obj_t* btnm, const char* text) {
    auton = lv_btnm_get_pressed(btnm) + 1;
    render();
    return LV_RES_OK;
}

lv_res_t blue_btnm_action(lv_obj_t* btnm, const char* text) {
    auton = -lv_btnm_get_pressed(btnm) - 1;
    render();
    return LV_RES_OK;
}

lv_res_t skills_btnm_action(lv_obj_t* btnm, const char* text) {
    auton = 0;
    render();
    return LV_RES_OK;
}

int get_auton() {
    return auton;
}

void render() {
    if (auton = 0) { // skills
        lv_btnm_set_toggle(red_btnm, false, 0);
        lv_btnm_set_toggle(blue_btnm, false, 0);
        lv_btnm_set_toggle(skills_btnm, true, 0);
    } else if (auton > 0) { // red
        lv_btnm_set_toggle(red_btnm, true, auton - 1);
        lv_btnm_set_toggle(blue_btnm, false, 0);
        lv_btnm_set_toggle(skills_btnm, false, 0);
    } else { // blue
        lv_btnm_set_toggle(red_btnm, false, 0);
        lv_btnm_set_toggle(blue_btnm, true, -auton - 1);
        lv_btnm_set_toggle(skills_btnm, false, 0);
    }
}

void init(lv_obj_t* page, char** autons, int default_auton) {
    while (autons[auton_count][0] != '\0' && auton_count < MAX_AUTONS) {
        map[auton_count] = autons[auton_count];
        auton_count++;
    }
    map[auton_count] = "";
    auton = default_auton;

    red_btnm = lv_btnm_create(page, NULL);
    lv_btnm_set_map(red_btnm, map);
    lv_btnm_set_action(red_btnm, red_btnm_action);
    lv_obj_set_size(red_btnm, 450, 50);
    lv_obj_set_pos(red_btnm, 0, 0);
    lv_obj_align(red_btnm, NULL, LV_ALIGN_CENTER, 0, -50);
    lv_style_copy(&red_btnm_style, lv_theme_get_alien()->btnm.bg);
    red_btnm_style.body.border.color = lv_color_hsv_to_rgb(0, 60, 80);
    lv_btnm_set_style(red_btnm, LV_BTNM_STYLE_BG, &red_btnm_style);
    lv_style_copy(&red_btn_style, lv_theme_get_alien()->btnm.btn.tgl_rel);
    red_btn_style.body.border.color = lv_color_hsv_to_rgb(0, 80, 80);
    lv_btnm_set_style(red_btnm, LV_BTNM_STYLE_BTN_TGL_REL, &red_btn_style);

    blue_btnm = lv_btnm_create(page, NULL);
    lv_btnm_set_map(blue_btnm, map);
    lv_btnm_set_action(blue_btnm, blue_btnm_action);
    lv_obj_set_size(blue_btnm, 450, 50);
    lv_obj_set_pos(blue_btnm, 0, 50);
    lv_obj_align(blue_btnm, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_style_copy(&blue_btnm_style, lv_theme_get_alien()->btnm.bg);
    blue_btnm_style.body.border.color = lv_color_hsv_to_rgb(240, 60, 80);
    lv_btnm_set_style(blue_btnm, LV_BTNM_STYLE_BG, &blue_btnm_style);
    lv_style_copy(&blue_btn_style, lv_theme_get_alien()->btnm.btn.tgl_rel);
    blue_btn_style.body.border.color = lv_color_hsv_to_rgb(240, 80, 80);
    lv_btnm_set_style(blue_btnm, LV_BTNM_STYLE_BTN_TGL_REL, &blue_btn_style);

    skills_btnm = lv_btnm_create(page, NULL);
    lv_btnm_set_map(skills_btnm, skills_map);
    lv_btnm_set_action(skills_btnm, skills_btnm_action);
    lv_obj_set_size(skills_btnm, 450, 50);
    lv_obj_set_pos(skills_btnm, 0, 100);
    lv_obj_align(skills_btnm, NULL, LV_ALIGN_CENTER, 0, 50);

    render();
}
}