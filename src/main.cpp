#include "main.h"
#include "lcd2/log.h"
#include "lcd2/selector.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
/* 	lv_theme_t *th = lv_theme_default_init(lv_disp_get_default(),
										lv_palette_main(LV_PALETTE_BLUE),
										lv_palette_main(LV_PALETTE_RED),
										true,
										LV_FONT_DEFAULT); */
	lv_theme_t *th = lv_theme_mono_init(lv_disp_get_default(), true, LV_FONT_DEFAULT);
	lv_disp_set_theme(lv_disp_get_default(), th);
	lv_obj_t* tab_view = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 3 * LV_DPI / 8);
	lv_obj_t* log_page = lv_tabview_add_tab(tab_view, "Log");
    lcd2::log::init(log_page);
	lv_obj_t* selector_page = lv_tabview_add_tab(tab_view, "Autons");
	const char* autons[] = {"Front", "Back", "Do Nothing", ""};
	lcd2::selector::init(selector_page, autons, 0);
	for (int i = 0; i < 10; i++) {
		lcd2::log::print("Log " + std::to_string(i));
	}
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	while (true) {
		pros::delay(20);
	}
}