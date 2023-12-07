#include "pch.h"
#include "ConnectMySQL.h"

ConnectMySQL::ConnectMySQL()
{
	InsertSQL = "";
}

ConnectMySQL::~ConnectMySQL()
{
	FreeConnect();
}

void ConnectMySQL::SetDatas(int A, int B, int C, int D, int E, int F, int CycleCriterion)
{
	this->A = A;
	this->B = B;
	this->C = C;
	this->D = D;
	this->E = E;
	this->F = F;
	this->CycleCriterion = CycleCriterion;
}

bool ConnectMySQL::EnterDataToDatabase()
{
	string str = "insert into materials(Material_A, Material_B, Material_C, Material_D, Material_E, Material_F, CycleCriterion) values (";
	str = str + A + ", " + B + ", " + C + ", " + D + ", " + E + ", " + F + ", " + CycleCriterion + ");";
	InsertSQL = str.c_str();

	sprintf_s(sql, InsertSQL); // 也可以控制台手动输入sql语句
	if (!mysql_query(&mysql, sql))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ConnectMySQL::ConnectDatabase()
{
	mysql_init(&mysql);  //连接mysql数据库，初始化
	const char* host = "localhost";
	const char* user = "root";
	const char* password = "Dilanxue&*943";
	const char* database = "absdata";
	if (!(mysql_real_connect(&mysql, host, user, password, database, 3307, NULL, 0))) //中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等），可以先写成参数再传进去
	{
		// cout << "连接数据库失败:" << mysql_error(&mysql) << endl;
		return false; // 连接失败
	}
	else
	{
		// cout << "连接成功..." << endl;
		return true; // 连接成功
	}
}

void ConnectMySQL::FreeConnect() // 释放资源
{
	// cout << "释放数据库资源..." << endl;
	mysql_close(&mysql);
}

string operator+(string str, int integer)
{
	string temp = "";
	char c;
	while (true)
	{
		c = integer % 10 + '0';
		temp += c;
		integer /= 10;
		if (integer == 0)
		{
			break;
		}
	}
	reverse(temp.begin(), temp.end());
	return str.append(temp);
}