#pragma once

typedef enum SoundType {
    SandSpawn,
    Ambient,
    StoneSpawn,
    PlantSpawn,
    WaterSpawn,
    FireSpawn
} SoundType;

void AudioManagerInit();

void AudioManagerPlaySoundOnce(SoundType soundType);
