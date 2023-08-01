#pragma once





#ifndef TEXT_HEADER
#define TEXT_HEADER
#include<list>
#include<vector>
#include<SDL.h>
#include "Object.h"







class Text {
private:
	std::list<int> arr;
	int xCor, yCor;
	SDL_Renderer* renderer;
	std::list<std::shared_ptr<Digit>> digits;
	int degree;
	bool flag = 1;
public:
	Text(SDL_Renderer* renderer, int number, int xCor, int yCor);
	
	void SetNumber(int number);
	void Draw();
	

};

#endif
