#include "Player.h"

Player::Player(SDL_Renderer* renderer, TTF_Font* font) :
	renderer(renderer), font(font)
{
	playerHUD = new PlayerHUD(renderer, font);
}

Player::~Player()
{
}


void Player::draw()
{
	playerHUD->draw();
}

void Player::update()
{
	playerHUD->update();
}