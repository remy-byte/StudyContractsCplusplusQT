#include "repository_contract.h"
#include <iostream>
#include "validator.h"
using namespace std;


void RepositoryContract::store_entity(const Contract& contract)
{
	if (exist(contract))
	{
		throw RepoContractException("There is a study contract with the following elements, subject_name: " + contract.get_Subject() + "and type" + contract.get_Type());
	}

	list.push_back(contract);

}

int RepositoryContract::findContractByName(const string name)
{
	int iterator{ -1 }, position{ -1 };

	for (const auto& element : list)
	{
		iterator += 1;
		if (element.get_Subject() == name)
		{
			position = iterator;
		}
	}

	if (position == -1)
	{
		throw RepoContractException("There is no subject with that name!");
	}

	return position;

}

void RepositoryContract::modify_contract(const Contract& contract)
{

	if (!exist(contract))
		throw RepoContractException("This contract does not exist!");
	for (auto& contract_it : list)
	{
		if (contract_it.get_Subject() == contract.get_Subject())
		{
			contract_it.set_Subject(contract.get_Subject());
			contract_it.set_Duration(contract.get_Duration());
			contract_it.set_Type(contract.get_Type());
			contract_it.set_Teacher_name(contract.get_Teacher_name());
		}
	}

}

const Contract RepositoryContract::findContractByPosition(int position)
{
	int iterator{ -1 };
	for (const auto& element : list)
	{
		iterator += 1;
		if (iterator == position)
		{
			return element;
		}
	}
	throw RepoContractException("There is no contract on this position!");

}


vector<Contract> RepositoryContract::transform()
{
	vector <Contract> return_list;

	for (const auto& p : list)
	{
		return_list.push_back(p);
	}
	return return_list;

}

bool RepositoryContract::exist(const Contract& contract) const {

	try {
		find(contract.get_Subject());
		return true;
	}
	catch (RepoContractException&)
	{
		return false;
	}

}

void RepositoryContract::delete_entity(int position) {

	if (position > list.size() or position < 0)
	{
		throw RepoContractException("This study contract does not exist!");
	}

	list.erase(list.begin() + position);


}


const Contract& RepositoryContract::find(string subject) const {

	//VectorTemplate<Contract> return_list = get_All_Template();

	for (const auto& iterator : list) {
		if (iterator.get_Subject() == subject)
			return iterator;
	}

	//throw exception if the entity based on the two elements is not in the list
	throw RepoContractException("There is no study contract based on the subject" + subject);

}
/*
const VectorTemplate<Contract>& RepositoryContract::get_All_Template() const
{
	return list;
}*/

vector<Contract> RepositoryContract::get_All() {
	vector<Contract> return_list = transform();
	return list;
}

ostream& operator<<(ostream& out, const RepoContractException& exception) {
	out << exception.error_message;
	return out;
}


void RepositoryContractFile::load_from_file()
{
	ifstream in(filename);

	if (!in.is_open())
	{
		throw RepoContractException("Unable to open file" + filename);
	}
	while (!in.eof())
	{
		string subject, type, teacher_name;
		int duration;

		in >> subject;
		in >> duration;
		in >> type;
		in >> teacher_name;

		Contract contract{ subject,duration,type,teacher_name };
		if (subject != "")
		RepositoryContract::store_entity(contract);
			
	}

}

void RepositoryContractFile::save_to_file()
{

	ofstream out(filename);

	if (!out.is_open())
	{
		throw RepoContractException("Unable to open file");
	}

	for (auto& contract : RepositoryContract::get_All())
	{
		out << contract.get_Subject();
		out << endl;
		out << contract.get_Duration();
		out << endl;
		out << contract.get_Type();
		out << endl;
		out << contract.get_Teacher_name();
		out << endl;
	}

	out.close();

}
