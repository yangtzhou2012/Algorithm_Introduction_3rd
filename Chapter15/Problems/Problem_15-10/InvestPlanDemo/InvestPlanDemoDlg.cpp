
// InvestPlanDemoDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "InvestPlanDemo.h"
#include "InvestPlanDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CInvestPlanDemoDlg 对话框



CInvestPlanDemoDlg::CInvestPlanDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INVESTPLANDEMO_DIALOG, pParent)
	, m_Years(10)
	, m_Investments(8)
	, m_Fee1(200)
	, m_Fee2(400)
	, m_InitialMoney(10000)
	, m_TotalIncome(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInvestPlanDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_YEARS_EDIT, m_Years);
	DDV_MinMaxInt(pDX, m_Years, 0, INT_MAX);
	DDX_Text(pDX, IDC_INVESTMENTS_EDIT, m_Investments);
	DDV_MinMaxInt(pDX, m_Investments, 0, INT_MAX);
	DDX_Text(pDX, IDC_F1_EDIT, m_Fee1);
	DDV_MinMaxInt(pDX, m_Fee1, 0, INT_MAX);
	DDX_Text(pDX, IDC_F2_EDIT, m_Fee2);
	DDV_MinMaxInt(pDX, m_Fee2, 0, INT_MAX);
	DDX_Text(pDX, IDC_INITIAL_MONEY_EDIT, m_InitialMoney);
	DDV_MinMaxInt(pDX, m_InitialMoney, 0, INT_MAX);
	DDX_Text(pDX, IDC_TOTAL_INCOME_EDIT, m_TotalIncome);
	DDV_MinMaxDouble(pDX, m_TotalIncome, 0, DBL_MAX);
}

BEGIN_MESSAGE_MAP(CInvestPlanDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_SET_PARAMS, &CInvestPlanDemoDlg::OnSetParams)
	ON_BN_CLICKED(IDC_RANDOM_RATE, &CInvestPlanDemoDlg::OnRandomRate)
	ON_BN_CLICKED(IDC_INVEST_PLAN, &CInvestPlanDemoDlg::OnInvestPlan)
END_MESSAGE_MAP()


// CInvestPlanDemoDlg 消息处理程序

BOOL CInvestPlanDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_InvestPlanFigure.SubclassDlgItem(IDC_INVEST_PLAN_FIGURE, this);

	m_InvestPlan.SetParameters(m_Years, m_Investments, m_Fee1, m_Fee2, m_InitialMoney);
	m_InvestPlan.GenerateRandomRate();
	m_InvestPlan.CreateInvestPlan();
	m_TotalIncome = m_InvestPlan.GetTotalIncome();

	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CInvestPlanDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CInvestPlanDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CInvestPlanDemoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CInvestPlanDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;

	CWnd *pWnd = GetDlgItem(IDC_INVEST_PLAN_FIGURE);
	if (pWnd && pWnd->m_hWnd)
	{
		pWnd->GetWindowRect(rect);
		ScreenToClient(rect);
		rect.bottom = cy - 12;
		rect.right = cx - 13;
		pWnd->MoveWindow(rect);
	}
}

void CInvestPlanDemoDlg::OnSetParams()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_InvestPlan.SetParameters(m_Years, m_Investments, m_Fee1, m_Fee2, m_InitialMoney);
	m_TotalIncome = m_InvestPlan.GetTotalIncome();
	m_InvestPlanFigure.ResetScrollRange();
	UpdateData(FALSE);
	Invalidate();
}

void CInvestPlanDemoDlg::OnRandomRate()
{
	// TODO: 在此添加控件通知处理程序代码
	m_InvestPlan.GenerateRandomRate();
	m_TotalIncome = m_InvestPlan.GetTotalIncome();
	UpdateData(FALSE);
	Invalidate();
}

void CInvestPlanDemoDlg::OnInvestPlan()
{
	// TODO: 在此添加控件通知处理程序代码
	m_InvestPlan.CreateInvestPlan();
	m_TotalIncome = m_InvestPlan.GetTotalIncome();
	UpdateData(FALSE);
	Invalidate();
}
