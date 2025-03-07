#pragma once
#include "contract.h"
#include "repository_contract.h"
#include <vector>
#include <string>
#include "validator.h"
#include <functional>
#include "study_contract.h"
#include "undo.h"

using namespace std;


class ContractList: public Observable {

	RepositoryContract& repository;
	Validate& validator;
	StudyContracts shoppingcart;
	vector <unique_ptr<Undo>> undo;

	vector <Contract> filter(function <bool(const Contract&)> function_filter);

	vector <Contract> general_sorting_service(bool(*compare_function)(const Contract&, const Contract&));

public:

	ContractList(RepositoryContract& repo, Validate& valid, StudyContracts& studies)noexcept :repository{ repo }, validator{ valid }, shoppingcart{ studies } {}

	ContractList(const ContractList& list) = delete;

	void addContractService(const string& subject, int duration, const string& type, const string& teacher_name);

	void deleteContractService(int position);

	void AddToCartService(const string name);

	const vector<Contract>& getShoppingCart();

	void clearCart();

	void random_fill(int dimension, vector<Contract> all);

	void export_to_file();

	vector<Contract> filter_by_duration(int duration);

	vector<Contract> filter_by_teacher_name(string teacher_name);

	void modifyContractService(const string subject_name, int duration, const string type, const string teacher_name);


	const vector<Contract> get_All() {
		return repository.get_All();
	};

	void makeUndo();

	vector<Contract> sort_by_duration();
	vector<Contract> sort_by_subject();
	vector<Contract> sort_by_teacher_and_type();
	int findContractbyName(const string subject);
};