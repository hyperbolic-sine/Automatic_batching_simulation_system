#pragma once

// 添加定时器ID
#define WMUSER_UPDATEPIC_TIMERID WM_USER + 1001

class CPublic
{
public:
	CPublic();
	virtual ~CPublic();

public:
	// 配料表
	static int materials[6];

	// 配料次数
	static int totalTimes;

	// 配料表总计
	static int sum;
};

