#pragma once

// ��Ӷ�ʱ��ID
#define WMUSER_UPDATEPIC_TIMERID WM_USER + 1001

class CPublic
{
public:
	CPublic();
	virtual ~CPublic();

public:
	// ���ϱ�
	static int materials[6];

	// ���ϴ���
	static int totalTimes;

	// ���ϱ��ܼ�
	static int sum;
};

