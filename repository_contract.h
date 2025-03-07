#pragma once
#include "contract.h"
#include <vector>
#include <string>
#include <iostream>
#include <ostream>
#include <fstream>
#include <map>
#include <cstdlib>

using namespace std;

class RepositoryContract {

private:

	vector<Contract> list;

	vector<Contract> transform();
	//verify in a private manner if the entitiy already exists in the repository
	bool exist(const Contract& contract)const;
public:
	RepositoryContract() = default;


	RepositoryContract(const RepositoryContract& contract) = delete;

	virtual void store_entity(const Contract& contract);

	int findContractByName(const string name);

	virtual void modify_contract(const Contract& contract);

	const Contract findContractByPosition(int position);

	const Contract& find(string subject) const;

	virtual vector<Contract> get_All();

	//const vectorContract>& get_All_Template() const;

	virtual void delete_entity(int position);
	virtual ~RepositoryContract() {};

};


class RepoContractException {

private:
	string error_message;
public:
	RepoContractException(string m) :error_message{ m } {}

	friend ostream& operator<<(ostream& out, const RepoContractException& exception);
};

ostream& operator<<(ostream& out, const RepoContractException& exception);


class RepositoryContractFile : public RepositoryContract {

private:

	void load_from_file();
	void save_to_file();
	string filename;


	void clearfile() {

		ofstream filestream(filename, ios::trunc);
		filestream.close();

	}
public:

	RepositoryContractFile(string filename) : RepositoryContract(), filename{ filename } {
		load_from_file();
	}

	void store_entity(const Contract& contract) override {
		RepositoryContract::store_entity(contract);
		save_to_file();
	}

	void modify_contract(const Contract& contract) override {

		RepositoryContract::modify_contract(contract);
		save_to_file();

	}

	void delete_entity(int position) override {

		RepositoryContract::delete_entity(position);
		save_to_file();
	}



};

class RepoContractStake : public RepositoryContract {
private:

	const int chance = 50;
	map <string, Contract> map;

public:

	void store_entity(const Contract& contract) override {

		const int chance_given = rand() % 100;

		if (chance_given >= chance) {
			RepositoryContract::store_entity(contract);
			map[contract.get_Subject()] = contract;
		}
		else throw RepoContractException("TRY AGAIN!");


	}

	void delete_entity(int position) override {

		const int chance_given = rand() % 100;

		if (chance_given > chance)
		{
			Contract contract_to_be_deleted = RepositoryContract::findContractByPosition(position);
			RepositoryContract::delete_entity(position);
			map.erase(contract_to_be_deleted.get_Subject());

		}
		else throw RepoContractException("TRY AGAIN!");

	}


	vector<Contract> get_All() override {

		const int chance_given = rand() % 100;

		if (chance_given >= chance)
		{
			return RepositoryContract::get_All();

		}
		else throw RepoContractException("TRY AGAIN!");


	}




};
