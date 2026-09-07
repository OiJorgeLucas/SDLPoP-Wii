/*
SDLPoP, a port/conversion of the DOS game Prince of Persia.
Copyright (C) 2013-2025  Dávid Nagy

Wii-specific controller identification and button mapping helpers.
The SDL event loop remains responsible for reading and storing input states.
*/

#include "wii_input.h"

#if defined(__WII__) || defined(HW_RVL) || defined(GEKKO)
#include <gccore.h>
#include <wiiuse/wpad.h>
#endif

#include <stdio.h>
#include <string.h>

static SDL_GameControllerButtonBind get_button_bind(
		SDL_GameController* controller,
		SDL_GameControllerButton button
) {
	SDL_GameControllerButtonBind empty_bind;
	memset(&empty_bind, 0, sizeof(empty_bind));
	if (controller == NULL) return empty_bind;
	return SDL_GameControllerGetBindForButton(controller, button);
}

static bool bind_exists(SDL_GameControllerButtonBind bind) {
	return bind.bindType != SDL_CONTROLLER_BINDTYPE_NONE;
}

static bool button_is_bound_to(
		SDL_GameController* controller,
		SDL_GameControllerButton button,
		int raw_button
) {
	SDL_GameControllerButtonBind bind = get_button_bind(controller, button);
	return bind.bindType == SDL_CONTROLLER_BINDTYPE_BUTTON && bind.value.button == raw_button;
}

static bool is_gamecube_name(const char* name) {
	return name != NULL && SDL_strncasecmp(name, "Gamecube", 8) == 0;
}

bool wii_input_is_gamecube_device_index(int index) {
	const char* name = SDL_JoystickNameForIndex(index);
	if (name == NULL) name = SDL_GameControllerNameForIndex(index);
	return is_gamecube_name(name);
}

bool wii_input_is_gamecube_controller(SDL_GameController* controller) {
	return controller != NULL && is_gamecube_name(SDL_GameControllerName(controller));
}

bool wii_input_is_supported_controller_index(int index) {
	return SDL_IsGameController(index) != SDL_FALSE;
}

bool wii_input_is_supported_controller(SDL_GameController* controller) {
	return controller != NULL;
}

int wii_input_find_controller_index(void) {
	for (int index = 0; index < SDL_NumJoysticks(); ++index) {
		if (wii_input_is_supported_controller_index(index) &&
				!wii_input_is_gamecube_device_index(index)) return index;
	}
	return -1;
}

