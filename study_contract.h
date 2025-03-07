#pragma once

#include "contract.h"
#include <vector>
#include <algorithm>
#include <random>
#include "Observer.h"


using std::vector;
using std::shuffle;


class StudyContracts : public Observable{

private:
	vector<Contract> cart;


public:

	StudyContracts();

	void addtoCart(const Contract& contract) {

		this->cart.push_back(contract);

	}

	void clearCart() {

		this->cart.clear();

	}

	const vector<Contract>& get_All_Cart()
	{
		return this->cart;
	}

	void fillCart(size_t dimension, vector<Contract> all) {
		vector<Contract> shoppingcart;
		std::shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}()));
		while ((this->cart.size() < dimension) && (all.size() > 0)) {
			this->cart.push_back(all.back());
			shoppingcart.push_back(all.back());
			all.pop_back();
			if (all.size() == 0 && cart.size() < dimension) {
				all = shoppingcart;
				shoppingcart.clear();
				std::shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}()));
			}
		}
	}



};