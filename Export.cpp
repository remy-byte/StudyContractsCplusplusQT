#include "Export.h"

void exportToCSV(string fileName, const vector<Contract>& all) {
	cout << "DA";
	ofstream out(fileName, ios::trunc);
	if (!out.is_open()) {
		throw RepoContractException("Cannot open the file " + fileName);
	}

	for (const auto& product : all) {
		out << product.get_Subject() << "," << product.get_Duration() << "," << product.get_Teacher_name() << "," << product.get_Type() << endl;
	}
	out.close();
}
