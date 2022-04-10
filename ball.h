// ball.h

#pragma once
#include "object.h"

enum {
	NORTH,
	NE,
	EAST,
	SE,
	SOUTH,
	SW,
	WEST,
	NW
};

class GameBall: public GameObject {

	public:

		double getRadi() {
			return radius;
		}

		void setRadius(double rad) {
			radius = rad;
		}

	private:
		double radius;
};