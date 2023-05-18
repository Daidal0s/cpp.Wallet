#include <iostream>
#include "Accounts.h"
#include "Bill.h"
#include "EventHandlers.h"

int main()
{
	AccountsList accList;
	Bills::BillList bl;

	Account acc("testo", eWallet::DOLLAR, 21);
	Account acc1("test1o", eWallet::DOLLAR, 22);
	Account acc2(acc1);
	Account acc3 = acc;

	Bills::Bill bill(123, Bills::eOperationType::INCREASE, Time());
	Bills::Bill bill1(1233, Bills::eOperationType::INCREASE, Time());
	Bills::Bill bill2(bill1);
	Bills::Bill bill3 = bill;

	accList.addAccount(acc);
	accList.addAccount(acc1);
	accList.addAccount(acc2);
	accList.addAccount(acc3);

	bl.addBill(bill);
	bl.addBill(bill1);
	bl.addBill(bill2);
	bl.addBill(bill3);

	Time time;
	time.setDate(12, 2, 123);
	time.setTime(19, 5, 6);

	std::cout << acc.getAccountId() << " " << acc1.getAccountId() << " " << time.stringDate();

	accList.printIds();

	accList.removeAccount(acc1);

	accList.printIds();

	std::cout << time.stringDate();
	std::cout << time.stringTime();

	bl.printBills();

	std::cin.get();
	std::cin.get();
}
