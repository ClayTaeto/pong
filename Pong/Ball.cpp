/*
#ifndef H_Ball
#define H_Ball
#include "Sprite.h"


class Ball : public MSprite {
public:
	int movementSpeed = 4;
	void move() {
		if (x < 0 || x > 640) {
			m_vx *= -1;
			m_vx *= -1;
		}
		if (y < 0 || y > 480) {
			m_vy *= -1;
			m_vy *= -1;
		}

		//add velocity to ball to make shit move
		x += m_vx;
		y += m_vy;		
	}

private:
	//velocity x & y
	int m_vx = 4;
	int m_vy = 4;
};
#endif
*/