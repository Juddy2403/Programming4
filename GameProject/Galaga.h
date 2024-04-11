#pragma once
#include "Singleton.h"
//TODO: remove singleton just init a galaga object inside main
class Galaga final : public GameEngine::Singleton<Galaga>
{
public:
    ~Galaga() = default;
    Galaga(const Galaga& other) = delete;
    Galaga(Galaga&& other) noexcept = delete;
    Galaga& operator=(const Galaga& other) = delete;
    Galaga& operator=(Galaga&& other) noexcept = delete;

    void LoadLevel() const;
private:
    friend class Singleton<Galaga>;
    Galaga() = default;
};
