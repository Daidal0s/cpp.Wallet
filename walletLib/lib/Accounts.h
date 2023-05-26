#pragma once
#include "pch.h"
#include "EventSytem.h"
#include "Bill.h"

enum class eWallet : wchar_t
{
	DOLLAR = 'D',
	EURO = 'E',
	RUBLES = 'R'
};


static eWallet findEWalletFromChar(int32_t num)
{
	char32_t ch = static_cast<char32_t>(num);

	switch (ch)
	{
	default:
		return eWallet::DOLLAR;
	case 'D':
		return eWallet::DOLLAR;
	case 'E':
		return eWallet::EURO;
	case 'R':
		return eWallet::RUBLES;
	}
}

static eWallet findEWallet(int32_t index)
{
	switch (index)
	{
	default:
		return eWallet::DOLLAR;
	case 0:
		return eWallet::DOLLAR;
	case 1:
		return eWallet::EURO;
	case 2:
		return eWallet::RUBLES;
	}
}

static std::string eWalletToString(eWallet wallet)
{
	switch (wallet)
	{
	default:
		return "Dollar";
	case eWallet::DOLLAR:
		return "Dollar";
	case eWallet::EURO:
		return "Euro";
	case eWallet::RUBLES:
		return "Rubles";
	}
}


class MYDLL_API Account : public eventSystem::Subject
{
private:
	class impl;
	std::unique_ptr<impl> pimpl;
public:
	Account(const std::string &name, eWallet wallet = eWallet::DOLLAR, int64_t value = 0);
	Account(int32_t id, const std::string& name, eWallet wallet = eWallet::DOLLAR, int64_t value = 0);			// TODO: Решить проблему 2-х конструкторов
	//Account(int32_t id, const std::string& name, eWallet wallet = eWallet::DOLLAR, int64_t value = 0, Bills::BillList bills);
	~Account();
public:
	Account(const Account& other);
	Account& operator=(const Account& rhs);
	Account(Account&& other) noexcept;
	Account& operator=(Account&& rhs) noexcept;
public:
	void setName(const std::string& name);
	void setStaticId(int32_t id);
	void setId(int32_t id);

	Bills::BillList &getBillList();
	std::string getName();
	int32_t getAccountId();
	eWallet getWallet();
	int64_t getValue();
public:
	void addValue(int32_t value);
	void reduceValue(int32_t value);
};

class MYDLL_API AccountsList
{
private:
	class impl;
	std::unique_ptr<impl> pimpl;
public:
	AccountsList();
	~AccountsList();
public:
	AccountsList(const AccountsList& other);
	AccountsList& operator=(const AccountsList& rhs);
	AccountsList(AccountsList&& other) noexcept = default;
	AccountsList& operator=(AccountsList&& rhs) noexcept = default;
public:
	std::vector<std::shared_ptr<Account>> getAccountList();
	int32_t getNumberOfAccounts() const;

	void addAccount(const Account& acc);
	void removeAccount(int32_t id);
	void printIds();
};
