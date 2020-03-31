// mobile.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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

void tarif(CSVRow row) {
	std::string timestamp = row[0];
	std::string origin = row[1];
	std::string dest = row[2];
	double call = std::stod(row[3], NULL);
	int sms = (int)std::stod(row[4], NULL);

}

int main()
{
	setlocale(LC_ALL, "ru");
	setlocale(LC_NUMERIC, "eng");
	std::ifstream       file("data.csv");

	CSVRow              row;
	file >> row;
	Tarif tar("911926375", 2, 0, 1, 50, 1, 0);
	while (file >> row)
	{
		tar.GetRow(row);
		tar.Telefonia();
		tar.SMS();
	}
	std::cout << "Итоговая стоимость всех звонков абонента = " << tar.telefoniamoney << std::endl;
	std::cout << "Итоговая стоимость всех смс абонента = " << tar.smsmoney << std::endl;
	std::cout << "Итого = " << tar.smsmoney + tar.telefoniamoney << std::endl;

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
