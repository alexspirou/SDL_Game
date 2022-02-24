#include "CSoundManager.h"

CSoundManager::CSoundManager()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Error: " << Mix_GetError() << std::endl;
}
void CSoundManager::loadSound(const char* id, const char* path)
{
	m_sfx = Mix_LoadWAV(path);
	m_sfx->volume = 15;

	m_SoundMap[id] = m_sfx;
}
void CSoundManager::loadSound(const char* path)
{
	m_sfx = Mix_LoadWAV(path);
	m_sfx->volume = 15;

	Mix_PlayChannel(-1, m_sfx, 0);
	//Mix_FreeChunk(m_sfx);

}

void CSoundManager::playSound(const char* id)
{
	Mix_PlayChannel(-1, m_SoundMap[id], 0);


}
void  CSoundManager::clean()
{
	Mix_FreeChunk(m_sfx);
	Mix_Quit();
}