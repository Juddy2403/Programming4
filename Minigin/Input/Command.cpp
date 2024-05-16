#include "Command.h"
#include "Minigin/Subjects/GameObject.h"
#include "Minigin/Managers/TimeManager.h"

using namespace GameEngine;

Command::Command(GameObject* actor) : m_Actor{ actor } {}

Move::Move(GameObject* actor, const glm::vec2& direction, int speed):
    Command(actor),
    m_Direction(direction),
    m_Speed(speed)
{}

Move::~Move() {}

void Move::Execute()
{
    m_Actor->GetLocalTransform().Translate(TimeManager::GetElapsed() * m_Speed * m_Direction);
}
Command::ExecuteOn Move::ExecuteOnKeyState() const { return ExecuteOn::keyPressed; }


