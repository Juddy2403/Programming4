#pragma once
#include <memory>
#include <string>
#include "SoundSystem.h"

namespace GameEngine
{
    class SdlSoundSystem final : public SoundSystem
    {
    public:
        SdlSoundSystem();
        SdlSoundSystem(const SdlSoundSystem& other) = delete;
        SdlSoundSystem(SdlSoundSystem&& other) noexcept = delete;
        SdlSoundSystem& operator=(const SdlSoundSystem& other) = delete;
        SdlSoundSystem& operator=(SdlSoundSystem&& other) noexcept = delete;
        virtual ~SdlSoundSystem() override;

        virtual void FillSoundPaths(const std::string& fileSource) override;
        virtual void PlaySound(const SoundId id, const int volume) override;
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

        void AddSoundToQueue(const SoundId id, const int volume) override;
        virtual void FillSoundPaths(const std::string& fileSource) override;
        void PlaySound(const SoundId id, const int volume) override{id;volume;} //
    };
    class NullSoundSystem final : public SoundSystem
    {
    public:
        virtual void PlaySound(const SoundId id, const int volume) override {id;volume;}
    };

}
