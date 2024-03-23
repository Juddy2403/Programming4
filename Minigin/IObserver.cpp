#include "IObserver.h"
#include "ISubject.h"
#include "GameActor.h"

GameEngine::IObserver::IObserver(const std::string& name) : m_Name{ name } {}

GameEngine::HealthObserver::HealthObserver(const std::string& name): IObserver(name) {}

void GameEngine::HealthObserver::Update(ISubject* subject)
{
	auto* textComp = GetComponent<TextComponent>();
	if (textComp)
	{
		auto gameActor = dynamic_cast<GameActor*>(subject);
		assert(gameActor);
		int lives = gameActor->GetRemainingLives();
		textComp->SetText("# lives: " + std::to_string(lives));
		textComp->Update();

	}
}

