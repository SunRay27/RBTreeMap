using namespace std;

#include <iostream>
#include "RBTree.h"
#include <string>


int main()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, 0x0 | 0x70);
	system("CLS");
	SetConsoleOutputCP(1251);

	//hey! it makes no garbage (as always)
	Map<int, double> map;

	for (size_t i = 1; i <= 15; i++)
	{
		printf("inserting %i", i);
		map.Insert(i, i * 5712);
		map.Print();
	}

	for (size_t i = 1; i < 6; i++)
	{
		printf("removing %i", i);
		map.Remove(i);
		map.Print();
	}

	map.Clear();

}


