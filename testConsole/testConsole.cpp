#include <iostream>
#include "Accounts.h"
#include "Bill.h"
#include "EventHandlers.h"
#include "IO.h"

int main()
{
	using json = nlohmann::json;
	json jim;

	AccountsList accList;
	AccountsList accList1;

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
	accList.addAccount(acc1);
	accList.addAccount(acc2);

	Time time;
	time.setDate(12, 2, 123);
	time.setTime(19, 5, 6);

	std::cout << acc.getAccountId() << " " << acc1.getAccountId() << " " << time.stringDate();

	int a = accList.getAccountList().size();
	
	accList.printIds();

	IO::saveAccounts(accList);

	accList.removeAccount(accList.getAccountList().back()->getAccountId());

	std::cout << time.stringDate();
	std::cout << time.stringTime();

	acc.getBillList().printBills();
	acc1.getBillList().printBills();

	IO::loadAccounts(accList1);

	accList1.printIds();

	std::cin.get();
	std::cin.get();
}
