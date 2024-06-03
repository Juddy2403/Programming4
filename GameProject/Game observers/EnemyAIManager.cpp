#include "EnemyAIManager.h"

std::vector<EnemyComponent*> EnemyAIManager::m_Enemies;
void EnemyAIManager::AddEnemy(EnemyComponent* enemy)
{
    m_Enemies.emplace_back(enemy);
}
void EnemyAIManager::RemoveEnemy(EnemyComponent* enemy)
{
    std::erase(m_Enemies, enemy);
}
void EnemyAIManager::Notify([[maybe_unused]] GameEngine::Subject* subject, int event, [[maybe_unused]] GameEngine::EventData* eventData)
{
    switch (static_cast<GameEvent>(event))
    {
    case GameEvent::bulletShot:
        break;
    case GameEvent::gotInFormation:
        ++m_EnemiesInFormation;
        break;
    case GameEvent::leftFormation:
        --m_EnemiesInFormation;
        break;
    default: break;
    }
}
void EnemyAIManager::Update()
{
    if (m_EnemiesInFormation == static_cast<int>(m_Enemies.size()))
    {
        int enemyToSetOut = rand() % m_Enemies.size();
        m_Enemies[enemyToSetOut]->GetInAttackState();
        m_Enemies[enemyToSetOut+1]->GetInAttackState();
    }
    // enemyComponent->GetGameObjParent()->Notify(static_cast<int>(GameEvent::bulletShot),
    //     static_cast<int>(ObserverIdentifier::bullet));
}
