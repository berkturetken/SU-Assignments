#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "matrixclass.h"

using namespace std;

int main()
{
	Matrix2D<string> stringMatrix1;
	Matrix2D<int> intMatrix1;

	Matrix2D<string> stringMatrix2;
	Matrix2D<int> intMatrix2;

	/*****NEW******/
	Matrix2D<string> stringMatrix3;
	Matrix2D<int> intMatrix3;
	
	string fileName1, fileName2, fileName3;

	cout << "Please enter a file name: ";
	cin >> fileName1;

	cout << "Please enter another file name: ";
	cin >> fileName2;

	/*****NEW******/
	cout << "Please enter a file name for the last time: ";
	cin >> fileName3;

	ifstream file;
	file.open(fileName1.c_str());
	
	file >> intMatrix1;
	file.clear();
	file.seekg(0);
	file >> stringMatrix1;
	file.close();
	
	file.open(fileName2.c_str());

	file >> intMatrix2;
	file.clear();
	file.seekg(0);
	file >> stringMatrix2;
	file.close();

	/*****new*****/
	file.open(fileName3.c_str());

	file >> stringMatrix3;
	file.clear();
	file.seekg(0);
	file >> intMatrix3;
	file.close();
	
	cout << intMatrix1 + intMatrix2; 
	cout << endl;
	cout << intMatrix1 + intMatrix2 + intMatrix3;
	cout << endl;
	cout << stringMatrix1 + stringMatrix2 + stringMatrix3;
	cout << endl;
	cout << stringMatrix1 + stringMatrix2;
	
	cout << endl;
	intMatrix1 += intMatrix1;

	stringMatrix2 = stringMatrix3 + stringMatrix1;

	cout << intMatrix1 << endl <<  stringMatrix2 << endl;

	Matrix2D<int> newOne = intMatrix2 + (intMatrix1 += intMatrix3);

	cout << newOne << endl;

	intMatrix1 = newOne;

	intMatrix1.SetIndex(1, 1, 10001);

	cout << intMatrix1 << endl;

	cout << newOne.GetIndex(1, 1) << endl; 
	
	return 0;
}