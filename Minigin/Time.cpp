#include "Time.h"
using namespace std::chrono;

duration<float> Time::m_ElapsedTime = duration<float>{};

float Time::GetElapsed() 
{
    return m_ElapsedTime.count();
}

high_resolution_clock::time_point Time::GetCurrent() const
{
    return m_Current;
}

duration<float, std::milli> Time::GetFixedTimeStep() const
{
    return m_FixedTimeStep;
}

void Time::Update()
{
    m_Current = high_resolution_clock::now();
    m_ElapsedTime = duration<float>(m_Current - m_Previous);
    m_Previous = m_Current;
}
