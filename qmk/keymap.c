#include QMK_KEYBOARD_H

enum layer_number {
    _COLEMAK = 0,
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define TG_QWE  TG(_QWERTY)
#define DF_CMK  DF(_COLEMAK)
#define DF_QWE  DF(_QWERTY)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_COLEMAK] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_MINS,
    KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_LBRC,     KC_RBRC, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                               KC_LALT, KC_LGUI, LOWER,  KC_SPC,      KC_ENT,  RAISE,   KC_BSPC, KC_RGUI
),

[_QWERTY] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC,     KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                               KC_LALT, KC_LGUI, LOWER,  KC_SPC,      KC_ENT,  RAISE,   KC_BSPC, KC_RGUI
),

[_LOWER] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_F12,
    _______, KC_GRV,  KC_TILD, KC_BSLS, KC_PIPE, XXXXXXX,                     XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
    _______, _______, _______, _______, _______, _______, _______,   _______, XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,
                               _______, _______, _______, _______,   _______, _______, _______, _______
),

[_RAISE] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,  _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,   _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MNXT, KC_MPLY,
                               _______, _______, _______, _______,   _______, _______, _______, _______
),

[_ADJUST] = LAYOUT(
    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
    XXXXXXX, DF_QWE,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, DF_CMK,  XXXXXXX, XXXXXXX, TG_QWE,  XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, _______, _______, _______,   _______, _______, _______, _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}

static void render_layer_status(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _COLEMAK:
            oled_write_ln_P(PSTR("ColemakDH"), false);
            break;
        case _QWERTY:
            oled_write_ln_P(PSTR("QWERTY"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
            break;
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_status();
        led_t leds = host_keyboard_led_state();
        oled_write_P(PSTR("Caps: "), false);
        oled_write_ln_P(leds.caps_lock ? PSTR("On") : PSTR("Off"), false);
    } else {
        oled_write_ln_P(PSTR("Lily58"), false);
        oled_write_ln_P(PSTR("Colemak"), false);
        oled_write_ln_P(PSTR("-DH"), false);
    }
    return false;
}

#endif
