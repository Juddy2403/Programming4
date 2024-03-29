#include "ICommand.h"

#include "ActorComponent.h"
#include "Time.h"
#include "GameObject.h"

using namespace GameEngine;

ICommand::ICommand(GameObject* actor) : m_Actor{ actor } {}

Move::Move(GameObject* actor, const glm::vec2& direction, const float speed):
    ICommand(actor),
    m_Speed(speed),
    m_Direction(direction)
{}

Move::~Move() {}

void Move::Execute()
{
    const auto increase = Time::GetElapsed() * m_Speed * m_Direction;
    m_Actor->GetLocalTransform().Translate(increase);
}
ICommand::ExecuteOn Move::ExecuteOnKeyState() const { return ExecuteOn::keyPressed; }

TakeDamage::TakeDamage(GameObject* actor): ICommand(actor) {}
void TakeDamage::Execute() { m_Actor->GetComponent<ActorComponent>()->Hit(); }

ICommand::ExecuteOn TakeDamage::ExecuteOnKeyState() const { return ExecuteOn::keyDown; }

SmallScoreIncrease::SmallScoreIncrease(GameObject* actor) : ICommand(actor) {}
void SmallScoreIncrease::Execute()
{
    m_Actor->GetComponent<ActorComponent>()->IncreaseScore(10);
}
ICommand::ExecuteOn SmallScoreIncrease::ExecuteOnKeyState() const { return ExecuteOn::keyDown; }

BigScoreIncrease::BigScoreIncrease(GameObject* actor) : ICommand(actor)
{
    m_Actor->GetComponent<ActorComponent>()->IncreaseScore(50);
}
void BigScoreIncrease::Execute()
{
    m_Actor->GetComponent<ActorComponent>()->IncreaseScore(50);
}
ICommand::ExecuteOn BigScoreIncrease::ExecuteOnKeyState() const { return ExecuteOn::keyDown; }
