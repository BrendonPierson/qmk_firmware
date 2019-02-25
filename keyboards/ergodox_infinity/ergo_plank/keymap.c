#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "stdio.h"
#include "stdlib.h"

#define BASE   0
#define ARROWS 1
#define SYMB   2
#define NUMS   3
#define NUMP   4

// These need to be set in the environment
#define ENV_EM_ASP  getenv("EM_ASP")
#define ENV_EM_GOOG getenv("EM_GOOG")

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  EM_ASP,
  EM_GOOG,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 * cocl = CMD OPT CTRL Left (move window to new scree with spectacle)
 * FScrn = CMD OPT f (full screen with spectacle)
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | COCL |           | COCR |   6  |   7  |   8  |   9  |   0  | Bksp   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  CMD |           | CMD  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|OPT-L |           | OPT-R|------+------+------+------+------+--------|
 * |CTL/Esc |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------| CTL- |           | CTL- |------+------+------+------+------+--------|
 * | Shift  |   Z  |   X  |   C  |   V  |   B  |SH-Tab|           | Tab  |   N  |   M  |   ,  |   .  |   /  |Enter/SH|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Arrows | Nums | CTL | ALT  |  CMD |                                       | SYMB |Left |  Up  | Down | Right |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.        ,-------------.
 *                                        | VolUp| VolDn|        |Brter |Darker|
 *                                 ,------|------|------|        |------+------+------.
 *                                 |      |      |FScrn |        |Sleep |      |      |
 *                                 | BkSP |Enter |------|        |------|  Del | Space|
 *                                 |      |      |NumPad|        |Pause |      |      |
 *                                 `--------------------'        `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*

[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GRAVE,          KC_1,      KC_2,      KC_3,      KC_4,     KC_5,   LCAG(KC_LEFT),
        KC_TAB,            KC_Q,      KC_W,      KC_E,      KC_R,     KC_T,   LCMD(LALT(KC_LEFT)),
        LCTL_T(KC_ESC),    KC_A,      KC_S,      KC_D,      KC_F,     KC_G,
        KC_LSFT,           KC_Z,      KC_X,      KC_C,      KC_V,     KC_B,   LCTL(LSFT(KC_TAB)),
        MO(ARROWS),        MO(NUMS),  KC_LCTL,   KC_LALT,   KC_LCMD,

                                                 KC__VOLUP, KC__VOLDOWN,
                                                            LCMD(LALT(KC_F)),
                                      KC_BSPC,   KC_ENT,    MO(NUMP),
        // right hand
      LCAG(KC_RIGHT),   KC_6,      KC_7,       KC_8,      KC_9,      KC_0,      KC_BSPC,
LCMD(LALT(KC_RIGHT)),   KC_Y,      KC_U,       KC_I,      KC_O,      KC_P,      KC_BSLS,
                        KC_H,      KC_J,       KC_K,      KC_L,      KC_SCLN,   KC_QUOT,
        LCTL(KC_TAB),   KC_N,      KC_M,       KC_COMM,   KC_DOT,    KC_SLSH,   RSFT_T(KC_ENT),
                                   MO(SYMB),   KC_LEFT,   KC_UP,     KC_DOWN,   KC_RGHT,

             KC_BRID,    KC_BRIU,
             KC_SYSTEM_SLEEP,
             KC_PAUSE,   KC_DELT,    KC_SPC
    ),

// layer for vim-like arrow keys and mouse keys
[ARROWS] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        _______,    _______,      _______,      _______,      _______,     _______,   _______,
        _______,    _______,      _______,      _______,      _______,     _______,   _______,
        _______,    _______,      _______,      _______,      _______,     _______,
        _______,    _______,      _______,      _______,      _______,     _______,   _______,
        KC_TRNS,    _______,      _______,      _______,      _______,

                                                 _______,     _______,
                                                              _______,
                                     KC_BTN1,    _______,     _______,
        // right hand
             _______,   _______,      _______,      _______,     _______,   _______,   _______,
             _______,   KC_MS_L,      KC_MS_D,      KC_MS_U,     KC_MS_R,   _______,   _______,
                        KC_LEFT,      KC_DOWN,      KC_UP,       KC_RGHT,   _______,   _______,
             _______,   _______,      _______,      _______,     _______,   _______,   _______,
                                      KC_ACL0,      KC_ACL1,     KC_ACL2,   _______,   _______,
             _______,   _______,
             _______,
             _______,   _______,    KC_BTN2
    ),

