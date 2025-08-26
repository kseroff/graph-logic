#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Phone.h"

using namespace std;

Phone::Phone() // ����������� �� ���������
{
	diagonal = NULL;
	iPrice = NULL;
	Manuf = new char[100];
	Model = new char[100];
	Manuf[0] = '\0';
	Model[0] = '\0';
}


Phone::Phone(const char* Manuf, const char* Model, int iPrice, int diagonal)
{
	this->iPrice = iPrice;
	this->diagonal = diagonal;
	this->Manuf = _strdup(Manuf);
	this->Model = _strdup(Model);
}

Phone::~Phone() {
	delete[]Manuf;
	delete[]Model;
}

//����������� �����������
Phone::Phone(const Phone& other)
{
	iPrice = other.iPrice;
	diagonal = other.diagonal;

	Manuf = _strdup(other.Manuf);
	Model = _strdup(other.Model);
}

// �������� ������������
Phone& Phone::operator=(const Phone& other)
{
	if (this != &other)
	{
		delete[] Manuf;
		delete[] Model;

		iPrice = other.iPrice;
		diagonal = other.diagonal;

		Manuf = _strdup(other.Manuf);
		Model = _strdup(other.Model);
	}

	return *this;
}

void Phone::Input() // ���� ���������� ������.
{
	cout << "������� ������������� � ������ ��������" << endl;
	cin.getline(Manuf, sizeof(Manuf));
	cin.getline(Model, sizeof(Model));
	cout << "������� ������������� �������� (���������/����(� ���.))" << endl;

	cin >> diagonal >> iPrice;
	cout << endl;
}

void Phone::Output() // ����� ���� ���������� ������.
{
	cout << "�������������: " << Manuf << endl;
	cout << "�������� ������: " << Model << endl;
	cout << "�������������� (���������/����): " << diagonal << ", " << iPrice << endl << endl;
}

void  Phone::Serialize(ostream& os) const {
	os << iPrice << ' ' << Manuf << ' ' << Model << ' ' << diagonal << ' ';
}

void  Phone::Deserialize(istream& is) {
	char temp[100];

	is >> iPrice;
	is.getline(temp, 100, ' ');
	is.getline(Manuf, sizeof(Manuf), ' ');
	is.getline(Model, sizeof(Model), ' ');
	is >> diagonal;

}

ostream& operator<<(ostream& os, design& phone)
{
	os << "�������: ";
	phone.Output();
	return os;
}

istream& operator>>(istream& is, design& phone)
{
	phone.Input();
	return is;
}