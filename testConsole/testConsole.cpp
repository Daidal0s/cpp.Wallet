#include <iostream>
#include "Account.h"

int main()
{
    Account acc("testo", Wallet::DOLLAR, 21);
    Account acc1("test1o", Wallet::DOLLAR, 21);

    std::cout << acc.getAccountId() << " " << acc1.getAccountId();
    std::cin.get();
    std::cin.get();
}
