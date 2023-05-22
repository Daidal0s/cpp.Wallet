#pragma once
#include "pch.h"
#include "Accounts.h"


// void saveAccounts(std::span<Account*>);

namespace IO
{
	using json = nlohmann::json;

	eWallet findTypeOfWallet(int32_t num)
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

	Bills::eOperationType findTypeOfOperation(int32_t num)
	{
		switch (num)
		{
		default:
			return Bills::eOperationType::DECREASE;
		case 0:
			return Bills::eOperationType::INCREASE;
		case 1:
			return Bills::eOperationType::DECREASE;
		}
	}

	void saveAccounts(AccountsList& acc)
	{
		json j;
		int32_t y(0), mon(0), d(0), h(0), mins(0), s(0);

		j += { {"NumberOfAccounts", acc.getNumberOfAccounts() }};

		for (int32_t iii = 0; iii < acc.getAccountList().size(); iii++)
		{
			j +=
			{
				{
					"Account",
					{
						{"ID", acc.getAccountList().at(iii)->getAccountId()},
						{"Name", acc.getAccountList().at(iii)->getName()},
						{"Wallet", acc.getAccountList().at(iii)->getWallet()},
						{"Value", acc.getAccountList().at(iii)->getValue()},
						{"NumberOfBills", acc.getAccountList().at(iii)->getBillList().getNumberOfBills() },
						{"Bills", json::array()}
					}
				}
			};

			for (int32_t jjj = 0; jjj < acc.getAccountList().at(iii)->getBillList().getList().capacity(); jjj++)
			{
				acc.getAccountList().at(iii)->getBillList().getList().at(jjj)->getOperationTime().getDate(&d, &mon, &y);
				acc.getAccountList().at(iii)->getBillList().getList().at(jjj)->getOperationTime().getTime(&h, &mins, &s);

				j[iii+1]["Account"]["Bills"] += 
					{
						{
							"Bill",
							{
								{"ID", acc.getAccountList().at(iii)->getBillList().getList().at(jjj)->getCurrentId()},
								{"OperationType", acc.getAccountList().at(iii)->getBillList().getList().at(jjj)->getOperationType()},
								{"Value", acc.getAccountList().at(iii)->getBillList().getList().at(jjj)->getValue()},
								{"Date",
									{
										{"Day",d},
										{"Month",mon},
										{"Year",y}
									}
								},
								{"Time",
									{
										{"Hours",h},
										{"Minutes",mins},
										{"Seconds",s}
									}
								}
							}
						}
					};
			}
		}

		std::ofstream("Accounts.json") << std::setw(4) << j;
	}


	static void loadAccounts(AccountsList& acc)
	{
		json j, inp;
		std::ifstream input("Accounts.json");
		j = inp.parse(input);
		input.close();

		AccountsList accList;

		int32_t numberOfAccounts = j[0]["NumberOfAccounts"];

		int32_t accId = 0;
		std::string name = "";
		eWallet wallet = eWallet::DOLLAR;
		int64_t accValue = 0;

		int32_t billId = 0;
		Bills::eOperationType opType = Bills::eOperationType::DECREASE;
		int32_t billValue = 0;
		Time operationTime;

		int32_t y(0), mon(0), d(0), h(0), mins(0), s(0);

		for (int32_t iii = 0; iii < numberOfAccounts; ++iii)
		{

			accId = j[iii+1]["Account"]["ID"];
			name = j[iii+1]["Account"]["Name"];
			accValue = j[iii+1]["Account"]["Value"];
			wallet = findTypeOfWallet(j[iii+1]["Account"]["Wallet"]);

			Account tempAccount(accId, name, wallet, accValue);
			int32_t numOfBills = j[iii + 1]["Account"]["NumberOfBills"];

			for (int32_t jjj = 0; jjj < numOfBills; ++jjj)
			{
				billId = j[iii + 1]["Account"]["Bills"][jjj]["Bill"]["ID"];
				opType = findTypeOfOperation(j[iii + 1]["Account"]["Bills"][jjj]["Bill"]["OperationType"]);
				billValue = j[iii + 1]["Account"]["Bills"][jjj]["Bill"]["Value"];

				d = j[iii + 1]["Account"]["Bills"][jjj]["Bill"]["Date"]["Day"];
				mon = j[iii + 1]["Account"]["Bills"][jjj]["Bill"]["Date"]["Month"];
				y = j[iii + 1]["Account"]["Bills"][jjj]["Bill"]["Date"]["Year"];
				
				h = j[iii + 1]["Account"]["Bills"][jjj]["Bill"]["Time"]["Hours"];
				mins = j[iii + 1]["Account"]["Bills"][jjj]["Bill"]["Time"]["Minutes"];
				s = j[iii + 1]["Account"]["Bills"][jjj]["Bill"]["Time"]["Seconds"];

				Time tempTime;
				tempTime.setDate(d, mon, y);
				tempTime.setTime(h, mins, s);

				Bills::Bill tempBill(Bills::Bill(billId, billValue, opType, tempTime));

				tempAccount.getBillList().addBill(tempBill);
			}
			
			accList.addAccount(tempAccount);
		}

		acc = accList;																// TODO: ядекюрэ онкмнжеммн RULE OF FIVE бегдее!!!!!
	}
}
