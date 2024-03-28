#include "ICommand.h"
#include "Time.h"
#include "GameActor.h"

using namespace GameEngine;

ICommand::ICommand(GameActor* actor) : m_Actor{ actor } {}

Move::Move(GameActor* actor, const glm::vec2& direction):
    ICommand(actor),
    m_Direction(direction)
{}

Move::~Move() {}

void Move::Execute()
{
    const auto increase = Time::GetElapsed() * m_Actor->GetSpeed() * m_Direction;
    m_Actor->GetLocalTransform().Translate(increase);
    
}
ICommand::ExecuteOn Move::ExecuteOnKeyState() const { return ExecuteOn::keyPressed; }

TakeDamage::TakeDamage(GameActor* actor): ICommand(actor) {}
void TakeDamage::Execute() { m_Actor->Hit(); }

ICommand::ExecuteOn TakeDamage::ExecuteOnKeyState() const { return ExecuteOn::keyDown; }

SmallScoreIncrease::SmallScoreIncrease(GameActor* actor) : ICommand(actor) {}
void SmallScoreIncrease::Execute() { m_Actor->IncreaseScore(10); }
ICommand::ExecuteOn SmallScoreIncrease::ExecuteOnKeyState() const { return ExecuteOn::keyDown; }

BigScoreIncrease::BigScoreIncrease(GameActor* actor) : ICommand(actor) { m_Actor->IncreaseScore(50); }
void BigScoreIncrease::Execute() {m_Actor->IncreaseScore(50);}
ICommand::ExecuteOn BigScoreIncrease::ExecuteOnKeyState() const { return ExecuteOn::keyDown; }
