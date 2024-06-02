#pragma once
#include <memory>
#include "Subjects/GameObject.h"

class PlayerComponent;
std::unique_ptr<GameEngine::GameObject> InitFighter();

std::unique_ptr<GameEngine::GameObject> InitBullet(int playerID);

std::unique_ptr<GameEngine::GameObject> InitEnemyBullet(const glm::vec2& direction);

std::unique_ptr<GameEngine::GameObject> InitBee(PlayerComponent* playerComponent);

std::unique_ptr<GameEngine::GameObject> InitButterfly(PlayerComponent* playerComponent);

std::unique_ptr<GameEngine::GameObject> InitBossGalaga(PlayerComponent* playerComponent);