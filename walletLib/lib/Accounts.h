#pragma once
#include "pch.h"
#include "EventSytem.h"

enum class Wallet : wchar_t
{
	DOLLAR = 'D',
	EURO = 'E',
	RUBLES = 'R'
};

class MYDLL_API Account : public eventSystem::Subject
{
private:
	class impl;
	std::unique_ptr<impl> pimpl;
public:
	Account(const std::string &name, Wallet wallet = Wallet::DOLLAR, int64_t value = 0);
	Account(int32_t id, const std::string& name, Wallet wallet = Wallet::DOLLAR, int64_t value = 0);
	~Account();
public:
	Account(const Account& other);
	Account& operator=(const Account& rhs);
	Account(Account&& other) noexcept;
	Account& operator=(Account&& rhs) noexcept;
public:
	void setName(std::string name);
	std::string getName();

	int32_t getAccountId();
	Wallet getWallet();
	int64_t getValue();

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
	void addAccount(Account& acc);
	void removeAccount(Account& acc);
	void printIds();
	// std::list<Account> getAccountList() const;
};
