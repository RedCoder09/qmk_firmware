/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "gpio.h"

static const char PROGMEM avatar[] = {
				// 'avatarqmk', 128x64px
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 
				0x88, 0x00, 0x20, 0x00, 0x88, 0x00, 0x20, 0x00, 0x88, 0x00, 0xa0, 0x00, 0x88, 0x00, 0x22, 0x00, 
				0x88, 0x00, 0xa2, 0x00, 0x88, 0x00, 0xaa, 0x00, 0xa8, 0x00, 0xaa, 0x80, 0x6a, 0x40, 0x6a, 0x20, 
				0xaa, 0xa0, 0x9a, 0x50, 0xda, 0x54, 0xda, 0x48, 0xaa, 0x6c, 0xaa, 0x28, 0xaa, 0x6c, 0xaa, 0x29, 
				0xaa, 0x6c, 0xaa, 0x68, 0xaa, 0x6c, 0xaa, 0x69, 0xca, 0x54, 0xda, 0x51, 0x9a, 0xa4, 0xaa, 0x35, 
				0x6a, 0x54, 0x6a, 0xd5, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0xd5, 0xaa, 0x55, 0xaa, 0xdd, 0xaa, 0x55, 
				0xaa, 0xdd, 0xaa, 0x75, 0xaa, 0xdd, 0xaa, 0x77, 0xaa, 0xdd, 0xaa, 0xf7, 0xaa, 0xdd, 0xaa, 0xff, 
				0xaa, 0xdd, 0xaa, 0xf7, 0xaa, 0xdd, 0xaa, 0xff, 0xaa, 0xfd, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 
				0x88, 0x00, 0x20, 0x00, 0x88, 0x00, 0x22, 0x00, 0x88, 0x00, 0xa2, 0x00, 0x88, 0x80, 0xaa, 0x80, 
				0xa8, 0xc0, 0xea, 0xd0, 0xc8, 0x24, 0xb2, 0x92, 0xe9, 0x45, 0x6c, 0x22, 0x2a, 0x21, 0x3b, 0x11, 
				0x1a, 0x18, 0x0a, 0x08, 0x0a, 0x0c, 0x0a, 0x0c, 0x06, 0x04, 0x86, 0xe4, 0x86, 0xe4, 0x86, 0xe5, 
				0x86, 0xe4, 0x86, 0xe5, 0x86, 0x04, 0x06, 0x0d, 0x0a, 0x0c, 0x0a, 0x0d, 0x0a, 0x1c, 0x1a, 0x15, 
				0x3b, 0x35, 0x2a, 0x36, 0x6c, 0x55, 0xe9, 0xd3, 0xb2, 0xe5, 0xca, 0xd5, 0xea, 0xdd, 0xaa, 0xd5, 
				0xaa, 0xdd, 0xaa, 0x75, 0xaa, 0xdd, 0xaa, 0x77, 0xaa, 0xdd, 0xaa, 0xf7, 0xaa, 0xdd, 0xaa, 0xff, 
				0xaa, 0xfd, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xfd, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 
				0x80, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x88, 0x00, 0x20, 0x00, 0x88, 0x00, 0x22, 0x00, 
				0x88, 0x00, 0xa2, 0x00, 0x88, 0x00, 0xaa, 0xc0, 0xf8, 0xf8, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 
				0xff, 0xff, 0xff, 0xff, 0xbf, 0x00, 0xea, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0xff, 0xff, 0xc1, 0xbf, 0x7f, 0x7f, 0x01, 
				0x7f, 0x7f, 0xbf, 0xc1, 0xff, 0xff, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xea, 0xdd, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 
				0xff, 0xff, 0xff, 0xff, 0xfe, 0xfd, 0xfa, 0xff, 0xaa, 0xdd, 0xaa, 0xff, 0xaa, 0xdd, 0xaa, 0xff, 
				0xaa, 0xfd, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xea, 0xff, 0xaa, 0xff, 0xee, 0xff, 0xaa, 0xff, 
				0x88, 0x00, 0x20, 0x00, 0x88, 0x00, 0x22, 0x00, 0x88, 0x00, 0xa0, 0x00, 0x88, 0x00, 0x22, 0x00, 
				0x88, 0x00, 0xa2, 0x00, 0x88, 0x00, 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
				0xff, 0xff, 0xbf, 0x03, 0xaa, 0xfc, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x07, 0x0f, 0x3f, 0x0f, 0x3f, 0x0f, 0x3c, 
				0x0f, 0x3f, 0x0f, 0x3f, 0x0f, 0x07, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfd, 0xaa, 0xf7, 0xbf, 0xff, 0xff, 0xff, 
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xaa, 0xfd, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 
				0xea, 0xff, 0xaa, 0xff, 0xee, 0xff, 0xaa, 0xff, 0xee, 0xff, 0xba, 0xff, 0xee, 0xff, 0xbb, 0xff, 
				0x88, 0x00, 0x20, 0x00, 0x88, 0x00, 0x22, 0x00, 0x88, 0x00, 0xa2, 0x00, 0x88, 0x00, 0xaa, 0x00, 
				0xa8, 0x00, 0xaa, 0x00, 0x88, 0x00, 0xaa, 0x07, 0xaf, 0x5f, 0xbf, 0x7f, 0xff, 0x7f, 0xff, 0x3f, 
				0xaf, 0xc3, 0xea, 0x38, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0xfe, 
				0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x3e, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x3e, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
				0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x3f, 0xea, 0xdf, 0xaf, 0xff, 
				0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xaf, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 
				0xea, 0xff, 0xaa, 0xff, 0xee, 0xff, 0xaa, 0xff, 0xee, 0xff, 0xba, 0xff, 0xee, 0xff, 0xbb, 0xff, 
				0x88, 0x00, 0xa2, 0x00, 0x88, 0x00, 0xaa, 0x00, 0x88, 0x00, 0xaa, 0x00, 0x88, 0x00, 0xaa, 0x00, 
				0xa8, 0x00, 0xaa, 0x00, 0xaa, 0x00, 0xaa, 0x00, 0xaa, 0x40, 0xaa, 0x00, 0xaa, 0x44, 0xaa, 0xfe, 
				0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 
				0x81, 0x81, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x81, 0x81, 0x80, 
				0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0xff, 
				0xaa, 0xfd, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xea, 0xff, 0xaa, 0xff, 0xee, 0xff, 0xaa, 0xff, 
				0xee, 0xff, 0xba, 0xff, 0xee, 0xff, 0xbb, 0xff, 0xee, 0xff, 0xfb, 0xff, 0xee, 0xff, 0xff, 0xff, 
				0x88, 0x00, 0xa2, 0x00, 0x88, 0x00, 0xaa, 0x00, 0xa8, 0x00, 0xaa, 0x00, 0xaa, 0x00, 0xaa, 0x00, 
				0xaa, 0x40, 0xaa, 0x00, 0xaa, 0x44, 0xaa, 0x00, 0xaa, 0x44, 0xaa, 0x10, 0xaa, 0x44, 0xaa, 0x11, 
				0xab, 0x46, 0xac, 0x5c, 0xb8, 0x50, 0xb0, 0x60, 0xe0, 0x40, 0xc0, 0x80, 0x80, 0x83, 0x06, 0x05, 
				0xce, 0x6d, 0xbb, 0x5f, 0xaa, 0x56, 0xaa, 0x56, 0xac, 0xd4, 0xac, 0x54, 0xac, 0xdc, 0xac, 0x54, 
				0xac, 0xdc, 0xac, 0x74, 0xac, 0xdc, 0xac, 0x76, 0xaa, 0xde, 0xaa, 0xff, 0xbb, 0xed, 0xce, 0x07, 
				0x06, 0x83, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xb0, 0xf0, 0xb8, 0xfc, 0xac, 0xfe, 0xab, 0xff, 
				0xea, 0xff, 0xaa, 0xff, 0xee, 0xff, 0xaa, 0xff, 0xee, 0xff, 0xba, 0xff, 0xee, 0xff, 0xbb, 0xff, 
				0xee, 0xff, 0xfa, 0xff, 0xee, 0xff, 0xbb, 0xff, 0xee, 0xff, 0xfb, 0xff, 0xee, 0xff, 0xff, 0xff, 
				0xa8, 0x00, 0xaa, 0x00, 0xa8, 0x00, 0xaa, 0x00, 0xa8, 0x40, 0xaa, 0x00, 0xaa, 0x00, 0xaa, 0x00, 
				0xaa, 0x40, 0xaa, 0x00, 0xaa, 0x44, 0xaa, 0x00, 0xaa, 0x44, 0xaa, 0x10, 0xaa, 0x44, 0xaa, 0x11, 
				0xaa, 0x44, 0xaa, 0x51, 0xaa, 0x44, 0xaa, 0x55, 0xaa, 0x54, 0xaa, 0x55, 0xaa, 0x55, 0xab, 0x55, 
				0xab, 0xd4, 0xaa, 0x55, 0xaa, 0xdd, 0xaa, 0x55, 0xaa, 0xd5, 0xaa, 0x75, 0xaa, 0xdd, 0xaa, 0x55, 
				0xaa, 0xdd, 0xaa, 0x75, 0xaa, 0xdd, 0xaa, 0x77, 0xaa, 0xdd, 0xaa, 0xf7, 0xaa, 0xdd, 0xab, 0xff, 
				0xab, 0xfd, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xea, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 
				0xea, 0xff, 0xaa, 0xff, 0xee, 0xff, 0xaa, 0xff, 0xee, 0xff, 0xba, 0xff, 0xee, 0xff, 0xbb, 0xff, 
				0xee, 0xff, 0xfb, 0xff, 0xee, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xee, 0xff, 0xff, 0xff
			};

