#include "contract.h"

bool compare_duration(const Contract& contract, const Contract& other)
{
	return contract.get_Duration() < other.get_Duration();
}

bool compare_subject(const Contract& contract, const Contract& other)
{
	return contract.get_Subject() < other.get_Subject();
}
