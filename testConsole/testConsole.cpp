#include <iostream>
#include "Accounts.h"
#include "Bill.h"
#include "EventHandlers.h"

int main()
{
    AccountsList accList;
    Account acc("testo", Wallet::DOLLAR, 21);
    Account acc1("test1o", Wallet::DOLLAR, 22);
    Account acc2(acc1);

    accList.addAccount(acc);
    accList.addAccount(acc1);
    accList.addAccount(acc2);

    Time time;
    time.setDate(12, 2, 123);

    std::cout << acc.getAccountId() << " " << acc1.getAccountId() << " " << time.stringDate();

    accList.printIds();

    accList.removeAccount(acc1);

    accList.printIds();

    std::cin.get();
    std::cin.get();
}
