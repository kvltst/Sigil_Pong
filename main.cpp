//**************************
// SIGIL PONG 32 bit
// by kvltst 2020-2022
//
// SIGIL API from Geoff Nagy
//

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "input.h"
#include "engine.h"

using namespace std;

const int WINDOW_W = 720;
const int WINDOW_H = 480;
const int FONTSIZE = 18;


int main() {

	// Program Start
	//
	srand (time(NULL));

	// Init SIGIL
	//
	InputManager InputOp;
	GameEngine GameOp(WINDOW_W, WINDOW_H, FONTSIZE);

	// Main Loop
	//
	while (!GameOp.shouldCloseWin() && GameOp.gameRun != false) {
		// INPUT
		GameOp.pollKeys();

		// Update
		GameOp.update(WINDOW_W, WINDOW_H);

		// Render
		GameOp.render();
	};

	GameOp.gameExit();
	return 0;
}