#include "ICommand.h"

#include "GameObject.h"
#include "TimeManager.h"
#include "GameProject/PlayerComponent.h"

using namespace GameEngine;

ICommand::ICommand(GameObject* actor) : m_Actor{ actor } {}

Move::Move(GameObject* actor, const glm::vec2& direction, int speed):
    ICommand(actor),
    m_Direction(direction),
    m_Speed(speed)
{}

Move::~Move() {}

void Move::Execute()
{
    m_Actor->GetLocalTransform().Translate(TimeManager::GetElapsed() * m_Speed * m_Direction);
}
ICommand::ExecuteOn Move::ExecuteOnKeyState() const { return ExecuteOn::keyPressed; }

TakeDamage::TakeDamage(GameObject* actor): ICommand(actor) {}
void TakeDamage::Execute() { m_Actor->GetComponent<HealthComponent>()->Hit(); }

ICommand::ExecuteOn TakeDamage::ExecuteOnKeyState() const { return ExecuteOn::keyDown; }


SmallScoreIncrease::SmallScoreIncrease(GameObject* actor) : ICommand(actor) {}
void SmallScoreIncrease::Execute()
{
    m_Actor->GetComponent<ScoreComponent>()->IncreaseScore(10);
}
ICommand::ExecuteOn SmallScoreIncrease::ExecuteOnKeyState() const { return ExecuteOn::keyDown; }

BigScoreIncrease::BigScoreIncrease(GameObject* actor) : ICommand(actor) {}

void BigScoreIncrease::Execute()
{
    m_Actor->GetComponent<ScoreComponent>()->IncreaseScore(50);
}
ICommand::ExecuteOn BigScoreIncrease::ExecuteOnKeyState() const { return ExecuteOn::keyDown; }
