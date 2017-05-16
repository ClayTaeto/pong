#ifndef H_Sprite
#define H_Sprite

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "graphics.h"
#include "Game.h"

class MSprite{
public:	
	MSprite() {
	}
	MSprite(const char *t_path, SDL_Renderer* t_renderer): m_context(t_renderer){
		m_texture = loadTexture(t_path, m_context);
		if (m_texture == nullptr) {
			cleanup(m_texture, m_context);			
		}
		
		SDL_QueryTexture(m_texture, NULL, NULL, &texture_size.w, &texture_size.h);
		x = 0;
		y = 0;		
	}

	MSprite(const char *t_path, SDL_Renderer* t_renderer, int t_x, int t_y) : x(t_x), y(t_y), m_context(t_renderer) {
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
	virtual void draw(void) { 
		renderTexture(m_texture, m_context, x, y);
	}
	void clean() {
		cleanup(m_texture);
	}
	int x, y;
	SDL_Rect texture_size;
	//velocity x & y
	int vx = 6;
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
			//vx *= -1;
			if (x < 0) {
				Game::blueScore += 1;
			} else {
				Game::redScore += 1;
			}
			
			//TODO: get rid of magic numbers... static graphics class? 
			x = 640 / 2 + texture_size.w / 2;
			x = 480 / 2 + texture_size.w / 2;

			if (vx > 0) {
				vx = -5;
			}
			else {
				vx = 5;
			}

			if (vy > 0) {
				vy = -4;
			} else {
				vy = 4;				
			}
			
			hitCounter = 0;
			std::cout << "Goooooooooaaaaallll\n";
			std::cout << "Blue: " << Game::blueScore << "\n";
			std::cout << "Red: " << Game::redScore << "\n";
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
					std::cout << "Hit Right Edge "<< vx << "\n";
					vx *= -1;
					hitCounter++;
				}				
			}

			//Left Edge
			if (colliders[i]->x < x + texture_size.w && colliders[i]->x + colliders[i]->texture_size.w > x + texture_size.w) {
				if (colliders[i]->y < y + texture_size.h/2 && colliders[i]->y + colliders[i]->texture_size.h > y + texture_size.h / 2) {
					std::cout << "Hit Left Edge " << vx << "\n";
					vx *= -1;
					hitCounter++;
					if (vx > 0 && vx < 7) {
						vx += 1;
						vy += 1;
					} else if(vx < 0 && vx > -7) {
						vx -= 1;
						vy -= 1;
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
			y += 3;
		}
		if (target->y < y + texture_size.h/2) {
			y -= 3;
		}
	}
	void setTarget(Ball *t_target) {
		target = t_target;
	}
	using MSprite::MSprite;
};

class ScoreCount : public MSprite {
public:	
	ScoreCount(SDL_Renderer* t_renderer, int* t_score) : m_context(t_renderer), m_score(t_score) {
		
		std::string paths[10] = {
			"img/0.png",
			"img/1.png",
			"img/2.png",
			"img/3.png",
			"img/4.png",
			"img/5.png",
			"img/6.png",
			"img/7.png",
			"img/8.png",
			"img/9.png"
		};
		for (int i = 0; i < 10; ++i){
			m_textures[i] = loadTexture(paths[i], m_context);
			if (m_textures[i] == nullptr) {
				cleanup(m_textures[i], m_context);
			}
		}
	};
	void draw() {
		m_index = *m_score;
		if (m_index > 9) {
			m_index = 9;
		}
		renderTexture(m_textures[m_index], m_context, x, y);
	}
	using MSprite::MSprite;
private:
	int m_index;
	int* m_score;
	SDL_Renderer* m_context;
	SDL_Texture* m_textures[10];
};
#endif