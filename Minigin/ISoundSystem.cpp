#include "ISoundSystem.h"
#include <fstream>
#include <iostream>
#include "DerivedSoundSystems.h"
#include "ServiceLocator.h"

using namespace GameEngine;
std::unique_ptr<ISoundSystem> ServiceLocator::m_SsInstance{ std::make_unique<NullSoundSystem>() };

ISoundSystem::ISoundSystem()
{
    m_WorkerThread = std::thread(&ISoundSystem::ProcessQueue, this);
}
ISoundSystem::~ISoundSystem()
{
    // Signal the worker thread to stop and wait for it to finish.
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_IsRunning = false;
    }
    m_ConditionVariable.notify_one();
    m_WorkerThread.join();
}
void ISoundSystem::AddSoundToQueue(const SoundId id, const int volume)
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
void ISoundSystem::Update()
{
    if (m_QueueHead == m_QueueTail) return;
    PlaySound(m_PendingSounds[m_QueueHead].id, m_PendingSounds[m_QueueHead].volume);
    m_QueueHead = (m_QueueHead + 1) % maxPending;
}
void ISoundSystem::FillSoundPaths(const std::string& fileSource)
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

int ISoundSystem::GetPending() const
{
    return abs(m_QueueHead - m_QueueTail);
}
void ISoundSystem::ProcessQueue()
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
