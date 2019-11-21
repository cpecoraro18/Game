#include "AudioManager.h"

void AudioManager::LoadChunk(const char* fileName, const char* name) {
	Mix_Chunk* chunk = Mix_LoadWAV(fileName);
	if (chunk != NULL) {
		this->chunks[name] = chunk;
	}

}

Mix_Chunk* AudioManager::GetChunk(const char* name) {
	return this->chunks.at(name);

}

void AudioManager::DestroyChunks() {
	std::map<const char*, Mix_Chunk*>::iterator it;
	for (it = chunks.begin(); it != chunks.end(); it++)
	{
		Mix_FreeChunk(it->second);
	}
	chunks.clear();

}

void AudioManager::LoadMusic(const char* fileName, const char* name) {
	Mix_Music* music = Mix_LoadMUS(fileName);
	if (music != NULL) {
		this->songs[name] = music;
	}

}

Mix_Music* AudioManager::GetMusic(const char* name) {
	return this->songs.at(name);

}

void AudioManager::DestroyMusic() {
	std::map<const char*, Mix_Music*>::iterator it;
	for (it = songs.begin(); it != songs.end(); it++)
	{
		Mix_FreeMusic(it->second);
	}
	songs.clear();

}