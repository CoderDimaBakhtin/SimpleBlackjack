#include "player.h"


Player::Player(SDL_Renderer* renderer, int xCor, int yCor) {
	this->renderer = renderer;
	this->xPos = xPos;
	this->yPos = yPos;

	playerdeck = std::make_shared<deck>(renderer, xCor, yCor);

	button1 = std::make_shared<Button>(renderer, HIT, xCor - 130, yCor - 100);

	button2 = std::make_shared<Button>(renderer, STAND, xCor - 130, yCor + 40);

	playerMoney = std::make_shared<Text>(renderer, money, xCor + 100, yCor - 100);
}

void Player::OnEvent(SDL_Event* Event) {
	
	if (PlayerActive) {
		if (!playerdeck->Over21()) {
			button1->EventHandler(Event);
			if (button1->ButtonPressed()) {
				playerdeck->AddCard();
			}

			button2->EventHandler(Event);

			if (button2->ButtonPressed()) {
				condition = 0;
			}

		}
	}
}


void Player::Draw() {
	if (PlayerActive) {
		playerdeck->Draw();
		if (ShowButtons) {
			button1->Draw();
			button2->Draw();
		}
		if (Dealer) {
			playerMoney->SetNumber(0);
		}
		else {
			playerMoney->SetNumber(money);
		}
		playerMoney->Draw();
	}
}


void Player::SetActive() {
	ShowButtonsTrue();
	condition = 1;
}

void Player::SetPassive() {
	ShowButtonsFalse();
	condition = 0;
}

bool Player::IsActive() {
	return condition;
}

int Player::GetPoints() {
	if (playerdeck != nullptr) {
		return playerdeck->GetPoints();
	}
	return 0;
}

void Player::AddCard() {
	playerdeck->AddCard();
}

void Player::ShowButtonsTrue() {
	ShowButtons = 1;
}

void Player::ShowButtonsFalse() {
	ShowButtons = 0;
}

void Player::Clear() {
	PlayerActive = 1;
	button1->Clear();
	button2->Clear();
	playerdeck->Clear();
	condition = 0;

	ShowButtons = 0;
}

void Player::SetMoneyW() {
	money += bet;
}
void Player::SetMoneyL() {
	money -= bet;
}

int Player::GetMoney() {
	return money;
}

void Player::PlayerEnd() {
	PlayerActive = 0;
}

void Player::DealerSpecific() {
	Dealer = 1;
}