#include "Object.h"

//////////////  Object

Object::Object(SDL_Renderer* renderer, int destX, int destY, int destW, int destH) {
	this->renderer = renderer;

	this->dest.x = destX;
	this->dest.y = destY;
	this->dest.w = destW;
	this->dest.h = destH;
}

void Object::SetDestination(int destX, int destY, int destW, int destH) {
	this->dest.x = destX;
	this->dest.y = destY;
	this->dest.w = destW;
	this->dest.h = destH;
}

SDL_Rect Object::GetDestination(/*int destX, int destY, int destW, int destH*/) {
	return dest;
}

//
//void Object::EventHandler(SDL_Event* Event) {
//	
//}



//////////////  Object_END

////////////// ColoredObject

ColoredObject::ColoredObject(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a,
	int destX, int destY, int destW, int destH) :Object(renderer, destX, destY, destW, destH) {
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->a = a;
}
void ColoredObject::Draw() {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &dest);
}

void ColoredObject::EventHandler(SDL_Event* Event) {

}

////////////// ColoredObject_END



////////////// ImageObject

ImageObject::ImageObject(SDL_Renderer* renderer, int sourceX, int sourceY, int sourceW, int sourceH,
	int destX, int destY, int destW, int destH, std::string image) :Object(renderer, destX, destY, destW, destH) {
	this->source.x = sourceX;
	this->source.y = sourceY;
	this->source.w = sourceW;
	this->source.h = sourceH;
	this->image = image;
	Surf_Display = IMG_Load(image.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, Surf_Display);
}

void ImageObject::Draw() {
	if(r == 1)
	SDL_RenderCopyEx(renderer, texture, &source, &dest, 0, nullptr, SDL_FLIP_NONE);
}

void ImageObject::SetSource(int sourceX, int sourceY, int sourceW, int sourceH) {
	this->source.x = sourceX;
	this->source.y = sourceY;
	this->source.w = sourceW;
	this->source.h = sourceH;
}

SDL_Rect ImageObject::GetSource() {
	return source;
}

void ImageObject::SetImage(std::string image) {
	this->image = image;
}

void ImageObject::EventHandler(SDL_Event* Event) {
	std::cout << "ImageObject::EventHandler\n";
}


////////////// ImageObject_END



Button::Button(SDL_Renderer* renderer, ButtonType type,
	int destX, int destY): ImageObject(renderer,type, 0, 70, 70,
		destX, destY, 100, 100, /*image*/"button.png") {
	
}

void Button::EventHandler(SDL_Event* Event) {//70
	//std::cout << "Button::EventHandler\n";
	SDL_GetMouseState(&mouseX, &mouseY);
	if (sqrt(pow(dest.x - mouseX + 45, 2) + pow(dest.y - mouseY + 45, 2)) < 45){
		if (Event->type == SDL_MOUSEBUTTONDOWN) {
			pressed = 1;
			//r = 0;
			SetSource(source.x, 70, 70, 70);
		}
	}

	if (Event->type == SDL_MOUSEBUTTONUP) {
		pressed = 0;
		//r = 0;
		SetSource(source.x, 0, 70, 70);
	}
}


bool Button::ButtonPressed() {
	return pressed;
}

void Button::Clear() {
	pressed = 0;
}

Card::Card(SDL_Renderer* renderer, int CardNumber, int destX, int destY) :
	ImageObject(renderer, ((CardNumber - 1)%13 )* 910/13, 25 + (CardNumber - 1)/13 *100, 70, 100, destX, destY, 70, 100, "cards.png") {
	
}



void Card::Draw() {
	SDL_Rect EndSource = GetDestination();
	int k = EndSource.y / (EndSource.x - WIDTH);
	int b = -k* WIDTH;

	if (DrawEntering <= 20) {
		DrawEntering++;
		//
		int x = WIDTH - (-EndSource.x + WIDTH) / 20 * DrawEntering;
		
		
		SetDestination(x, EndSource.y, 70, 100);
		std::chrono::milliseconds sleepDuration(4);
		std::this_thread::sleep_for(sleepDuration);
		//
		ImageObject::Draw();

		SetDestination(EndSource.x, EndSource.y, EndSource.w, EndSource.h);
	}
	else {
		ImageObject::Draw();
	}
}


Digit::Digit(SDL_Renderer* renderer, int digit, int destX, int destY) ://100    52//20    26
	ImageObject(renderer, (digit%5)*20, (digit/5)*26, 20, 26, destX, destY, 20, 26, "digits.png") {

}



