#include "deck.h"




std::map<int, std::shared_ptr<Card>> deck::GeneralDeckCards;

std::vector<int> deck::GeneralDeck;

bool deck::GeneralDeckCreated = 0;

int deck::GeneralDeckPointer = 1;




deck::deck(SDL_Renderer* renderer, int xCor, int yCor) {

	this->renderer = renderer;

	text1 = std::make_shared<Text>(renderer,0, xCor-30, yCor-30);
	text2 = std::make_shared<Text>(renderer, 0, xCor - 30, yCor + 130);


	countT = 0;
	if (GeneralDeckCards.empty() == 1) {
		for (int i = 1; i <= GeneralCardsAmount; i++) {
			GeneralDeck.push_back(i);

		}
		srand(time(0));
		std::random_shuffle(GeneralDeck.begin(), GeneralDeck.end());
		for (int i = 1; i < GeneralCardsAmount; i++) {
			GeneralDeckCards[i] = std::make_shared<Card>(renderer, GeneralDeck[i], 0, 0);
		}

		GeneralDeckCreated = 1;
		GeneralDeckPointer = 1;

		//////////////////////////
		

	}
	
	
	this->xCor = xCor;
	this->yCor = yCor;

	PointCalculator(GeneralDeck[GeneralDeckPointer]);
	LocalDeck.push_back(GeneralDeckCards[GeneralDeckPointer++]);
	
	PointCalculator(GeneralDeck[GeneralDeckPointer]);
	LocalDeck.push_back(GeneralDeckCards[GeneralDeckPointer++]);

	
	text1->SetNumber(points1);
	text2->SetNumber(points2);
	
}

void deck::Clear() {//it needs improvements
	text1->SetNumber(0);
	text2->SetNumber(0);
	points1 = 0;
	points2 = 0;
	countT = 0;
	LocalDeck.clear();
	if (!GeneralDeckCards.empty()) {
		GeneralDeckCards.clear();
		GeneralDeck.clear();
		for (int i = 1; i <= GeneralCardsAmount; i++) {
			GeneralDeck.push_back(i);

		}
		srand(time(0));
		std::random_shuffle(GeneralDeck.begin(), GeneralDeck.end());
		for (int i = 1; i < GeneralCardsAmount; i++) {
			GeneralDeckCards[i] = std::make_shared<Card>(renderer, GeneralDeck[i], 0, 0);
		}

		GeneralDeckCreated = 1;
		GeneralDeckPointer = 1;
	}

	PointCalculator(GeneralDeck[GeneralDeckPointer]);
	LocalDeck.push_back(GeneralDeckCards[GeneralDeckPointer++]);

	PointCalculator(GeneralDeck[GeneralDeckPointer]);
	LocalDeck.push_back(GeneralDeckCards[GeneralDeckPointer++]);


	text1->SetNumber(points1);
	text2->SetNumber(points2);

}


void deck::PointCalculator(int card) {

	if (card % 13 == 21) {
		points1 = 21;
	}
	else {
		if (card % 13 > 1 && card % 13 < 10) {
			points1 += card % 13;
			points2 += card % 13;
		}
		else {
			if (card % 13 >= 10 || card % 13 == 0) {
				points1 += 10;
				points2 += 10;
			}
			else {
				if (card % 13 == 1) {
					if (countT == 0) {
						points1 += 11;
						points2 += 1;
					}
					else {
						points1 += 1;
						points2 += 1;
					}
				}

			}
		}
		if (points1 > 21) {
			std::swap(points1, points2);
		}
	}

}

void deck::Draw() {
	if (points1 < 22) {/////////////right
		text1->Draw();
	}
	if (points2 < 22) {
		if (points1 != points2) {
			text2->Draw();
		}
	}
	
	
	for (int i = 0; i < LocalDeck.size(); i++) {
		LocalDeck[i]->SetDestination(xCor + 20 * i, yCor, 70, 100);
		LocalDeck[i]->Draw();
	}

}


void deck::AddCard() {
	PointCalculator(GeneralDeck[GeneralDeckPointer]);
	LocalDeck.push_back(GeneralDeckCards[GeneralDeckPointer++]);

	
	
	text1->SetNumber(points1);
	

	text2->SetNumber(points2);
	
}


bool deck::Over21() {
	if (points1 > 21) {
		return 1;
	}
	return 0;
}

int deck::GetPoints() {
	return points1;
}