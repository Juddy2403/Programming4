#pragma once
#include "EventData.h"
#include "Sound/DerivedSoundSystems.h"

enum class GameId
{
    enemy,
    player,
    bullet,
    observer,
    text,
    texture,
    misc
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

struct ScoreData : GameEngine::EventData
{
    int playerId;
    int enemyId;
};

