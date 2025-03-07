#pragma once

#include "contract.h"
#include "repository_contract.h"
#include <vector>


class Undo {

public:
	virtual void doUndo() = 0;

	virtual ~Undo() = default;

};

class UndoDelete : public Undo {

	Contract contract_to_add;
	RepositoryContract& contracts;

public:

	UndoDelete(const Contract contract, RepositoryContract& repo) : contract_to_add{ contract }, contracts{ repo } {};

	void doUndo() override
	{
		contracts.store_entity(contract_to_add);
	}

};


class UndoAdd : public Undo {

	Contract contract_to_del;
	RepositoryContract& contracts;

public:

	UndoAdd(const Contract contract, RepositoryContract& repo) : contract_to_del{ contract }, contracts{ repo } {};

	void doUndo() override
	{
		contracts.delete_entity(contracts.findContractByName(contract_to_del.get_Subject()));
	}

};

class UndoModify : public Undo {

	Contract contract_to_modify;
	RepositoryContract& contracts;

public:

	UndoModify(const Contract contract, RepositoryContract& repo) : contract_to_modify{ contract }, contracts{ repo } {};

	void doUndo() override
	{
		contracts.delete_entity(contracts.findContractByName(contract_to_modify.get_Subject()));

		contracts.store_entity(contract_to_modify);
	}


};