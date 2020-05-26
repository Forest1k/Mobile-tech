#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "csv.cpp"

using namespace std;

int net(std::string filename) {
	setlocale(LC_ALL, "ru");
	setlocale(LC_NUMERIC, "eng");
	std::ifstream file(filename);
	if (file.fail()) {
		std::cout << "This file does not exist\n";
		return 1;
	}
	std::string ipaddr = "192.168.250.41";
	//std::cout << "Enter IP: ";
	//std::cin >> ipaddr;
	
	CSVRow row;
	file >> row;
	Nettarif user(1, ipaddr);
	while (file >> row) {
		if (!row[0].compare("Summary")) break;
		user.GetRow(row);
		user.Internet();
	}
	user.CountMoney();

	return 0;
}