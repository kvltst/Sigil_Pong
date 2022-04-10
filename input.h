// input manager

#pragma once
#include "sl.h"

enum {
	KEY_ESC,
	KEY_W,
	KEY_S,
	KEY_UP,
	KEY_DOWN,
	KEY_F1,
	KEY_F2,
	KEY_F4
};

class InputManager {

		// boolean array for key on/off state database
		//
		bool inputKeyState[8];

	public:

		InputManager();

		void pollKeys(); // not used atm
		bool pollKeyState(int vKey);
};

bool InputManager::pollKeyState(int vKey) {

	// There are only 8 keys used
	// ignores the rest
	if (vKey < 0 || vKey > 8) {
		return 8;
	} else {
		return inputKeyState[vKey];
	}
}

InputManager::InputManager() {

	// Init values to false
	//
	for (int i = 0; i >= 8; i++) {
		inputKeyState[i] = false;
	}
}

void InputManager::pollKeys() {

	// Check Key States
	// and update DB
	//

	if (slGetKey(SL_KEY_ESCAPE) ) {
		inputKeyState[KEY_ESC] = true;
	} else {
		inputKeyState[KEY_ESC] = false;
	}

	if (slGetKey(SL_KEY_F1)) {
		inputKeyState[KEY_F1] = true;
	} else {
		inputKeyState[KEY_F1] = false;
	}

	if (slGetKey(SL_KEY_F2)) {
		inputKeyState[KEY_F2] = true;
	} else {
		inputKeyState[KEY_F2] = false;
	}

	if (slGetKey(SL_KEY_F4)) {
		inputKeyState[KEY_F4] = true;
	} else {
		inputKeyState[KEY_F4] = false;
	}

// P1
	if (slGetKey('W')) {
		inputKeyState[KEY_W] = true;
	} else {
		inputKeyState[KEY_W] = false;
	}

	if (slGetKey('S')) {
		inputKeyState[KEY_S] = true;
	} else {
		inputKeyState[KEY_S] = false;
	}

// P2
	if (slGetKey(SL_KEY_UP)) {
		inputKeyState[KEY_UP] = true;
	} else {
		inputKeyState[KEY_UP] = false;
	}

	if (slGetKey(SL_KEY_DOWN)) {
		inputKeyState[KEY_DOWN] = true;
	} else {
		inputKeyState[KEY_DOWN] = false;
	}
}