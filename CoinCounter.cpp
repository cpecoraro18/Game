#include "CoinCounter.h"
#include "TextureManager.h"


CoinCounter::CoinCounter(GameDataRef data) : data(data) {

	texture = data->texmanager.GetTexture("numbers");
	coinTexture = data->texmanager.GetTexture("coin");
	srcOnes.x = srcOnes.y = srcTens.x = srcTens.y =  srcHundreds.x = srcHundreds.y = srcCoin.x = srcCoin.y = 0;
	srcOnes.w =  srcTens.w =  srcHundreds.w =  NUMBER_SPRITE_WIDTH;
	srcOnes.h = srcTens.h = srcHundreds.h =  NUMBER_SPRITE_HEIGHT;
	srcCoin.h = COIN_SPRITE_HEIGHT;
	srcCoin.w = COIN_SPRITE_WIDTH;
	destOnes.y = destTens.y = destHundreds.y = destCoin.y= SCREEN_HEIGHT*.1;
	destOnes.x = SCREEN_WIDTH*.15;
	destTens.x = SCREEN_WIDTH*.1;
	destHundreds.x = SCREEN_WIDTH*.05;
	destCoin.x = 0;
	destOnes.w =  destTens.w =  destHundreds.w =  destCoin.w =  NUMBER_WIDTH;
	destOnes.h = destTens.h = destHundreds.h = destCoin.h = NUMBER_HEIGHT;
	numCoins = 0;

}

CoinCounter::~CoinCounter() {
}

void CoinCounter::Notify(int numCoins) {
	this->numCoins = numCoins;
}

void CoinCounter::Display() {
	int temp;
	int numCoinsLeft = numCoins;
	
	temp = numCoinsLeft % 10;
	srcOnes.x = temp  * NUMBER_SPRITE_WIDTH;
	numCoinsLeft /= 10;
	temp = numCoinsLeft % 10;
	srcTens.x = temp * NUMBER_SPRITE_WIDTH;
	numCoinsLeft /= 10;
	temp = numCoinsLeft % 10;
	srcHundreds.x = temp * NUMBER_SPRITE_WIDTH;
	numCoinsLeft /= 10;
	data->texmanager.Draw(coinTexture, srcCoin, destCoin, data->renderer);
	data->texmanager.Draw(texture, srcOnes, destOnes, data->renderer);
	if (numCoins >= 10) {
		data->texmanager.Draw(texture, srcTens, destTens, data->renderer);
	}
	if (numCoins >= 100) {
		data->texmanager.Draw(texture, srcHundreds, destHundreds, data->renderer);

	}
	


}