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

	sprintf_s(sql, InsertSQL); // Ҳ���Կ���̨�ֶ�����sql���
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
	mysql_init(&mysql);  //����mysql���ݿ⣬��ʼ��
	const char* host = "localhost";
	const char* user = "root";
	const char* password = "Dilanxue&*943";
	const char* database = "absdata";
	if (!(mysql_real_connect(&mysql, host, user, password, database, 3307, NULL, 0))) //�м�ֱ����������û��������룬���ݿ������˿ںţ�����дĬ��0����3306�ȣ���������д�ɲ����ٴ���ȥ
	{
		// cout << "�������ݿ�ʧ��:" << mysql_error(&mysql) << endl;
		return false; // ����ʧ��
	}
	else
	{
		// cout << "���ӳɹ�..." << endl;
		return true; // ���ӳɹ�
	}
}

void ConnectMySQL::FreeConnect() // �ͷ���Դ
{
	// cout << "�ͷ����ݿ���Դ..." << endl;
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