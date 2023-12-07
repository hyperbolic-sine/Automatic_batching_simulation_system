#pragma once
#include<graphics.h>
#include<math.h>
#include<conio.h>
#include<ctime>
#include<windows.h>

// С���������
#define Max_Load 100
// �ٶ�ϵ��
#define Speed_Coeffient 0.2
#define PI 3.1415926
// С����ʼλ��
#define car_x0 640
#define car_y0 294

// ���ڻ���Ԫ�ػ���
void Init_Windows();
// ���Ƶױ�ˮƽ��������
void Draw_Triangles(int x0, int y0, int weight, int height, int UpOrDown);
// �����϶�
void Draw_Mixer(int lines[][4], int Tra[3][2]);
// ����С��
void Draw_Car(int x0, int y0);
// С���켣���
void Clear_Car(int x0, int y0);
// Сǰ���˶�
int Run(int position, int length);
// С��װ��
void loading(int position);
// С��ж��
void discharging(int position);
// С��ж�����
void discharging_reset(int p);
// ����ԭ��
void Draw_Materials(int x0, int y0, int number);
// ԭ�Ϻۼ����
void Clear_Materials(int x0, int y0);
// С��ԭ·����
void Back(int p);