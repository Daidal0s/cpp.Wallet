#include <iostream>
#include "Accounts.h"
#include "Bill.h"
#include "EventHandlers.h"
#include <fstream>
#include <nlohmann/json.hpp>

void createJsonFile(Account& acc, nlohmann::json j)
{
	nlohmann::json bills;
	j = {
		{"Account",
			{
				{"AccountID", acc.getAccountId()},
				{"AccountName", acc.getName()},
				{"AccountWallet", acc.getWallet()},
				{"AccountValue", acc.getValue()}
			}
		}
	};
	bills =
	{
		{"BillsList",
		{

		}
		}
	};
	for (auto c : *acc.getBillList().getList())
	{
	}
}


int main()
{
	using json = nlohmann::json;
	json jim;

	AccountsList accList;
	Bills::BillList bl;

	Bills::Bill bill(123, Bills::eOperationType::INCREASE, Time());
	Bills::Bill bill1(1233, Bills::eOperationType::INCREASE, Time());
	Bills::Bill bill2(bill1);
	Bills::Bill bill3 = bill;

	Account acc("testo", eWallet::EURO, 21);

	acc.getBillList().addBill(bill);
	acc.getBillList().addBill(bill1);
	acc.getBillList().addBill(bill2);
	acc.getBillList().addBill(bill3);

	Account acc1("test1o", eWallet::DOLLAR, 22);
	acc1.getBillList().addBill(bill);
	acc1.getBillList().addBill(bill1);

	Account acc2(acc1);
	Account acc3 = acc;


	accList.addAccount(acc);

	Time time;
	time.setDate(12, 2, 123);
	time.setTime(19, 5, 6);

	std::cout << acc.getAccountId() << " " << acc1.getAccountId() << " " << time.stringDate();

	accList.printIds();

	accList.removeAccount(acc1);

	accList.printIds();

	std::cout << time.stringDate();
	std::cout << time.stringTime();

	acc.getBillList().printBills();
	acc1.getBillList().printBills();

	createJsonFile(acc, jim);

	std::cin.get();
	std::cin.get();
}
