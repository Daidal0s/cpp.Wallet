#include "pch.h"
#include "Bill.h"

class Time::impl
{
private:
	stTime m_time;
public:
	impl() { }
	~impl() { }
public:
	void setTime(int hours, int minutes, int seconds) 
	{ 
		m_time.H = hours < 24 && hours > 0 ? static_cast<std::chrono::hours>(hours) : static_cast <std::chrono::hours>(0);
		m_time.Min = minutes < 60 && minutes > 0 ? static_cast<std::chrono::minutes>(minutes) : static_cast <std::chrono::minutes>(0);
		m_time.S = seconds < 60 && seconds > 0 ? static_cast<std::chrono::seconds>(seconds) : static_cast <std::chrono::seconds>(0);
	}
	void setDate(int day, int month, int year) 
	{ 
		m_time.D = day <= 31 && day >= 1 ? static_cast<std::chrono::days>(day) : static_cast<std::chrono::days>(0);
		m_time.Mon = month <= 12 && day >= 1 ? static_cast<std::chrono::months>(month) : static_cast<std::chrono::months>(0);
		m_time.Y = year <= 32760 && day >= 1 ? static_cast<std::chrono::years>(year) : static_cast<std::chrono::years>(0);
	}
	void getTime(int* hours, int* minutes, int* seconds) const 
	{  
		*hours = m_time.H.count();
		*minutes = m_time.Min.count();
		*seconds = m_time.S.count();
	}
	void getDate(int* day, int* month, int* year) const 
	{  
		*day = m_time.D.count();
		*month = m_time.Mon.count();
		*year = m_time.Y.count();
	}
	std::string stringDate() const 
	{
		std::string str = std::to_string(m_time.D.count()) + "." + std::to_string(m_time.Mon.count()) + "." + std::to_string(m_time.Y.count());
		return str;
	}
	std::string stringTime() const 
	{ 
		std::string str = std::to_string(m_time.H.count()) + ":" + std::to_string(m_time.Min.count()) + ":" + std::to_string(m_time.S.count());
		return str;
	}
};

Time::Time() :
	pimpl(std::make_unique<impl>())
{ }
Time::~Time() { }

void Time::setTime(int hours, int minutes, int seconds) { pimpl->setTime(hours, minutes, seconds); }
void Time::setDate(int day, int month, int year) { pimpl->setDate(day, month, year); }
void Time::getTime(int* hours, int* minutes, int* seconds) const { pimpl->getTime(hours, minutes, seconds); }
void Time::getDate(int* day, int* month, int* year) const { pimpl->getDate(day, month, year); }
std::string Time::stringDate() const { return pimpl->stringDate(); }
std::string Time::stringTime() const { return pimpl->stringTime(); }




class Bills::Bill::impl
{
private:
	
public:

public:
};

class Bills::BillList::impl
{
private:
	int32_t m_walletId;
	std::list<Bill*> m_billList;
public:
public:
};