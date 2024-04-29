#pragma once
#include <unordered_map>
#include <thread>
#include <condition_variable>

namespace GameEngine
{
    using SoundId = unsigned short;
    struct SoundInfo
    {
        SoundId id;
        int volume;
    };
    class ISoundSystem
    {
    public:
        ISoundSystem();
        ISoundSystem(const ISoundSystem& other) = delete;
        ISoundSystem(ISoundSystem&& other) noexcept = delete;
        ISoundSystem& operator=(const ISoundSystem& other) = delete;
        ISoundSystem& operator=(ISoundSystem&& other) noexcept = delete;
        virtual ~ISoundSystem();

        virtual void AddSoundToQueue(const SoundId id, const int volume);
        virtual void Update();
        virtual void FillSoundPaths(const std::string& fileSource);
        virtual void PlaySound(const SoundId id, const int volume) = 0;
        int GetPending() const;
    protected:
        static constexpr int maxPending = 16;
        SoundInfo m_PendingSounds[maxPending]{};
        int m_QueueHead{};
        int m_QueueTail{};
        std::vector<std::string> m_SoundFilePaths;
    private:
        std::mutex m_Mutex;
        std::condition_variable m_ConditionVariable;
        std::thread m_WorkerThread;
        bool m_IsRunning{true};
        void ProcessQueue();
    };

}
