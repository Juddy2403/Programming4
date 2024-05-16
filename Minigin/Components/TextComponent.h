#pragma once
#include <memory>
#include <string>

#include "Component.h"

namespace GameEngine
{
    class Font;
    class TextComponent final : public Component
    {
    public:
        explicit TextComponent(GameObject* gameObj, std::shared_ptr<Font> font = nullptr, const std::string& text = {});

        void SetText(const std::string& text);
        void SetFont(const std::shared_ptr<Font>& font);
        virtual void Update() override;
    private:
        std::string m_Text{};
        std::shared_ptr<Font> m_Font{};
        bool m_NeedsUpdate{ true };
    };
}
