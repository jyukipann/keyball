/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

#ifdef OLED_ENABLE
enum custom_keycodes {
  TOGGLE_OLED = SAFE_RANGE,
  OLED_MIN,
  OLED_MAX,
};

typedef union {
	uint32_t raw;
	struct {
		bool is_oled_enabled: 1;
		uint8_t brightness: 8;
	};
} user_config_t;
user_config_t user_config;
#endif


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_universal(
		KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_DEL   ,
		KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_BS    ,
		KC_LCTL  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     ,LT(3,KC_ENT),KC_RCTL ,
		KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_LNG2  ,              KC_LNG1, KC_N     , KC_M     , KC_BTN1  , KC_BTN2  , KC_BTN3  , KC_RSFT  ,
		KC_LCTL  , KC_LALT  , KC_LWIN  , KC_LALT  ,LT(1,KC_SPC),LT(2,KC_TAB),LT(3,KC_ESC),        KC_BSPC,LT(2,KC_ENT), _______, _______  , _______  , G(KC_DOT), LT(2,KC_RWIN)
	),

	[1] = LAYOUT_universal(
		KC_ESC   ,G(KC_LEFT),G(KC_DOWN), G(KC_UP) ,G(KC_RGHT), A(KC_F4) ,                                  KC_GRV   , S(KC_GRV), S(KC_9)  , S(KC_0)  , KC_MINS  , KC_EQL   ,
		KC_TAB   , _______  , KC_HOME  , KC_UP    , KC_END   , A(KC_UP) ,                                  S(KC_COMM),S(KC_DOT),S(KC_LBRC),S(KC_RBRC), KC_SLSH  , KC_BSLS  ,
		KC_LCTL  , _______  , KC_LEFT  , KC_DOWN  , KC_RGHT  ,A(KC_DOWN),                                  KC_COMM  , KC_DOT   , KC_LBRC  , KC_RBRC  , KC_SCLN  , KC_QUOT  ,
		KC_LSFT  , _______  , KC_PGUP  , _______  , KC_PGDN  , _______  , _______  ,            _______  , _______  , _______  ,S(KC_COMM), S(KC_DOT),S(KC_SCLN), KC_RSFT  ,
		KC_LCTL  , KC_LALT  , KC_LWIN  , KC_LALT  , _______  , _______  , _______  ,            KC_DEL   , KC_ENT   , _______  , _______  , _______  , KC_RALT  , KC_RCTL  
	),

	[2] = LAYOUT_universal(
		SSNP_FRE , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
		SSNP_VRT , _______  , KC_7     , KC_8     , KC_9     , _______  ,                                  KC_PGUP  , KC_LEFT  , KC_UP    , KC_RGHT  , _______  , KC_F12   ,
		SSNP_HOR , _______  , KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                                  KC_PGDN  , KC_BTN1  , KC_DOWN  , KC_BTN2  , KC_BTN3  , _______  ,
		_______  , _______  , KC_1     , KC_2     , KC_3     ,S(KC_MINS), S(KC_8)  ,          TOGGLE_OLED,A(KC_LEFT),A(KC_RGHT), KC_BTN1  , KC_BTN2  , KC_BTN3  , _______  ,
		_______  , _______  , KC_0     , KC_DOT   , _______  , _______  , _______  ,            KC_DEL   , KC_ENT   , _______  , _______  , _______  , KC_RALT  , KC_RSFT  
	),

	[3] = LAYOUT_universal(
		RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                  RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
		RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,                                  RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
		RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
		_______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , EE_CLR   ,            EE_CLR   , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
		QK_BOOT  , _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,            _______  , KC_BSPC  , _______  , _______  , _______  , _______  , QK_BOOT
	),
};
// clang-format on

#ifdef RGBLIGHT_LAYERS
// #define HSV_L_R(HSV_L, HSV_R) ({0, 34, HSV_L}, {34, 74, HSV_R})
// #define DEF_LAYER(NAME) const rgblight_segment_t PROGMEM NAME[]
// DEF_LAYER(rgb_layer_1st) = RGBLIGHT_LAYER_SEGMENTS(
//   HSV_L_R(HSV_CYAN, HSV_GOLD));
// DEF_LAYER(rgb_layer_off) = RGBLIGHT_LAYER_SEGMENTS(
//   HSV_L_R(HSV_OFF, HSV_OFF));

const rgblight_segment_t PROGMEM rgb_layer_0[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 37, HSV_CYAN}, {37, 74, HSV_GOLD}
);

const rgblight_segment_t PROGMEM rgb_layer_1[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 37, HSV_RED}, {37, 74, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM rgb_layer_2[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 37, HSV_ORANGE}, {37, 74, HSV_PINK}
);

const rgblight_segment_t PROGMEM rgb_layer_3[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 37, HSV_WHITE}, {37, 74, HSV_WHITE}
);

