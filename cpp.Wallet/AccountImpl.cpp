#include "pch.h"
#include "Account.h"

class Account::impl 
{
private:
	static int32_t m_accountId;
	int32_t m_currentId;
	std::string m_name = "test";
	Wallet m_wallet = Wallet::DOLLAR;
	int64_t m_value = 0;
public:
	impl(const std::string &name, Wallet wallet, int64_t value) :
		m_name(name), m_wallet(wallet), m_value(value)
	{
		m_currentId = ++m_accountId;
	}
	~impl()	{ }
public:
	void setName(std::string name) { m_name = name; }
	std::string getName() { return m_name; }

	int32_t getAccountId() { return m_currentId; }
	Wallet getWallet() { return m_wallet; }
	int64_t getValue() { return m_value; }

	void addValue(int32_t value) { m_value += value; }
	void reduceValue(int32_t value) { m_value -= value; }
};

int32_t Account::impl::m_accountId = 0;

Account::Account(const std::string &name, Wallet wallet, int64_t value) :
	pimpl(std::make_unique<impl>(name, wallet, value))
{ }

Account::~Account() {  }

void Account::setName(std::string name) { pimpl->setName(name); }
std::string Account::getName() { return pimpl->getName(); }

int32_t Account::getAccountId() { return pimpl->getAccountId(); }
Wallet Account::getWallet() { return pimpl->getWallet(); }
int64_t Account::getValue() { return pimpl->getValue(); }

void Account::addValue(int32_t value) { pimpl->addValue(value); }
void Account::reduceValue(int32_t value) { pimpl->reduceValue(value); }
