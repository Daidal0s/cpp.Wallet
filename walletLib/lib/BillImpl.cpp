#include "pch.h"
#include "Bill.h"

class Time::impl
{
private:
	stTime m_time = zeroTime;
public:
	impl() { }
	impl(const Time& other) :
		m_time(other.pimpl->m_time)
	{ }
	~impl() { }
public:

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

Time::Time(const Time& other) :
	pimpl(std::make_unique<impl>(other))
{ }
Time& Time::operator=(const Time& rhs)
{
	if (this != &rhs)
		pimpl.reset(new impl(*rhs.pimpl));
	return *this;
}

void Time::setTime(int hours, int minutes, int seconds) { pimpl->setTime(hours, minutes, seconds); }
void Time::setDate(int day, int month, int year) { pimpl->setDate(day, month, year); }
void Time::getTime(int* hours, int* minutes, int* seconds) const { pimpl->getTime(hours, minutes, seconds); }
void Time::getDate(int* day, int* month, int* year) const { pimpl->getDate(day, month, year); }
std::string Time::stringDate() const { return pimpl->stringDate(); }
std::string Time::stringTime() const { return pimpl->stringTime(); }


/////////////////////////////////////////////////////////////////////////////////////////////////////////


class Bills::Bill::impl
{
private:
	int32_t m_value = 0;
	eOperationType m_opType = eOperationType::DECREASE;
	static int32_t m_billId;
	int32_t m_currentId;
	Time m_operationTime;
public:
	impl(int32_t value, eOperationType opType, const Time& operationTime) :
		m_value(value),
		m_opType(opType),
		m_operationTime(operationTime),
		m_currentId(++m_billId)
	{ }
	impl(int32_t currentId, int32_t value, eOperationType opType, const Time& operationTime) :
		m_value(value),
		m_opType(opType),
		m_currentId(currentId),
		m_operationTime(operationTime)
	{ }
	~impl() { }
public:
	impl(const Bill& other) :
		m_value(other.pimpl->m_value),
		m_opType(other.pimpl->m_opType),
		m_currentId(++m_billId),
		m_operationTime(other.pimpl->m_operationTime)
	{ }
public:
	void setBillStaticId(int32_t lastId) { m_billId = lastId; }
	void setValue(int32_t value) { m_value = value; }
	void setOpType(eOperationType type) { m_opType = type; }
	void setCurrentId(int32_t id) { m_currentId = id; }
	void setOperationTime(Time time) { m_operationTime = time; }

	int32_t	getValue() { return m_value; }
	eOperationType getOperationType() { return m_opType; }
	int32_t getCurrentId() { return m_currentId; }
	Time& getOperationTime() { return m_operationTime; }
};

int32_t Bills::Bill::impl::m_billId = 0;

Bills::Bill::Bill(int32_t value, eOperationType opType, const Time& operationTime) :
	pimpl(std::make_unique<impl>(value, opType, operationTime))
{ }
Bills::Bill::Bill(int32_t currentId, int32_t value, eOperationType opType, const Time& operationTime) :
	pimpl(std::make_unique<impl>(currentId, value, opType, operationTime))
{ }

Bills::Bill::~Bill() { pimpl->~impl(); }

Bills::Bill::Bill(const Bill& other) :
	pimpl(std::make_unique<impl>(other))
{ }
Bills::Bill& Bills::Bill::operator=(const Bill& rhs)
{
	if (this != &rhs)
		pimpl.reset(new impl(*rhs.pimpl));
	return *this;
}

void Bills::Bill::setBillStaticId(int32_t lastId) { pimpl->setBillStaticId(lastId); }
void Bills::Bill::setValue(int32_t value) { pimpl->setValue(value); }
void Bills::Bill::setOpType(eOperationType type) { pimpl->setOpType(type); }
void Bills::Bill::setCurrentId(int32_t id) { pimpl->setCurrentId(id); }
void Bills::Bill::setOperationTime(Time time) { pimpl->setOperationTime(time); }

int32_t Bills::Bill::getValue() { return pimpl->getValue(); }
Bills::eOperationType Bills::Bill::getOperationType() { return pimpl->getOperationType(); }
int32_t Bills::Bill::getCurrentId() { return pimpl->getCurrentId(); }
Time& Bills::Bill::getOperationTime() { return pimpl->getOperationTime(); }


/////////////////////////////////////////////////////////////////////////////////////////////////


class Bills::BillList::impl
{
private:
	std::list<Bill*> m_billList;
public:
	impl() { }
	~impl() { }
public:
	impl(const BillList& other) :
		m_billList(other.pimpl->m_billList)
	{ }
public:
	void addBill(Bill& bill)
	{
		m_billList.push_back(&bill);
	}
	void removeBill(Bill& bill)
	{
		m_billList.remove(&bill);
	}
	void printBills()
	{
		std::cout << "\n";
		for (auto c : m_billList)
		{
			std::cout << "id: " << c->getCurrentId() << "\n"
				<< "Operation Type: " << (c->getOperationType() == eOperationType::DECREASE ? "Decrease" : "Increase") << "\n"
				<< "Value: " << c->getValue() << "\n"
				<< "asdas" << c->getOperationTime().stringDate() << "\t" << c->getOperationTime().stringTime() << "\n";
		}
	}
	std::list<Bill*>* getList() { return &m_billList; }
};

Bills::BillList::BillList() :
	pimpl(std::make_unique<impl>())
{ }
Bills::BillList::~BillList() { pimpl->~impl(); }

Bills::BillList::BillList(const BillList& other) :
	pimpl(std::make_unique<impl>(other))
{ }
Bills::BillList& Bills::BillList::operator=(const BillList& rhs)
{
	if (this != &rhs)
		pimpl.reset(new impl(*rhs.pimpl));
	return *this;
}

void Bills::BillList::addBill(Bill& bill) { pimpl->addBill(bill); }
void Bills::BillList::removeBill(Bill& bill) { pimpl->removeBill(bill); }
void Bills::BillList::printBills() { pimpl->printBills(); }
std::list<Bills::Bill*>* Bills::BillList::getList() { return pimpl->getList(); }