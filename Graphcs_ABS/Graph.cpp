#include<iostream>
#include<thread>
#include"DrawCar.h"
#include"Car.h"
#include"Menu.h"
using namespace std;


// �����ʼ����
Car car;
Menu menu;
bool flag = true;

bool isPass(int* p, int size);
// �����߳�
void key();
// ��ͼ�߳�
void Draw();


int main()
{
	// �䷽����׶�
	while (true)
	{
		cout << "\n	�纸����ҩ���Զ�����ģ��ϵͳ\n" << endl;
		cout << "���� A��B��C��D��E��F ��6��ԭ�ϣ�����ԭ��֮���������ʹ��100kg" << endl;
		cout << "������ԭ���䷽�����Իس����ύ\n" << endl;
		int temp_materials[6] = { 0,0,0,0,0,0 };
		for (int i = 0; i < 6; i++)
		{
			cout << menu.getNames(i) << "ԭ��: ";
			cin >> temp_materials[i];
		}
		if (isPass(temp_materials, 6))
		{
			menu.setMaterials(temp_materials);
			break;
		}
		else
		{
			cout << "�����䷽����ȷ������������!" << endl;
			system("pause");
			system("cls");
		}
	}
	// �䷽��ʾ
	system("cls");
	cout << "\n\t       �䷽��" << endl;
	menu.PrintMaterials();
	cout << "ģ�⼴����ʼ >>>" << endl;
	Sleep(3000);


	// �����߳�
	thread thread1(key);
	thread thread2(Draw);

	thread1.join();
	thread2.join();

	system("pause");
	return 0;
}


// ��֤�䷽�Ƿ���ȷ
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

// �����߳�
void key()
{
	int res = 0;
	while (true)
	{
		res = MessageBox(NULL, _T("�Ƿ��´�\"ֹͣ����\"����?\n��ʾ�����������С��λ��0��7λ��ʱ��Ч!"), _T("����"), MB_OKCANCEL);
		if ((res == 1) && (car.Curr_Position == 0 || car.Curr_Position == 7))
		{
			// ֹͣ����������Ч
			flag = false;
			return;
		}
	}
}


// ��ͼ�߳�
void Draw()
{
	// ����ͼ�����
	Init_Windows();

	while (true)
	{
		car.Curr_Position = 0;
		car.load = 0;

		// ��⵽"ֹͣװ��"����˳��߳�
		if (!flag)
		{
			return;
		}

		// ��ǰС���ڴ����ڵ�λ��
		int car_location = car_x0;

		car.Curr_Position += 1;

		// װ����
		for (; car.Curr_Position < 7; car.Curr_Position++)
		{
			// С������car.Curr_Positionλ��
			// car.Curr_Positionλ����Ҫװ��
			if (menu.getMaterials(car.Curr_Position - 1) != 0)
			{
				// ����
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
				// װ��
				car.load += menu.getMaterials(car.Curr_Position - 1);
				Sleep((long)(car.load * Speed_Coeffient * 200));
				Clear_Materials(615 - 80 * (car.Curr_Position - 1), 226);
			}
			else
			{
				car_location = Run(car_location, 80);
			}
		}

		// 7��λ��
		car_location = Run(car_location, 64);
		discharging(car_location);
		Draw_Materials(car_location - 20, car_y0 + 30, 100);
		Sleep((long)(car.load * Speed_Coeffient * 200));
		Clear_Materials(car_location - 20, car_y0 + 30);
		discharging_reset(car_location);
		Back(car_location);
		Sleep(500);

		// ��⵽"ֹͣװ��"����˳��߳�
		if (!flag)
		{
			return;
		}
	}
}