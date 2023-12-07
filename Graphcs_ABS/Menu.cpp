#include<iostream>
#include"Menu.h"
using namespace std;

// ԭ���䷽��ʼ��
Menu::Menu()
{
	for (int i = 0; i < 6; i++)
	{
		materials[i] = 0;
		names[i] = 'A' + i;
	}
}

void Menu::setMaterials(int* p)
{
	for (int i = 0; i < 6; i++)
	{
		materials[i] = p[i];
	}
}

int Menu::getMaterials(int index)
{
	return materials[index];
}

char Menu::getNames(int index)
{
	return names[index];
}

void Menu::PrintMaterials()
{
	// �䷽��ʽ����ӡ
	cout << "\n=======================================" << endl;
	for (int i = 0; i < 3; i++)
	{
		printf("|  %c: %-2dkg  |", names[i], materials[i]);
		// cout << names[i] << " " << materials[i] << "";
	}
	cout << "\n---------------------------------------" << endl;
	for (int i = 3; i < 6; i++)
	{
		printf("|  %c: %-2dkg  |", names[i], materials[i]);
		// cout << names[i] << ": " << materials[i] << endl;
	}
	cout << "\n=======================================\n" << endl;
}