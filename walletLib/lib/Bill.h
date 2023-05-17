#pragma once
#include "pch.h"
#include "EventSytem.h"

struct stTime
{
	std::chrono::years Y;
	std::chrono::months Mon;
	std::chrono::days D;
	std::chrono::hours H;
	std::chrono::minutes Min;
	std::chrono::seconds S;
};

class MYDLL_API Time
{
private:
	class impl;
	std::unique_ptr<impl> pimpl;
public:
	Time();
	~Time();
public:
	void setTime(int hours, int minutes, int seconds);
	void setDate(int day, int month, int year);
	void getTime(int *hours, int *minutes, int *seconds) const;
	void getDate(int *day, int *month, int *year) const;
	std::string stringDate() const;
	std::string stringTime() const;
};

namespace Bills
{
	enum class eOperationType : int8_t
	{
		INREASE = 0,
		DECREASE
	};

	class MYDLL_API Bill : public eventSystem::Subject
	{
	private:
		class impl;
		std::unique_ptr<impl> pimpl;
	public:
		// Bill();
		Bill();
		~Bill();
	public:
		Bill(const Bill& other);
		Bill& operator=(const Bill& rhs);
		Bill(Bill&& other) noexcept;
		Bill& operator=(Bill&& rhs) noexcept;
	public:
		std::string billString();
		void setBillId(int32_t lastId);
	};

	class MYDLL_API BillList
	{
	private:
		class impl;
		std::unique_ptr<impl> pimpl;
	public:
		BillList(int32_t walletId);
		~BillList();
	public:
		void addBill(Bill& bill);
		void removeBill(Bill& bill);
		std::list<Bill> getBillList() const;
	};
}
