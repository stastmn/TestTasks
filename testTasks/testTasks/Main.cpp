#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <ostream>
#include "CustomList.h"


void printToBinNumerals(int decNum);

int main()
{
	printToBinNumerals(10);
	printToBinNumerals(-10);
	printToBinNumerals(0);
	printToBinNumerals(INT32_MAX);
	printToBinNumerals(INT32_MIN);

	

	List* list = new List();
	std::cout << "\n\nPlease, enter the number of strings for List\n";
	int nums;
	std::cin >> nums;
	std::cout << "Please, enter a strings\n";
	for(int i = 0;i<nums;i++)
	{
		std::string bar;
		std::cin >> bar;
		list->Add(bar);
		
	}

	
	FILE * ptrFile = fopen("file.bin", "wb");
	list->Serialize(ptrFile);
	fclose(ptrFile);
	list->ReleseNodes(); delete list;

	
	ptrFile = fopen("file.bin", "rb");
	List *list2 = new List();
	list2->Deserialize(ptrFile);
	std::cout << "\n\n Data from file: \n";
	for(int i = 0;i<nums;i++)
	{
		std::cout << list2->operator[](i) << "\n";
	}
	
	fclose(ptrFile);
	list2->ReleseNodes(); delete list2;
		
	return 0;
}


//Print binary representation of a decimal number into std::cout
void printToBinNumerals(int decNum)
{
	
#ifdef _DEBUG
	std::cout << decNum << " -\t\t\t";

#endif
		
	std::string binRepr(sizeof(int) * 8, '*');

	for (int i = 0; i < sizeof(int) * 8; i++) 
	{
		if (decNum & 0x80000000)
		{
			binRepr[i] = '1';
		}
		else
		{
			binRepr[i] = '0';
		}
		decNum <<= 1;
	}
	
	std::cout << binRepr << std::endl;

	
}
