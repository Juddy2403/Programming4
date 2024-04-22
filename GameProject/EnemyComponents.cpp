#include "EnemyComponents.h"

BeeComponent::BeeComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent):
    Component(gameObj),
    m_SpriteComponent(spriteComponent)
{}

void BeeComponent::Update()
{
    Component::Update();
}
ButterflyComponent::ButterflyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent):
    Component(gameObj),
    m_SpriteComponent(spriteComponent)
{}

void ButterflyComponent::Update()
{
    Component::Update();
}
BossGalagaComponent::BossGalagaComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent):
    Component(gameObj),
    m_SpriteComponent(spriteComponent)
{}
void BossGalagaComponent::Update()
{
    Component::Update();
}
