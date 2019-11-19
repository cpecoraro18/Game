#include "CoinCounter.h"
#include "TextureManager.h"

CoinCounter::CoinCounter(GameDataRef data) : data(data) {

	texture = data->texmanager.GetTexture("numbers");
	coinTexture = data->texmanager.GetTexture("coin");
	srcOnes.x = srcOnes.y = srcTens.x = srcTens.y =  srcHundreds.x = srcHundreds.y = srcCoin.x = srcCoin.y = 0;
	srcOnes.w = srcOnes.h = srcTens.w = srcTens.h = srcHundreds.w = srcHundreds.h = srcCoin.w = srcCoin.h = 32;
	destOnes.y = destTens.y = destHundreds.y = destCoin.y= 50;
	destOnes.x = 150;
	destTens.x = 100;
	destHundreds.x = 50;
	destCoin.x = 0;
	destOnes.w = destOnes.h = destTens.w = destTens.h = destHundreds.w = destHundreds.h = destCoin.w = destCoin.h = 50;
	
	numCoins = 0;

}

void CoinCounter::Notify(int numCoins) {
	this->numCoins = numCoins;
}

void CoinCounter::Display() {
	int temp;
	int numCoinsLeft = numCoins;
	
	temp = numCoinsLeft % 10;
	srcOnes.x = temp  * 32;
	numCoinsLeft /= 10;
	temp = numCoinsLeft % 10;
	srcTens.x = temp * 32;
	numCoinsLeft /= 10;
	temp = numCoinsLeft % 10;
	srcHundreds.x = temp * 32;
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