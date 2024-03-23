#pragma once
#include "GameObject.h"

namespace GameEngine {
	class ISubject;
	class IObserver
	{
	private:
		std::string m_Name{};
	public:
		virtual void Update(ISubject* subject) = 0;

		IObserver() = default;
		IObserver(const std::string& name);
		virtual ~IObserver() = default;
		IObserver(const IObserver& other) = delete;
		IObserver(IObserver&& other) = delete;
		IObserver& operator=(const IObserver& other) = delete;
		IObserver& operator=(IObserver&& other) = delete;
	};

	class RenderableObserver : public IObserver, public GameObject
	{
	public:
		RenderableObserver(const std::string& name) : IObserver(name) {}
	};

	class HealthObserver : public RenderableObserver
	{
	private:
	public:
		HealthObserver(const std::string& name) : RenderableObserver(name) {}
		virtual void Update(ISubject* subject) override; 
	};

	class ScoreObserver : public RenderableObserver
	{
	private:
	public:
		ScoreObserver(const std::string& name) : RenderableObserver(name) {}
		virtual void Update(ISubject* subject) override; 
	};
}