wii_controller_kind wii_input_get_controller_kind(SDL_GameController* controller) {
	if (!wii_input_is_supported_controller(controller)) return WII_CONTROLLER_NONE;
	if (wii_input_is_gamecube_controller(controller)) return WII_CONTROLLER_GAMECUBE;

	/*
	 * The Wii SDL2 backend exposes a horizontal Wii Remote with these raw
	 * button bindings. A Nunchuk changes the face-button bindings, while a
	 * Classic Controller exposes dedicated shoulder buttons.
	 */
	if (button_is_bound_to(controller, SDL_CONTROLLER_BUTTON_A, 2) &&
			button_is_bound_to(controller, SDL_CONTROLLER_BUTTON_B, 3) &&
			button_is_bound_to(controller, SDL_CONTROLLER_BUTTON_X, 0) &&
			button_is_bound_to(controller, SDL_CONTROLLER_BUTTON_Y, 1)) {
		return WII_CONTROLLER_REMOTE;
	}

	if (bind_exists(get_button_bind(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) ||
			bind_exists(get_button_bind(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))) {
		return WII_CONTROLLER_CLASSIC;
	}

	return WII_CONTROLLER_NUNCHUK;
}

int wii_input_get_wpad_channel(SDL_Joystick* joystick) {
#if defined(__WII__) || defined(HW_RVL) || defined(GEKKO)
	if (joystick == NULL) return -1;

	const char* name = SDL_JoystickName(joystick);
	int channel = -1;
	if (name == NULL || sscanf(name, "Wiimote %d", &channel) != 1 ||
			channel < WPAD_CHAN_0 || channel > WPAD_CHAN_3) {
		return -1;
	}
	return channel;
#else
	(void)joystick;
	return -1;
#endif
}

wii_controller_kind wii_input_get_physical_controller_kind(SDL_Joystick* joystick) {
#if defined(__WII__) || defined(HW_RVL) || defined(GEKKO)
	if (joystick == NULL) return WII_CONTROLLER_NONE;

	const char* name = SDL_JoystickName(joystick);
	if (is_gamecube_name(name)) return WII_CONTROLLER_GAMECUBE;
	int channel = wii_input_get_wpad_channel(joystick);
	if (channel < 0) return WII_CONTROLLER_NONE;

	WPADData* data = WPAD_Data(channel);
	if (data == NULL || data->err == WPAD_ERR_NO_CONTROLLER) return WII_CONTROLLER_NONE;

	switch (data->exp.type) {
		case WPAD_EXP_NUNCHUK: return WII_CONTROLLER_NUNCHUK;
		case WPAD_EXP_CLASSIC: return WII_CONTROLLER_CLASSIC;
		case WPAD_EXP_NONE: return WII_CONTROLLER_REMOTE;
		default: return WII_CONTROLLER_NONE;
	}
#else
	(void)joystick;
	return WII_CONTROLLER_NONE;
#endif
}

#if defined(__WII__) || defined(HW_RVL) || defined(GEKKO)
static Uint32 classic_priority_buttons_from_wpad(u32 buttons) {
	Uint32 result = 0;
	if (buttons & WPAD_CLASSIC_BUTTON_A) result |= WII_CLASSIC_PRIORITY_BUTTON_A;
	if (buttons & WPAD_CLASSIC_BUTTON_B) result |= WII_CLASSIC_PRIORITY_BUTTON_B;
	if (buttons & WPAD_CLASSIC_BUTTON_MINUS) result |= WII_CLASSIC_PRIORITY_BUTTON_MINUS;
	if (buttons & WPAD_CLASSIC_BUTTON_PLUS) result |= WII_CLASSIC_PRIORITY_BUTTON_PLUS;
	if (buttons & (WPAD_BUTTON_HOME | WPAD_CLASSIC_BUTTON_HOME)) result |= WII_CLASSIC_PRIORITY_BUTTON_HOME;
	if (buttons & WPAD_CLASSIC_BUTTON_LEFT) result |= WII_CLASSIC_PRIORITY_BUTTON_LEFT;
	if (buttons & WPAD_CLASSIC_BUTTON_RIGHT) result |= WII_CLASSIC_PRIORITY_BUTTON_RIGHT;
	if (buttons & WPAD_CLASSIC_BUTTON_UP) result |= WII_CLASSIC_PRIORITY_BUTTON_UP;
	if (buttons & WPAD_CLASSIC_BUTTON_DOWN) result |= WII_CLASSIC_PRIORITY_BUTTON_DOWN;
	return result;
}
#endif

bool wii_input_read_classic_priority_state(int channel, wii_classic_priority_state* state) {
	if (state == NULL) return false;
	memset(state, 0, sizeof(*state));

#if defined(__WII__) || defined(HW_RVL) || defined(GEKKO)
	if (channel < WPAD_CHAN_0 || channel > WPAD_CHAN_3) return false;
	WPADData* data = WPAD_Data(channel);
	if (data == NULL || data->err == WPAD_ERR_NO_CONTROLLER ||
			data->exp.type != WPAD_EXP_CLASSIC) {
		return false;
	}

	state->held = classic_priority_buttons_from_wpad(data->btns_h);
	state->down = classic_priority_buttons_from_wpad(data->btns_d);
	state->up = classic_priority_buttons_from_wpad(data->btns_u);
	return true;
#else
	(void)channel;
	return false;
#endif
}

wii_gameplay_action wii_input_get_gameplay_action(wii_controller_kind kind, Uint8 button) {
	switch (kind) {
		case WII_CONTROLLER_REMOTE:
			switch (button) {
				case SDL_CONTROLLER_BUTTON_A: return WII_GAMEPLAY_ACTION_SHIFT;  /* 1 */
				case SDL_CONTROLLER_BUTTON_B: return WII_GAMEPLAY_ACTION_JUMP;   /* 2 */
				case SDL_CONTROLLER_BUTTON_X: return WII_GAMEPLAY_ACTION_TIME;   /* A */
				case SDL_CONTROLLER_BUTTON_Y: return WII_GAMEPLAY_ACTION_CROUCH; /* B */
				default: return WII_GAMEPLAY_ACTION_NONE;
			}

		case WII_CONTROLLER_NUNCHUK:
			switch (button) {
				case SDL_CONTROLLER_BUTTON_A: return WII_GAMEPLAY_ACTION_JUMP;   /* A */
				case SDL_CONTROLLER_BUTTON_B: return WII_GAMEPLAY_ACTION_SHIFT;  /* B */
				case SDL_CONTROLLER_BUTTON_X: return WII_GAMEPLAY_ACTION_CROUCH; /* Z */
				case SDL_CONTROLLER_BUTTON_Y: return WII_GAMEPLAY_ACTION_TIME;   /* C */
				default: return WII_GAMEPLAY_ACTION_NONE;
			}

		case WII_CONTROLLER_CLASSIC:
			switch (button) {
				case SDL_CONTROLLER_BUTTON_A: return WII_GAMEPLAY_ACTION_JUMP;   /* B */
				case SDL_CONTROLLER_BUTTON_B: return WII_GAMEPLAY_ACTION_SHIFT;  /* A */
				case SDL_CONTROLLER_BUTTON_X: return WII_GAMEPLAY_ACTION_TIME;   /* Y */
				case SDL_CONTROLLER_BUTTON_Y: return WII_GAMEPLAY_ACTION_SHIFT;  /* X */
				default: return WII_GAMEPLAY_ACTION_NONE;
			}

		case WII_CONTROLLER_GAMECUBE:
			/* The OGC GameController mapping intentionally follows SDL's ABXY
			 * convention, so physical GameCube B is SDL X and physical X is SDL B. */
			switch (button) {
				case SDL_CONTROLLER_BUTTON_A: return WII_GAMEPLAY_ACTION_JUMP;  /* physical A */
				case SDL_CONTROLLER_BUTTON_X: return WII_GAMEPLAY_ACTION_SHIFT; /* physical B */
				case SDL_CONTROLLER_BUTTON_B: return WII_GAMEPLAY_ACTION_SHIFT; /* physical X */
				case SDL_CONTROLLER_BUTTON_Y: return WII_GAMEPLAY_ACTION_TIME;  /* physical Y */
				default: return WII_GAMEPLAY_ACTION_NONE;
			}

		default:
			return WII_GAMEPLAY_ACTION_NONE;
	}
}

bool wii_input_is_face_button(Uint8 button) {
	return button == SDL_CONTROLLER_BUTTON_A ||
		button == SDL_CONTROLLER_BUTTON_B ||
		button == SDL_CONTROLLER_BUTTON_X ||
		button == SDL_CONTROLLER_BUTTON_Y;
}

SDL_Scancode wii_input_get_menu_scancode(wii_controller_kind kind, Uint8 button) {
	switch (kind) {
		case WII_CONTROLLER_NUNCHUK:
			if (button == SDL_CONTROLLER_BUTTON_A) return SDL_SCANCODE_RETURN;
			if (button == SDL_CONTROLLER_BUTTON_B) return SDL_SCANCODE_ESCAPE;
			break;

		case WII_CONTROLLER_REMOTE:
		case WII_CONTROLLER_CLASSIC:
			if (button == SDL_CONTROLLER_BUTTON_B) return SDL_SCANCODE_RETURN;
			if (button == SDL_CONTROLLER_BUTTON_A) return SDL_SCANCODE_ESCAPE;
			break;

		case WII_CONTROLLER_GAMECUBE:
			if (button == SDL_CONTROLLER_BUTTON_A) return SDL_SCANCODE_RETURN; /* physical A */
			if (button == SDL_CONTROLLER_BUTTON_X) return SDL_SCANCODE_ESCAPE; /* physical B */
			break;

		default:
			break;
	}

	return SDL_SCANCODE_UNKNOWN;
}
