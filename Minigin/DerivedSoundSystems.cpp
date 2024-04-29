#include "DerivedSoundSystems.h"
#include "SDL_mixer.h"
#include <iostream>

using namespace GameEngine;

class SdlSoundSystem::SDLAudioClip final
{
public:
    SDLAudioClip(const SDLAudioClip& other) = delete;
    SDLAudioClip(SDLAudioClip&& other) noexcept = delete;
    SDLAudioClip& operator=(const SDLAudioClip& other) = delete;
    SDLAudioClip& operator=(SDLAudioClip&& other) noexcept = delete;
    explicit SDLAudioClip(const std::string& filePath) : m_FilePath(filePath) {}
    ~SDLAudioClip()
    {
        if (m_pSound != nullptr)
        {
            Mix_FreeChunk(m_pSound);
            m_pSound = nullptr;
        }
    }
    void Load()
    {
        m_pSound = Mix_LoadWAV(m_FilePath.c_str());
        if (m_pSound == nullptr)
        {
            std::cerr << "Failed to load sound: " << m_FilePath << '\n';
        }
    }
    [[nodiscard]] bool IsLoaded() const
    {
        return m_pSound != nullptr;
    }
    void SetVolume(const int volume) const
    {
        Mix_VolumeChunk(m_pSound, volume);
    }
    void Play() const
    {
        Mix_PlayChannel(-1, m_pSound, 0);
    }
    static void OpenAudio()
    {
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            std::cerr << "Failed to initialize sound system.\n";
        }
        else
        {
            std::cout << "Sound system initialized.\n";
        }
    }
    static void CloseAudio()
    {
        Mix_CloseAudio();
    }
private:
    std::string m_FilePath{};
    Mix_Chunk* m_pSound{};
};

SdlSoundSystem::SdlSoundSystem() : SoundSystem()
{
    SDLAudioClip::OpenAudio();
}
SdlSoundSystem::~SdlSoundSystem()
{
    SDLAudioClip::CloseAudio();
}
void SdlSoundSystem::FillSoundPaths(const std::string& fileSource)
{
    SoundSystem::FillSoundPaths(fileSource);
    for (const auto& path : m_SoundFilePaths)
    {
        m_AudioClips.emplace_back(std::make_unique<SDLAudioClip>(path));
    }
}
void SdlSoundSystem::PlaySound(const SoundId id, const int volume)
{
    auto audioClip = m_AudioClips[id].get();
    if (!audioClip->IsLoaded())
        audioClip->Load();
    audioClip->SetVolume(volume);
    audioClip->Play();
}

void LoggingSoundSystem::AddSoundToQueue(const SoundId id, const int volume)
{
    m_RealSs->AddSoundToQueue(id, volume);
    std::cout << "Adding to the queue: " << id << " at volume " << volume << '\n';
}
void LoggingSoundSystem::FillSoundPaths(const std::string& fileSource)
{
    m_RealSs->FillSoundPaths(fileSource);
    std::cout << "Filling sound paths from " << fileSource << "\n";
}

