﻿#pragma once
#include "DerivedSoundSystems.h"

enum class GameId
{
    enemy,
    player,
    bullet,
    observer,
    text,
    texture
};

enum class EnemyId
{
    bee,
    beeDiving,
    butterfly,
    butterflyDiving,
    bossGalaga,
    bossGalagaDiving
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
