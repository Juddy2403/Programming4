﻿#pragma once
#include <memory>

namespace GameEngine
{
    enum class KeyboardInputKey
    {
        A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
    };
    class KeyboardInput final
    {
    public:
        KeyboardInput();
        ~KeyboardInput();
        KeyboardInput(const KeyboardInput& other) = delete;
        KeyboardInput(KeyboardInput&& other) = delete;
        KeyboardInput& operator=(const KeyboardInput& other) = delete;
        KeyboardInput& operator=(KeyboardInput&& other) = delete;

        [[nodiscard]] bool ProcessKeyboardInput() const;

        [[nodiscard]] bool IsKeyDown(KeyboardInputKey inputKey) const;
        [[nodiscard]] bool IsKeyUp(KeyboardInputKey inputKey) const;
        [[nodiscard]] bool IsKeyPressed(KeyboardInputKey inputKey) const;

    private:
        class SDLInput;
        std::unique_ptr<SDLInput> m_pSDLInput;
    };
}
