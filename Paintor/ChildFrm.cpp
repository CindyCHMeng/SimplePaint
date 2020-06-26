
// ChildFrm.cpp : CChildFrame 類別的實作
//

#include "stdafx.h"
#include "Paintor.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CChildFrame 建構/解構

CChildFrame::CChildFrame()
{
	// TODO:  在此加入成員初始化程式碼
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此經由修改 CREATESTRUCT cs 達到修改視窗類別或樣式的目的
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 診斷

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 訊息處理常式


void CChildFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	CMDIChildWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
