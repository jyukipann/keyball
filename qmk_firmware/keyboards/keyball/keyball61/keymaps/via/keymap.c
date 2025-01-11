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
enum custom_keycodes
{
	TOGGLE_OLED = SAFE_RANGE,
	OLED_MIN,
	OLED_MAX,
};

typedef union
{
	uint32_t raw;
	struct
	{
		bool is_oled_enabled : 1;
		uint8_t brightness : 8;
	};
} user_config_t;
user_config_t user_config;
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_universal(
		KC_NO   , KC_1    , KC_2    , KC_3    , KC_4         , KC_5         ,                                          KC_6         , KC_7    , KC_8    , KC_9    , KC_0         , KC_NO   ,
		KC_NO   , KC_Q    , KC_W    , KC_E    , KC_R         , KC_T         ,                                          KC_Y         , KC_U    , KC_I    , KC_O    , KC_P         , KC_NO   ,
		KC_LCTL , KC_A    , KC_S    , KC_D    , KC_F         , KC_G         ,                                          KC_H         , KC_J    , KC_K    , KC_L    , LT(3,KC_ENT) , KC_RCTL ,
		KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V         , KC_B         , KC_LNG2       ,        RALT_T(KC_LNG1) , KC_N         , KC_M    , KC_BTN1 , KC_BTN2 , KC_BTN3      , KC_RSFT ,
		KC_LCTL , KC_LALT , KC_LWIN , KC_LALT , LT(1,KC_SPC) , LT(2,KC_TAB) , CTL_T(KC_ESC) ,        KC_BSPC         , LT(2,KC_ENT) , _______ , _______ , _______ , KC_RALT      , KC_RCTL
	),

	[1] = LAYOUT_universal(
		_______ , G(KC_LEFT), G(KC_DOWN), G(KC_UP) , G(KC_RGHT) , A(KC_F4)   ,                                  KC_GRV     , S(KC_GRV)  , S(KC_9)    , S(KC_0)    , KC_MINS    , KC_EQL  ,
		_______ , _______   , KC_HOME   , KC_UP    , KC_END     , A(KC_UP)   ,                                  S(KC_COMM) , S(KC_DOT)  , S(KC_LBRC) , S(KC_RBRC) , KC_SLSH    , KC_BSLS ,
		_______ , _______   , KC_LEFT   , KC_DOWN  , KC_RGHT    , A(KC_DOWN) ,                                  KC_COMM    , KC_DOT     , KC_LBRC    , KC_RBRC    , KC_SCLN    , KC_QUOT ,
		_______ , _______   , KC_PGUP   , _______  , KC_PGDN    , _______    , _______ ,              _______ , _______    , _______    , S(KC_COMM) , S(KC_DOT)  , S(KC_SCLN) , _______ ,
		_______ , _______   , _______   , _______  , _______    , _______    , _______ ,              KC_DEL  , KC_ENT     , _______    , _______    , _______    , _______    , _______ 
	), 

	[2] = LAYOUT_universal(
		QK_BOOT , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                            KC_F6      , KC_F7      , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
		RGB_TOG , KBC_RST  , KBC_SAVE , CPI_D100 , CPI_I100 , AML_TO   ,                                            KC_PGUP    , KC_LEFT    , KC_UP   , KC_RGHT , _______ , KC_F12  ,
		RGB_VAI , RGB_HUI  , RGB_SAI  , SSNP_FRE , SSNP_VRT , SSNP_HOR ,                                            KC_PGDN    , KC_BTN1    , KC_DOWN , KC_BTN2 , KC_BTN3 , _______ ,
		RGB_VAD , RGB_HUD  , RGB_SAD  , _______  , OLED_MIN , OLED_MAX , TOGGLE_OLED ,                TOGGLE_OLED , A(KC_LEFT) , A(KC_RGHT) , KC_BTN1 , KC_BTN2 , KC_BTN3 , _______ ,
		_______ , _______  , KC_0     , KC_DOT   , _______  , _______  , _______     ,                KC_DEL      , KC_ENT     , _______    , _______ , _______ , _______ , _______ 
	),

	[3] = LAYOUT_universal(
		KC_NO , KC_NO , KC_NO , KC_NO  , KC_NO  , KC_NO ,                        KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
		KC_NO , KC_NO , KC_NO , KC_NO  , KC_NO  , KC_NO ,                        KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
		KC_NO , KC_NO , KC_NO , KC_NO  , KC_NO  , KC_NO ,                        KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
		KC_NO , KC_NO , KC_NO , KC_NO  , KC_NO  , KC_NO , KC_NO ,        KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
		KC_NO , KC_NO , KC_NO , KC_NO  , KC_NO  , KC_NO , KC_NO ,        KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO
	),
};
// clang-format on
#define MY_COLOR 240, 255, 100
#ifdef RGBLIGHT_LAYERS
// #define HSV_L_R(HSV_L, HSV_R) ({0, 34, HSV_L}, {34, 74, HSV_R})
// #define DEF_LAYER(NAME) const rgblight_segment_t PROGMEM NAME[]
// DEF_LAYER(rgb_layer_1st) = RGBLIGHT_LAYER_SEGMENTS(
//   HSV_L_R(HSV_CYAN, HSV_GOLD));
// DEF_LAYER(rgb_layer_off) = RGBLIGHT_LAYER_SEGMENTS(
//   HSV_L_R(HSV_OFF, HSV_OFF));

