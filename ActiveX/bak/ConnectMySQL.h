#pragma once

#include <winsock.h>
#include <mysql.h>
#include <iostream>
using namespace std;

string operator+(string str, int integer); // 重载加法运算符string + int

class ConnectMySQL
{
public:
	MYSQL mysql; // mysql连接
	char sql[150] = ""; // sql语句
	const char* InsertSQL; // 新增语句

	ConnectMySQL();
	~ConnectMySQL();

	// 设置各参数值
	void SetDatas(int A, int B, int C, int D, int E, int F, int CycleCriterion);
	// 数据输入数据库
	bool EnterDataToDatabase();
	// 连接数据库
	bool ConnectDatabase();
	// 释放资源
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

