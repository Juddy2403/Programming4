#include "GameCommands.h"

#include "BulletTracker.h"
#include "DataStructs.h"
#include "Galaga.h"
#include "Subjects/GameObject.h"
#include "Game components/ModeSelectionComp.h"

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
SwitchModesCommand::SwitchModesCommand(GameEngine::GameObject* actor, bool movingUp):
    Command(actor), m_ModeSelectionComp(actor->GetComponent<ModeSelectionComp>()),
    m_IsMovingUp(movingUp)
{}
void SwitchModesCommand::Execute()
{
    if (m_IsMovingUp) m_ModeSelectionComp->MoveUp();
    else m_ModeSelectionComp->MoveDown();
}
GameEngine::Command::ExecuteOn SwitchModesCommand::ExecuteOnKeyState() const
{
    return ExecuteOn::keyDown;
}

SelectModeCommand::SelectModeCommand(GameEngine::GameObject* actor):
    Command(actor),
    m_ModeSelectionComp(actor->GetComponent<ModeSelectionComp>()) {}
void SelectModeCommand::Execute()
{
    GameMode mode = m_ModeSelectionComp->GetSelectedMode();
    Galaga::GetInstance().SetGameMode(mode);
}
GameEngine::Command::ExecuteOn SelectModeCommand::ExecuteOnKeyState() const
{
    return ExecuteOn::keyDown;
}
