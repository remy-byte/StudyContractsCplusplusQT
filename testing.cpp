#include "repository_contract.h"
#include "contract_service.h"
#include "validator.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include "Export.h"

using namespace std;

void run_repository_tests()
{

	RepositoryContract contract_list;


	contract_list.store_entity(Contract{ "aq",2,"a","a" });

	assert(contract_list.get_All().size() == 1);

	try {
		contract_list.find("a").get_Duration();
		assert(false);
	}
	catch (RepoContractException&)
	{
		assert(true);
	}

	try {
		contract_list.store_entity(Contract{ "aq",2,"a","a" });
	}
	catch (RepoContractException&)
	{
		assert(true);
	}




}

void run_validation_tests() {

	Validate validator;

	Contract contract{ "",-2,"","" };
	try {
		validator.validate(contract);
	}
	catch (const ValidateException& exception) {

		stringstream sout;

		sout << exception;

		const auto message = sout.str();
		assert(message.find("Invalid subject!") >= 0);
		assert(message.find("Invalid duration of study!") >= 0);
		assert(message.find("Invalid teacher name!") >= 0);
		assert(message.find("Invalid type of contract studies!") >= 0);

	}

}


void run_service_tests()
{
	RepositoryContract repository;
	Validate validation;
	StudyContracts studies;
	ContractList ctrlist{ repository, validation, studies };

	ctrlist.addContractService("a", 20, "a", "a");
	assert(ctrlist.get_All().size() == 1);

	try {

		ctrlist.addContractService("", -1, "", "");
		assert(false);
	}
	catch (ValidateException&)
	{
		assert(true);
	}
	ctrlist.deleteContractService(0);
	assert(ctrlist.get_All().size() == 0);
	try {

		ctrlist.deleteContractService(1);
		assert(false);
	}
	catch (RepoContractException&)
	{
		assert(true);
	}

	ctrlist.addContractService("b", 20, "c", "c");
	ctrlist.addContractService("a", 20, "a", "a");

	ctrlist.AddToCartService("a");
	ctrlist.clearCart();
	ctrlist.random_fill(2, ctrlist.get_All());
	exportToCSV("test", ctrlist.getShoppingCart());


	assert(ctrlist.filter_by_duration(20).size() == 2);

	assert(ctrlist.filter_by_teacher_name("a").size() == 1);


	ctrlist.addContractService("c", 15, "a", "b");

	auto first_element = ctrlist.sort_by_duration()[0];
	assert(first_element.get_Subject() == "c");

	first_element = ctrlist.sort_by_subject()[0];
	assert(first_element.get_Subject() == "a");

	first_element = ctrlist.sort_by_teacher_and_type()[0];
	assert(first_element.get_Subject() == "b");

}

void run_tests_fake_repo()
{









}




void run_all_tests() {
	run_repository_tests();
	run_validation_tests();
	run_service_tests();
	run_tests_fake_repo();
}