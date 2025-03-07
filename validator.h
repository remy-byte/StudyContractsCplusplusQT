#pragma once
#include <string>
#include "contract.h"
#include <vector>

using namespace std;

class Validate {

public:
	void validate(const Contract& contract);

};

class ValidateException {

protected:
	vector<string> error_message;

public:

	ValidateException(const vector<string>& error) : error_message{ error } {}

	//overriding the operator
	friend ostream& operator<<(ostream& out, const ValidateException& exception);
	string what(const ValidateException& exception);

};

ostream& operator<<(ostream& out, const ValidateException& exception);