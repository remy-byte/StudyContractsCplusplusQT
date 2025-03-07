#include "testing.h"
#include "ui.h"
#include "contract.h"
#include "repository_contract.h"
#include "contract_service.h"
#include "validator.h"
#include <iostream>
#include "GUI.h"
#include "Observer.h"
#include <ui_Study_contracts_GUI.h>
#include "Test.h"



void clear_file()
{
	ofstream f("FILE_CONTRACTS.TXT", ios::trunc);
	f.close();
}

void run()
{

	run_all_tests();
	//RepositoryContractFile rpf{ "FILE_CONTRACTS.TXT" };
	RepoContractStake rcs;
	RepositoryContract contract;
	Validate validate;
	StudyContracts study_contract;
	ContractList list{ contract, validate, study_contract };
	ConsoleUI ui{ list };
	ui.start();
}

using namespace std;

int main(int argc, char* argv[]) {
	run_all_tests();
	ruleaza_teste();
	QApplication a(argc, argv);
	RepositoryContract contract;
	Validate validate;
	RepositoryContractFile rpf{ "FILE_CONTRACTS.TXT" };
	StudyContracts study_contract;
	ContractList list{ rpf, validate, study_contract };
	vector<Contract> contracts = list.get_All();
	ContractList listr{ rpf, validate, study_contract };
	ShoppingGUI shop{ listr };
	GUI g{ list , shop};
	QApplication::setFont(QFont{ "Verdana", 10});
	g.show();
	//run();
	_CrtDumpMemoryLeaks();
	return QApplication::exec();
}