#pragma once
#include "SDL_mixer.h"
#include <iostream>
#include <map>

class CSoundManager
{

public:
	CSoundManager();
	void loadSound(const char* id, const char* path);
	void playSound(const char* id, int volume);
	void loadMusic(const char* id, const char* path);
	void playMusic(const char* id, int volume);

	void muteAll();
	void clean(const char* id);

private:


	std::map<const char*, Mix_Chunk*> m_SoundMap;
	std::map<const char*, Mix_Music*> m_MusicMap;

};

