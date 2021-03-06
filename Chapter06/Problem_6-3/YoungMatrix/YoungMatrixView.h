#pragma once


// CYoungMatrixView

class CYoungMatrixView : public CWnd
{
	DECLARE_DYNAMIC(CYoungMatrixView)

public:
	CYoungMatrixView();
	virtual ~CYoungMatrixView();

	void ResetScrollRange();

protected:
	DECLARE_MESSAGE_MAP()

	const static int blockSideLength = 32;
	const static int fontHeight = 16;

	void PaintYoungMatrix(CDC &dc);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
};


