#pragma once
#ifndef SRC_LEVELBUTTON_H_
#define SRC_LEVELBUTTON_H_
#include "Button.h"
#include <string>

class LevelButton : public Button {
public:
	LevelButton(GameDataRef data, float x, float y, int srcw, int srch, float w, float h, std::string level);
	
	std::string getLevel() { return level; }

private:
	std::string level;


};

#endif /* SRC_LEVELBUTTON_H_ */