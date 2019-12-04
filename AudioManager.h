#pragma once

#ifndef SRC_AUDIOMANAGER_H_
#define SRC_AUDIOMANAGER_H_
#include "SDL_Mixer.h"
#include <map>
#include <string>

class AudioManager {
public:
	void LoadChunk(std::string fileName, const char* name);
	Mix_Chunk* GetChunk(const char* name);
	void DestroyChunks();

	void LoadMusic(std::string fileName, const char* name);
	Mix_Music* GetMusic(const char* name);
	void DestroyMusic();

private:
	std::map<const char*, Mix_Chunk*> chunks;
	std::map<const char*, Mix_Music*> songs;


};

#endif /* SRC_AUDIOMANAGER_H_ */