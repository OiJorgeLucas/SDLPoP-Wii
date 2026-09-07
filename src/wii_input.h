#ifndef SDLPOP_WII_INPUT_H
#define SDLPOP_WII_INPUT_H

#include <stdbool.h>
#include <SDL.h>

typedef enum wii_controller_kind {
	WII_CONTROLLER_NONE = 0,
	WII_CONTROLLER_REMOTE,
	WII_CONTROLLER_NUNCHUK,
	WII_CONTROLLER_CLASSIC,
	WII_CONTROLLER_GAMECUBE,
} wii_controller_kind;

typedef enum wii_gameplay_action {
	WII_GAMEPLAY_ACTION_NONE = 0,
	WII_GAMEPLAY_ACTION_JUMP,
	WII_GAMEPLAY_ACTION_SHIFT,
	WII_GAMEPLAY_ACTION_TIME,
	WII_GAMEPLAY_ACTION_CROUCH,
} wii_gameplay_action;

typedef enum wii_classic_priority_button {
	WII_CLASSIC_PRIORITY_BUTTON_A     = 1u << 0,
	WII_CLASSIC_PRIORITY_BUTTON_B     = 1u << 1,
	WII_CLASSIC_PRIORITY_BUTTON_MINUS = 1u << 2,
	WII_CLASSIC_PRIORITY_BUTTON_PLUS  = 1u << 3,
	WII_CLASSIC_PRIORITY_BUTTON_HOME  = 1u << 4,
	WII_CLASSIC_PRIORITY_BUTTON_LEFT  = 1u << 5,
	WII_CLASSIC_PRIORITY_BUTTON_RIGHT = 1u << 6,
	WII_CLASSIC_PRIORITY_BUTTON_UP    = 1u << 7,
	WII_CLASSIC_PRIORITY_BUTTON_DOWN  = 1u << 8,
} wii_classic_priority_button;

typedef struct wii_classic_priority_state {
	Uint32 held;
	Uint32 down;
	Uint32 up;
} wii_classic_priority_state;

int wii_input_find_controller_index(void);
bool wii_input_is_gamecube_device_index(int index);
bool wii_input_is_gamecube_controller(SDL_GameController* controller);
bool wii_input_is_supported_controller_index(int index);
bool wii_input_is_supported_controller(SDL_GameController* controller);
wii_controller_kind wii_input_get_controller_kind(SDL_GameController* controller);
int wii_input_get_wpad_channel(SDL_Joystick* joystick);
wii_controller_kind wii_input_get_physical_controller_kind(SDL_Joystick* joystick);
bool wii_input_read_classic_priority_state(int channel, wii_classic_priority_state* state);
wii_gameplay_action wii_input_get_gameplay_action(wii_controller_kind kind, Uint8 button);
bool wii_input_is_face_button(Uint8 button);
SDL_Scancode wii_input_get_menu_scancode(wii_controller_kind kind, Uint8 button);

#endif
