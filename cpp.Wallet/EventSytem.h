#pragma once
#include "pch.h"

namespace eventSystem
{
	class Publisher
	{
	private:
		class impl;
		std::unique_ptr<impl> pimpl;
	public:

	};

	class MYDLL_API Subscriber : public ISubscriber
	{
	private:
		class impl;
		std::unique_ptr<impl> pimpl;
	public:
		void update(/**/);
	};

	class MYDLL_API Publisher
	{
	private:
		class impl;
		std::unique_ptr<impl> pimpl;
	public:

	};

}