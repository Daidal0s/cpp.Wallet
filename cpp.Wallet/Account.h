#pragma once
#include "pch.h"

enum class Wallet : wchar_t
{
	DOLLAR = 'D',
	EURO = 'E',
	RUBLES = 'R'
};

class MYDLL_API Account
{
private:
	class impl;
	std::unique_ptr<impl> pimpl;
public:
	Account(std::string name = "test", Wallet wallet = Wallet::DOLLAR, int64_t value = 0);
	~Account();
public:
	void setName(std::string name);
	std::string getName();

	int32_t getAccountId();
	Wallet getWallet();
	int64_t getValue();

	void addValue(int32_t value);
	void reduceValue(int32_t value);
};

