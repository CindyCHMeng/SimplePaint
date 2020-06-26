#include "stdafx.h"
#include "KeyEdit.h"
#include "PaintorView.h"


CKeyEdit::CKeyEdit()
{
	
}


CKeyEdit::~CKeyEdit()
{
}
BEGIN_MESSAGE_MAP(CKeyEdit, CEdit)
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
END_MESSAGE_MAP()


void CKeyEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);

	if (nChar == VK_RETURN)
	{
		GetParent()->PostMessage(WM_EDIT_ENTER, 0, 0);
	}
	else if (GetParent()->IsKindOf(RUNTIME_CLASS(CPaintorView)))
	{
		CString inputString;
		CPaintorView * pPaintorView = (CPaintorView*)GetParent();			
		CRect currentRect = pPaintorView->GetCrtEidiTextRect();
		CClientDC pDC(this);

		GetWindowText(inputString);

		pDC.SelectObject(GetFont());

		CRect crtEditRect(0, 0, 3000, 3000);
		pDC.DrawText(inputString, crtEditRect, DT_WORDBREAK | DT_CALCRECT);
			
		if ((inputString.GetLength() > 0) && ((currentRect.Width() * 0.7 < crtEditRect.Width()) || ((currentRect.Width() * 0.7 > crtEditRect.Width()))))
		{
			int iWidth = crtEditRect.Width() / (inputString.GetLength() <= 0 ? 1 : inputString.GetLength());

			currentRect.right = currentRect.left + crtEditRect.Width() + iWidth * 2;
			MoveWindow(currentRect);
			pPaintorView->SetCrtEidiTextRect(currentRect);
		}
		else if (inputString.GetLength() == 0)
		{
			crtEditRect.SetRect(0, 0, 3000, 3000);
			pDC.DrawText(_T("A"), crtEditRect, DT_WORDBREAK | DT_CALCRECT);

			int iWidth = crtEditRect.Width();

			currentRect.right = currentRect.left + crtEditRect.Width() + iWidth;
			MoveWindow(currentRect);
			pPaintorView->SetCrtEidiTextRect(currentRect);
		}
	}	
}


int CKeyEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此加入特別建立的程式碼
	CPaintorView * pPaintorView = (CPaintorView*)GetParent();
	CRect currentRect = pPaintorView->GetCrtEidiTextRect();
	CClientDC pDC(this);

	m_myFont.CreatePointFontIndirect(&pPaintorView->GetCurrentFont());

	SetFont(&m_myFont);	

	pDC.SelectObject(GetFont());

	CRect crtEditRect(0, 0, 3000, 3000);
	pDC.DrawText(_T("A"), crtEditRect, DT_WORDBREAK | DT_CALCRECT);

	int iWidth = crtEditRect.Width();

	currentRect.right = currentRect.left + crtEditRect.Width() + iWidth;
	currentRect.bottom = (LONG)(currentRect.top + crtEditRect.Height()*1.3);
	MoveWindow(currentRect);
	pPaintorView->SetCrtEidiTextRect(currentRect);

	return 0;
}
