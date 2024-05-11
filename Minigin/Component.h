#pragma once
#include <string>
#include "Font.h"
#include "Texture2D.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <chrono>
#include <SDL_rect.h>
#include <SDL.h>

namespace GameEngine
{
    class GameObject;
    class Component
    {
    private:
        GameObject* m_pParent;
        bool m_IsDestroyed{ false };
    public:
        virtual void Update() {}
        virtual void Render() {}
        [[nodiscard]] GameObject* GetGameObjParent() const;
        [[nodiscard]] bool IsDestroyed() const;
        void SetDestroyedFlag();
        //virtual void Transform();

        virtual ~Component() = default;
        Component(const Component& other) = delete;
        Component(Component&& other) = delete;
        Component& operator=(const Component& other) = delete;
        Component& operator=(Component&& other) = delete;
    protected:
        explicit Component(GameObject* gameObj);
    };

    class Texture2D;
    class TextureComponent : public Component
    {
    public:
        explicit TextureComponent(GameObject* gameObj);
        explicit TextureComponent(GameObject* gameObj, const std::string& filename);
        explicit TextureComponent(GameObject* gameObj, const std::shared_ptr<Texture2D>& texture);
        //virtual void Update() override;
        virtual void Render() override;
        [[nodiscard]] Texture2D* GetTexture() const;
        void SetTexture(const std::string& filename);
        void SetTexture(const std::shared_ptr<Texture2D>& texture);

        SDL_Rect m_DestRect{};
        SDL_Rect m_SrcRect{};

        void SetFlipMode(const SDL_RendererFlip& flipMode) { m_FlipMode = flipMode; }
        void SetRotationAngle(float angle) { m_RotationAngle = angle; }
        void SetRotationCenter(const SDL_Point& center) { m_RotationCenter = center; }
    protected:
        float m_RotationAngle{};
        SDL_Point m_RotationCenter{};
        SDL_RendererFlip m_FlipMode{ SDL_FLIP_NONE };
        void InitRects();
        std::shared_ptr<Texture2D> m_Texture{};
    };

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

    struct SpriteInfo
    {
        glm::ivec2 m_StartPos{};
        int m_Width{};
        int m_Height{};
        int m_NrOfCols{};
        int m_NrOfRows{};
        int m_CurrentRow{};
        int m_CurrentCol{};
        int m_Spacing{};
        float m_TimeInterval{};

        SDL_Rect GetSrcRect()
        {
            SDL_Rect srcRect{};
            srcRect.x = m_StartPos.x + (m_Width + m_Spacing) * m_CurrentCol;
            srcRect.y = m_StartPos.y + (m_Height + m_Spacing) * m_CurrentRow;
            srcRect.w = m_Width;
            srcRect.h = m_Height;
            return srcRect;
        }
    };

    class SpriteComponent : public TextureComponent
    {
    public:
        explicit SpriteComponent(GameObject* gameObj);
        explicit SpriteComponent(GameObject* gameObj, const std::string& filename);
        explicit SpriteComponent(GameObject* gameObj, const std::shared_ptr<Texture2D>& texture);
        void UpdateSrcRect();
        virtual void Update() override;
        SpriteInfo m_SpriteInfo{};
        bool m_IsActive{true};
        float m_Scale{};
    protected:
        float m_CurrentTimeElapsed{};
    };

    class CollisionComponent final : public Component
    {
    public:
        explicit CollisionComponent(GameObject* gameObj,SDL_Rect collisionRect);
        [[nodiscard]] const SDL_Rect& GetCollisionRect() const;
        bool IsColliding(CollisionComponent* other) const;
        void CollidedWith(CollisionComponent* other) const;
        virtual void Update() override;

        virtual ~CollisionComponent() override;
        CollisionComponent(const CollisionComponent& other) = delete;
        CollisionComponent(CollisionComponent&& other) = delete;
        CollisionComponent& operator=(const CollisionComponent& other) = delete;
        CollisionComponent& operator=(CollisionComponent&& other) = delete;
    private:
        SDL_Rect m_CollisionRect{};
        glm::ivec2 m_LastPosition{};
    };

}
