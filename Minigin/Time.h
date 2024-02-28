#pragma once
#include "Singleton.h"
#include <chrono>

using namespace std::chrono;

class Time final : public GameEngine::Singleton<Time>
{
public:
	float GetElapsed() const;
	high_resolution_clock::time_point GetCurrent() const;
	duration<float, std::milli> GetFixedTimeStep() const;
	void Update();
private:
	friend class GameEngine::Singleton<Time>;
	Time() = default;
	duration<float> m_ElapsedTime{};
	high_resolution_clock::time_point m_Previous{ high_resolution_clock::now() };
	const duration<float, std::milli> m_FixedTimeStep{ 100.f / 16.f };
	high_resolution_clock::time_point m_Current{};
};
