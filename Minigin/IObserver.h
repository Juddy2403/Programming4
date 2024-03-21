#pragma once
namespace GameEngine {
	class ISubject;
	class IObserver
	{
	private:
	public:
		virtual void Update(ISubject* subject) = 0;

		IObserver() = default;
		virtual ~IObserver() = default;
		IObserver(const IObserver& other) = delete;
		IObserver(IObserver&& other) = delete;
		IObserver& operator=(const IObserver& other) = delete;
		IObserver& operator=(IObserver&& other) = delete;
	};

	class EventSystem : public IObserver
	{
	private:
		bool m_HasDied{ false };
	public:
		virtual void Update(ISubject* subject) override; // subject -> getState

	};
}