const rgblight_segment_t PROGMEM rgb_layer_0[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 74, HSV_WHITE});

const rgblight_segment_t PROGMEM rgb_layer_1[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 37, HSV_PURPLE}, {37, 74, HSV_CYAN});

const rgblight_segment_t PROGMEM rgb_layer_2[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 37, HSV_ORANGE}, {37, 74, HSV_RED});

const rgblight_segment_t PROGMEM rgb_layer_3[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 74, MY_COLOR});

const rgblight_segment_t PROGMEM rgb_layer_off[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 37, HSV_OFF}, {37, 74, HSV_OFF});

const rgblight_segment_t *const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
	rgb_layer_0,
	rgb_layer_1,
	rgb_layer_2,
	rgb_layer_3,
	rgb_layer_off);
#endif

#define u8 uint8_t

#ifdef SPLIT_COLOR

void rgblight_sethsv_master(u8 hue, u8 sat, u8 val)
{
	rgblight_sethsv_range(hue, sat, val, 0, (u8)RGBLED_NUM / 2);
}

void rgblight_sethsv_slave(u8 hue, u8 sat, u8 val)
{
	rgblight_sethsv_range(hue, sat, val, (u8)RGBLED_NUM / 2, (u8)RGBLED_NUM);
}

void set_split_color(
	u8 h_l, u8 s_l, u8 v_l,
	u8 h_r, u8 s_r, u8 v_r)
{
	// this is master and right
	if (keyball.this_have_ball)
	{
		rgblight_sethsv_master(h_r, s_r, v_r);
		rgblight_sethsv_slave(h_l, s_l, v_l);
	}
	else
	{
		rgblight_sethsv_master(h_l, s_l, v_l);
		rgblight_sethsv_slave(h_r, s_r, v_r);
	}
}
#endif

void set_oled_switch(bool onoff)
{
	if (onoff)
	{
		oled_on();
	}
	else
	{
		oled_off();
	}
	user_config.is_oled_enabled = is_oled_on();
	eeconfig_update_user(user_config.raw);
}

void oled_set_brightness_and_update(uint8_t value)
{
	oled_set_brightness(value);
	user_config.brightness = oled_get_brightness();
	eeconfig_update_user(user_config.raw);
}

void keyboard_post_init_user(void)
{
#ifdef RGBLIGHT_LAYERS
	rgblight_layers = rgb_layers;
#endif
#ifdef OLED_ENABLE
	set_oled_switch(false);
#endif
	set_auto_mouse_enable(false);
}

void get_values_from_hsv(
	u8 hue, u8 sat, u8 val,
	u8 *hue2set, u8 *sat2set, u8 *val2set)
{
	*hue2set = hue;
	*sat2set = sat;
	*val2set = val;
}

bool should_process_keypress(void) { return true; }

u8 hue2set, sat2set, val2set;
layer_state_t layer_state_set_user(layer_state_t state)
{
	// Auto enable scroll mode when the highest layer is 3
	uint8_t layer = get_highest_layer(state);
	keyball_set_scroll_mode(layer == 3);
	layer = biton32(state);
	rgblight_set_layer_state(0, layer_state_cmp(state, 0));
	rgblight_set_layer_state(1, layer_state_cmp(state, 1));
	rgblight_set_layer_state(2, layer_state_cmp(state, 2));
	rgblight_set_layer_state(3, layer_state_cmp(state, 3));
	return state;
}

#ifdef OLED_ENABLE
#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void)
{
	keyball_oled_render_keyinfo();
	keyball_oled_render_ballinfo();
	keyball_oled_render_layerinfo();
}

bool oled_task_user(void)
{
	if (!user_config.is_oled_enabled)
	{
		return true;
	}
	if (is_keyboard_master())
	{
		oledkit_render_info_user();
	}
	else
	{
		oledkit_render_logo_user();
	}
	return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
	switch (keycode)
	{
	case TOGGLE_OLED:
		if (record->event.pressed)
		{
			set_oled_switch(!user_config.is_oled_enabled);
		}
		return false;
		break;
	case OLED_MIN:
		if (record->event.pressed)
		{
			oled_set_brightness_and_update(0);
		}
		return false;
		break;
	case OLED_MAX:
		if (record->event.pressed)
		{
			oled_set_brightness_and_update(255);
		}
		return false;
		break;
	}
	return true;
}
#endif