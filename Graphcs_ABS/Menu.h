#pragma once
class Menu
{
private:
	int materials[6];
	char names[6];

public:
	// 原料配方初始化
	Menu();

	void setMaterials(int* p);

	int getMaterials(int index);

	char getNames(int index);

	void PrintMaterials();
};