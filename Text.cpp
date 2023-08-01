#include "Text.h"



Text::Text(SDL_Renderer* renderer, int number, int xCor, int yCor) {
	this->renderer = renderer;
	this->xCor = xCor;
	this->yCor = yCor;

	SetNumber(number);

}


void Text::Draw() {
	for (std::list<std::shared_ptr<Digit>>::iterator it = digits.begin(); it != digits.end(); it++) {
		(*it)->Draw();

	}

}

void Text::SetNumber(int number) {

	digits.clear();

	int tempnumber = number;
	int counter = 0;
	while (tempnumber != 0) {
		tempnumber /= 10;
		counter++;
	}
	tempnumber = number;
	counter--;
	while (tempnumber != 0) {

		digits.push_front(std::make_shared<Digit>(renderer, tempnumber % 10, xCor + 20 * counter--, yCor));

		tempnumber /= 10;

	}

	if (digits.empty()) {
		digits.push_front(std::make_shared<Digit>(renderer, 0, xCor, yCor));
	}

}