#pragma once
class Menu
{
private:
	int materials[6];
	char names[6];

public:
	// ԭ���䷽��ʼ��
	Menu();

	void setMaterials(int* p);

	int getMaterials(int index);

	char getNames(int index);

	void PrintMaterials();
};