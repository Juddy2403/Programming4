#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "Scene.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>("Background");
	go->AddComponent<TextureComponent>();
	go->GetComponent<TextureComponent>()->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>("Logo");
	go->AddComponent<TextureComponent>();
	go->GetComponent<TextureComponent>()->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto to = std::make_shared<dae::GameObject>("Title");
	to->AddComponent<TextComponent>();
	to->GetComponent<TextComponent>()->SetText("Programming 4 Assignment");
	to->GetComponent<TextComponent>()->SetFont(font);
	to->SetPosition(80, 20);
	scene.Add(to);

	to = std::make_shared<dae::GameObject>("FPSCounter");
	to->AddComponent<TextComponent>();
	to->GetComponent<TextComponent>()->SetText("160");
	to->GetComponent<TextComponent>()->SetFont(font);
	to->SetPosition(20, 80);
	scene.Add(to);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}