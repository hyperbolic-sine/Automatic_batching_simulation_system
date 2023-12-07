#include"DrawCar.h"

void Init_Windows()
{
	initgraph(800, 640);
	setbkcolor(WHITE);
	cleardevice();
	// 设置线条颜色
	setlinecolor(BLACK);

	// 绘制料斗
	char name = 'F';
	settextstyle(30, 0, _T("Consolas"));
	for (int i = 0; i < 6; i++)
	{
		settextcolor(BLACK);
		outtextxy(210 + 80 * i, 120, name - i);
		setfillcolor(RGB(235, 110 + 15 * i, 69));
		Draw_Triangles(200 + 80 * i, 160, 30, 45, -1);
	}

	// 绘制轨道
	setlinestyle(PS_SOLID, 4);
	line(120, 340, 700, 340);
	setlinestyle(PS_SOLID, 1);
	// 轨道端点
	setfillcolor(BLACK);
	fillrectangle(119, 333, 127, 341);
	fillrectangle(701, 333, 709, 341);

	// 绘制料斗触发开关
	name = '7';
	settextstyle(24, 0, _T("Consolas"));
	for (int i = 0; i < 8; i++)
	{
		settextcolor(BLACK);
		outtextxy(130 + 80 * i, 360, name - i);
		setfillcolor(RGB(235, 95 + 15 * i, 69));
		Draw_Triangles(130 + 80 * i, 349, 10, 8, 1);
	}

	// 绘制搅拌机
	setlinestyle(PS_SOLID, 2);
	int mixer_lines[][4] = {
		{120, 340, 120, 400},
		{120, 400, 140, 400},
		{140, 400, 140, 450},
		{140, 450, 50, 450},
		{50, 450, 50, 400}
	};
	int mixer_flag[3][2] = { {50, 280},{50, 400},{86, 400} };
	Draw_Mixer(mixer_lines, mixer_flag);
}

void Draw_Triangles(int x0, int y0, int weight, int height, int UpOrDown)
{
	int center_x = x0 + weight / 2;
	int top_point_y;
	if (UpOrDown == 1)
	{
		top_point_y = y0 - height;
	}
	else
	{
		top_point_y = y0 + height;
	}
	POINT pts[] = { {x0, y0},{center_x, top_point_y},{x0 + weight, y0} };

	fillpolygon(pts, 3);
}

void Draw_Mixer(int lines[][4], int Tra[3][2])
{
	for (int i = 0; i < 5; i++)
	{
		line(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
	}

	POINT pts[] = { {Tra[0][0], Tra[0][1]},{Tra[1][0], Tra[1][1]},{Tra[2][0], Tra[2][1]} };
	setfillcolor(RGB(187, 255, 238));
	fillpolygon(pts, 3);

	settextcolor(BLACK);
	settextstyle(18, 0, _T("黑体"));
	outtextxy(lines[2][2] + 20, lines[2][3] - 30, _T("搅拌机"));
}

void Draw_Car(int x0, int y0)
{
	setlinestyle(PS_SOLID, 2);
	rectangle(x0, y0, x0 + 60, y0 + 30);

	setlinestyle(PS_SOLID, 1);
	setfillcolor(RGB(30, 144, 255));
	fillcircle(x0 + 17, y0 + 35, 8);
	fillcircle(x0 + 43, y0 + 35, 8);
}

void Clear_Car(int x0, int y0)
{
	setfillcolor(WHITE);
	POINT car[] = { {x0 - 1, y0 - 1},{x0 - 1, y0 + 31}, {x0 + 62, y0 + 31},{x0 + 62, y0 - 1} };
	POINT wheel[] = { {x0 + 9, y0 + 30}, {x0 + 9, y0 + 44}, {x0 + 53, y0 + 44}, {x0 + 53, y0 + 30} };
	clearpolygon(car, 4);
	clearpolygon(wheel, 4);
}

int Run(int position, int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		position--;
		Draw_Car(position, car_y0);
		Sleep(30);
		Clear_Car(position, car_y0);
	}
	Draw_Car(position, car_y0);
	return position;
}

// 小车装货
void loading(int position)
{
	Draw_Materials(615 - 80 * (position - 1), 226, 100);
}

// 小车卸货
void discharging(int position)
{
	// 清除小车
	Clear_Car(position, car_y0);

	// 绘制车架
	setlinestyle(PS_SOLID, 2);
	line(position, car_y0 + 30, position + 60, car_y0 + 30);
	line(position + 60, car_y0 + 30, position + 60, car_y0);

	// 车厢
	line(position - 21, car_y0 + 9, position, car_y0 + 30);
	line(position, car_y0 + 30, position + 42, car_y0 - 12);
	line(position + 42, car_y0 - 12, position + 21, car_y0 - 34);
	line(position + 21, car_y0 - 34, position - 21, car_y0 + 9);
	line(position + 40, car_y0 + 30, position + 24, car_y0 + 6);

	// 补上轮子
	setlinestyle(PS_SOLID, 1);
	setfillcolor(RGB(30, 144, 255));
	fillcircle(position + 17, car_y0 + 35, 8);
	fillcircle(position + 43, car_y0 + 35, 8);
}

// 小车卸货轨迹清除
void discharging_reset(int p)
{
	// 清除车厢
	POINT pts[] = {
		{p - 23, car_y0 + 9},
		{p - 1, car_y0 + 31},
		{p + 62, car_y0 + 31},
		{p + 62, car_y0 - 1},
		{p + 21, car_y0 - 36}
	};
	clearpolygon(pts, 5);

	// 清除小车
	Clear_Car(p, car_y0);

	// 绘制小车
	Draw_Car(p, car_y0);
}

void Draw_Materials(int x0, int y0, int number)
{
	srand((int)time(0));
	int count = 0;
	int x, y;
	while (count < number)
	{
		x = rand() % 16 - 8;
		y = rand() % 45;
		if ((y >= 45 / 8 * x) && (y >= -45 / 8 * x))
		{
			count++;
			putpixel(x0 + x, y0 + y, BLACK);
		}
	}
}

void Clear_Materials(int x0, int y0)
{
	POINT materials[] = { {x0, y0 - 2}, {x0 - 10, y0 + 46}, {x0 + 10, y0 + 46} };
	clearpolygon(materials, 3);
}

void Back(int p)
{
	for (int i = 0; i < abs(car_x0 - p); i += 3)
	{
		// 绘制小车
		Draw_Car(p + i, car_y0);
		Sleep(30);
		// 清除小车
		Clear_Car(p + i, car_y0);
	}
	Draw_Car(car_x0, car_y0);
}