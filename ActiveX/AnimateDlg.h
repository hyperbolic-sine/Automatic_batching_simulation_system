#pragma once


// AnimateDlg 对话框

class AnimateDlg : public CDialog
{
	DECLARE_DYNAMIC(AnimateDlg)

public:
	AnimateDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AnimateDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ANIMATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

public:
	// 背景图
	CStatic m_picture;

	// 小车
	CStatic m_carn, m_cars;
	bool flag = true;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void CarMove(CRect& curCRT, int sleepTimes);
	// 小车当前位置
	int curr_location = 0;
	int time_counter = 0;

	// 装料次数
	int counter = 1;

	// 需要加料?
	bool Working = false;
	// 需要卸料?
	bool Unloading = false;
	int carMovePix[8] = { 624,566,496,426,356,286,216,156 };

	// 原料
	CStatic m_A, m_B, m_C, m_D, m_E, m_F, m_s;
	int materialPix[7] = { 593,523,453,383,313,243,125 };

	// 卸料、原料等的图片显示
	void pic_show(int pos);
	// 隐藏
	void pic_hide(int pos);
	// 按下停止配料按钮
	bool stopRun();
};
