#pragma once
#include "EventData.h"
#include "Sound/DerivedSoundSystems.h"


enum class ObserverIdentifier
{
    health,
    score,
    bullet,
    collision,
    formation
};
enum class GameEvent
{
    collision, //must be the first one since its in the engine too
    hasBeenHit, 
    died,
    bulletShot,
    bulletOutOfBounds,
    scoreIncrease,
    gotInFormation,
    event = -1//for when smth generic happens
};

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

