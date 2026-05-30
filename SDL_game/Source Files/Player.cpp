#include "Player.h"

Player::Player(SDL_Renderer* renderer, TTF_Font* font, int currentHealth, int totalHealth) :
	renderer(renderer),
	font(font),
	currentHealth(currentHealth),
	totalHealth(totalHealth)

{
	currentHealth = 50;
	totalHealth = 100;
	playerHUD = new PlayerHUD(renderer, font, currentHealth, totalHealth);
}

Player::~Player()
{
	delete playerHUD;
}


void Player::draw()
{
	playerHUD->draw();
}

void Player::update()
{
	playerHUD->update();
}