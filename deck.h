#pragma once

#ifndef deck_h_
#define deck_h_

#include<vector>
#include<map>
#include <algorithm>
#include "Object.h"
#include "Text.h"

class deck {
private:
	static std::vector<int> GeneralDeck;

	std::vector<std::shared_ptr<Card>> LocalDeck;

	static std::map<int, std::shared_ptr<Card>> GeneralDeckCards;
	
	static bool GeneralDeckCreated;
	static int GeneralDeckPointer;
	const int GeneralCardsAmount = 52;

	int xCor = 0, yCor = 0;

	int points1 = 0;
	int points2 = 0;

	int countT = 0;

	std::shared_ptr<Text> text1;
	std::shared_ptr<Text> text2;
	

	SDL_Renderer* renderer = nullptr;

public:
	deck(SDL_Renderer* renderer, int xCor, int yCor);
	void AddCard();//

	void Draw();


	

	void PointCalculator(int card);

	bool Over21();

	int GetPoints();

	void Clear();


};


//std::map<int, std::shared_ptr<Card>> deck::GeneralDeckCards;
//
//std::vector<int> deck::GeneralDeck;
//
//
//bool deck::GeneralDeckCreated = 0;
//int deck::GeneralDeckPointer = 1;

#endif // !deck_h_