void keyboard_pre_init_user(void) {
    gpio_set_pin_output(24);
    gpio_write_pin_high(24);
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
  // Call the post init code.
  rgb_matrix_enable(); // enables Rgb, without saving settings
  rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
  //rgb_matrix_sethsv_noeeprom(HSV_OFF); // sets the color to teal/cyan without saving
}

enum layers {
    _BASE = 0,      // Colemak-DH (or QWERTY)
    _NAV,       // Navigation
    _MOUSE,     // Mouse control
	_MEDIA,      // Media controls
    _NUM,       // Numbers
    _SYM,       // Symbols
    _FUN,       // Function keys
	_STENO
};

// Home row mods (Miryoku style)
// Left: GUI, Alt, Ctrl, Shift
// Right: Shift, Ctrl, Alt, GUI
#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LCTL_T(KC_S)
#define HOME_T LSFT_T(KC_T)

#define HOME_N RSFT_T(KC_N)
#define HOME_E RCTL_T(KC_E)
#define HOME_I RALT_T(KC_I)
#define HOME_O RGUI_T(KC_O)

// Layer taps for thumbs
#define NAV_SPC LT(_NAV, KC_SPC)
#define MSE_TAB LT(_MOUSE, KC_TAB)
#define NUM_BSPC LT(_NUM, KC_BSPC)
#define SYM_ENT LT(_SYM, KC_ENT)
#define FUN_DEL LT(_FUN, KC_DEL)
#define MED_ESC LT(_MEDIA, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
//   ,--------+--------+--------+--------+--------+--------.                                      ,--------+--------+--------+--------+--------+--------.
       KC_TAB ,  KC_Q  ,  KC_W  ,  KC_F  ,  KC_P  ,  KC_B  ,                                         KC_J  ,  KC_L  ,  KC_U  ,  KC_Y  ,KC_QUOT ,KC_BSLS ,
