
// PaintorView.h : CPaintorView ���O������
//

#pragma once
#include "atltypes.h"
#include "Element.h"
#include "KeyEdit.h"
#include <string>
#include <iostream>
#include <memory>
#include "PaintorDoc.h"

class CPaintorView : public CScrollView
{
protected: // �ȱq�ǦC�ƫإ�
	CPaintorView();
	DECLARE_DYNCREATE(CPaintorView)

// �ݩ�
public:
	CPaintorDoc* GetDocument() const;

// �@�~
public:

// �мg
public:
	virtual void OnDraw(CDC* pDC);  // �мg�H�yø���˵�
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �{���X��@
public:
	virtual ~CPaintorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CRect GetCrtEidiTextRect() const { return m_crtEditTextRect; }
	void SetCrtEidiTextRect(CRect tempEditTextRect) { m_crtEditTextRect = tempEditTextRect; }
	LOGFONT GetCurrentFont() const { return GetDocument()->GetElementFont(); }

protected:
	CElement * CreateElement(void) const;
	void MoveElement(CClientDC & aDC, const CPoint & point);
	void ExitMoveElementMode();

// ���ͪ��T�������禡
protected:
	DECLARE_MESSAGE_MAP()
	
protected:

	CPoint m_FirstPoint;     // First point record for an element
	CPoint m_SecondPoint;    // Second point record for an element
	CPoint m_CursorPos;      // Cursor position
	CPoint m_FirstPos;       // Original position in a move
	std::shared_ptr<CElement> m_pTempElement;
	//std::shared_ptr<CElement> m_pSelected;         // Record element under the cursor
	CKeyEdit *m_Text;
	CRect m_crtEditTextRect;
	bool m_MoveMode;         // Move element flag
	bool m_EditMode;
	bool m_SelectFlag;
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	void SetMassage();
	void MoveElementByKB(UINT nChar);

public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnElementMove();
	afx_msg void OnElementDelete();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnElementSendtoback();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnSetMessage(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // PaintorView.cpp ������������
inline CPaintorDoc* CPaintorView::GetDocument() const
   { return reinterpret_cast<CPaintorDoc*>(m_pDocument); }
#endif

