//**************************
// SIGIL PONG 32 bit
// by kvltst
//
// SIGIL API from Geoff Nagy

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "sl.h"
#include "paddle.h"
#include "object.h"

using namespace std;

const int WINDOW_W = 720;
const int WINDOW_H = 480;
const int FONTSIZE = 18;

enum Direction {
	NORTH, NE, EAST, SE, SOUTH, SW, WEST, NW
};

int randDir() {
	int result;
	// rand for 50/50
	result = rand() % 100 + 1;

	if (result <= 50) {
		// rand for 0-7
		result = rand() % 7;
		if (result == NORTH) { return NE; }
		if (result == EAST)  { return SE; }
		if (result == SOUTH) { return SW; }
		if (result == WEST)  { return NW; }
	}
	else {
		result = rand() % 7;
		if (result == NORTH) { return NW; }
		if (result == EAST)  { return SW; }
		if (result == SOUTH) { return SE; }
		if (result == WEST)  { return NE; }
	}
	return NW;
}

int main()
{
	// init rand seed
	srand (time(NULL));
	
	// SIGIL First Call
	slWindow(WINDOW_W, WINDOW_H, "SIGIL Pong Test", false);

	slSetFont(slLoadFont("ttf/white_rabbit.ttf"), FONTSIZE);

	int scoreP1 = 0;
	int scoreP2 = 0;

	char msg[16] = "";

	Paddle Pad1; // Player 1
	Paddle Pad2; // Player 2

	Object Ball; // could prob use one class for everything

	Ball.x			= WINDOW_W / 2;
	Ball.y			= WINDOW_H / 2;
	Ball.radius		= 6;
	Ball.speed		= 266;
	Ball.accel		= 233;
	Ball.isMoving	= false;
	Ball.dir		= randDir();

	Pad1.x 		= 20;
	Pad1.y 		= WINDOW_H / 2;
	Pad1.height = 60;
	Pad1.width 	= 16;

	Pad2.x		= WINDOW_W - 20;
	Pad2.y		= WINDOW_H / 2;
	Pad2.height = 60;
	Pad2.width	= 16;

	bool wkey 		= false;
	bool skey 		= false;
	bool upkey		= false;
	bool downkey	= false;
	bool resetkey	= false;
	bool playkey	= false;
	bool stopkey	= false;

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		// INPUT
		if (slGetKey(SL_KEY_F1)) { playkey = true; }
		else { playkey = false; }
		
		if (slGetKey(SL_KEY_F2)) { stopkey = true; }
		else { stopkey = false; }
		
		if (slGetKey(SL_KEY_F4)) { resetkey = true; }
		else { resetkey = false; }

		// P1
		if (slGetKey('W')) { wkey = true; }
		else { wkey = false; }
		
		if (slGetKey('S')) { skey = true; }
		else { skey = false; }

		// P2
		if (slGetKey(SL_KEY_UP)) { upkey = true; }
		else { upkey = false; }
		
		if (slGetKey(SL_KEY_DOWN)) { downkey = true; }
		else { downkey = false; }
		
		// reset scores
		if (resetkey) {
			scoreP1 = 0;
			scoreP2 = 0;
			
			Ball.isMoving 	= false;
			Ball.x 			= WINDOW_W / 2;
			Ball.y 			= WINDOW_H / 2;
			Ball.dir		= randDir();
		}
		
		// Start or Pause Ball
		if (playkey) {
			Ball.isMoving = true;
		}
		if (stopkey) {
			Ball.isMoving = false;
		}

		// Move + Collision detect for paddles
		if (wkey) {
			if ( (Pad1.y + Pad1.height / 2) < WINDOW_H) {
				Pad1.y += slGetDeltaTime() * 500;
				Pad1.dir = NORTH;
			}
		}
		if (skey) {
			if ( (Pad1.y - Pad1.height / 2) > (WINDOW_H - WINDOW_H) ) {
				Pad1.y -= slGetDeltaTime() * 500;
				Pad1.dir = SOUTH;
			}
		}

		// P2
		if (upkey) {
			if ( (Pad2.y + Pad2.height / 2) < WINDOW_H) {
				Pad2.y += slGetDeltaTime() * 500;
				Pad2.dir = NORTH;
			}
		}
		if (downkey) {
			if ( (Pad2.y - Pad2.height / 2) > (WINDOW_H - WINDOW_H) ) {
				Pad2.y -= slGetDeltaTime() * 500;
				Pad2.dir = SOUTH;
			}
		}

		if (Ball.isMoving) {
			// movement code
			if (Ball.dir == NE) {
				Ball.x += Ball.speed * slGetDeltaTime();
				Ball.y += Ball.speed * slGetDeltaTime();
			}
			if (Ball.dir == NW) {
				Ball.x -= Ball.speed * slGetDeltaTime();
				Ball.y += Ball.speed * slGetDeltaTime();
			}
			if (Ball.dir == SE) {
				Ball.x += Ball.speed * slGetDeltaTime();
				Ball.y -= Ball.speed * slGetDeltaTime();
			}
			if (Ball.dir == SW) {
				Ball.x -= Ball.speed * slGetDeltaTime();
				Ball.y -= Ball.speed * slGetDeltaTime();
			}
		}
		
		// Ball Ceiling + Floor Collision Detection
		if ( Ball.y <= 0 + 6 && Ball.dir == SW && Ball.x > 30) {
			Ball.dir = NW;
		}
		if ( Ball.y <= 0 + 6 && Ball.dir == SE && Ball.x < WINDOW_W - 30) {
			Ball.dir = NE;
		}
		if (Ball.y >= WINDOW_H - 6 && Ball.dir == NW && Ball.x > 30) {
			Ball.dir = SW;
		}
		if (Ball.y >= WINDOW_H - 6 && Ball.dir == NE && Ball.x < WINDOW_W - 30) {
			Ball.dir = SE;
		}
		
		// check paddles
		// P1
		if (Ball.x + 3 <= Pad1.x + 8 && Ball.y + 3 > Pad1.y - 30 && Ball.y + 3 < Pad1.y + 30) {
			if (Ball.dir = NW && Pad1.dir == NORTH) {
				Ball.dir = NE;
				Ball.x++;
				Ball.y++;
				Ball.x += slGetDeltaTime() * Ball.accel;
				Ball.y += slGetDeltaTime() * Ball.accel;
			}
			else if (Ball.dir = NW && Pad1.dir == SOUTH) {
				Ball.dir = SE;
				Ball.x++;
				Ball.y--;
				Ball.x += slGetDeltaTime() * Ball.accel;
				Ball.y -= slGetDeltaTime() * Ball.accel;
			}
			else if (Ball.dir = SW && Pad1.dir == SOUTH) {
				Ball.dir = SE;
				Ball.x++;
				Ball.y--;
				Ball.x += slGetDeltaTime() * Ball.accel;
				Ball.y -= slGetDeltaTime() * Ball.accel;
			}
			else if (Ball.dir = SW && Pad1.dir == NORTH) {
				Ball.dir = NE;
				Ball.x += slGetDeltaTime() * Ball.accel;
				Ball.y += slGetDeltaTime() * Ball.accel;
			}
			else {
				Ball.dir = NE;
				Ball.x++;
				Ball.y++;
				Ball.x += slGetDeltaTime() * Ball.accel;
				Ball.y += slGetDeltaTime() * Ball.accel;
			}
		}
		
		// P2
		if (Ball.x + 3 >= Pad2.x - 8 && Ball.y + 3 > Pad2.y - 30 && Ball.y + 3 < Pad2.y + 30) {
			if (Ball.dir = NE && Pad2.dir == NORTH) {
				Ball.dir = NW;
				Ball.x--;
				Ball.y++;
				Ball.x -= slGetDeltaTime() * Ball.accel;
				Ball.y += slGetDeltaTime() * Ball.accel;
			}
			else if (Ball.dir = NE && Pad2.dir == SOUTH) {
				Ball.dir = SW;
				Ball.x--;
				Ball.y--;
				Ball.x -= slGetDeltaTime() * Ball.accel;
				Ball.y -= slGetDeltaTime() * Ball.accel;
			}
			else if (Ball.dir = SE && Pad2.dir == SOUTH) {
				Ball.dir = SW;
				Ball.x--;
				Ball.y--;
				Ball.x -= slGetDeltaTime() * Ball.accel;
				Ball.y -= slGetDeltaTime() * Ball.accel;
			}
			else if (Ball.dir = SE && Pad2.dir == NORTH) {
				Ball.dir = NW;
				Ball.x--;
				Ball.y++;
				Ball.x -= slGetDeltaTime() * Ball.accel;
				Ball.y += slGetDeltaTime() * Ball.accel;
			}
			else {
				Ball.dir = NE;
				Ball.x++;
				Ball.y++;
				Ball.x += slGetDeltaTime() * Ball.accel;
				Ball.y += slGetDeltaTime() * Ball.accel;
			}
		}
		
		// check score walls
		if (Ball.x <= 0) {
			scoreP1++;
			Ball.isMoving = false;
			Ball.x = WINDOW_W / 2;
			Ball.y = WINDOW_H / 2;
			Ball.dir = randDir();
		}
		if (Ball.x >= WINDOW_W) {
			scoreP2++;
			Ball.isMoving = false;
			Ball.x = WINDOW_W / 2;
			Ball.y = WINDOW_H / 2;
			Ball.dir = randDir();
		}
		
		// Draw
		slSetForeColor(1.0, 1.0, 1.0, 1.0); // white

		slSetTextAlign(SL_ALIGN_CENTER);
		sprintf(msg, "%d : %d", scoreP1, scoreP2);
		slText(360, 460, msg);
		
		if (Ball.isMoving) {
			slText(360, 10, "Press F2 to Pause | F4 to Reset");
		}
		if (!Ball.isMoving) {
			slText(360, 10, "Press F1 to Start | F4 to Reset");
		}

		slRectangleFill(Pad1.x, Pad1.y, Pad1.width, Pad1.height);
		slRectangleFill(Pad2.x, Pad2.y, Pad2.width, Pad2.height);
		slCircleFill(Ball.x, Ball.y, Ball.radius, 12);

		slRender();
	};

	slClose();
	return 0;
}