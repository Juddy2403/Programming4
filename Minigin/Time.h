#pragma once
#include "Singleton.h"
#include <chrono>

using namespace std::chrono;

class Time final : public GameEngine::Singleton<Time>
{
public:
	float GetElapsed() const;
	high_resolution_clock::time_point GetCurrent() const;
	void Update();
private:
	friend class GameEngine::Singleton<Time>;
	Time() = default;
	duration<float> m_ElapsedTime{};
	high_resolution_clock::time_point m_Previous{ high_resolution_clock::now() };
	high_resolution_clock::time_point m_Current{};
};
