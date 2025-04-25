#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SDL_mixer.h>

extern Mix_Music* g_background_music; 
extern Mix_Chunk* g_bullet_hit_sound; 
extern Mix_Chunk* g_eat_brain_sound;
extern Mix_Chunk* g_hit_threat_sound;
extern Mix_Chunk* g_hit_boom_sound;

#endif 