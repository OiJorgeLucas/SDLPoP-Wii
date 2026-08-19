#ifndef SDLPOP_WII_INPUT_H
#define SDLPOP_WII_INPUT_H

#include <stdbool.h>
#include <SDL.h>

typedef enum wii_controller_kind {
	WII_CONTROLLER_NONE = 0,
	WII_CONTROLLER_REMOTE,
	WII_CONTROLLER_NUNCHUK,
	WII_CONTROLLER_CLASSIC,
} wii_controller_kind;

typedef enum wii_gameplay_action {
	WII_GAMEPLAY_ACTION_NONE = 0,
	WII_GAMEPLAY_ACTION_JUMP,
	WII_GAMEPLAY_ACTION_SHIFT,
	WII_GAMEPLAY_ACTION_TIME,
	WII_GAMEPLAY_ACTION_CROUCH,
} wii_gameplay_action;

int wii_input_find_controller_index(void);
bool wii_input_is_supported_controller_index(int index);
bool wii_input_is_supported_controller(SDL_GameController* controller);
wii_controller_kind wii_input_get_controller_kind(SDL_GameController* controller);
wii_controller_kind wii_input_get_physical_controller_kind(SDL_Joystick* joystick);
wii_gameplay_action wii_input_get_gameplay_action(wii_controller_kind kind, Uint8 button);
bool wii_input_is_face_button(Uint8 button);
SDL_Scancode wii_input_get_menu_scancode(wii_controller_kind kind, Uint8 button);

#endif
