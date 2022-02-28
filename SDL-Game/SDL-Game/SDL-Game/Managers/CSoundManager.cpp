#include "CSoundManager.h"

CSoundManager::CSoundManager()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Error: " << Mix_GetError() << std::endl;

}
void CSoundManager::loadSound(const char* path , const char* id)
{
	m_sfx = Mix_LoadWAV(path);
	m_SoundMap[id] = m_sfx;

}
void CSoundManager::playSound(const char* id)
{
	Mix_PlayChannel(-1, m_SoundMap[id], 0);
}
void  CSoundManager::clean(const char* id)
{
	m_SoundMap.erase(id);
	Mix_FreeChunk(m_sfx);
	Mix_Quit();
}