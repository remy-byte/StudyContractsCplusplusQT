#include "validator.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>

using namespace std;

void Validate::validate(const Contract& contract) {

	vector<string>error_message;
	string types[3]
		= { "optional", "obligatory", "facultative" };

	if (contract.get_Subject().size() == 0)
		error_message.push_back("Invalid subject!");
	if (contract.get_Duration() < 0)
		error_message.push_back("Invalid duration of study!");
	if (contract.get_Teacher_name().size() == 0)
		error_message.push_back("Invalid teacher name!");
	if (contract.get_Type().size() == 0)
		error_message.push_back("Invalid type of contract studies!");
	/*for (int i = 0; i < 3; i++)
	{
		bool found = false;
		string contract_type = contract.get_Type();
		transform(contract_type.begin(), contract_type.end(), contract_type.begin(), tolower);
		if (contract_type == types[i])
		{
			found = true;
		}

		if (found == false)
		{
			error_message.push_back("Invalid type of study (Use from: Obligatory, Facultative, Optional");
		}

	}*/
	if (error_message.size() > 0)
	{
		throw ValidateException(error_message);
	}

}

ostream& operator<<(ostream& out, const ValidateException& exception) {

	for (const auto& message : exception.error_message)
	{
		out << message << endl;
	}
	return out;


}

string ValidateException::what(const ValidateException& exception)
{

	string error=nullptr;
	for (const auto& message : exception.error_message)
	{
		error += message;
	}

	return error;
}