// Plank like layer of symbols on the home row
[SYMB] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        _______,    _______,      _______,      _______,      _______,     _______,   _______,
        _______,    _______,      _______,      _______,      KC_CIRC,     _______,   _______,
        _______,    KC_EXLM,      KC_AT,        KC_HASH,      KC_DLR,      KC_PERC,
        _______,    _______,      _______,      EM_ASP,       EM_GOOG,     _______,   _______,
        _______,    _______,      _______,      _______,      _______,

                                                 _______,     _______,
                                                              _______,
                                     _______,    _______,     _______,
        // right hand
             _______,   _______,      _______,      _______,     _______,   _______,   _______,
             _______,   _______,      KC_ASTR,      KC_LPRN,     KC_RPRN,   _______,   _______,
                        _______,      KC_MINS,      KC_EQL,      KC_LBRC,   KC_RBRC,   _______,
             _______,   _______,      KC_UNDS,      KC_PLUS,     KC_LCBR,   KC_RCBR,   _______,
                                      KC_TRNS,      _______,     _______,   _______,   _______,
             _______,   _______,
             _______,
             _______,   _______,    _______
    ),

// Plank like layer of numbers on home-row with function keys
[NUMS] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        _______,    _______,      _______,      _______,      _______,     _______,   _______,
        _______,    KC_F11,       KC_F12,       KC_F13,       KC_F14,      KC_F15,     _______,
        _______,    KC_1,         KC_2,         KC_3,         KC_4,        KC_5,
        _______,    KC_F1,        KC_F2,        KC_F3,        KC_F4,       KC_F5,     _______,
        _______,    KC_TRNS,      _______,      _______,      _______,

                                                 _______,     _______,
                                                              _______,
                                     _______,    _______,     _______,
        // right hand
             _______,   _______,      _______,      _______,     _______,   _______,   _______,
             _______,   _______,      _______,      _______,     _______,   _______,   _______,
                        KC_6,         KC_7,         KC_8,        KC_9,      KC_0,      _______,
             _______,   KC_F6,        KC_F7,        KC_F8,       KC_F9,     _______,     _______,
                                      _______,      _______,     _______,   _______,   _______,
             _______,   _______,
             _______,
             _______,   _______,    _______
    ),


/* Keymap 1: Extra Layer
 * mouse keys: KC_MS_L,      KC_MS_L,      KC_MS_L,     KC_MS_L,
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           | PSCR |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Caps   |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |   0  |   ,  |   .  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |VolUp |VolDn |       | Prev | Next |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       | Stop |Bright|Bright|
 *                                 | Mute |Pause |------|       |------|ness- |ness+ |
 *                                 |      |      |      |       | Play |      |      |
 *                                 `--------------------'       `--------------------'
 */

// Numpad layer
[NUMP] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_CAPS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_VOLU,KC_VOLD,
                                               KC_TRNS,
                               KC_MUTE,KC_PAUS,KC_TRNS,
       // right hand
       KC_PSCR, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_0,   KC_COMM, KC_DOT,  KC_EQL,  KC_TRNS,
       KC_MPRV, KC_MNXT,
       KC_STOP,
       KC_MPLY, RGB_VAD, RGB_VAI
),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
    // Aspire Email
    case EM_ASP:
      if (record->event.pressed) {
        SEND_STRING(ENV_EM_ASP);
      }
      return false;
      break;
    // Google Email
    case EM_GOOG:
      if (record->event.pressed) {
        SEND_STRING(ENV_EM_GOOG);
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
