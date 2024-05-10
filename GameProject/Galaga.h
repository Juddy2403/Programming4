#pragma once
class Galaga final 
{
public:
    Galaga() = default;
    ~Galaga() = default;
    Galaga(const Galaga& other) = delete;
    Galaga(Galaga&& other) noexcept = delete;
    Galaga& operator=(const Galaga& other) = delete;
    Galaga& operator=(Galaga&& other) noexcept = delete;

    static void LoadLevel();
};
