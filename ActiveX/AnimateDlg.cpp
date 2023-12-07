// AnimateDlg.cpp: 实现文件
//

#include "pch.h"
#include "ActiveX.h"
#include "AnimateDlg.h"
#include "afxdialogex.h"
#include "CPublic.h"

// AnimateDlg 对话框

IMPLEMENT_DYNAMIC(AnimateDlg, CDialog)

AnimateDlg::AnimateDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_ANIMATE, pParent)
{
}

AnimateDlg::~AnimateDlg()
{
}

void AnimateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AnimateDlg, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// AnimateDlg 消息处理程序

BOOL AnimateDlg::OnInitDialog()
{
	// TODO:  在此添加额外的初始化

	// 绘制背景图
	CRect rect(40, 120, 740, 420);
	m_picture.Create(L"XXX", WS_CHILD | WS_VISIBLE | SS_BITMAP, rect, this, 1000);
	HBITMAP hbitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));
	// 设置
	m_picture.SetBitmap(hbitmap);

	// 小车行驶图片加载
	HBITMAP carmap;
	carmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2));
	CRect rectcarn(carMovePix[0], 120 + 157, carMovePix[0] + 70, 323); //584,157
	m_carn.Create(L"3XXX", WS_CHILD | WS_VISIBLE | SS_BITMAP, rectcarn, this, 2000);
	m_carn.SetBitmap(carmap);

	// 小车卸料图片加载  !暂不显示!
	carmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3));
	CRect rectcars(carMovePix[7] - 24, 238, carMovePix[7] + 70, 323);
	m_cars.Create(L"3XXX", WS_CHILD | SS_BITMAP, rectcars, this, 3000);
	m_cars.SetBitmap(carmap);

	// 原料图片 加料  !暂不显示!
	HBITMAP materialmap_n;
	materialmap_n = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4));
	CRect rectA(materialPix[5], 219, materialPix[5] + 15, 263);
	CRect rectB(materialPix[4], 219, materialPix[4] + 15, 263);
	CRect rectC(materialPix[3], 219, materialPix[3] + 15, 263);
	CRect rectD(materialPix[2], 219, materialPix[2] + 15, 263);
	CRect rectE(materialPix[1], 219, materialPix[1] + 15, 263);
	CRect rectF(materialPix[0], 219, materialPix[0] + 15, 263);
	m_A.Create(L"4XXX", WS_CHILD | SS_BITMAP, rectA, this, 2000);
	m_B.Create(L"4XXX", WS_CHILD | SS_BITMAP, rectB, this, 2000);
	m_C.Create(L"4XXX", WS_CHILD | SS_BITMAP, rectC, this, 2000);
	m_D.Create(L"4XXX", WS_CHILD | SS_BITMAP, rectD, this, 2000);
	m_E.Create(L"4XXX", WS_CHILD | SS_BITMAP, rectE, this, 2000);
	m_F.Create(L"4XXX", WS_CHILD | SS_BITMAP, rectF, this, 2000);
	m_A.SetBitmap(materialmap_n);
	m_B.SetBitmap(materialmap_n);
	m_C.SetBitmap(materialmap_n);
	m_D.SetBitmap(materialmap_n);
	m_E.SetBitmap(materialmap_n);
	m_F.SetBitmap(materialmap_n);
	// 原料图片 卸料  !暂不显示!
	HBITMAP materialmap_s;
	materialmap_s = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5));
	CRect rectUn(materialPix[6], 307, materialPix[6] + 15, 351);
	m_s.Create(L"4XXX", WS_CHILD | SS_BITMAP, rectUn, this, 2000);
	m_s.SetBitmap(materialmap_s);

	return TRUE;
}

void AnimateDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (nIDEvent)
	{
	case WMUSER_UPDATEPIC_TIMERID:
		CRect curCRT;
		m_carn.GetClientRect(&curCRT);
		m_carn.ClientToScreen(curCRT);
		ScreenToClient(curCRT);

		// 装料次数限制
		if (counter == CPublic::totalTimes + 1)
		{
			// 小车停止运动
			KillTimer(WMUSER_UPDATEPIC_TIMERID);
		}

		// 正向行驶,并且移动到标记处
		int sleepTimes = 0;
		if (flag && (curCRT.left == carMovePix[curr_location]))
		{
			// 该位置需要装料
			if (CPublic::materials[curr_location - 1] != 0)
			{
				Working = true;
				sleepTimes = CPublic::materials[curr_location - 1] * 6;
				pic_show(curr_location - 1);
			}

			// 进入卸料区
			if (curr_location == 7)
			{
				Unloading = true;
				sleepTimes = CPublic::sum * 7;
				pic_show(curr_location - 1);
			}
		}
		CarMove(curCRT, sleepTimes);
	}

	CDialog::OnTimer(nIDEvent);
}

