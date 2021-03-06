
// OptimalBSTDlg.cpp: 实现文件
//

#include <string>
#include <sstring>

#include "stdafx.h"
#include "OptimalBST.h"
#include "OptimalBSTDlg.h"
#include "afxdialogex.h"

#include "OptimalBinarySearchTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COptimalBSTDlg 对话框



COptimalBSTDlg::COptimalBSTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OPTIMALBST_DIALOG, pParent)
	, m_Probability(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_EditItem = -1;
	m_EditSubitem = -1;
}

void COptimalBSTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROBABILITY_LIST, m_ProbabilityList);
	DDX_Text(pDX, IDC_PROBABILITY_EDIT, m_Probability);
}

BEGIN_MESSAGE_MAP(COptimalBSTDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_GET_OPTIMAL_BST, &COptimalBSTDlg::OnGetOptimalBST)
	ON_BN_CLICKED(IDC_CLEAR, &COptimalBSTDlg::OnClear)
	ON_NOTIFY(NM_DBLCLK, IDC_PROBABILITY_LIST, &COptimalBSTDlg::OnDblclkProbabilityList)
	ON_EN_KILLFOCUS(IDC_PROBABILITY_EDIT, &COptimalBSTDlg::OnKillfocusProbabilityEdit)
	ON_NOTIFY(NM_RETURN, IDC_PROBABILITY_LIST, &COptimalBSTDlg::OnReturnProbabilityList)
END_MESSAGE_MAP()


template <typename T>
void COptimalBSTDlg::InitProbabilityList(T keyPR[], T dummyPR[], int n)
{
	unsigned long listCtrlStyle = m_ProbabilityList.GetExtendedStyle();
	listCtrlStyle |= (LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ProbabilityList.SetExtendedStyle(listCtrlStyle);

	m_ProbabilityList.InsertColumn(0, CString("Index"), LVCFMT_CENTER, 45);
	m_ProbabilityList.InsertColumn(1, CString("Key PR."), LVCFMT_CENTER, 64);
	m_ProbabilityList.InsertColumn(2, CString("Dummy PR."), LVCFMT_CENTER, 76);

	int i = 0;

	if(dummyPR != NULL && (n == 0 || (n > 0 && keyPR != NULL)))
	{
		for(i = 0; i <= n; ++i)
		{
			ostringstream oss;
			oss << i;
			m_ProbabilityList.InsertItem(i, CString(oss.str().c_str()));

			if(i > 0)
			{
				oss.str("");
				oss << keyPR[i-1];
				m_ProbabilityList.SetItemText(i, 1, CString(oss.str().c_str()));
			}

			oss.str("");
			oss << dummyPR[i];
			m_ProbabilityList.SetItemText(i, 2, CString(oss.str().c_str()));
		}
	}

	m_ProbabilityList.InsertItem(i, CString(""));
}


// COptimalBSTDlg 消息处理程序

BOOL COptimalBSTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PROBABILITY_EDIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PROBABILITY_EDIT)->ModifyStyle(ES_LEFT, ES_CENTER);

	m_OptimalBSTFigure.SubclassDlgItem(IDC_OPTIMAL_BST_FIGURE, this);

	double keyPR[] = {0.15, 0.1, 0.05, 0.1, 0.2};
	double dummyPR[] = {0.05, 0.1, 0.05, 0.05, 0.05, 0.1};
	InitProbabilityList(keyPR, dummyPR, (keyPR != NULL ? sizeof(keyPR)/sizeof(double) : 0));
	m_OptimalBST.build(keyPR, dummyPR, (keyPR != NULL ? sizeof(keyPR)/sizeof(double) : 0));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COptimalBSTDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COptimalBSTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL COptimalBSTDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void COptimalBSTDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;

	if(m_OptimalBSTFigure.m_hWnd)
	{
		m_OptimalBSTFigure.GetWindowRect(rect);
		ScreenToClient(rect);
		rect.bottom = cy-13;
		rect.right = cx-12;
		m_OptimalBSTFigure.MoveWindow(rect);
	}

	CWnd *pWnd = GetDlgItem(IDC_CLEAR);
	int button_top = 0;
	if(pWnd && pWnd->m_hWnd)
	{
		pWnd->GetWindowRect(rect);
		ScreenToClient(rect);
		int b = rect.bottom;
		rect.bottom = cy-12;
		rect.top += (rect.bottom - b);
		button_top = rect.top;
		pWnd->MoveWindow(rect);
	}

	pWnd = GetDlgItem(IDC_GET_OPTIMAL_BST);
	if(pWnd && pWnd->m_hWnd)
	{
		pWnd->GetWindowRect(rect);
		ScreenToClient(rect);
		int b = rect.bottom;
		rect.bottom = button_top-10;
		rect.top += (rect.bottom - b);
		button_top = rect.top;
		pWnd->MoveWindow(rect);
	}

	pWnd = GetDlgItem(IDC_PROBABILITY_LIST);
	if(pWnd && pWnd->m_hWnd)
	{
		pWnd->GetWindowRect(rect);
		ScreenToClient(rect);
		rect.bottom = button_top-9;
		pWnd->MoveWindow(rect);
	}

	Invalidate();
}

