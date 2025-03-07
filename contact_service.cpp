#include "contract_service.h"
#include "contract.h"
#include <functional>
#include <algorithm>
#include <assert.h>

using namespace std;

void ContractList::addContractService(const string& subject, int duration, const string& type, const string& teacher_name)
{

	Contract contract(subject, duration, type, teacher_name);
	validator.validate(contract);
	repository.store_entity(contract);
	undo.push_back(make_unique<UndoAdd>(contract, this->repository));

}

void ContractList::deleteContractService(int position)
{
	Contract contract = repository.findContractByPosition(position);
	repository.delete_entity(position);
	undo.push_back(std::make_unique<UndoDelete>(contract, this->repository));
}


void ContractList::modifyContractService(const string subject_name, int duration, const string type, const string teacher_name) {

	Contract contract{ subject_name, duration, type, teacher_name };
	validator.validate(contract);
	undo.push_back(std::make_unique<UndoModify>(repository.findContractByPosition(repository.findContractByName(contract.get_Subject())), this->repository));
	repository.modify_contract(contract);

}

vector <Contract> ContractList::filter(function <bool(const Contract&)> function_filter) {

	vector<Contract> result;

	for (const auto& iterator : repository.get_All())
	{
		if (function_filter(iterator))
		{
			result.push_back(iterator);
		}
	}

	return result;

}


vector <Contract> ContractList::filter_by_duration(int duration)
{
	return filter([duration](const Contract& contract)
		{return contract.get_Duration() == duration; });
}

vector <Contract> ContractList::filter_by_teacher_name(string teacher_name) {

	return filter([teacher_name](const Contract& contract)
		{return contract.get_Teacher_name() == teacher_name; });

}


vector <Contract> ContractList::general_sorting_service(bool(*compare_function)(const Contract&, const Contract&)) {
	vector<Contract> contracts{ repository.get_All() };

	for (int i = 0; i < contracts.size(); i++)
	{
		for (int j = i + 1; j < contracts.size(); j++)
		{
			if (!compare_function(contracts[i], contracts[j]))
			{
				swap(contracts[i], contracts[j]);
			}
		}
	}
	return contracts;
}


vector<Contract> ContractList::sort_by_duration() {

	return general_sorting_service(compare_duration);

}

vector<Contract> ContractList::sort_by_subject() {

	return general_sorting_service(compare_subject);
}

vector<Contract> ContractList::sort_by_teacher_and_type()
{
	return general_sorting_service([](const Contract& contract, const Contract& other)
		{
			if (contract.get_Teacher_name() == other.get_Teacher_name())
			{
				return contract.get_Type() > other.get_Type();
			}
			return contract.get_Teacher_name() > other.get_Teacher_name();
		});
}

int ContractList::findContractbyName(const string subject)
{
	return repository.findContractByName(subject);
}

void ContractList::AddToCartService(const string name)
{
	const int iterator = repository.findContractByName(name);
	const Contract contract_to_add = repository.findContractByPosition(iterator);
	shoppingcart.addtoCart(contract_to_add);
	notify();

}

const vector<Contract>& ContractList::getShoppingCart() {
	return shoppingcart.get_All_Cart();
}

void ContractList::clearCart() {
	shoppingcart.clearCart();
	notify();
}

void ContractList::random_fill(int dimension, vector<Contract> all) {

	shoppingcart.fillCart(dimension, all);
	notify();
}

void ContractList::makeUndo()
{

	if (undo.empty()) {
		throw RepoContractException{ "No more undo action to do!\n" };
	}
	undo.back()->doUndo();
	undo.pop_back();

}