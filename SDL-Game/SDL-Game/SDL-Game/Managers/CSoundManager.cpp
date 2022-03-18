#include "CSoundManager.h"

CSoundManager::CSoundManager()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Error: " << Mix_GetError() << std::endl;

}
void CSoundManager::loadSound(const char* id, const char* path)
{
	Mix_Chunk* m_sfx;
	m_sfx = Mix_LoadWAV(path);
	m_SoundMap[id] = m_sfx;
	m_sfx = NULL;

}
void CSoundManager::playSound(const char* id, int volume)
{

	Mix_VolumeChunk(m_SoundMap[id], volume);
	Mix_PlayChannel(-1, m_SoundMap[id], 0);
}
void CSoundManager::loadMusic(const char* id, const char* path)
{
	//Load music
	Mix_Music* m_Music;
	m_Music = Mix_LoadMUS(path);
	if (m_Music == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	m_MusicMap[id] = m_Music;
	m_Music = NULL;
}
void CSoundManager::playMusic(const char* id, int volume)
{
	Mix_VolumeMusic(volume);
	Mix_PlayMusic(m_MusicMap[id], -1);
}
void CSoundManager::muteAll()
{


}
void  CSoundManager::clean(const char* id)
{
	Mix_FreeChunk(m_SoundMap[id]);
	m_SoundMap.erase(id);
	Mix_Quit();
}