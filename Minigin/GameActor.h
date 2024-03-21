#pragma once
#include "GameObject.h"

namespace GameEngine {
	class GameActor : public GameObject
	{
	public:
		void Hit() { --m_Lives; };
		int GetRemainingLives() const { return m_Lives; }
		enum class MessageTypes {
			updatePlayerHealth,
			log,
			handleAchievements,
			updateScore
		};
	private:
		int m_Lives{ 3 };
	};
}


