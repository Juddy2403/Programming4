#pragma once
#include "Singleton.h"
#include <chrono>

namespace GameEngine
{
	class TimeManager final : public GameEngine::Singleton<TimeManager>
	{
	public:
		static float GetElapsed();
		[[nodiscard]] std::chrono::high_resolution_clock::time_point GetCurrent() const;
		[[nodiscard]] std::chrono::duration<float, std::milli> GetFixedTimeStep() const;
		void Update();
	private:
		friend class GameEngine::Singleton<TimeManager>;
		TimeManager() = default;
		static std::chrono::duration<float> m_ElapsedTime;
		std::chrono::high_resolution_clock::time_point m_Previous{std::chrono::high_resolution_clock::now() };
		const std::chrono::duration<float, std::milli> m_FixedTimeStep{ 100.f / 16.f };
		std::chrono::high_resolution_clock::time_point m_Current{};
	};
}

