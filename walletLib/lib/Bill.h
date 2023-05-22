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

const stTime zeroTime{
	static_cast<std::chrono::years>(0),
	static_cast<std::chrono::months>(0),
	static_cast<std::chrono::days>(0),
	static_cast<std::chrono::hours>(0),
	static_cast<std::chrono::minutes>(0),
	static_cast<std::chrono::seconds>(0)
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
	Time(const Time& other);
	Time& operator=(const Time& rhs);
	Time(Time&& other) noexcept = default;
	Time& operator=(Time&& rhs) noexcept = default;
public:
	void setTime(int hours, int minutes, int seconds);
	void setDate(int day, int month, int year);
	void getTime(int* hours, int* minutes, int* seconds) const;
	void getDate(int* day, int* month, int* year) const;
	std::string stringDate() const;
	std::string stringTime() const;
};

namespace Bills
{
	enum class eOperationType : int8_t
	{
		INCREASE = 0,
		DECREASE
	};

	class MYDLL_API Bill : public eventSystem::Subject
	{
	private:
		class impl;
		std::unique_ptr<impl> pimpl;
	public:
		Bill(int32_t value, eOperationType opType, const Time& operationTime);
		Bill(int32_t currentId, int32_t value, eOperationType opType, const Time& operationTime);
		~Bill();
	public:
		Bill(const Bill& other);
		Bill& operator=(const Bill& rhs);
		Bill(Bill&& other) noexcept = default;
		Bill& operator=(Bill&& rhs) noexcept = default;
	public:
		void setBillStaticId(int32_t lastId);
		void setValue(int32_t value);
		void setOpType(eOperationType type);
		void setCurrentId(int32_t id);
		void setOperationTime(Time time);

		int32_t	getValue();
		eOperationType getOperationType();
		int32_t getCurrentId();
		Time& getOperationTime();
	};

	class MYDLL_API BillList : public eventSystem::Subject
	{
	private:
		class impl;
		std::unique_ptr<impl> pimpl;
	public:
		BillList();
		~BillList();
	public:
		BillList(const BillList& other);
		BillList& operator=(const BillList& rhs);
		BillList(BillList&& other) noexcept = default;
		BillList& operator=(BillList&& rhs) noexcept = default;
	public:
		std::vector<std::shared_ptr<Bill>> getList();
		int32_t getNumberOfBills() const;

		void addBill(Bill& bill);
		void removeBill(int32_t id);
		void printBills();
	};
}