#pragma once
#ifndef SRC_ENDLEVEL_H_
#define SRC_ENDLEVEL_H_
#include "SDL.h"
#include "Entity.h"
#include "Player.h"
#include <string>s

class EndLevel : public Entity {
public:

	EndLevel(GameDataRef data, float x, float y, float h, float w);
	EndLevel(GameDataRef data, float x, float y, float h, float w, int nFrames, int frameSpeed);
	~EndLevel();

	void update(World* world) override;
	void handleinput(SDL_Event event, const Uint8* keystate);
	void draw();
	void handleCollisions(Player* player, int onx);

private:
	std::string nextLevel;
	
};

#endif /* SRC_ENDLEVEL_H_ */