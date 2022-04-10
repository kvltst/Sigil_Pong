// GameEngine Class
//

#pragma once
#include "sl.h"
#include "input.h"
#include "paddle.h"
#include "ball.h"

// Player 1 & 2 for scores array
//
const int P1 = 0;
const int P2 = 1;



class GameEngine: public InputManager {

	public:

		bool gameRun;

		GameEngine(const int winW, const int winH, const int fntSize);

		void update(const int WIN_W, const int WIN_H);
		void render();

		bool shouldCloseWin() {
			return slShouldClose();
		}

		void gameExit() {
			slClose();
		}


	private:

		int scores[1];

		Paddle Pad1; // Player 1
		Paddle Pad2; // Player 2
		GameBall Ball;

};

GameEngine::GameEngine(const int winW, const int winH, const int fntSize) {

	// Init SIGIL API here
	//
	slWindow(winW, winH, "SIGIL Pong Demo", false);

	// Load Font
	slSetFont(slLoadFont("ttf/white_rabbit.ttf"), fntSize);

	scores[P1] = 0;
	scores[P2] = 0;

	Pad1.setPosX(20);
	Pad1.setPosY(winH / 2);
	Pad1.setHeight(60);
	Pad1.setWidth(16);

	Pad2.setPosX(winW - 20);
	Pad2.setPosY(winH / 2);
	Pad2.setHeight(60);
	Pad2.setWidth(16);

	Ball.setPosX(winW / 2);
	Ball.setPosY(winH / 2);

	Ball.setRadius(6);
	Ball.setSpeed(266);
	Ball.setAccel(233);
	Ball.setMoveState(false);
	Ball.setDir(NE);

	gameRun = true;

}

