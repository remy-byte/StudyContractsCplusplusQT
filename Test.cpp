#include "Test.h"

void filtrare_dupa_duratie__lista_vida__return_lista_vida() {

	FakeRepo repo;
	Validate validator;
	StudyContracts contracts;
	ContractList service{ repo,validator, contracts };

	vector <Contract> elemente_returnate = service.filter_by_duration(2);


	assert(elemente_returnate.size() == 0);


}

void filtrare_dupa_duratie__elemente_care_nu_contin_duratia_data__return_lista_vida()
{

	FakeRepo repo;
	Validate validator;
	StudyContracts contracts;
	ContractList service{ repo,validator, contracts };

	vector <Contract> elemente_returnate = service.filter_by_duration(2);
	repo.caz = 2;

	assert(elemente_returnate.size() == 0);
}

void filtrare_dupa_duratie_elemente_care_au_duratia_data() {

	FakeRepo repo;
	Validate validator;
	StudyContracts contracts;
	ContractList service{ repo,validator, contracts };

	repo.caz = 1;
	vector <Contract> elemente_returnate = service.filter_by_duration(2);

	assert(elemente_returnate.size() == 1);

}

void ruleaza_teste()
{

	filtrare_dupa_duratie_elemente_care_au_duratia_data();
	filtrare_dupa_duratie__elemente_care_nu_contin_duratia_data__return_lista_vida();
	filtrare_dupa_duratie__lista_vida__return_lista_vida();

}