void AnimateDlg::CarMove(CRect& curCRT, int sleepTimes)
{
	// 加料中。。。
	if (Working)
	{
		time_counter++;
		m_carn.MoveWindow(curCRT.left, curCRT.top, curCRT.Width(), curCRT.Height(), TRUE);
		// 停留时间
		// 6 * CPublic::materials[curr_location - 1] * 20ms = CPublic::materials[curr_location - 1] * 120ms
		if (time_counter >= sleepTimes)
		{
			Working = false;
			time_counter = 0;
			pic_hide(curr_location - 1);
			// 往前走一步
			m_carn.MoveWindow(curCRT.left - 2, curCRT.top, curCRT.Width(), curCRT.Height(), TRUE);
		}
		return;
	}
	// 卸料中。。。
	if (Unloading)
	{
		time_counter++;
		// 停留时间
		// 7 * 100(kg) * 20ms = 14000ms = 14s
		if (time_counter >= sleepTimes)
		{
			time_counter = 0;
			pic_hide(curr_location - 1);

			// 卸料完毕，返回
			flag = false;
			Unloading = false;
		}
		return;
	}

	// 到达卸货点
	if (curCRT.left == carMovePix[7])
	{
		flag = false;
	}
	// 到达起始点
	if (curCRT.left >= carMovePix[0])
	{
		flag = true;
	}

	// 每次向左移动2个像素
	// 正向移动
	if (flag)
	{
		m_carn.MoveWindow(curCRT.left - 2, curCRT.top, curCRT.Width(), curCRT.Height(), TRUE);
	}
	else
	{
		m_carn.MoveWindow(curCRT.left + 4, curCRT.top, curCRT.Width(), curCRT.Height(), TRUE);
	}

	//  0	1	2	3	4	5	6	7
	// 624,566,496,426,356,286,216,156
	if (curCRT.left >= carMovePix[7] && curCRT.left <= carMovePix[7] + 24)
	{
		curr_location = 7;
	}
	else if (curCRT.left > carMovePix[0] - 24 && curCRT.left <= carMovePix[0])
	{
		curr_location = 0;
	}
	else
	{
		switch ((curCRT.left - carMovePix[7] - 24) / 70)
		{
		case 0:
			curr_location = 6;
			break;
		case 1:
			curr_location = 5;
			break;
		case 2:
			curr_location = 4;
			break;
		case 3:
			curr_location = 3;
			break;
		case 4:
			curr_location = 2;
			break;
		case 5:
			curr_location = 1;
			break;
		default:
			break;
		}
	}

	// 装料趟数
	if (flag && (curCRT.left == carMovePix[0]))
	{
		// 一趟计数
		counter++;
		CString str;
		if (counter <= CPublic::totalTimes)
		{
			str.Format(TEXT("第 %d 次配料, 共 %d 次"), counter, CPublic::totalTimes);
		}
		else
		{
			str.Format(TEXT("配料计划已完成!"));
		}
		GetDlgItem(IDC_STATIC_CTIMES)->SetWindowTextW(str);
	}
}

bool AnimateDlg::stopRun()
{
	// TODO: 在此添加控件通知处理程序代码
	// 小车停止运动
	if (curr_location == 7 || curr_location == 0)
	{
		KillTimer(WMUSER_UPDATEPIC_TIMERID);
		return true;
	}
	else
	{
		return false;
	}
}

void AnimateDlg::pic_show(int pos)
{
	switch (pos)
	{
		// F位置
	case 0:
		m_F.ShowWindow(SW_SHOW);
		break;
	case 1:
		m_E.ShowWindow(SW_SHOW);
		break;
	case 2:
		m_D.ShowWindow(SW_SHOW);
		break;
	case 3:
		m_C.ShowWindow(SW_SHOW);
		break;
	case 4:
		m_B.ShowWindow(SW_SHOW);
		break;
	case 5:
		m_A.ShowWindow(SW_SHOW);
		break;
	case 6:
		m_carn.ShowWindow(SW_HIDE);
		m_s.ShowWindow(SW_SHOW);
		m_cars.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
}

void AnimateDlg::pic_hide(int pos)
{
	switch (pos)
	{
		// F位置
	case 0:
		m_F.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_E.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_D.ShowWindow(SW_HIDE);
		break;
	case 3:
		m_C.ShowWindow(SW_HIDE);
		break;
	case 4:
		m_B.ShowWindow(SW_HIDE);
		break;
	case 5:
		m_A.ShowWindow(SW_HIDE);
		break;
	case 6:
		m_carn.ShowWindow(SW_SHOW);
		m_s.ShowWindow(SW_HIDE);
		m_cars.ShowWindow(SW_HIDE);
		break;
	default:
		break;
	}
}