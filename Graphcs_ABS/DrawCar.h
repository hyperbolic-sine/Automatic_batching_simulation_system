#pragma once
#include<graphics.h>
#include<math.h>
#include<conio.h>
#include<ctime>
#include<windows.h>

// 小车最大载重
#define Max_Load 100
// 速度系数
#define Speed_Coeffient 0.2
#define PI 3.1415926
// 小车初始位置
#define car_x0 640
#define car_y0 294

// 窗口基本元素绘制
void Init_Windows();
// 绘制底边水平的三角形
void Draw_Triangles(int x0, int y0, int weight, int height, int UpOrDown);
// 绘制料斗
void Draw_Mixer(int lines[][4], int Tra[3][2]);
// 绘制小车
void Draw_Car(int x0, int y0);
// 小车轨迹清除
void Clear_Car(int x0, int y0);
// 小前向车运动
int Run(int position, int length);
// 小车装货
void loading(int position);
// 小车卸货
void discharging(int position);
// 小车卸货完毕
void discharging_reset(int p);
// 绘制原料
void Draw_Materials(int x0, int y0, int number);
// 原料痕迹清除
void Clear_Materials(int x0, int y0);
// 小车原路返回
void Back(int p);