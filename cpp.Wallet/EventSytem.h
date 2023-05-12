#pragma once
#include "pch.h"

namespace eventSystem
{
	class MYDLL_API Subscriber
	{
		friend class Publisher;
	private:
		class impl;
		std::unique_ptr<impl> pimpl;
	public:
		Subscriber(Publisher &pub);
		~Subscriber();
	public:
		Subscriber(const Subscriber& other);
		Subscriber& operator=(const Subscriber& rhs);
		Subscriber(Subscriber&& other) noexcept;
		Subscriber& operator=(Subscriber&& rhs) noexcept;
	public:
		void update(const std::string& messageByPub);
		int32_t getId() const;
	};

	class MYDLL_API Publisher
	{
		friend class Subscriber;
	private:
		class impl;
		std::unique_ptr<impl> pimpl;
	public:
		Publisher(const std::string& name);
		~Publisher();
	public:
		Publisher(const Publisher& other);
		Publisher& operator=(const Publisher& rhs);
		Publisher(Publisher&& other) noexcept;
		Publisher& operator=(Publisher&& rhs) noexcept;
	public:
		void addSub(Subscriber *sub);
		void removeSub(Subscriber *sub);
		void updateState(const std::string &str);
		void notify();
	};

}