#include <iostream>
#include "Account.h"
#include "Bill.h"

int main()
{
    Account acc("testo", Wallet::DOLLAR, 21);
    Account acc1("test1o", Wallet::DOLLAR, 21);

    Time time;
    time.setDate(12, 2, 123);

    std::cout << acc.getAccountId() << " " << acc1.getAccountId() << " " << time.stringDate();
    std::cin.get();
    std::cin.get();
}
