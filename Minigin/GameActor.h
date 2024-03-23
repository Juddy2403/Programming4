#pragma once
#include "GameObject.h"

namespace GameEngine {
	class GameActor : public GameObject
	{
	public:
		GameActor(std::string name);
		explicit GameActor(std::string name,int lives, float speed);

		void Hit();
		float GetSpeed() const { return m_Speed; }
		int GetRemainingLives() const { return m_Lives; }

		enum class MessageTypes {
			updatePlayerHealth,
			log,
			handleAchievements,
			updateScore
		};

	private:
		int m_Lives{ 3 };
		float m_Speed{ 100 };
	};
}


