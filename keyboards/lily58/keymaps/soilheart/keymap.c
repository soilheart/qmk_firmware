#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
  V_COMM,
  V_DOT,
  V_SCLN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC/`|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | BSPC |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  |   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCtrl |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGui |Lower | LAlt | /Space  /       \Enter \  |RAlt  | Raise| APP  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
 [_QWERTY] = LAYOUT(
  KC_GESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSPO,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
                             KC_LGUI, LOWER,   KC_LALT, KC_SPC,  KC_ENT,  KC_RALT, RAISE,   KC_APP
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ~   |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |  _   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | CSPC |CAPSLK| ZRST | ZMOT | ZMIN |      |-------.    ,-------|   |  |   _  |   +  |   {  |   }  |  +   |
 * |------+------+------+------+------+------| WBACK |    | WFWD  |------+------+------+------+------+------|
 * |      |      | PSCR | SCLR | PAUS |      |-------|    |-------|   \  |   -  |   =  |   [  |   ]  | INS  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
#define KY_CSPC LCTL(KC_SPC)
#define KY_ZMIN LCTL(KC_EQL)
#define KY_ZOUT LCTL(KC_MINS)
#define KY_ZRST LCTL(KC_0)
// #define KY_ALTT LALT(KC_TAB)
[_LOWER] = LAYOUT(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
  KY_CSPC, KC_CAPS, KY_ZRST, KY_ZOUT, KY_ZMIN, _______,                 KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PLUS,
  _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, KC_WBAK, KC_WFWD, KC_BSLS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_INS,
                             _______, _______, _______, _______, _______, _______, _______, _______
),
//  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
//  _______, KC_HOME, KC_PGUP, KC_UP,   KC_PGDN, KC_END ,                   _______, _______, KC_PGUP, KC_MINS, KC_EQL,  KC_F11,
//  _______, KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, _______,                   KC_VOLU, KC_HOME, KC_PGDN, KC_END,  V_SCLN,  KC_F12,
//  _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, KC_VOLD, KC_MUTE, V_COMM,  V_DOT,   _______, KC_INS,
//                             _______, _______, _______, KC_BSPC, KC_DEL,  _______, _______, _______
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |-------.    ,-------| left | down |  up  | rght |   -  | F12  |
 * |------+------+------+------+------+------| WBACK |    | WFWD  |------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  | F10  |-------|    |-------| home | pgdn | pgup | end  |   =  | INS  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_RAISE] = LAYOUT(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F11,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_MINS, KC_F12,
  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_WBAK, KC_WFWD, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_EQL,  KC_INS,
                             _______, _______, _______, _______, _______, _______, _______, _______
),
//   KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
//   _______, KC_HOME, KC_PGUP, KC_UP,   KC_PGDN, KC_END ,                   _______, _______, KC_PGUP, KC_MINS, KC_EQL,  KC_F11,
//   _______, KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, _______,                   _______, KC_HOME, KC_PGDN, KC_END,  V_SCLN,  KC_F12,
//   _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, KC_VOLD, KC_MUTE, V_COMM,  V_DOT,   _______, KC_INS,
//                              _______, _______, _______, KC_BSPC, KC_DEL,  _______, _______, _______

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
#define WS_LEFT LCTL(LGUI(KC_LEFT))
#define WS_DOWN LCTL(LALT(KC_LEFT))
#define WS_UP   LCTL(LALT(KC_RGHT))
#define WS_RGHT LCTL(LGUI(KC_RGHT))
[_ADJUST] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_MUTE, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT,                   WS_LEFT, WS_DOWN, WS_UP,   WS_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
  )
//   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
//   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
//   _______, _______, WS_LEFT, _______, WS_RGHT, _______,                   _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
//   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
//                              _______, _______, _______, _______, _______,  _______, _______, _______
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return OLED_ROTATION_270;  // flips the display 270 degrees if main hand
  else
    return OLED_ROTATION_180;
  // return rotation;
}

void render_layer_state(void) {
    oled_write_P(PSTR("Layer"), false);
    oled_write_P(PSTR("RAISE"), layer_state_is(_RAISE));
    oled_write_P(PSTR("QWERT"), layer_state_is(_QWERTY));
    oled_write_P(PSTR("LOWER"), layer_state_is(_LOWER));
    oled_write_ln_P(PSTR(" "), false);
}

void render_mod_status(uint8_t modifiers) {
    oled_write_ln_P(PSTR("Mods"), false);
    oled_write_P(PSTR("SHIFT"), (modifiers & MOD_MASK_SHIFT));
    oled_write_ln_P(PSTR("CTRL"), (modifiers & MOD_MASK_CTRL));
    oled_write_ln_P(PSTR("ALT"), (modifiers & MOD_MASK_ALT));
    oled_write_ln_P(PSTR("WIN"), (modifiers & MOD_MASK_GUI));
    oled_write_ln_P(PSTR(" "), false);
}

// When you add source files to SRC in rules.mk, you can use functions.
//const char *read_layer_state(void);
const char *read_logo(void);
// void set_keylog(uint16_t keycode, keyrecord_t *record);
// const char *read_keylog(void);
// const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    render_layer_state();
    render_mod_status(get_mods());
    //oled_write_ln(read_layer_state(), false);
    //oled_write_ln(read_keylog(), false);
    //oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
  return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    //set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
	layer_on(_ADJUST);
      } else {
	layer_off(_ADJUST);
      }
      return false;
      break;
    // case V_COMM:
    //   if (record->event.pressed) {
    //     SEND_STRING("<=");
    //   }
    //   break;
    // case V_DOT:
    //   if (record->event.pressed) {
    //     SEND_STRING("=>");
    //   }
    //   break;
    // case V_SCLN:
    //   if (record->event.pressed) {
    //     SEND_STRING(":=");
    //   }
    //   break;
  }
  return true;
}
