#pragma once
#include <string>
using namespace std;


class Interface {
public:

	virtual ~Interface() = default;

	virtual void Input() = 0;// Ввод параметров класса.

	virtual void Output() = 0; // Вывод всех параметров класса.

	virtual void Serialize(ostream& os) const = 0;

	virtual void Deserialize(istream& is) = 0;

};

class Phone : public Interface
{
protected:
	int		iPrice;			// Цена в тысячах.
	char* Manuf;
	char* Model;
	int diagonal;
public:
	Phone();// конструктор по умолчанию

	Phone& operator=(const Phone& other);

	Phone(const Phone& other);

	Phone(const char* Manuf, const char* Model, int iPrice, int diagonal);  // конструктор с параметрами 

	~Phone() override;

	void Input();// Ввод параметров класса.

	void Output(); // Вывод всех параметров класса.


	void Serialize(ostream& os) const override;

	void Deserialize(istream& is) override;
};

class design :public Phone
{
public:
	design() { color = " "; }
	~design() override = default;
	design(const char* Manuf, const char* Model, int iPrice, int diagonal, string color) :Phone(Manuf, Model, iPrice, diagonal), color(color) {}
	void Input() {
		cin.ignore(cin.rdbuf()->in_avail());
		Phone::Input();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Введите цвет телефона " << endl;
		getline(cin, color);
	}

	void Output() {
		Phone::Output();
		cout << "Цвет:" << color << endl << endl;
	}

	void  Serialize(ostream& os) const override {
		Phone::Serialize(os);
		os << color << ' ';
	}

	void  Deserialize(istream& is) override {
		Phone::Deserialize(is);
		getline(is >> ws, color, ' ');
	}

	bool operator>=(const design& other) const
	{
		size_t thisPrefixLength = min(color.length(), static_cast<size_t>(5));
		size_t otherSuffixStart = max(other.color.length(), static_cast<size_t>(5)) - 5;

		return color.substr(0, thisPrefixLength) >= other.color.substr(otherSuffixStart, 5);
	}


	// Оператор "|=" для удаления подстроки ptr из строки color
	design& operator|=(const string& ptr)
	{
		size_t found = color.find(ptr);
		if (found != string::npos)
		{
			color.erase(found, ptr.length());
		}
		return *this;
	}

private:
	string color;

	friend ostream& operator<<(ostream& os, design& phone);
	friend istream& operator>>(istream& is, design& phone);
};


class OS :public Phone
{
public:
	OS() { nameOS = " "; }
	~OS() override = default;

	void Input() override {
		cin.ignore(cin.rdbuf()->in_avail());
		Phone::Input();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Введите ОС телефона" << endl;
		getline(cin, nameOS);
	}

	void Output() override {
		Phone::Output();
		cout << "OC:" << nameOS << endl << endl;
	}

	void  Serialize(ostream& os) const override {
		Phone::Serialize(os);
		os << nameOS << ' ';
	}

	void  Deserialize(istream& is) override {
		Phone::Deserialize(is);
		getline(is >> ws, nameOS, ' ');
	}

private:
	string nameOS;
};

class matrix : public design
{
public:
	matrix() { count_matrix = 0; }
	~matrix() override = default;
	void Input() override {
		cin.ignore(cin.rdbuf()->in_avail());
		design::Input();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Введите разрешение камеры" << endl;
		cin >> count_matrix;
	}

	void Output() override {
		design::Output();
		cout << "Разрешение камеры:" << count_matrix << endl << endl;
	}

	void  Serialize(ostream& os) const override {
		design::Serialize(os);
		os << count_matrix << ' ';
	}

	void  Deserialize(istream& is) override {
		design::Deserialize(is);
		is >> count_matrix;
	}

private:
	int count_matrix;
};