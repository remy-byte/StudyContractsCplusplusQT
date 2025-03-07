#include "ui.h"
#include "contract.h"
#include <iostream>
#include "Export.h"

#define EXIT 0
#define ADD_CONTRACT 1
#define PRINT_ALL_CONTRACTS 2
#define DELETE_A_CONTRACT 3
#define MODIFY_A_CONTRACT 4
#define FILTER_BY_DURATION 5
#define FILTER_BY_TEACHER 6
#define SORT_BY_DURATION 7
#define SORT_BY_SUBJECT 8
#define SORT_BY_TEACHER_AND_TYPE 9
#define ADD_TO_STUDY_CART 10
#define PRINT_THE_SHOPPING_CART 11
#define CLEAR_CART 12
#define FILL_CART_WITH_RANDOM_CONTRACTS 13
#define EXPORT_TO_FILE 14
#define UNDO 15



using namespace std;

void ConsoleUI::add_contract_ui() {

	string subject, type, teacher_name;
	int duration;

	cout << "Subject name:";
	cin >> subject;
	cout << "Duration:";
	cin >> duration;
	cout << "Type:";
	cin >> type;
	cout << "Teacher's name:";
	cin >> teacher_name;

	ctr.addContractService(subject, duration, type, teacher_name);
	cout << "Study contract added with sucess!";

}


void ConsoleUI::print_all_contracts(const vector<Contract>& contract_list)
{
	cout << "------------------------------------------------------\n";
	cout << "Contracts: " << endl;
	int contract_number = 0;
	for (const auto& iteration : contract_list)
	{
		cout << contract_number << ". " << iteration.get_Subject() << " " << iteration.get_Duration() << " " << iteration.get_Type() << " " << iteration.get_Teacher_name() << endl;

		contract_number++;
	}
	cout << "------------------------------------------------------\n";
}

void ConsoleUI::delete_contract_ui()
{

	int position;

	cout << "Enter the number of the contract that you wish to delete:";
	cin >> position;

	ctr.deleteContractService(position);


}

void ConsoleUI::add_to_shoppingcart_ui()
{
	string subject_name;
	cout << "Name of the study you wish to add to your cart:";
	cin >> subject_name;


	ctr.AddToCartService(subject_name);

}


void ConsoleUI::modify_contract_ui()
{
	string subject, type, teacher_name;
	int duration;

	cout << "Subject name:";
	cin >> subject;
	cout << "Duration:";
	cin >> duration;
	cout << "Type:";
	cin >> type;
	cout << "Teacher's name:";
	cin >> teacher_name;

	ctr.modifyContractService(subject, duration, type, teacher_name);
	cout << "Study contract modified with sucess!";
}

void ConsoleUI::export_to_file()
{

	string filename;
	cout << "Filename: ";
	cin >> filename;

	exportToCSV(filename, ctr.getShoppingCart());
}

void ConsoleUI::do_undo()
{
	ctr.makeUndo();
}


void ConsoleUI::start() {

	while (true) {

		cout << "Menu: \n";

		cout << "1. Add a contract\n2. Print all contracts\n3. Delete a contract\n4.Modify a contract\n5. Filter by duration\n6. Filter by teacher's name\n7. Sort by contracts by duration"
			"\n8. Sort contracts by subject name\n9. Sort subjects by teacher's name and type of contract\n10. Add a contract to your studies\n11. Show your contract\n12. Empty the cart\n13. Fill cart with random contracts\n14. Export to file\n0. Exit the application\n";

		int command = 0;

		cin >> command;

		try {
			switch (command) {
			case ADD_CONTRACT:
				add_contract_ui();
				break;
			case PRINT_ALL_CONTRACTS:
				print_all_contracts(ctr.get_All());
				break;
			case DELETE_A_CONTRACT:
				delete_contract_ui();
				break;
			case MODIFY_A_CONTRACT:
			{
				modify_contract_ui();
				break;
			}
			case FILTER_BY_DURATION:
				cout << "Filtering by the duration? : ";
				int price;
				cin >> price;
				print_all_contracts(ctr.filter_by_duration(price));
				break;
			case FILTER_BY_TEACHER:
			{
				cout << "Teacher's name: ";
				string name;
				cin >> name;
				print_all_contracts(ctr.filter_by_teacher_name(name));
				break;
			}
			case SORT_BY_DURATION:
			{
				print_all_contracts(ctr.sort_by_duration());
				break;
			}
			case SORT_BY_SUBJECT:
			{
				print_all_contracts(ctr.sort_by_subject());
				break;
			}
			case SORT_BY_TEACHER_AND_TYPE:
			{
				print_all_contracts(ctr.sort_by_teacher_and_type());
				break;
			}
			case ADD_TO_STUDY_CART:
			{
				add_to_shoppingcart_ui();
				break;
			}
			case PRINT_THE_SHOPPING_CART:
			{
				print_all_contracts(ctr.getShoppingCart());
				break;
			}
			case CLEAR_CART:
			{
				ctr.clearCart();
				break;
			}
			case FILL_CART_WITH_RANDOM_CONTRACTS:
			{
				int dimension;
				cout << "Dimension: ";
				cin >> dimension;
				ctr.random_fill(dimension, ctr.get_All());
				break;
			}
			case EXPORT_TO_FILE:
			{
				export_to_file();
				break;
			}
			case UNDO:
			{
				do_undo();
				break;
			}
			case EXIT:
				return;
				break;
			default:
				cout << "invalid command...\nTry again!";
				break;
			}
		}
		catch (const RepoContractException& exception)
		{
			cout << exception << endl;
		}
		catch (const ValidateException& exception)
		{
			cout << exception << endl;
		}
	}

}