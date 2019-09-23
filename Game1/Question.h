#pragma once
#include "Set.h"
#include "Player.h"

class Question : public Set
{
private:
public:
	Vector2D pos0;

	Question(Vector2D* pos,int w,int h, SDL_Renderer* rend):
		Set(pos, w, h, rend, "assets/question.png", 1.0), 
		pos0(*pos)
	{
		setType(QUESTION);
	}
	void hit(Player* p);
	const Vector2D getPos0(){ return pos0; }
};