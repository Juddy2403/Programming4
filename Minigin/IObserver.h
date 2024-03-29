#pragma once
#include "GameObject.h"

namespace GameEngine {
	class Subject;
	class IObserver
	{
	private:
		std::string m_Name{};
	public:
		virtual void Notify(GameEvent event,Subject* subject) = 0;
		//mainly to give the observer an initial state. Should prob rework this
		virtual void Notify(Subject* subject) = 0;

		IObserver() = default;
		IObserver(std::string name);
		virtual ~IObserver() = default;
		IObserver(const IObserver& other) = delete;
		IObserver(IObserver&& other) = delete;
		IObserver& operator=(const IObserver& other) = delete;
		IObserver& operator=(IObserver&& other) = delete;
	};
	//TODO: just inherit from component
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
		virtual void Notify(GameEvent event, Subject* subject) override;
		virtual void Notify(Subject* subject) override;
	};

	class ScoreObserver : public RenderableObserver
	{
	private:
	public:
		ScoreObserver(const std::string& name) : RenderableObserver(name) {}
		virtual void Notify(GameEvent event, Subject* subject) override;
		virtual void Notify(Subject* subject) override;
	};
}

