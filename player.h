#pragma once

#include<memory>

#include"deck.h"
#include"Object.h"

enum Condition {
	Passive = 0,
	Active = 1
};


class Player {
private:
	int xPos = 0, yPos = 0;
	int money = 100;
	int bet = 20;
	SDL_Renderer* renderer = nullptr;
	std::shared_ptr<deck> playerdeck;
	std::shared_ptr<Button> button1;
	std::shared_ptr<Button> button2;


	std::shared_ptr<Text> playerMoney = nullptr;
	bool condition = 0;

	bool ShowButtons = 0;

	bool PlayerActive = 1;

	bool Dealer = 0;
		
public:
	Player(SDL_Renderer* renderer, int xCor, int yCor);

	void OnEvent(SDL_Event* Event);

	void Draw();

	void SetActive();

	void SetPassive();

	bool IsActive();

	int GetPoints();

	void AddCard();

	void ShowButtonsTrue();

	void ShowButtonsFalse();

	void Clear();

	void SetMoneyW();

	void SetMoneyL();

	int GetMoney();

	void PlayerEnd();

	void DealerSpecific();
	
};