const rgblight_segment_t PROGMEM rgb_layer_off[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 37, HSV_OFF}, {37, 74, HSV_OFF}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
	rgb_layer_0,
	rgb_layer_1,
	rgb_layer_2,
	rgb_layer_3,
	rgb_layer_off
);
#endif

#define u8 uint8_t

#ifdef SPLIT_COLOR

void rgblight_sethsv_master(u8 hue, u8 sat, u8 val) {
	rgblight_sethsv_range(hue, sat, val, 0, (u8)RGBLED_NUM / 2);
}

void rgblight_sethsv_slave(u8 hue, u8 sat, u8 val) {
	rgblight_sethsv_range(hue, sat, val, (u8)RGBLED_NUM / 2, (u8)RGBLED_NUM);
}

void set_split_color(
					 u8 h_l, u8 s_l, u8 v_l,
					 u8 h_r, u8 s_r, u8 v_r){
	// this is master and right
	if(keyball.this_have_ball){
		rgblight_sethsv_master(h_r, s_r, v_r);
		rgblight_sethsv_slave(h_l, s_l, v_l);
	}else{
		rgblight_sethsv_master(h_l, s_l, v_l);
		rgblight_sethsv_slave(h_r, s_r, v_r);
	}
}
#endif

void keyboard_post_init_user(void) {
	// #ifdef RGBLIGHT_LAYERS
	// rgblight_layers = rgb_layers;
	// #endif
	// Read the user config from EEPROM
	#ifdef OLED_ENABLE
	user_config.raw = eeconfig_read_user();
	oled_set_brightness(user_config.brightness);
	if(user_config.is_oled_enabled){
		oled_on();
	}else{
		oled_off();
	}
	#endif
}

void get_values_from_hsv(
		u8 hue, u8 sat, u8 val, 
		u8 *hue2set, u8 *sat2set, u8 *val2set){
	*hue2set = hue;
	*sat2set = sat;
	*val2set = val;
}


u8 hue2set, sat2set, val2set;
layer_state_t layer_state_set_user(layer_state_t state) {
	// Auto enable scroll mode when the highest layer is 3
	uint8_t layer = get_highest_layer(state);
	keyball_set_scroll_mode(layer == 3);
	layer = biton32(state);
	#if defined RGBLIGHT_LAYERS
	rgblight_set_layer_state(layer, true);
	#elif defined SPLIT_COLOR
	#define MY_COLOR 255, 0, 100
	switch(layer){
		case 0:
			set_split_color(HSV_PURPLE, HSV_RED);
			break;
		case 1:
			set_split_color(HSV_GOLD, HSV_CYAN);
			break;
		case 2:
			set_split_color(HSV_ORANGE, HSV_PINK);
			break;
		case 3:
			rgblight_setrgb(MY_COLOR);
			break;
		default:
			rgblight_sethsv(HSV_OFF);
	}
	#else
	switch(layer){
		case 0:
			get_values_from_hsv(HSV_PURPLE, &hue2set, &sat2set, &val2set);
			break;
		case 1:
			get_values_from_hsv(HSV_GOLD, &hue2set, &sat2set, &val2set);
			break;
		case 2:
			get_values_from_hsv(HSV_CYAN, &hue2set, &sat2set, &val2set);
			break;
		case 3:
			get_values_from_hsv(HSV_RED, &hue2set, &sat2set, &val2set);
			break;
		default:
			get_values_from_hsv(HSV_OFF, &hue2set, &sat2set, &val2set);
	}
	if(val2set > rgblight_get_val()){
		val2set = rgblight_get_val();
	}
	rgblight_sethsv(hue2set, sat2set, val2set);
	#endif
	return state;
}

#ifdef OLED_ENABLE
#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
	keyball_oled_render_keyinfo();
	keyball_oled_render_ballinfo();
	keyball_oled_render_layerinfo();
}

bool oled_task_user(void) {
	if(!user_config.is_oled_enabled){
		return true;
	}
	if (is_keyboard_master()) {
		oledkit_render_info_user();
	} else {
		oledkit_render_logo_user();
	}
	return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case TOGGLE_OLED:
			if (record->event.pressed) {
				if(user_config.is_oled_enabled){
					oled_off();
				}else{
					oled_on();
				}
				user_config.is_oled_enabled = is_oled_on();
				eeconfig_update_user(user_config.raw); 
			}
			return false;
			break;
		case OLED_MIN:
			if (record->event.pressed) {
				oled_set_brightness(0);
				user_config.brightness = oled_get_brightness();
				eeconfig_update_user(user_config.raw); 
			}
			return false;
			break;
		case OLED_MAX:
			if (record->event.pressed) {
				oled_set_brightness(255);
				user_config.brightness = oled_get_brightness();
				eeconfig_update_user(user_config.raw); 
			}
			return false;
			break;
	}
	return true;
}
#endif