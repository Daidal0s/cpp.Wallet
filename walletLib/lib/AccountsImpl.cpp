#include "pch.h"
#include "Accounts.h"

class Account::impl
{
private:
	static int32_t m_accountId;
	int32_t m_currentId;
	std::string m_name = "test";
	eWallet m_wallet = eWallet::DOLLAR;
	int64_t m_value = 0;
public:
	impl(const std::string& name, eWallet wallet, int64_t value) :
		m_name(name),
		m_wallet(wallet),
		m_value(value)
	{
		m_currentId = ++m_accountId;
	}
	impl(int32_t id, const std::string& name, eWallet wallet, int64_t value) :
		m_name(name),
		m_wallet(wallet),
		m_value(value),
		m_currentId(id)
	{ }
	~impl() { }
public:
	impl(const Account& other) :
		m_name(other.pimpl->m_name),
		m_wallet(other.pimpl->m_wallet),
		m_value(other.pimpl->m_value)
	{ 
		m_currentId = ++m_accountId;
	}
public:
	void setName(std::string name) { m_name = name; }
	void setStaticId(int32_t id) { m_accountId = id; }

	std::string getName() { return m_name; }
	int32_t getAccountId() { return m_currentId; }
	eWallet getWallet() { return m_wallet; }
	int64_t getValue() { return m_value; }
public:
	void addValue(int32_t value) { m_value += value; }
	void reduceValue(int32_t value) { m_value -= value; }
};

int32_t Account::impl::m_accountId = 0;

Account::Account(const std::string& name, eWallet wallet, int64_t value) :
	pimpl(std::make_unique<impl>(name, wallet, value))
{ }
Account::Account(int32_t id, const std::string& name, eWallet wallet, int64_t value) :
	pimpl(std::make_unique<impl>(id, name, wallet, value))
{ }

Account::~Account()
{
	pimpl->~impl();
}

Account::Account(const Account& other) :
	pimpl(std::make_unique<impl>(other))
{ }
Account& Account::operator=(const Account& rhs)
{
	if (this != &rhs)
		pimpl.reset(new impl(*rhs.pimpl));
	return *this;
}
Account::Account(Account&& other) noexcept = default;
Account& Account::operator=(Account&& rhs) noexcept = default;

void Account::setName(std::string name) { pimpl->setName(name); }
void Account::setStaticId(int32_t id) { pimpl->setStaticId(id); }

std::string Account::getName() { return pimpl->getName(); }
int32_t Account::getAccountId() { return pimpl->getAccountId(); }
eWallet Account::getWallet() { return pimpl->getWallet(); }
int64_t Account::getValue() { return pimpl->getValue(); }

void Account::addValue(int32_t value) { pimpl->addValue(value); }
void Account::reduceValue(int32_t value) { pimpl->reduceValue(value); }


class AccountsList::impl
{
private:
	std::list<Account*> m_accList;
public:
	impl() { }
	~impl()	{ }
public:
	void addAccount(Account& acc)
	{
		m_accList.push_back(&acc);
	}
	void removeAccount(Account& acc)
	{
		m_accList.remove(&acc);
	}
	void printIds()
	{
		std::cout << "\n";
		for (auto c : m_accList)
		{
			std::cout << c->getAccountId() << "\t";
		}
	}
};

AccountsList::AccountsList() : 
	pimpl(std::make_unique<impl>())
{ }
AccountsList::~AccountsList() { pimpl->~impl(); }

void AccountsList::addAccount(Account& acc) { pimpl->addAccount(acc); }
void AccountsList::removeAccount(Account& acc) { pimpl->removeAccount(acc); }
void AccountsList::printIds() { pimpl->printIds(); }