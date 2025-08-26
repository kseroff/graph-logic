#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "MyQueue.h"
#include "Phone.h"

using namespace std;


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    ////////////////////////////////////////////////////////////////////////////////////////
	/*
	Interface** arr = new Interface * [4];

	*(arr + 0) = new Phone();
	*(arr + 1) = new OS();
	*(arr + 2) = new design();
	*(arr + 3) = new matrix();

	for (int i = 0; i < 4; i++) {
		arr[i]->Input();
		cout << endl;
	}

	for (int i = 0; i < 4; i++) {
		arr[i]->Output();
		cout << endl;
	}
	*/
	////////////////////////////////////////////////////////////////////////////////////////

	/*
	design phone1, phone2;

	phone1.Input(); 
	cout << endl<<endl;
	phone2.Input(); 

	// Пример использования оператора ">="
	if (phone1 >= phone2)
	{
		cout << "Первый телефон имеет большую или равную подстроку color по сравнению со вторым." << endl;
	}
	else
	{
		cout << "Второй телефон имеет большую подстроку color по сравнению с первым." << endl;
	}

	// Пример использования оператора "|="
	string substringToRemove = "someSubstring";
	phone1 |= substringToRemove;
	cout << "После удаления подстроки '" << substringToRemove << "' из первого телефона:" << endl;


	//пример использования ofstream;
	cout << phone1 << endl;
	*/

	////////////////////////////////////////////////////////////////////////////////////////
	
		/*TQueue<int> a;
		for(int i=0; i<6; i++){
		int temp;
		cin>>temp;
		a.push(temp);
		} 
		for(int i=0; i<6; i++){
		cout << a.GetFront()<<" ";
		a.front();
		}*/
		
		
	////////////////////////////////////////////////////////////////////////////////////////

	TQueue testphone;
	Phone c("test1", "test2", 12, 2020); 
	design c1("test21", "test22", 21, 2021, "pink");
	testphone.push(&c);
	testphone.push(&c1);
	// Сериализация
	ofstream outFile("output.txt");
	testphone.Serialize(outFile);
	outFile.close();
	// Десериализация
	ifstream inFile("output.txt");
	testphone.Deserialize(inFile);
	inFile.close();
	// Вывод данных после десериализации
	testphone.Output();

		return 0;

}