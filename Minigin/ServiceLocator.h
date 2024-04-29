#pragma once
#include <memory>
#include "DerivedSoundSystems.h"

namespace GameEngine
{
    class SoundSystem;
    class ServiceLocator final
    {
        static std::unique_ptr<SoundSystem> m_SsInstance;
    public:
        static SoundSystem& GetSoundSystem() { return *m_SsInstance; }
        static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
        {
            m_SsInstance = ss == nullptr ? std::make_unique<NullSoundSystem>() : std::move(ss);
        }
    };
    
}

