#include "GameCommands.h"
#include "GameObject.h"

ShootBulletCommand::ShootBulletCommand(GameEngine::GameObject* actor): Command(actor) {}

void ShootBulletCommand::Execute()
{
    m_Current = GameEngine::TimeManager::GetInstance().GetCurrent();
    const std::chrono::duration<float> elapsed = m_Current - m_Previous;
    
    if (m_ShootsAvailable < m_MaxShootCount && elapsed.count() > m_ShootCooldown) m_ShootsAvailable = m_MaxShootCount;
    if (m_ShootsAvailable <= 0) return;
    
    --m_ShootsAvailable;
    m_Actor->Notify(GameEngine::GameEvent::bulletShot, static_cast<int>(GameEngine::ObserverIdentifier::bullet));
    
    m_Previous = m_Current;
}

GameEngine::Command::ExecuteOn ShootBulletCommand::ExecuteOnKeyState() const
{
    return ExecuteOn::keyDown;
}
