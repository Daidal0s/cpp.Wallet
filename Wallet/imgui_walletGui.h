#include "stdafx.h"
#pragma once

namespace ImGui
{
	static eWallet indexToEWallet(int32_t index)
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

	static Bills::eOperationType indexToEOperationType(int32_t index)
	{
		switch (index)
		{
		default:
			return Bills::eOperationType::DECREASE;
		case 0:
			return Bills::eOperationType::INCREASE;
		case 1:
			return Bills::eOperationType::DECREASE;
		}
	}

	struct AccountWindows
	{
	public:
		bool show_addBillMenu = true;
		bool show_billsList = true;
	};

	void addBill(Bills::BillList& bills, bool* p_open, std::string& name)
	{
		std::string windowName = "Add Bill to " + name;

		const char* operations[] = {"Increase","Decrease"};
		static int32_t index = 0;

		static int32_t value = 0;
		static int32_t id = 0;
		static int32_t d, mon, y, h, mins, s;
		d = mon = y = h = mins = s = 0;
		static Bills::eOperationType operationType = Bills::eOperationType::DECREASE;
		
		{
			ImGui::Begin(windowName.c_str(), p_open);

			ImGui::InputInt("Value", &value);

			ImGui::InputInt("Day", &d);
			ImGui::InputInt("Month", &mon);
			ImGui::InputInt("Year", &y);

			ImGui::InputInt("Hours", &h);
			ImGui::InputInt("Minutes", &mins);
			ImGui::InputInt("Seconds", &s);

			ImGui::Combo("Operation Type", &index, operations, IM_ARRAYSIZE(operations));

			
			if (ImGui::Button("Add Bill"))
			{
				Time tempTime;
				tempTime.setDate(d, mon, y);
				tempTime.setTime(h, mins, s);
				Bills::Bill tempBill(value, indexToEOperationType(index), tempTime);
				bills.addBill(tempBill);
			}

			ImGui::End();
		}
	}

	void CreateAccount(AccountsList& accList, bool* winOpen)
	{
		static int32_t value = 0;
		static int32_t i = 0;
		static std::string name = "Account Name 1";
		const char* typeOfWallet[] = { "Dollar","Euro","Rubles" };

		if (winOpen)
		{
			ImGui::Begin("Create new account", winOpen);
			ImGui::InputText("Name of Account", &name);
			ImGui::Combo("Type of Wallet", &i, typeOfWallet, IM_ARRAYSIZE(typeOfWallet));
			ImGui::InputInt("Value", &value);

			if (ImGui::Button("Create Account"))
			{
				Account acc(name, ImGui::indexToEWallet(i), value);
				accList.addAccount(acc);										// TODO: Превратить в лямбду; перегрузить, чтобы принимал анонимные члены (Account)
				// IO::saveAccounts(accountList);
			}

			ImGui::End();
		}
	}

	void AccountGenerator(AccountsList& accList, int32_t index, bool* showAccounts)
	{

		std::string name = accList.getAccountList().at(index)->getName();
		eWallet walletType = accList.getAccountList().at(index)->getWallet();
		int32_t value = accList.getAccountList().at(index)->getValue();
		int32_t id = accList.getAccountList().at(index)->getAccountId();
		Bills::BillList& billList = accList.getAccountList().at(index)->getBillList();

		{
			AccountWindows accWins;

			// ImGui::SetNextItemOpen(showAccounts, ImGuiCond_None);

			ImGui::Begin(name.c_str(), showAccounts, ImGuiWindowFlags_MenuBar);

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Bills"))
				{
					if (ImGui::MenuItem("Add Bill", NULL, &accWins.show_addBillMenu)) {}
					if (ImGui::MenuItem("Show Bills", NULL, &accWins.show_billsList)) {}
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			ImGui::Text("Wallet Type: "); ImGui::SameLine();
			ImGui::Text(eWalletToString(walletType).c_str());
			ImGui::Text("Value: %d", value);

			if (accWins.show_addBillMenu)
				addBill(billList, &accWins.show_addBillMenu, name);

			ImGui::End();
		}
	}
}