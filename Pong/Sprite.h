#ifndef H_Sprite
#define H_Sprite

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "graphics.h"

class MSprite{
public:	
	MSprite(const char *t_path, SDL_Renderer* t_renderer): m_context(t_renderer){
		
		
		m_texture = loadTexture(t_path, m_context);
		if (m_texture == nullptr) {
			cleanup(m_texture, m_context);			
		}
		
		SDL_QueryTexture(m_texture, NULL, NULL, &texture_size.w, &texture_size.h);
		x = 0;
		y = 0;		
	}
	MSprite(const char *t_path, int t_x, int t_y) : x(t_x), y(t_y) {
		//TODO: throw if no render context

		m_texture = loadTexture(t_path, m_context);
		if (m_texture == nullptr) {
			cleanup(m_texture, m_context);
		}

		SDL_QueryTexture(m_texture, NULL, NULL, &texture_size.w, &texture_size.h);
		x = 0;
		y = 0;
	}
	virtual void move(void) { }
	void draw(void) { 
		renderTexture(m_texture, m_context, x, y);
	}
	void clean() {
		cleanup(m_texture);
	}
	int x, y;
	SDL_Rect texture_size;
	//velocity x & y
	int vx = 4;
	int vy = 2;
	
private:
	SDL_Renderer* m_context;
	std::string m_path;
	SDL_Texture* m_texture;
};


class Ball : public MSprite {
public:	
	using MSprite::MSprite;
	int hitCounter = 0;
	std::vector<MSprite*> colliders; //guess who ran into slicing
	void move() {

		if (x < 0 || x > 640 - texture_size.w) {
			vx *= -1;
			//TODO: SCORE
			//TODO: get rid of magic numbers... static graphics class? 
			x = 640 / 2 + texture_size.w / 2;
			x = 480 / 2 + texture_size.w / 2;
			hitCounter = 0;
			std::cout << "Goooooooooaaaaallll\n";
		}

		//bounce off top
		if (y < 0 || y > 480 - texture_size.h) {
			vy *= -1;			
		}
		
		//std::cout << colliders[0]->y << "\n";
		for (int i = 0; i < colliders.size(); i++) {

			//Right Edge
			if (colliders[i]->x < x && colliders[i]->x + colliders[i]->texture_size.w > x) {
				if (colliders[i]->y < y + texture_size.h/2 && colliders[i]->y + colliders[i]->texture_size.h > y + texture_size.h/2) {
					std::cout << "Hit Right Edge \n";
					vx *= -1;
					hitCounter++;
				}				
			}

			//Left Edge
			if (colliders[i]->x < x + texture_size.w && colliders[i]->x + colliders[i]->texture_size.w > x + texture_size.w) {
				if (colliders[i]->y < y + texture_size.h/2 && colliders[i]->y + colliders[i]->texture_size.h > y + texture_size.h / 2) {
					std::cout << "Hit Left Edge \n";
					vx *= -1;
					hitCounter++;
					if (vx > 0 && vx < 6) {
						vx += 1;
					} else if(vx < 0 && vx > 6) {
						vx -= 1;
					}

				}
			}

			//TODO: top & bottom
			//TODO: don't flip if already colliding


		}

		//add velocity to ball to make shit move
		x += vx;
		y += vy;
	}
};



class MyPaddle : public MSprite {
public:
	using MSprite::MSprite;
	void moveUp() {
		if (y > 0) {
			y -= 4;
		}
		
	}
	void moveDown() {
		if (y < 480 - texture_size.h) {
			y += 4;
		}
	}

};


class CpuPaddle : public MSprite {
public:
	Ball* target;
	void move() {
		if (target->y > y + texture_size.h/2) {
			y += 2;
		}
		if (target->y < y + texture_size.h/2) {
			y -= 2;
		}
	}
	void setTarget(Ball *t_target) {
		target = t_target;
	}
	using MSprite::MSprite;
};
#endif