#include "TimeManager.h"
    
using namespace std::chrono;
using namespace GameEngine;

duration<float> TimeManager::m_ElapsedTime = duration<float>{};

float TimeManager::GetElapsed() 
{
    return m_ElapsedTime.count();
}

high_resolution_clock::time_point TimeManager::GetCurrent() const
{
    return m_Current;
}

duration<float, std::milli> TimeManager::GetFixedTimeStep() const
{
    return m_FixedTimeStep;
}

void TimeManager::Update()
{
    m_Current = high_resolution_clock::now();
    m_ElapsedTime = duration<float>(m_Current - m_Previous);
    m_Previous = m_Current;
}
