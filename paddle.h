// paddle.h

#pragma once
#include "object.h"

class Paddle: public GameObject {

	public:
		double getWidth() {
			return width;
		}
		double getHeight() {
			return height;
		}
		void setWidth(double w) {
			width = w;
		}
		void setHeight(double h) {
			height = h;
		}

	private:
		double width;
		double height;
};