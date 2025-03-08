/**
 * @file      lvgl9.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2025  Shenzhen Xinyuan Electronic Technology Co., Ltd
 * @date      2025-02-27
 * @note      This sketch is adapted to lvgl9 version. Please upgrade lvgl to lvgl 9 version,
 *            and rename <LilyGo-AMOLED-Series/src/lv_conf.h> to <lv_conf.h.v8> and <lv_conf.h.v9> to <lv_conf.h>
 */
#include <LilyGo_RGBPanel.h>
#include <LV_Helper.h>

LilyGo_RGBPanel panel;

static void set_angle(void * obj, int32_t v)
{
    lv_arc_set_value((lv_obj_t *)obj, v);
}

void setup()
{
    Serial.begin(115200);

    //** Four initialization methods */

    // Automatically determine the touch model to determine the initialization screen type. If touch is not available, it may fail.
    // bool rslt = panel.begin();

    // Specify 2.1-inch semicircular screen
    // https://www.lilygo.cc/products/t-rgb?variant=42407295877301
    // bool rslt = panel.begin(LILYGO_T_RGB_2_1_INCHES_HALF_CIRCLE);

    // Specified as a 2.1-inch full-circle screen
    // https://www.lilygo.cc/products/t-rgb
    bool rslt = panel.begin(LILYGO_T_RGB_2_1_INCHES_FULL_CIRCLE);

    // Specified as a 2.8-inch full-circle screen
    // https://www.lilygo.cc/products/t-rgb?variant=42880799441077
    // bool rslt = panel.begin(LILYGO_T_RGB_2_8_INCHES);

    if (!rslt) {
        while (1) {
            Serial.println("Error, failed to initialize T-RGB"); delay(1000);
        }
    }

    // Call lvgl initialization
    beginLvglHelper(panel);


#if LVGL_VERSION_MAJOR == 9
    /*Create an Arc*/
    lv_obj_t *arc = lv_arc_create(lv_screen_active());
    lv_arc_set_rotation(arc, 270);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_remove_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_center(arc);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, arc);
    lv_anim_set_exec_cb(&a, set_angle);
    lv_anim_set_duration(&a, 1000);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
    lv_anim_set_repeat_delay(&a, 500);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_start(&a);


    lv_obj_t *label = lv_label_create( lv_screen_active() );
    lv_label_set_text( label, "Hello Arduino, I'm LVGL!" );
    lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
    lv_obj_align_to(label, arc, LV_ALIGN_OUT_BOTTOM_MID, 0, 0 );

    static lv_style_t style_bg;
    static lv_style_t style_indic;

    lv_style_init(&style_bg);
    lv_style_set_border_color(&style_bg, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_border_width(&style_bg, 2);
    lv_style_set_pad_all(&style_bg, 6); /*To make the indicator smaller*/
    lv_style_set_radius(&style_bg, 6);
    lv_style_set_anim_duration(&style_bg, 1000);

    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_radius(&style_indic, 3);

    lv_obj_t *bar = lv_bar_create(lv_screen_active());
    lv_obj_remove_style_all(bar);  /*To have a clean start*/
    lv_obj_add_style(bar, &style_bg, 0);
    lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);

    lv_obj_set_size(bar, 200, 20);
    lv_obj_align_to(bar, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 0 );
    lv_bar_set_value(bar, 100, LV_ANIM_ON);
#endif

    // Turn on the backlight and set it to the highest value, ranging from 0 to 16
    panel.setBrightness(16);
}


void loop()
{
#if LVGL_VERSION_MAJOR == 9
    lv_task_handler();
    delay(5);
#else
    Serial.println("This sketch is adapted to lvgl9 version. Please upgrade lvgl to lvgl 9 version, and rename <LilyGo-AMOLED-Series/src/lv_conf.h> to <lv_conf.h.v8> and <lv_conf.h.v9> to <lv_conf.h>");
    delay(1000);
#endif
}
