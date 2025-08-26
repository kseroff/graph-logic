
#include <iostream>
#include <time.h>
#include <iomanip>
using namespace std;

int main(void)
{
	srand(time(NULL));
	setlocale(0, "");

	int n, m, max = 0, min = 999;
	cout << "Введите размер матрицы: ";
	cin >> n >> m;
	int** arr = new int*[n];
	for(int i=0; i<n; i++)
	{
		arr[i] = new int[m];
	}

	cout << "Массив: " << endl;
	for (int i = 0; i < n; i++)
	{
		int sum = 0;
		cout <<endl;
		for (int j = 0; j < m; j++) 
		{
			arr[i][j] = 10 + rand() % 90;

			if (arr[i][j] > max) { max = arr[i][j]; }
			if (arr[i][j] < min) { min = arr[i][j]; }
			sum += arr[i][j];

			cout <<setw(3)<< arr[i][j] << " ";
		}
		cout << "--- сумма: " << sum;
	}
	cout<<endl<<endl<<"Разница максимального и минимального элемента: " << max - min;

	for (int i = 0; i < n; i++)
		delete[] arr[i];
	delete[] arr;

	cin.get(); cin.get();
	return 0;
}

