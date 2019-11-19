#pragma once
#ifndef SRC_COINCOUNTER_H_
#define SRC_COINCOUNTER_H_

#include "SDL.h"
#include "Game.h"


class CoinCounter {
public:
	CoinCounter(GameDataRef data);

	void Notify(int numCoins);

	void Display();

	SDL_Rect srcOnes, destOnes, srcTens, destTens, srcHundreds, destHundreds, srcCoin, destCoin;
	SDL_Texture* texture;
	SDL_Texture* coinTexture;

	int numCoins;
	GameDataRef data;
};

#endif /* SRC_COINCOUNTER_H_ */