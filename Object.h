#pragma once
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include<iostream>

#include"Defines.h"

#include<thread>




class Object {
protected:
	SDL_Rect dest;
	SDL_Surface* Surf_Display = nullptr;
	SDL_Renderer* renderer = nullptr;

public:

	Object(SDL_Renderer* renderer, int destX, int destY, int destW, int destH);

	void SetDestination(int destX, int destY, int destW, int destH);

	SDL_Rect GetDestination(/*int destX, int destY, int destW, int destH*/);

	virtual void Draw() = 0;

	virtual void EventHandler(SDL_Event* Event) = 0;
	

};


class ColoredObject : public Object {
private:
	Uint8 red = 255, green = 255, blue = 255, a = 255;
	SDL_Rect color;

public:
	ColoredObject(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a,
		int destX, int destY, int destW, int destH);
	void Draw();
	void EventHandler(SDL_Event* Event);
};



class ImageObject : public Object {
private:
	//SDL_Rect source;
	SDL_Texture* texture = nullptr;
	std::string image;
protected:
	SDL_Rect source;
	bool r = 1;

public:
	ImageObject(SDL_Renderer* renderer, int sourceX, int sourceY, int sourceW, int sourceH,
		int destX, int destY, int destW, int destH, std::string image);

	void Draw();

	void SetSource(int sourceX, int sourceY, int sourceW, int sourceH);

	SDL_Rect GetSource();

	void SetImage(std::string image);

	void EventHandler(SDL_Event* Event);

};



enum ButtonType{
	DEAL = 0,
	CLEAR = 70,
	YES = 140,
	NO = 210,
	HIT = 280,
	STAND = 350,
	DOUBLE = 420,
	SPLIT = 490,
	REBET = 560,
	NEW_HAND = 630
};



class Button : public ImageObject {
private:
	bool pressed = 0;
	int mouseX = 0;
	int mouseY = 0;
	const std::string image = "button.png";
	
public:
	
	Button(SDL_Renderer* renderer, ButtonType type, int destX, int destY);

	void EventHandler(SDL_Event* Event);

	bool ButtonPressed();

	void Clear();

};



class Card : public ImageObject {
private:
	const std::string image = "button.png";
	int DrawEntering = 0;
public:
	Card(SDL_Renderer* renderer, int CardNumber, int destX, int destY);


	void Draw();
	
};


class Digit : public ImageObject {
private:
	const std::string image = "digits.png";

public:
	Digit(SDL_Renderer* renderer, int digit, int destX, int destY);

};





#endif

