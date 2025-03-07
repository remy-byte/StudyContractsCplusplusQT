#pragma once
class Observer {
public:
	virtual void update() = 0;
};


#include <vector>
#include <algorithm>
class Observable {
private:

	std::vector<Observer*> observers;
public:
	void addObserver(Observer* observable_object) {
		observers.push_back(observable_object);
	}
	void removeObserver(Observer* observable_object) {
		observers.erase(std::remove(observers.begin(), observers.end(), observable_object), observers.end());
	}
protected:
	void notify() {
		for (auto observable_objects : observers) {
			observable_objects->update();
		}
	}
};