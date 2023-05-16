#pragma once
#include "pch.h"

namespace eventSystem
{
	enum class NotifyAction { Done, UnRegister };

	class Subject;
	class Event
	{
	};

	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual NotifyAction onNotify(Subject& subject, Event const& event) = 0;
	};

	class Subject
	{
	private:
		std::vector<Observer*> m_observers;
	public:
		void registerObserver(Observer& observer)
		{
			if (std::find(std::begin(m_observers), std::end(m_observers), &observer) == std::end(m_observers))					// ���? ������ ���� �������� � ���������� first, � �� last
			{
				throw std::runtime_error("registerObserver(): observer already registered");
			}
			m_observers.push_back(&observer);
		}

		void unregisterObserver(Observer& observer)																				// ������� �� �����������
		{
			m_observers.erase(std::remove(std::begin(m_observers), std::end(m_observers), &observer), std::end(m_observers));
		}

		void notifyObservers(Event const& event)																				// ����������� ����������
		{
			std::vector<Observer*> deadObservers;
			for (Observer* observer : m_observers)
			{
				if (observer->onNotify(*this, event) == NotifyAction::UnRegister)
				{
					deadObservers.push_back(observer);
				}
			}

			auto newEnd = std::end(m_observers);
			for (Observer* dead : deadObservers)
			{
				newEnd = std::remove(std::begin(m_observers), newEnd, dead);
			}
			m_observers.erase(newEnd, std::end(m_observers));
		}
	};

	class EventHandler : public Observer
	{
	private:
		std::unordered_map<std::type_index, std::function<void(Subject&, Event const&)>> m_handlers;
	public:
		NotifyAction onNotify(Subject& subject, Event const& event) override													// ��������� ��������� ����������
		{
			auto find = m_handlers.find(std::type_index(typeid(event)));
			if (find != m_handlers.end()) {
				find->second(subject, event);
			}
			return NotifyAction::Done;
		}

		template<typename T>
		void registerEventHandler(std::function<void(Subject&, Event const&)> handler)
		{
			m_handlers[std::type_index(typeid(T))] = handler;																	// ����������� ��� ������� ��� �������� ����� ������� � ������ �������, ������� ������ �� ������� � �����
		}

	};

	// ������ �������� ������������ �������

	////	class MouseMove : public Event {};
	////	class MouseClick : public Event {};

	////	class MouseHandler : public EventHandler
	////	{
	////	private:
	////		void mouseClick(Subject&, Event const&)
	////		{
	////			std::cout << "Mouse Clicked\n";
	////		}
	////	public:
	////		MouseHandler()
	////		{
	////			// Register a call to a member method
	////			registerEventHandler<MouseClick>(std::bind(&MouseHandler::mouseClick, this, std::placeholders::_1, std::placeholders::_2));		// ��������� ������� ������� �����, �������� ����� bind ������� �� ������� mouseClick,
	////																																			// ����� ������� ������� ������ �� ������� 
	////			/*MouseHandler    mouseEventHandler;
	////			mouseEventHandler.registerEventHandler<MouseMove>([](Subject&, Event const&) {std::cout << "Mouse Moved\n"; });*/				// ������
	////		}
	////	};

	////	class Mouse : public Subject
	////	{
	////	};
}