#include "EnemyAIManager.h"

#include "Game components/Enemy components/BossGalagaComponent.h"

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
        if (m_Enemies[enemyToSetOut]->GetEnemyID() == EnemyId::bossGalaga)
        {
            if (rand() % 2 == 0)
            {
                auto boss = dynamic_cast<BossGalagaComponent*>(m_Enemies[enemyToSetOut]);
                boss->GetInBeamAttackState();
                return;
            }
        }
        m_Enemies[enemyToSetOut]->GetInAttackState();
        if (m_Enemies.size() == 1) return;
        //set out a second enemy
        if (rand() % 3 <= 1) m_Enemies[enemyToSetOut - 1]->GetInAttackState();
    }
}
