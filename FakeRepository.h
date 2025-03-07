#pragma once

#include "repository_contract.h"


class FakeRepo : public RepositoryContract {

public :
	bool returnvalue;
	int caz= 0;

	vector <Contract> get_All() override {

	

			if (caz == 1)
		{
				vector<Contract> elemente;

			elemente.push_back({"C",2,"B","D"});
			elemente.push_back({ "C",3,"B","D" });

			return elemente;
		}
		if (caz == 2)
		{
			vector<Contract> elemente;

			elemente.push_back({ "C",1,"B","D" });
			elemente.push_back({ "C",3,"B","D" });

			return elemente;

		}
		else
		{
			return vector<Contract>();
		}




	}


};