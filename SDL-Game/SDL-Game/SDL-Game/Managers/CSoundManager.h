#pragma once
#include "SDL_mixer.h"
#include <iostream>
#include <map>

class CSoundManager
{

public:
	CSoundManager();
	void loadSound(const char* id, const char* path);

	void playSound(const char* id);
	void clean(const char* id);

private:

	Mix_Chunk* m_sfx{};
	std::map<const char*, Mix_Chunk*> m_SoundMap;

};