//   |--------+--------+--------+--------+--------+--------|                                      |--------+--------+--------+--------+--------+--------|
       KC_ESC , HOME_A , HOME_R , HOME_S , HOME_T ,  KC_G  ,                                         KC_M  , HOME_N , HOME_E , HOME_I , HOME_O ,KC_QUOT ,
//   |--------+--------+--------+--------+--------+--------+-----------------.  ,-----------------+--------+--------+--------+--------+--------+--------|
      KC_LSFT ,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_D  ,  KC_V  ,KC_LBRC ,KC_LPRN ,   KC_RPRN ,KC_RBRC ,  KC_K  ,  KC_H  ,KC_COMM , KC_DOT ,KC_SLSH ,KC_RSFT ,
//   `-----------------------------------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------------------------'
                               TG(_STENO), EE_CLR ,MED_ESC ,NAV_SPC ,MSE_TAB ,   SYM_ENT ,NUM_BSPC,FUN_DEL ,XXXXXXX ,XXXXXXX
//                              `--------------------------------------------'  `--------------------------------------------'
    ),
	
	[_NAV] = LAYOUT(
//   ,--------+--------+--------+--------+--------+--------.                                      ,--------+--------+--------+--------+--------+--------.
      XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                       C(KC_Y) ,KC_PSTE ,KC_COPY , KC_CUT ,C(KC_Z) ,_______ ,
//   |--------+--------+--------+--------+--------+--------|                                      |--------+--------+--------+--------+--------+--------|
      XXXXXXX ,KC_LGUI ,KC_LALT ,KC_LCTL ,KC_LSFT ,XXXXXXX ,                                       KC_CAPS ,KC_LEFT ,KC_DOWN , KC_UP  ,KC_RGHT ,_______ ,
//   |--------+--------+--------+--------+--------+--------+-----------------.  ,-----------------+--------+--------+--------+--------+--------+--------|
      XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,QK_LLCK ,XXXXXXX ,_______ ,_______ ,   _______ ,_______ , KC_INS ,KC_HOME ,KC_PGDN ,KC_PGUP , KC_END ,_______ ,
//   `-----------------------------------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------------------------'
                                 _______ ,_______ ,_______ ,_______ ,_______ ,    KC_ENT ,KC_BSPC , KC_DEL ,_______ ,_______
//                              `--------------------------------------------'  `--------------------------------------------'
    ),