void COptimalBSTDlg::OnGetOptimalBST()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	int itemCount = m_ProbabilityList.GetItemCount()-1;
	double *keyPR = NULL;
	double *dummyPR = NULL;

	if(itemCount > 1)
		keyPR = new double[itemCount-1];

	if(itemCount > 0)
		dummyPR = new double[itemCount];

	for(int i = 0; i < itemCount; ++i)
	{
		if(i > 0)
			keyPR[i-1] = _wtof(m_ProbabilityList.GetItemText(i, 1));

		dummyPR[i] = _wtof(m_ProbabilityList.GetItemText(i, 2));
	}

	m_OptimalBST.build(keyPR, dummyPR, itemCount-1);

	if(keyPR != NULL) delete[] keyPR;
	if(dummyPR != NULL) delete[] dummyPR;

	Invalidate();
}

void COptimalBSTDlg::OnClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_OptimalBST.clear();
	m_OptimalBSTFigure.ResetScrollRange();

	m_ProbabilityList.DeleteAllItems();
	m_ProbabilityList.InsertItem(0, CString(""));

	Invalidate();
}

void COptimalBSTDlg::OnDblclkProbabilityList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	// TODO: 在此添加控件通知处理程序代码
	m_EditItem = pNMItemActivate->iItem;
	m_EditSubitem = pNMItemActivate->iSubItem;

	if(m_EditItem > -1 && m_EditSubitem > 0)
	{
		CRect editRect;
		m_ProbabilityList.GetSubItemRect(m_EditItem, m_EditSubitem, LVIR_BOUNDS, editRect);
		m_ProbabilityList.ClientToScreen(editRect);
		ScreenToClient(editRect);
		GetDlgItem(IDC_PROBABILITY_EDIT)->MoveWindow(editRect);
		GetDlgItem(IDC_PROBABILITY_EDIT)->ShowWindow(SW_SHOW);

		m_Probability = m_ProbabilityList.GetItemText(m_EditItem, m_EditSubitem);
		UpdateData(FALSE);

		GetDlgItem(IDC_PROBABILITY_EDIT)->SetFocus();
		((CEdit*)GetDlgItem(IDC_PROBABILITY_EDIT))->SetSel(-1);
	}

	*pResult = 0;
}

void COptimalBSTDlg::OnKillfocusProbabilityEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	int itemCount = m_ProbabilityList.GetItemCount();

	UpdateData();
	GetDlgItem(IDC_PROBABILITY_EDIT)->ShowWindow(SW_HIDE);
	m_ProbabilityList.SetItemText(m_EditItem, m_EditSubitem, m_Probability);

	if(m_EditItem == itemCount-1)
	{
		if(!m_ProbabilityList.GetItemText(m_EditItem, m_EditSubitem).IsEmpty())
		{
			ostringstream oss;
			oss << m_EditItem;
			m_ProbabilityList.SetItemText(m_EditItem, 0, CString(oss.str().c_str()));
			m_ProbabilityList.InsertItem(m_EditItem+1, CString(""));
		}
	}
	else if(m_EditItem == itemCount-2)
	{
		if(m_ProbabilityList.GetItemText(m_EditItem, 1).IsEmpty()
			&& m_ProbabilityList.GetItemText(m_EditItem, 2).IsEmpty())
		{
			m_ProbabilityList.SetItemText(m_EditItem, 0, CString(""));
			m_ProbabilityList.DeleteItem(m_EditItem+1);
		}
	}

	Invalidate();
}

void COptimalBSTDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(GetFocus() == GetDlgItem(IDC_PROBABILITY_EDIT))
	{
		int itemCount = m_ProbabilityList.GetItemCount();

		UpdateData();
		GetDlgItem(IDC_PROBABILITY_EDIT)->ShowWindow(SW_HIDE);
		m_ProbabilityList.SetItemText(m_EditItem, m_EditSubitem, m_Probability);

		if(m_EditItem == itemCount-1)
		{
			if(!m_ProbabilityList.GetItemText(m_EditItem, m_EditSubitem).IsEmpty())
			{
				ostringstream oss;
				oss << m_EditItem;
				m_ProbabilityList.SetItemText(m_EditItem, 0, CString(oss.str().c_str()));

				itemCount = m_ProbabilityList.GetItemCount();

				if(itemCount < m_EditItem+2)
				{
					m_ProbabilityList.InsertItem(m_EditItem+1, CString(""));
				}
				else
				{
					while(itemCount > m_EditItem+2)
						m_ProbabilityList.DeleteItem(--itemCount);
				}
			}
		}
		else if(m_EditItem == itemCount-2)
		{
			if(m_ProbabilityList.GetItemText(m_EditItem, 1).IsEmpty()
				&& m_ProbabilityList.GetItemText(m_EditItem, 2).IsEmpty())
			{
				m_ProbabilityList.SetItemText(m_EditItem, 0, CString(""));
				m_ProbabilityList.DeleteItem(m_EditItem+1);
			}
		}

		Invalidate();
	}

	//CDialog::OnOK();
}


void COptimalBSTDlg::OnReturnProbabilityList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
