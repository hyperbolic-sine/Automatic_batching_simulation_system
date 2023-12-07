#pragma once

#include <winsock.h>
#include <mysql.h>
#include <iostream>
using namespace std;

string operator+(string str, int integer); // ���ؼӷ������string + int

class ConnectMySQL
{
public:
	MYSQL mysql; // mysql����
	char sql[150] = ""; // sql���
	const char* InsertSQL; // �������

	ConnectMySQL();
	~ConnectMySQL();

	// ���ø�����ֵ
	void SetDatas(int A, int B, int C, int D, int E, int F, int CycleCriterion);
	// �����������ݿ�
	bool EnterDataToDatabase();
	// �������ݿ�
	bool ConnectDatabase();
	// �ͷ���Դ
	void FreeConnect();

private:
	int A = 0;
	int B = 0;
	int C = 0;
	int D = 0;
	int E = 0;
	int F = 0;
	int CycleCriterion = 1;
};

