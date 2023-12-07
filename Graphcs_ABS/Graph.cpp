#include<iostream>
#include<thread>
#include"DrawCar.h"
#include"Car.h"
#include"Menu.h"
using namespace std;


// 定义初始参数
Car car;
Menu menu;
bool flag = true;

bool isPass(int* p, int size);
// 开关线程
void key();
// 绘图线程
void Draw();


int main()
{
	// 配方输入阶段
	while (true)
	{
		cout << "\n	电焊条焊药的自动配料模拟系统\n" << endl;
		cout << "现有 A、B、C、D、E、F 共6种原料，所有原料之和最多允许使用100kg" << endl;
		cout << "请输入原料配方，并以回车键提交\n" << endl;
		int temp_materials[6] = { 0,0,0,0,0,0 };
		for (int i = 0; i < 6; i++)
		{
			cout << menu.getNames(i) << "原料: ";
			cin >> temp_materials[i];
		}
		if (isPass(temp_materials, 6))
		{
			menu.setMaterials(temp_materials);
			break;
		}
		else
		{
			cout << "输入配方不正确，请重新输入!" << endl;
			system("pause");
			system("cls");
		}
	}
	// 配方显示
	system("cls");
	cout << "\n\t       配方表" << endl;
	menu.PrintMaterials();
	cout << "模拟即将开始 >>>" << endl;
	Sleep(3000);


	// 启动线程
	thread thread1(key);
	thread thread2(Draw);

	thread1.join();
	thread2.join();

	system("pause");
	return 0;
}


// 验证配方是否正确
bool isPass(int* p, int size)
{
	int total = 0, i;
	for (i = 0; i < size; i++)
	{
		if (p[i] < 0)
		{
			return false;
		}
		total += p[i];
	}
	if (total <= Max_Load && total > 0)
	{
		return true;
	}
	return false;
}

// 开关线程
void key()
{
	int res = 0;
	while (true)
	{
		res = MessageBox(NULL, _T("是否下达\"停止配料\"命令?\n提示：该命令仅在小车位于0或7位置时生效!"), _T("开关"), MB_OKCANCEL);
		if ((res == 1) && (car.Curr_Position == 0 || car.Curr_Position == 7))
		{
			// 停止配料命令生效
			flag = false;
			return;
		}
	}
}


// 绘图线程
void Draw()
{
	// 基础图像加载
	Init_Windows();

	while (true)
	{
		car.Curr_Position = 0;
		car.load = 0;

		// 检测到"停止装配"命令，退出线程
		if (!flag)
		{
			return;
		}

		// 当前小车在窗口内的位置
		int car_location = car_x0;

		car.Curr_Position += 1;

		// 装料区
		for (; car.Curr_Position < 7; car.Curr_Position++)
		{
			// 小车来到car.Curr_Position位置
			// car.Curr_Position位置需要装料
			if (menu.getMaterials(car.Curr_Position - 1) != 0)
			{
				// 动画
				if (car.Curr_Position == 1)
				{
					car_location = Run(car_location, 54);
					Draw_Materials(615, 226, 100);
				}
				else
				{
					car_location = Run(car_location, 80);
					loading(car.Curr_Position);
				}
				// 装料
				car.load += menu.getMaterials(car.Curr_Position - 1);
				Sleep((long)(car.load * Speed_Coeffient * 200));
				Clear_Materials(615 - 80 * (car.Curr_Position - 1), 226);
			}
			else
			{
				car_location = Run(car_location, 80);
			}
		}

		// 7号位置
		car_location = Run(car_location, 64);
		discharging(car_location);
		Draw_Materials(car_location - 20, car_y0 + 30, 100);
		Sleep((long)(car.load * Speed_Coeffient * 200));
		Clear_Materials(car_location - 20, car_y0 + 30);
		discharging_reset(car_location);
		Back(car_location);
		Sleep(500);

		// 检测到"停止装配"命令，退出线程
		if (!flag)
		{
			return;
		}
	}
}