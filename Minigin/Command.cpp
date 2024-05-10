#include "Command.h"

#include "GameObject.h"
#include "TimeManager.h"
#include "GameProject/PlayerComponent.h"

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

TakeDamage::TakeDamage(GameObject* actor): Command(actor) {}
void TakeDamage::Execute() { m_Actor->GetComponent<HealthComponent>()->Hit(); }

Command::ExecuteOn TakeDamage::ExecuteOnKeyState() const { return ExecuteOn::keyDown; }


SmallScoreIncrease::SmallScoreIncrease(GameObject* actor) : Command(actor) {}
void SmallScoreIncrease::Execute()
{
    m_Actor->GetComponent<ScoreComponent>()->IncreaseScore(10);
}
Command::ExecuteOn SmallScoreIncrease::ExecuteOnKeyState() const { return ExecuteOn::keyDown; }

BigScoreIncrease::BigScoreIncrease(GameObject* actor) : Command(actor) {}

void BigScoreIncrease::Execute()
{
    m_Actor->GetComponent<ScoreComponent>()->IncreaseScore(50);
}
Command::ExecuteOn BigScoreIncrease::ExecuteOnKeyState() const { return ExecuteOn::keyDown; }
