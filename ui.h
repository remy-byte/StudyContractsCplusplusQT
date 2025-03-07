#pragma once
#include "contract_service.h"
#include "repository_contract.h"
#include "validator.h"
#include "contract.h"

class ConsoleUI {
private:

	ContractList& ctr;

	void add_contract_ui();

	void print_all_contracts(const vector<Contract>& contrat_list);

	void delete_contract_ui();

	void add_to_shoppingcart_ui();

	void modify_contract_ui();

	void export_to_file();

public:

	ConsoleUI(ContractList& ctr)noexcept : ctr{ ctr } {}

	void do_undo();


	void start();
};
