#pragma once
#include "EventData.h"
#include "SoundSystem.h"

enum class GameId
{
    player,
    enemy,
    bullet,
    observer,
    text,
    texture
};

enum class SoundId : GameEngine::SoundId
{
    bossDeath,
    capturedShip,
    enemyDeath,
    playerDeath,
    playerShoot,
    start,
    tractorBeam
};
