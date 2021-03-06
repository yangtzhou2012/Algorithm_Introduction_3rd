
// MinBitonicPathDlg.h: 头文件
//

#pragma once

#include "MinBitonicPathView.h"


// CMinBitonicPathDlg 对话框
class CMinBitonicPathDlg : public CDialogEx
{
// 构造
public:
	CMinBitonicPathDlg(CWnd* pParent = nullptr);	// 标准构造函数

	const CPoint* GetPoint(void) const { return m_Point; }
	const int* GetPointChain(void) const { return m_PointChain; }
	const int GetPointNum(void) const { return m_PointNum; }
	const double GetPathLength(void) const { return m_PathLength; }

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MINBITONICPATH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CMinBitonicPathView m_MinBitonicPathFigure;
	CListCtrl m_PointList;
	CString m_Coordinate;
	CPoint *m_Point;
	int *m_PointChain;
	int m_PointNum;
	double m_PathLength;
	int m_EditItem;
	int m_EditSubitem;

	void InitPointList(CPoint point[], int n);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDblclkPointList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKillfocusPointEdit();
	virtual void OnOK();
	afx_msg void OnGetMinBitonicPath();
	afx_msg void OnClear();
};
