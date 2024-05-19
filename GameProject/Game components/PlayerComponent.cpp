#include "PlayerComponent.h"

PlayerComponent::PlayerComponent(GameEngine::GameObject* gameObject, int playerID):
Component(gameObject), m_PlayerID(playerID){}


