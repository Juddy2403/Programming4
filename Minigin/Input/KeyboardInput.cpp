#include "KeyboardInput.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <backends/imgui_impl_sdl2.h>
#include <array>
#include <SDL.h>
#include <iostream>
#include <unordered_map>

using namespace GameEngine;
class KeyboardInput::SDLInput
{
public:
    SDLInput()
    {
        m_PreviousState.fill(0);
        m_CurrentState.fill(0);
        m_KeysPressedThisFrame.fill(0);
        m_KeysReleasedThisFrame.fill(0);
    }
    SDLInput(const SDLInput& other) = delete;
    SDLInput(SDLInput&& other) noexcept = delete;
    SDLInput& operator=(const SDLInput& other) = delete;
    SDLInput& operator=(SDLInput&& other) noexcept = delete;
    ~SDLInput() = default;

    bool ProcessKeyboardInput()
    {
        std::ranges::copy(m_CurrentState, m_PreviousState.begin());
        m_KeysReleasedThisFrame.fill(0);
        m_KeysPressedThisFrame.fill(0);

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            const int keyCode = static_cast<int>(e.key.keysym.scancode);
            switch (e.type)
            {
            case SDL_QUIT:
                return false;
            case SDL_KEYDOWN:
                m_CurrentState[keyCode] = 1;
                if (!m_PreviousState[keyCode]) m_KeysPressedThisFrame[keyCode] = 1;
                m_KeysReleasedThisFrame[keyCode] = 0;
                break;
            case SDL_KEYUP:
                m_CurrentState[keyCode] = 0;
                if (m_PreviousState[keyCode]) m_KeysReleasedThisFrame[keyCode] = 1;
                m_KeysPressedThisFrame[keyCode] = 0;
                break;
            default: ;
            }
            ImGui_ImplSDL2_ProcessEvent(&e);
        }
        return true;
    }
    [[nodiscard]] bool IsDownThisFrame(KeyboardInputKey key) const
    {
        try
        {
            return m_KeysPressedThisFrame[keyMappings.at(key)];
        }
        catch (const std::out_of_range& e)
        {
            std::cerr <<"Out of range error: "<<e.what()<<" KeyboardInput.cpp\n";
        }
        return false;
    }

    [[nodiscard]] bool IsUpThisFrame(KeyboardInputKey key) const
    {
        try
        {
            return m_KeysReleasedThisFrame[keyMappings.at(key)];
        }
        catch (const std::out_of_range& e)
        {
            std::cerr <<"Out of range error: "<<e.what()<<" KeyboardInput.cpp\n";
        }
        return false;
    }

    [[nodiscard]] bool IsPressed(KeyboardInputKey key) const
    {
        try
        {
            return m_CurrentState[keyMappings.at(key)];
        }
        catch (const std::out_of_range& e)
        {
            std::cerr <<"Out of range error: "<<e.what()<<" KeyboardInput.cpp\n";
        }
        return false;
    }
private:
    const std::unordered_map<KeyboardInputKey, int> keyMappings = {
        { KeyboardInputKey::A,SDL_SCANCODE_A },
        { KeyboardInputKey::B,SDL_SCANCODE_B },
        { KeyboardInputKey::C,SDL_SCANCODE_C },
        { KeyboardInputKey::D,SDL_SCANCODE_D },
        { KeyboardInputKey::E,SDL_SCANCODE_E },
        { KeyboardInputKey::F,SDL_SCANCODE_F },
        { KeyboardInputKey::G,SDL_SCANCODE_G },
        { KeyboardInputKey::H,SDL_SCANCODE_H },
        { KeyboardInputKey::I,SDL_SCANCODE_I },
        { KeyboardInputKey::J,SDL_SCANCODE_J },
        { KeyboardInputKey::K,SDL_SCANCODE_K },
        { KeyboardInputKey::L,SDL_SCANCODE_L },
        { KeyboardInputKey::M,SDL_SCANCODE_M },
        { KeyboardInputKey::N,SDL_SCANCODE_N },
        { KeyboardInputKey::O,SDL_SCANCODE_O },
        { KeyboardInputKey::P,SDL_SCANCODE_P },
        { KeyboardInputKey::Q,SDL_SCANCODE_Q },
        { KeyboardInputKey::R,SDL_SCANCODE_R },
        { KeyboardInputKey::S,SDL_SCANCODE_S },
        { KeyboardInputKey::T,SDL_SCANCODE_T },
        { KeyboardInputKey::U,SDL_SCANCODE_U },
        { KeyboardInputKey::V,SDL_SCANCODE_V },
        { KeyboardInputKey::W,SDL_SCANCODE_W },
        { KeyboardInputKey::X,SDL_SCANCODE_X },
        { KeyboardInputKey::Y,SDL_SCANCODE_Y },
        { KeyboardInputKey::SPACE,SDL_SCANCODE_SPACE },
        { KeyboardInputKey::Z,SDL_SCANCODE_Z } };
    
    std::array<Uint8, SDL_NUM_SCANCODES> m_PreviousState;
    std::array<Uint8, SDL_NUM_SCANCODES> m_CurrentState;
    std::array<Uint8, SDL_NUM_SCANCODES> m_KeysPressedThisFrame;
    std::array<Uint8, SDL_NUM_SCANCODES> m_KeysReleasedThisFrame;
};
KeyboardInput::KeyboardInput(): m_pSDLInput(std::make_unique<SDLInput>())
{}
KeyboardInput::~KeyboardInput() {}

bool KeyboardInput::ProcessKeyboardInput() const
{
    return m_pSDLInput->ProcessKeyboardInput();
}
bool KeyboardInput::IsKeyDown(KeyboardInputKey inputKey) const
{
    return m_pSDLInput->IsDownThisFrame(inputKey);
}
bool KeyboardInput::IsKeyUp(KeyboardInputKey inputKey) const
{
    return m_pSDLInput->IsUpThisFrame(inputKey);
}
bool KeyboardInput::IsKeyPressed(KeyboardInputKey inputKey) const
{
    return m_pSDLInput->IsPressed(inputKey);
}
