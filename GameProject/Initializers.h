#pragma once
#include <memory>
#include "Subjects/GameObject.h"

std::unique_ptr<GameEngine::GameObject> InitFighter();

std::unique_ptr<GameEngine::GameObject> InitBullet(int playerID);

std::unique_ptr<GameEngine::GameObject> InitBee();

std::unique_ptr<GameEngine::GameObject> InitButterfly();

std::unique_ptr<GameEngine::GameObject> InitBossGalaga();