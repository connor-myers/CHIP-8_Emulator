#include "headers/sound.h"

/**
 * No idea what I'm doing here.
 * Thanks to these people below I got sound working
 * https://discourse.libsdl.org/t/having-considerable-difficulty-getting-a-pure-sine-wave-with-sdl-it-sounds-very-close-to-a-sine-wave-but-theres-a-subtle-secondary-freqency/26684
 * https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlopenaudio.html
 */

// Don't use in normal execution; this is so we can free the resources later
audio_user_data *globalAudioUserData;
SDL_AudioSpec *globalDesired;
SDL_AudioSpec *globalObtained;

void init_sound()
{
        audio_user_data *audioUserData = malloc(sizeof(audio_user_data));
        audioUserData->SamplesPerSecond = 100000;
        audioUserData->BytesPerSample = 2 * sizeof(int16_t);
        audioUserData->SampleIndex = 0;
        audioUserData->ToneVolume = 5000;
        audioUserData->ToneHz = 440;
        audioUserData->WavePeriod = audioUserData->SamplesPerSecond / audioUserData->ToneHz;

        SDL_AudioSpec *desired = malloc(sizeof(SDL_AudioSpec));
        SDL_AudioSpec *obtained = malloc(sizeof(SDL_AudioSpec));

        desired->freq = audioUserData->SamplesPerSecond;
        desired->format = AUDIO_S16;
        desired->channels = 2;
        desired->samples = 4096;
        desired->callback = &audio_call_back;
        desired->userdata = audioUserData;
        SDL_OpenAudio(desired, obtained);

        // So we can free these dynamically allocated resources later
        globalAudioUserData = audioUserData;
        globalDesired = desired;
        globalObtained = obtained;
}

void play_audio()
{
        //SDL_PauseAudioDevice(*audioDevice, 0); // Start playing
        SDL_PauseAudio(0);
}

void pause_audio()
{
        //SDL_PauseAudioDevice(*audioDevice, 1); // stop playing
        SDL_PauseAudio(1);
}

void audio_call_back(void* UserData, uint8_t* Stream, int Length)
{
    audio_user_data* AudioUserData = (audio_user_data*)UserData;
    static uint32_t Count = 0;

    uint16_t* SampleBuffer = (uint16_t*)Stream;
    int SamplesToWrite = Length / AudioUserData->BytesPerSample;
    for(int SampleIndex = 0; SampleIndex < SamplesToWrite; SampleIndex++)
    {
       uint16_t ToneValue = round((AudioUserData->ToneVolume * sin(Tau32 * (float)Count / (float)AudioUserData->WavePeriod)));
        *SampleBuffer++ = ToneValue;
        *SampleBuffer++ = ToneValue;
        ++Count;
    }
}

/*
        Releases all heap allocated memory required by audio system
*/
void release_audio_resources()
{
        free(globalAudioUserData);
        free(globalDesired);
        free(globalObtained);
}