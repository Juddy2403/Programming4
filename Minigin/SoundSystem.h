#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

namespace GameEngine
{
    using SoundId = unsigned short;
    class SoundSystem
    {
    public:
        SoundSystem() = default;
        SoundSystem(const SoundSystem& other) = delete;
        SoundSystem(SoundSystem&& other) noexcept = delete;
        SoundSystem& operator=(const SoundSystem& other) = delete;
        SoundSystem& operator=(SoundSystem&& other) noexcept = delete;
        virtual ~SoundSystem() = default;

        virtual void Play(const SoundId id, const int volume) = 0;
        virtual void FillSoundPaths(const std::string& fileSource);
    protected:
        std::vector<std::string> m_SoundFilePaths;
    };

    class SdlSoundSystem final : public SoundSystem
    {
    public:
        SdlSoundSystem();
        SdlSoundSystem(const SdlSoundSystem& other) = delete;
        SdlSoundSystem(SdlSoundSystem&& other) noexcept = delete;
        SdlSoundSystem& operator=(const SdlSoundSystem& other) = delete;
        SdlSoundSystem& operator=(SdlSoundSystem&& other) noexcept = delete;
        virtual ~SdlSoundSystem() override;

        void Play(const SoundId id, const int volume) override;
        virtual void FillSoundPaths(const std::string& fileSource) override;
    private:
        class SDLAudioClip;
        std::vector<std::unique_ptr<SDLAudioClip>> m_AudioClips;
    };
    class LoggingSoundSystem final : public SoundSystem
    {
        std::unique_ptr<SoundSystem> m_RealSs;
    public:
        LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss) : m_RealSs(std::move(ss)) {}
        LoggingSoundSystem(const LoggingSoundSystem& other) = delete;
        LoggingSoundSystem(LoggingSoundSystem&& other) noexcept = delete;
        LoggingSoundSystem& operator=(const LoggingSoundSystem& other) = delete;
        LoggingSoundSystem& operator=(LoggingSoundSystem&& other) noexcept = delete;
        virtual ~LoggingSoundSystem() override = default;

        void Play(const SoundId id, const int volume) override;
        virtual void FillSoundPaths(const std::string& fileSource) override;
    };
    class NullSoundSystem final : public SoundSystem
    {
    public:
        void Play(const SoundId id, const int volume) override {id;volume;}
        virtual void FillSoundPaths(const std::string& fileSource) override {fileSource;};
    };

    class ServiceLocator final
    {
        static std::unique_ptr<SoundSystem> m_SsInstance;
    public:
        static SoundSystem& GetSoundSystem() { return *m_SsInstance; }
        static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss);
       
    };
}
