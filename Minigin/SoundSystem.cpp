#include "SoundSystem.h"
#include <fstream>
#include <iostream>
#include "DerivedSoundSystems.h"
#include "ServiceLocator.h"

using namespace GameEngine;
std::unique_ptr<SoundSystem> ServiceLocator::m_SsInstance{ std::make_unique<NullSoundSystem>() };

SoundSystem::SoundSystem()
{
    m_WorkerThread = std::thread(&SoundSystem::ProcessQueue, this);
}
SoundSystem::~SoundSystem()
{
    // Signal the worker thread to stop and wait for it to finish.
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_IsRunning = false;
    }
    m_ConditionVariable.notify_one();
    m_WorkerThread.join();
}
void SoundSystem::AddSoundToQueue(const SoundId id, const int volume)
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    if ((m_QueueTail + 1) % maxPending == m_QueueHead)
    {
        std::cerr << "Too many pending sounds\n";
        return;
    }
    for (int i = m_QueueHead; i != m_QueueTail; i = (i + 1) % maxPending)
    {
        if (m_PendingSounds[i].id == id)
        {
            // Use the larger of the two volumes.
            m_PendingSounds[i].volume = std::max(volume, m_PendingSounds[i].volume);

            // Don't need to enqueue.
            return;
        }
    }
    m_PendingSounds[m_QueueTail] = { id,volume };
    m_QueueTail = (m_QueueTail + 1) % maxPending;
    m_ConditionVariable.notify_one();
}
void SoundSystem::Update()
{
    if (m_QueueHead == m_QueueTail) return;
    PlaySound(m_PendingSounds[m_QueueHead].id, m_PendingSounds[m_QueueHead].volume);
    m_QueueHead = (m_QueueHead + 1) % maxPending;
}
void SoundSystem::FillSoundPaths(const std::string& fileSource)
{
    std::ifstream file(fileSource);

    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << fileSource << '\n';
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        m_SoundFilePaths.emplace_back(line);
    }

    file.close();
}

int SoundSystem::GetPending() const
{
    return abs(m_QueueHead - m_QueueTail);
}
void SoundSystem::ProcessQueue()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(m_Mutex);
        m_ConditionVariable.wait(lock, [this] { return !m_IsRunning || GetPending(); });

        if (!m_IsRunning && GetPending() == 0)
        {
            break;
        }

        // Process queue
        Update();
    }
}
