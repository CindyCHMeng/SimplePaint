
// ChildFrm.cpp : CChildFrame ���O����@
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

// CChildFrame �غc/�Ѻc

CChildFrame::CChildFrame()
{
	// TODO:  �b���[�J������l�Ƶ{���X
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �b���g�ѭק� CREATESTRUCT cs �F��ק�������O�μ˦����ت�
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame �E�_

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

// CChildFrame �T���B�z�`��


void CChildFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��

	CMDIChildWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
