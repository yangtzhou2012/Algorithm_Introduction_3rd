#pragma once


// CBinaryHeapView

#include <sstream>
#include "MaxPriorityQueue.h"

using namespace std;

class CBinaryHeapView : public CWnd
{
	DECLARE_DYNAMIC(CBinaryHeapView)

public:
	CBinaryHeapView();
	virtual ~CBinaryHeapView();

	void ResetScrollRange();

protected:
	DECLARE_MESSAGE_MAP()

private:
	static const int m_TreeNodeWidth = 48;
	static const int m_TreeNodeHeight = 48;
	static const int m_FontHeight = 20;
	template <typename T> CSize GetPaintSize(const MaxPriorityQueue<T> &queue);
	template <typename T> void Paint(const MaxPriorityQueue<T> &queue, CDC &dc);

public:
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

template <typename T>
CSize CBinaryHeapView::GetPaintSize(const MaxPriorityQueue<T> &queue)
{
	int h = -1;
	for (int i = 0; i < queue.size(); i = i*2 + 1)
		h++;

	int w = 0;
	if (h >= 0)
	{
		w = 1;
		for (int i = 0; i < h; ++i)
			w *= 2;
	}

	return CSize(w*m_TreeNodeWidth, (h+1)*m_TreeNodeHeight);
}

template <typename T>
void CBinaryHeapView::Paint(const MaxPriorityQueue<T> &queue, CDC &dc)
{
	CRect wndRect;
	GetClientRect(wndRect);
	CRgn rgn;
	rgn.CreateRectRgn(wndRect.left, wndRect.top, wndRect.right, wndRect.bottom);
	dc.SelectClipRgn(&rgn, RGN_COPY);
	dc.FillSolidRect(wndRect, RGB(255, 255, 255));

	CSize paintSize = GetPaintSize(queue);
	int dx = GetScrollPos(SB_HORZ);
	int dy = GetScrollPos(SB_VERT);

	if (paintSize.cx <= wndRect.Width())
		dx = -(wndRect.Width()-paintSize.cx)/2;

	CFont font;
	font.CreateFont(m_FontHeight, 0, 000, 000, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_TT_ALWAYS, PROOF_QUALITY, VARIABLE_PITCH|FF_ROMAN, CString("Courier New"));
	CFont *pOldFont = dc.SelectObject(&font);
	int oldTextAlign = dc.SetTextAlign(TA_BOTTOM|TA_CENTER);

	int floorStart = 1;
	int paintIntervalX = paintSize.cx;
	int paintBaseX = paintSize.cx/2 - dx;
	int paintBaseY = (m_TreeNodeHeight+m_FontHeight)/2 - dy;
	int paintNodeX = paintBaseX;

	for (int i = 0; i < queue.size(); ++i)
	{
		ostringstream is;
		is << queue[i];
		CString str(is.str().c_str());
		dc.TextOut(paintNodeX, paintBaseY, str);

		if (i > 0)
		{
			dc.MoveTo(paintNodeX, paintBaseY-m_FontHeight-2);
			if ((i&1) == 1)
				dc.LineTo(paintNodeX+paintIntervalX/2-2, paintBaseY-m_TreeNodeHeight);
			else
				dc.LineTo(paintNodeX-paintIntervalX/2+2, paintBaseY-m_TreeNodeHeight);
		}

		paintNodeX += paintIntervalX;

		if (i == floorStart - 1)
		{
			floorStart = floorStart*2 + 1;
			paintIntervalX /= 2;
			paintBaseX -= paintIntervalX/2;
			paintBaseY += m_TreeNodeHeight;
			paintNodeX = paintBaseX;
		}
	}

	dc.SetTextAlign(oldTextAlign);
	dc.SelectObject(pOldFont);
}
