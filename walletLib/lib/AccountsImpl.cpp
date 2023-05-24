#include "pch.h"
#include "Accounts.h"
#include "Bill.h"

class Account::impl
{
private:
	Bills::BillList m_billList;

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
	impl(int32_t id, const std::string& name, eWallet wallet, int64_t value, Bills::BillList bills) :
		impl(id, name, wallet, value),
		m_billList(bills)
	{ }
	~impl() { }
public:
	impl(const Account& other) :
		m_name(other.pimpl->m_name),
		m_wallet(other.pimpl->m_wallet),
		m_value(other.pimpl->m_value),
		m_billList(other.pimpl->m_billList)
	{ 
		m_currentId = ++m_accountId;
	}
public:
	void setName(std::string name) { m_name = name; }
	void setId(int32_t id) { m_currentId = id; }
	void setStaticId(int32_t id) { m_accountId = id; }

	Bills::BillList& getBillList() { return m_billList; }
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
Account::Account(int32_t id, const std::string& name, eWallet wallet, int64_t value, Bills::BillList bills) :
	pimpl(std::make_unique<impl>(id, name, wallet, value, bills))
{ }

Account::~Account() { }

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
void Account::setId(int32_t id) { pimpl->setId(id); }

Bills::BillList& Account::getBillList() { return pimpl->getBillList(); }
std::string Account::getName() { return pimpl->getName(); }
int32_t Account::getAccountId() { return pimpl->getAccountId(); }
eWallet Account::getWallet() { return pimpl->getWallet(); }
int64_t Account::getValue() { return pimpl->getValue(); }

void Account::addValue(int32_t value) { pimpl->addValue(value); }
void Account::reduceValue(int32_t value) { pimpl->reduceValue(value); }


class AccountsList::impl
{
private:
	std::vector<std::shared_ptr<Account>> m_accList;
public:
	impl() { }
	~impl()	{ }
public:
	impl(const AccountsList& other) :
		m_accList(other.pimpl->m_accList)
	{ }
public:
	int32_t getNumberOfAccounts() const
	{
		return m_accList.size();
	}
	std::vector<std::shared_ptr<Account>> getAccountList()
	{
		return m_accList;
	}

	void addAccount(Account& acc)
	{
		m_accList.push_back(std::make_shared<Account>(acc));
		m_accList.back()->setId(m_accList.size()-1);
	}
	void removeAccount(int32_t id)
	{
		m_accList.erase(m_accList.begin() + id);
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
AccountsList::~AccountsList() { }

AccountsList::AccountsList(const AccountsList& other) { }
AccountsList& AccountsList::operator=(const AccountsList& rhs)
{
	if (this != &rhs)
		pimpl.reset(new impl(*rhs.pimpl));
	return *this;
}

std::vector<std::shared_ptr<Account>> AccountsList::getAccountList() { return pimpl.get()->getAccountList(); }
int32_t AccountsList::getNumberOfAccounts() const {	return pimpl->getNumberOfAccounts(); }

void AccountsList::addAccount(Account& acc) { pimpl->addAccount(acc); }
void AccountsList::removeAccount(int32_t id) { pimpl->removeAccount(id); }
void AccountsList::printIds() { pimpl->printIds(); }