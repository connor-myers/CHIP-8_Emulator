#ifndef SOUND_H
#define SOUND_H

/** Includes **/
#include <SDL2/SDL.h>
#include <math.h>

/** Functions **/
void init_sound();
void audio_call_back(void* UserData, uint8_t* Stream, int Length);

void play_audio();
void pause_audio();
void release_audio_resources();

/** Definitions **/

#define Pi32 3.14159265359f
#define Tau32 (2.0f * Pi32)

typedef struct audio_user_data audio_user_data;
struct audio_user_data
{
    int SamplesPerSecond;
    int BytesPerSample;
    int SampleIndex;
    int ToneHz;
    int ToneVolume;
    int WavePeriod;
    uint32_t FileLength;
    uint16_t* BufferLocation;
};

#endif