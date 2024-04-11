#include "ICommand.h"

#include "ActorComponent.h"
#include "TimeManager.h"
#include "GameObject.h"

using namespace GameEngine;

ICommand::ICommand(GameObject* actor) : m_Actor{ actor } {}

Move::Move(GameObject* actor, const glm::vec2& direction):
    ICommand(actor),
    m_Direction(direction)
{}

Move::~Move() {}

void Move::Execute()
{
    m_Actor->GetComponent<ActorComponent>()->Move(m_Direction);
}
ICommand::ExecuteOn Move::ExecuteOnKeyState() const { return ExecuteOn::keyPressed; }

TakeDamage::TakeDamage(GameObject* actor): ICommand(actor) {}
void TakeDamage::Execute() { m_Actor->GetComponent<ActorComponent>()->Hit(); }

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
