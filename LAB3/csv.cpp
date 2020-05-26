#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

#ifndef CSV_CPP
#define CSV_CPP

class CSVRow
{
public:
	std::string const& operator[](std::size_t index) const
	{
		return m_data.at(index);
	}
	std::size_t size() const
	{
		return m_data.size();
	}
	void readNextRow(std::istream& str)
	{
		std::string         line;
		std::getline(str, line);

		std::stringstream   lineStream(line);
		std::string         cell;

		m_data.clear();
		while (std::getline(lineStream, cell, ','))
		{
			m_data.push_back(cell);
		}
		// This checks for a trailing comma with no data after it.
		if (!lineStream && cell.empty())
		{
			// If there was a trailing comma then add an empty element.
			m_data.push_back("");
		}
	}
private:
	std::vector<std::string>    m_data;
};

std::istream& operator>>(std::istream& str, CSVRow& data)
{
	data.readNextRow(str);
	return str;
}

class Tarif {
public:
	std::string timestamp, origin, dest, tariffingnumber;
	double call; int sms;
	double telefoniamoney = 0;
	int smsmoney = 0;
	int outcall; int freeoutcall; int incall; int freeincall; int smstarif; int freesmscount;
	Tarif(std::string number, int out, int freeout, int in, int freein, int sms, int freesms) {
		outcall = out;
		freeoutcall = freeout;
		incall = in;
		freeincall = freein;
		smstarif = sms;
		freesmscount = freesms;
		tariffingnumber = number;
	}
	void GetRow(CSVRow row) {
		timestamp = row[0];
		origin = row[1];
		dest = row[2];
		call = std::stod(row[3]);
		sms = std::stoi(row[4]);
	}

	void Telefonia() {
		if (!tariffingnumber.compare(origin)) {
			if (freeoutcall < 0) {
				if (call <= abs(freeoutcall)) {
					telefoniamoney += call * outcall;
				}
				else {
					telefoniamoney += abs(freeoutcall) * outcall;
				}
			}
			if (freeoutcall >= 0)
				if (call > freeoutcall) {
					telefoniamoney += (call - freeoutcall) * outcall;
				}
		}
		if (!tariffingnumber.compare(dest)) {
			if (call > freeincall) {
				telefoniamoney += (call - (double)freeincall) * (double)incall;
			}
		}
	}
	void SMS() {
		if (!tariffingnumber.compare(origin)) {
			if (sms > freesmscount) {
				smsmoney += (sms - freesmscount) * smstarif;
			}
		}
	}

};

class Nettarif {
public:
	int tarif;
	std::string destip;
	std::string srcip;
	std::string tarifedip;
	int bytes;
	double money = 0;
	int usedbytes = 0;
	Nettarif(int tar, std::string ip) {
		tarif = tar;
		tarifedip = ip;
	}
	void GetRow(CSVRow csv) {
		srcip = csv[3];
		destip = csv[4];
		bytes = std::stoi(csv[12]);

	}
	void Internet() {
		if (!tarifedip.compare(srcip) || !tarifedip.compare(destip)) {
			usedbytes += bytes;
		}
	}
	void CountMoney() {
		money = (double)usedbytes / (pow(2,20)) * tarif;
		//std::cout << "Total amount of bytes = " << usedbytes << " = "<<(double)usedbytes/(1024*1024) <<" Mb"<< std::endl;
		//std::cout << "The total cost is equal to " << money << " RUB"<< std::endl;
		printf("Total cost is of internet equal to %.01f RUB\n", money);
	}

};

#endif