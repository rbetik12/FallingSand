#include "AudioManager.h"
#include <stdio.h>
#include <time.h>
#include <vx-sound.h>


static AudioSource ambientAudio;
static AudioSource sandSpawnAudio;
static AudioSource fireSpawnAudio;
static AudioSource waterSpawnAudio;
static AudioSource stoneSpawnAudio;
static AudioSource plantSpawnAudio;

struct timespec start;
struct timespec finish;
double elapsed;

void AudioManagerInit() {
#ifdef UNIX
    clock_gettime(CLOCK_MONOTONIC, &start);
    clock_gettime(CLOCK_MONOTONIC, &finish);
#endif
    VxSndInit();
    VxSndLoadSound("data/sound/ambient.mp3", &ambientAudio);
    VxSndLoadSound("data/sound/sand_spawn.mp3", &sandSpawnAudio);
    VxSndLoadSound("data/sound/water_spawn.mp3", &waterSpawnAudio);
    VxSndLoadSound("data/sound/fire_spawn.mp3", &fireSpawnAudio);
    VxSndLoadSound("data/sound/stone_spawn.mp3", &stoneSpawnAudio);
    VxSndLoadSound("data/sound/plant_spawn.mp3", &plantSpawnAudio);
    if (!ambientAudio.loaded || !sandSpawnAudio.loaded) {
        fprintf(stderr, "Can't load music!\n");
    }
}

void AudioManagerPlaySoundOnce(SoundType soundType) {
#ifdef UNIX
    clock_gettime(CLOCK_MONOTONIC, &start);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    finish = start;
    if (-elapsed < 0.2f) return;
#endif
    switch (soundType) {
        case Ambient:
            VxSndPlaySound(&ambientAudio);
            break;
        case SandSpawn:
            VxSndPlaySound(&sandSpawnAudio);
            break;
        case StoneSpawn:
            VxSndPlaySound(&stoneSpawnAudio);
            break;
        case WaterSpawn:
            VxSndPlaySound(&waterSpawnAudio);
            break;
        case FireSpawn:
            VxSndPlaySound(&fireSpawnAudio);
            break;
        case PlantSpawn:
            VxSndPlaySound(&plantSpawnAudio);
            break;
    }
}