/*
 * MOUSE LAYER - Mouse control
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | Redo | Paste| Copy | Cut  | Undo |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  ⌘   |  ⎇   |  ⌃   |  ⇧   |      |                              | M Lt | M Dn | M Up | M Rt | Btn3 |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      | WhlL | WhlD | WhlU | WhlR | Btn4 |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      | ///  |      |      |      |  |      | Btn1 | Btn2 | Btn3 |      |
 *                        |      |      |      |      |      |  |      | LClk | RClk | MClk |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MOUSE] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                                 C(KC_Y), KC_PSTE, KC_COPY, KC_CUT, C(KC_Z), _______,
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                                                 XXXXXXX, MS_LEFT, MS_DOWN,  MS_UP, MS_RGHT, _______,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_LLCK, XXXXXXX, _______, _______,        _______, _______,      XXXXXXX, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, _______,
                                 _______, _______, _______, _______, _______,        MS_BTN2, MS_BTN1,      MS_BTN3, _______, _______
    ),

/*
 * MEDIA LAYER - Media controls and system
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | BOOT |      |      |      |      |                              | RGB  | Hue+ | Sat+ | Bri+ | Eff+ |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  ⌘   |  ⎇   |  ⌃   |  ⇧   |      |                              | Prev | Vol- | Vol+ | Next |      |        | //inaccurate diagram
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      | Hue- | Sat- | Bri- | Eff- |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | ///  |      |      |      |      |  |      | Stop | Play | Mute | ///  |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MEDIA] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                                 RM_TOGG, XXXXXXX, RM_HUEU, RM_SATU, RM_VALU, _______,
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                                                 XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_LLCK, XXXXXXX, _______, _______,        _______, _______,      _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______,        KC_MSTP, KC_MPLY,      KC_MUTE, _______, _______
    ),

/*
 * NUM LAYER - Numbers and math
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  [   |  7   |  8   |  9   |  ]   |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  ;   |  4   |  5   |  6   |  =   |                              |      |  ⇧   |  ⌃   |  ⎇   |  ⌘   |        |//inaccurate diagram
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  `   |  1   |  2   |  3   |  \   |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  .   | ///  |  -   |  0   |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUM] = LAYOUT(
      _______, KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      _______, KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                                                  XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
      _______, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS, _______, _______,        _______, _______,      XXXXXXX, QK_LLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 _______,  _______, KC_DOT,   KC_0,  KC_MINS,        _______, _______,      _______, _______, _______
    ),

/*
 * SYM LAYER - Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  {   |  &   |  *   |  (   |  }   |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  :   |  $   |  %   |  ^   |  +   |                              |      |  ⇧   |  ⌃   |  ⎇   |  ⌘   |        |//inaccurate diagram
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  ~   |  !   |  @   |  #   |  |   |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  (   |  )   |  _   |  )   |      |  |      | ///  |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
      _______, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      _______, KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,                                                 XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
      _______, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE, _______, _______,        _______, _______,      XXXXXXX, QK_LLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 _______, _______, KC_LPRN, KC_RPRN, KC_UNDS,        _______, _______,      _______, _______, _______
    ),

/*
 * FUN LAYER - Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | F12  |  F7  |  F8  |  F9  |PrtScr|                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | F11  |  F4  |  F5  |  F6  |ScrLck|                              |      |  ⇧   |  ⌃   |  ⎇   |  ⌘   |        |//inaccurate diagram
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | F10  |  F1  |  F2  |  F3  | Pause|      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Menu | Space| Tab  |      |      |  |      |      | ///  |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUN] = LAYOUT(
      _______, KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      _______, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SCRL,                                                 XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
      _______, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, _______, _______,        _______, _______,      XXXXXXX, QK_LLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 _______, _______, KC_APP,  KC_SPC,  KC_TAB,         _______, _______,      _______, _______, _______
    ),

/*
 * STENO LAYER - Stenography via Gemini PR
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | F12  |  F7  |  F8  |  F9  |PrtScr|                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | F11  |  F4  |  F5  |  F6  |ScrLck|                              |      |  ⇧   |  ⌃   |  ⎇   |  ⌘   |        |//inaccurate diagram
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | F10  |  F1  |  F2  |  F3  | Pause|      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Menu | Space| Tab  |      |      |  |      |      | ///  |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_STENO] = LAYOUT(
      KC_F12,  STN_S1,  STN_TL,   STN_PL,   STN_HL, STN_ST1,                                            STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
      KC_F11,  STN_S2,  STN_KL,   STN_WL,   STN_RL, STN_ST2,                                            STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                              TG(_STENO),  XXXXXXX, STN_A,   STN_O,   XXXXXXX,        XXXXXXX, STN_E,   STN_U,   XXXXXXX, XXXXXXX
    )
	
};

#ifdef POINTING_DEVICE_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Pointing device code only runs on master/left
    return mouse_report;
}
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

static void render_logo(void) {
    oled_write_raw_P(avatar, sizeof(avatar));
}

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        render_logo();
    }
    return false;
}
#endif

#ifdef RGB_MATRIX_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _BASE:
            rgb_matrix_sethsv_noeeprom(HSV_WHITE);
            break;
        case _NAV:
            rgb_matrix_sethsv_noeeprom(HSV_CYAN);
            break;
        case _MOUSE:
            rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
            break;
        case _NUM:
            rgb_matrix_sethsv_noeeprom(HSV_BLUE);
            break;
        case _SYM:
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
            break;
        case _FUN:
            rgb_matrix_sethsv_noeeprom(HSV_RED);
            break;
        case _MEDIA:
            rgb_matrix_sethsv_noeeprom(HSV_MAGENTA);
            break;
    }
    return state;
}
#endif