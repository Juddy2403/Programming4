#pragma once
#include "Singleton.h"
#include <chrono>

class Time final : public GameEngine::Singleton<Time>
{
public:
	static float GetElapsed();
	std::chrono::high_resolution_clock::time_point GetCurrent() const;
	std::chrono::duration<float, std::milli> GetFixedTimeStep() const;
	void Update();
private:
	friend class GameEngine::Singleton<Time>;
	Time() = default;
	static std::chrono::duration<float> m_ElapsedTime;
	std::chrono::high_resolution_clock::time_point m_Previous{std::chrono::high_resolution_clock::now() };
	const std::chrono::duration<float, std::milli> m_FixedTimeStep{ 100.f / 16.f };
	std::chrono::high_resolution_clock::time_point m_Current{};
};
