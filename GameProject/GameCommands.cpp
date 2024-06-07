#include "GameCommands.h"

#include "BulletTracker.h"
#include "DataStructs.h"
#include "Subjects/GameObject.h"

ShootBulletCommand::ShootBulletCommand(GameEngine::GameObject* actor): Command(actor) {}

void ShootBulletCommand::Execute()
{
    m_Current = GameEngine::TimeManager::GetInstance().GetCurrent();
    const std::chrono::duration<float> elapsed = m_Current - m_Previous;
    
    if (m_ShootsAvailable < m_MaxShootCount && elapsed.count() > m_ShootCooldown) m_ShootsAvailable = m_MaxShootCount;
    if (m_ShootsAvailable <= 0) return;
    
    --m_ShootsAvailable;
    m_Actor->Notify(static_cast<int>(GameEvent::bulletShot),
        static_cast<int>(ObserverIdentifier::bullet));
    
    m_Previous = m_Current;
    BulletTracker::BulletFired();
}

GameEngine::Command::ExecuteOn ShootBulletCommand::ExecuteOnKeyState() const
{
    return ExecuteOn::keyDown;
}