void GameEngine::update(const int WIN_W, const int WIN_H) {

	// Exit Game
	if (InputManager::pollKeyState(KEY_ESC)) {
		gameRun = false;
	}
	// reset scores
	//
	if (InputManager::pollKeyState(KEY_F4)) {
		scores[P1] = 0;
		scores[P2] = 0;

		Ball.setMoveState(false);
		Ball.setPosX(WIN_W / 2);
		Ball.setPosY(WIN_H / 2);
		Ball.setDir(NE);

		Pad1.setPosY(WIN_H / 2);
		Pad2.setPosY(WIN_H / 2);
	}

	// Start or Pause Ball
	if (InputManager::pollKeyState(KEY_F1)) {
		Ball.setMoveState(true);
	}
	if (InputManager::pollKeyState(KEY_F2)) {
		Ball.setMoveState(false);
	}

	// Move + Collision detect for paddles
	if (InputManager::pollKeyState(KEY_W)) {
		if ( (Pad1.getPosY() + Pad1.getHeight() / 2) < WIN_H) {
			Pad1.setPosY( Pad1.getPosY() + slGetDeltaTime() * 500 );
			Pad1.setDir(NORTH);
		}
	}
	if (InputManager::pollKeyState(KEY_S)) {
		if ( (Pad1.getPosY() - Pad1.getHeight() / 2) > (WIN_H - WIN_H) ) {
			Pad1.setPosY( Pad1.getPosY() - slGetDeltaTime() * 500 );
			Pad1.setDir(SOUTH);
		}
	}

	// P2
	if (InputManager::pollKeyState(KEY_UP)) {
		if ( (Pad2.getPosY() + Pad2.getHeight() / 2) < WIN_H) {
			Pad2.setPosY( Pad2.getPosY() + slGetDeltaTime() * 500 );
			Pad2.setDir(NORTH);
		}
	}
	if (InputManager::pollKeyState(KEY_DOWN)) {
		if ( (Pad2.getPosY() - Pad2.getHeight() / 2) > (WIN_H - WIN_H) ) {
			Pad2.setPosY( Pad2.getPosY() - slGetDeltaTime() * 500 );
			Pad2.setDir(SOUTH);
		}
	}

	if (Ball.getMoveState() ) {
		// movement code
		if (Ball.getDir() == NE) {
			Ball.setPosX( Ball.getPosX() + Ball.getSpeed() * slGetDeltaTime() );
			Ball.setPosY( Ball.getPosY() + Ball.getSpeed() * slGetDeltaTime() );
		}
		if (Ball.getDir() == NW) {
			Ball.setPosX( Ball.getPosX() - Ball.getSpeed() * slGetDeltaTime() );
			Ball.setPosY( Ball.getPosY() + Ball.getSpeed() * slGetDeltaTime() );
		}
		if (Ball.getDir() == SE) {
			Ball.setPosX( Ball.getPosX() + Ball.getSpeed() * slGetDeltaTime() );
			Ball.setPosY( Ball.getPosY() - Ball.getSpeed() * slGetDeltaTime() );
		}
		if (Ball.getDir() == SW) {
			Ball.setPosX( Ball.getPosX() - Ball.getSpeed() * slGetDeltaTime() );
			Ball.setPosY( Ball.getPosY() - Ball.getSpeed() * slGetDeltaTime() );
		}
	}

	// Ball Ceiling + Floor Collision Detection
	if ( Ball.getPosY() <= 6 && Ball.getDir() == SW && Ball.getPosX() > 30) {
		Ball.setDir(NW);
	}
	if ( Ball.getPosY() <= 6 && Ball.getDir() == SE && Ball.getPosX() < WIN_W - 30) {
		Ball.setDir(NE);
	}
	if (Ball.getPosY() >= WIN_H - 6 && Ball.getDir() == NW && Ball.getPosX() > 30) {
		Ball.setDir(SW);
	}
	if (Ball.getPosY() >= WIN_H - 6 && Ball.getDir() == NE && Ball.getPosX() < WIN_W - 30) {
		Ball.setDir(SE);
	}

	// check paddles
	// P1
	if (Ball.getPosX() + 3 <= Pad1.getPosX() + 8 && Ball.getPosY() + 3 > Pad1.getPosY() - 30
	        && Ball.getPosY() + 3 < Pad1.getPosY() + 30) {
		if (Ball.getDir() == NW && Pad1.getDir() == NORTH) {
			Ball.setDir(NE);
			Ball.setPosX( Ball.getPosX() + 1 );
			Ball.setPosY( Ball.getPosY() + 1 );
			Ball.setPosX( Ball.getPosX() + slGetDeltaTime() * Ball.getAccel() );
			Ball.setPosY( Ball.getPosY() + slGetDeltaTime() * Ball.getAccel() );
		} else if (Ball.getDir() == NW && Pad1.getDir() == SOUTH) {
			Ball.setDir(SE);
			Ball.setPosX( Ball.getPosX() + 1 );
			Ball.setPosY( Ball.getPosY() - 1 );
			Ball.setPosX( Ball.getPosX() + slGetDeltaTime() * Ball.getAccel() );
			Ball.setPosY( Ball.getPosY() - slGetDeltaTime() * Ball.getAccel() );
		} else if (Ball.getDir() == SW && Pad1.getDir() == SOUTH) {
			Ball.setDir(SE);
			Ball.setPosX( Ball.getPosX() + 1 );
			Ball.setPosY( Ball.getPosY() - 1 );
			Ball.setPosX( Ball.getPosX() + slGetDeltaTime() * Ball.getAccel() );
			Ball.setPosY( Ball.getPosY() - slGetDeltaTime() * Ball.getAccel() );
		} else if (Ball.getDir() == SW && Pad1.getDir() == NORTH) {
			Ball.setDir(NE);
			Ball.setPosX( Ball.getPosX() + slGetDeltaTime() * Ball.getAccel() );
			Ball.setPosY( Ball.getPosY() + slGetDeltaTime() * Ball.getAccel() );
		} else {
			Ball.setDir(NE);
			Ball.setPosX( Ball.getPosX() + 1 );
			Ball.setPosY( Ball.getPosY() - 1 );
			Ball.setPosX( Ball.getPosX() + slGetDeltaTime() * Ball.getAccel() );
			Ball.setPosY( Ball.getPosY() + slGetDeltaTime() * Ball.getAccel() );
		}
	}

	// P2
	if (Ball.getPosX() + 3 >= Pad2.getPosX() - 8 && Ball.getPosY() + 3 > Pad2.getPosY() - 30
	        && Ball.getPosY() + 3 < Pad2.getPosY() + 30) {
		if (Ball.getDir() == NE && Pad2.getDir() == NORTH) {
			Ball.setDir(NW);
			Ball.setPosX( Ball.getPosX() + 1 );
			Ball.setPosY( Ball.getPosY() + 1 );
			Ball.setPosX( Ball.getPosX() - slGetDeltaTime() * Ball.getAccel() );
			Ball.setPosY( Ball.getPosY() + slGetDeltaTime() * Ball.getAccel() );
		} else if (Ball.getDir() == NE && Pad2.getDir() == SOUTH) {
			Ball.setDir(SW);
			Ball.setPosX( Ball.getPosX() - 1 );
			Ball.setPosY( Ball.getPosY() - 1 );
			Ball.setPosX( Ball.getPosX() - slGetDeltaTime() * Ball.getAccel() );
			Ball.setPosY( Ball.getPosY() - slGetDeltaTime() * Ball.getAccel() );
		} else if (Ball.getDir() == SE && Pad2.getDir() == SOUTH) {
			Ball.setDir(SW);
			Ball.setPosX( Ball.getPosX() - 1 );
			Ball.setPosY( Ball.getPosY() - 1 );
			Ball.setPosX( Ball.getPosX() - slGetDeltaTime() * Ball.getAccel() );
			Ball.setPosY( Ball.getPosY() - slGetDeltaTime() * Ball.getAccel() );
		} else if (Ball.getDir() == SE && Pad2.getDir() == NORTH) {
			Ball.setDir(NW);
			Ball.setPosX( Ball.getPosX() - 1 ) ;
			Ball.setPosY( Ball.getPosY() + 1 );
			Ball.setPosX( Ball.getPosX() - slGetDeltaTime() * Ball.getAccel() );
			Ball.setPosY( Ball.getPosY() + slGetDeltaTime() * Ball.getAccel() );
		} else {
			Ball.setDir(NE);
			Ball.setPosX( Ball.getPosX() + 1);
			Ball.setPosY( Ball.getPosY() + 1);
			Ball.setPosX( Ball.getPosX() + slGetDeltaTime() * Ball.getAccel() );
			Ball.setPosY( Ball.getPosY() + slGetDeltaTime() * Ball.getAccel() );
		}
	}

	// check score walls
	if (Ball.getPosX() <= 0) {
		scores[P2]++;
		Ball.setMoveState(false);
		Ball.setPosX( WIN_W / 2 );
		Ball.setPosY( WIN_H / 2 );
		if (scores[P2] > scores[P1]) {
			Ball.setDir(NW);
		} else {
			Ball.setDir(NE);
		}
	}
	if (Ball.getPosX() >= WIN_W) {
		scores[P1]++;
		Ball.setMoveState(false);
		Ball.setPosX( WIN_W / 2 );
		Ball.setPosY( WIN_H / 2 );
		if (scores[P1] > scores[P2]) {
			Ball.setDir(NE);
		} else {
			Ball.setDir(NW);
		}
	}
}

void GameEngine::render() {

	// Draw
	//
	char msg[16] = ""; // message buffer

	// Text, Paddles, Ball, etc.
	slSetForeColor(1.0, 1.0, 1.0, 1.0); // white

	slSetTextAlign(SL_ALIGN_CENTER);
	sprintf(msg, "%d : %d", scores[P1], scores[P2] );
	slText(360, 460, msg);

	if ( Ball.getMoveState() ) {
		slText(360, 10, "Press F2 to Pause | F4 to Reset");
	}
	if ( !Ball.getMoveState() ) {
		slText(360, 10, "Press F1 to Start | F4 to Reset");
	}

	slRectangleFill(Pad1.getPosX(), Pad1.getPosY(), Pad1.getWidth(), Pad1.getHeight() );
	slRectangleFill(Pad2.getPosX(), Pad2.getPosY(), Pad2.getWidth(), Pad2.getHeight() );
	slCircleFill(Ball.getPosX(), Ball.getPosY(), Ball.getRadi(), 12);

	slRender();
}