#include "LevelButton.h"

LevelButton::LevelButton(GameDataRef data, float x, float y, int srcw, int srch, float w, float h, std::string level) : Button(data, x, y, srcw, srch, w, h) {
	
	this->level = level;

}