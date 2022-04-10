// object.h
//

#pragma once
#include "input.h"

class GameObject: public InputManager {

	public:
		// Read Parameters
		//
		double getPosX() {
			return xPos;
		}
		double getPosY() {
			return yPos;
		}
		double getSpeed() {
			return speed;
		}
		double getAccel() {
			return accel;
		}

		// Set Parameters
		//
		void setPosX(double newPosX) {
			xPos = newPosX;
		}
		void setPosY(double newPosY) {
			yPos = newPosY;
		}

		void setSpeed(double newSpeed) {
			speed = newSpeed;
		}
		void setAccel(double vel) {
			accel = vel;
		}

		bool getMoveState() {
			return isMoving;
		}

		// Switches move state
		void setMoveState(bool state) {
			isMoving = state;
		}

		// Set the Dir of the Object
		//
		void setDir(int newDir) {
			dir = newDir;
		}

		int getDir() {
			return dir;
		}

		//update
		void updatePos() {
			setPosX( getPosX() );
			setPosY( getPosY() );
		}

	private:

		double xPos;
		double yPos;

		double speed;
		double accel;

		bool isMoving;
		int dir;
};