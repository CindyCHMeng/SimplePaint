
// PaintorView.cpp : CPaintorView 類別的實作
//

#include "stdafx.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "Paintor.h"
#endif

#include "PaintorDoc.h"
#include "PaintorView.h"
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Curve.h"
#include "Text.h"
#include "TextDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPaintorView

IMPLEMENT_DYNCREATE(CPaintorView, CScrollView)

BEGIN_MESSAGE_MAP(CPaintorView, CScrollView)
	// 標準列印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ELEMENT_MOVE, &CPaintorView::OnElementMove)
	ON_COMMAND(ID_ELEMENT_DELETE, &CPaintorView::OnElementDelete)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ELEMENT_SENDTOBACK, &CPaintorView::OnElementSendtoback)
	ON_WM_KEYDOWN()
	ON_REGISTERED_MESSAGE(WM_EDIT_ENTER, OnSetMessage)
END_MESSAGE_MAP()

// CPaintorView 建構/解構

CPaintorView::CPaintorView()
	: m_FirstPoint(CPoint(0, 0)), m_SecondPoint(CPoint(0, 0)), m_pTempElement(nullptr), /*m_pSelected(nullptr),*/ m_Text(nullptr), m_crtEditTextRect(0), 
	m_CursorPos(CPoint(0, 0)), m_FirstPos(CPoint(0, 0)), m_MoveMode(false), m_EditMode(0), m_SelectFlag(false)
{
	// TODO:  在此加入建構程式碼

}

CPaintorView::~CPaintorView()
{
}

BOOL CPaintorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CView::PreCreateWindow(cs);
}

// CPaintorView 描繪

void CPaintorView::OnDraw(CDC* pDC)
{
//	CDC m_dcMem;
//	CBitmap m_bmp;

	CPaintorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
//	m_dcMem.CreateCompatibleDC(pDC);
//	m_bmp.CreateCompatibleBitmap(pDC, 3000, 3000);
//	m_dcMem.SelectObject(&m_bmp);
//	m_dcMem.SetBkMode(RGB(255, 255, 255));

//	CRect rect;
//	pDC->GetClipBox(rect);
//	pDC->LPtoDP(rect);

	pDoc->DrawElemt(pDC);

/*	for (std::shared_ptr<CElement> pElement : pDoc->GetElementList() )
		if (pDC->RectVisible(pElement->GetEnclosingRect()))
			pElement->Draw(pDC, m_pSelected);*/

/*	for (auto iter = pDoc->begin(); iter != pDoc->end(); ++iter)
	{
		std::shared_ptr<CElement> pElement(*iter);

		if (pDC->RectVisible(pElement->GetEnclosingRect()))
			pElement->Draw(pDC, m_pSelected);
	}*/

//	pDC->BitBlt(0, 0, 3000, 3000, &m_dcMem, 0, 0, SRCCOPY);
}


// CPaintorView 列印

BOOL CPaintorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 預設的準備列印程式碼
	return DoPreparePrinting(pInfo);
}

void CPaintorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  加入列印前額外的初始設定
}

void CPaintorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  加入列印後的清除程式碼
}


// CPaintorView 診斷

#ifdef _DEBUG
void CPaintorView::AssertValid() const
{
	CView::AssertValid();
}

void CPaintorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaintorDoc* CPaintorView::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaintorDoc)));
	return (CPaintorDoc*)m_pDocument;
}
#endif //_DEBUG


// CPaintorView 訊息處理常式


void CPaintorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC aDC(this);
	OnPrepareDC(&aDC);
	aDC.DPtoLP(&point);
	CPaintorDoc * pDoc = GetDocument();
	
	if (m_MoveMode)
	{
		ExitMoveElementMode();

/*		m_MoveMode = false;
		pDoc->RemoveSelectElement();
		Invalidate();
		UpdateWindow();
		//pDoc->UpdateAllViews(nullptr, 0, pElement.get());
		pDoc->SetModifiedFlag();*/
	}
	else if (m_EditMode)
	{
		SetMassage();
	}
	else if (pDoc->GetElementType() == ElementType::TEXT)
	{
		m_Text = new CKeyEdit();

		aDC.LPtoDP(&point);

		m_crtEditTextRect.SetRect(point.x, point.y, point.x + 50, point.y + 30);

		m_Text->Create(ES_LEFT | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_WANTRETURN | ES_AUTOVSCROLL, m_crtEditTextRect, this, 0xff);
		m_Text->SetFocus();
		m_EditMode = true;

		Invalidate();
		UpdateWindow();
	}
/*	else if (pDoc->GetElementType() == ElementType::TEXT)
	{
		CTextDialog aDlg;

		if (aDlg.DoModal() == IDOK)
		{
			CClientDC pDC(this);
			CFont font;
			font.CreatePointFontIndirect(&pDoc->GetElementFont());

			pDC.SelectObject(font);
			CRect crtEditRect(0, 0, pDC.GetTextExtent(aDlg.m_TextString).cx *50, 30);
			pDC.DrawText(aDlg.m_TextString, crtEditRect, DT_WORDBREAK | DT_CALCRECT);

			std::shared_ptr<CElement> pTextElement = std::make_shared<CText>(point, point + CSize(crtEditRect.right - crtEditRect.left, -(crtEditRect.bottom - crtEditRect.top)), aDlg.m_TextString, static_cast<COLORREF>(pDoc->GetElementColor()), static_cast<COLORREF>(pDoc->GetElementColor()), static_cast<LOGFONT>(pDoc->GetElementFont()));
			pDoc->AddElement(pTextElement);

			Invalidate();
			UpdateWindow();
			pDoc->UpdateAllViews(nullptr, 0, pTextElement.get());
		}
	}*/
	else if (pDoc->GetElementType() == ElementType::SELECT)
	{
		std::shared_ptr<CElement> pElement = GetDocument()->GetSelectElement();

		if (pElement && (pElement == GetDocument()->FindElement(point)))
		{
			m_SelectFlag = true;
			OnElementMove();
		}
		else
			GetDocument()->SetSelectElement(&aDC, point);

		/*auto pOldSelected(m_pSelected);        // Copy previous
		m_pSelected = GetDocument()->FindElement(point);

		if (m_pSelected != pOldSelected)
		{
			if (m_pSelected)
				GetDocument()->UpdateAllViews(nullptr, 0, m_pSelected.get());
			if (pOldSelected)
				GetDocument()->UpdateAllViews(nullptr, 0, pOldSelected.get());
		}*/
	}
	else
	{
		m_FirstPoint = point;

		// Capture subsequent mouse message
		SetCapture();
	}
}


void CPaintorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// Stop capturing mouse message
	if (this == GetCapture())
		ReleaseCapture();

	if (m_pTempElement)
	{
		CRect aRect = m_pTempElement->GetEnclosingRect();
		
		GetDocument()->AddElement(m_pTempElement);

		CClientDC aDC(this);
		OnPrepareDC(&aDC);
		aDC.LPtoDP(aRect);
		InvalidateRect(aRect);
		m_pTempElement.reset();
	}
	else if (m_SelectFlag)
	{
		m_SelectFlag = false;
		ExitMoveElementMode();
	}
}


void CPaintorView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC aDC(this);
	OnPrepareDC(&aDC);
	aDC.DPtoLP(&point);

	if (m_MoveMode)
	{
		MoveElement(aDC, point);
	}
	else if ((nFlags & MK_LBUTTON) && (this == GetCapture()))
	{
		m_SecondPoint = point;
		
		if (m_pTempElement)
		{
			if (ElementType::CURVE == GetDocument()->GetElementType())
			{
				std::static_pointer_cast<CCurve>(m_pTempElement)->AddSegment(m_SecondPoint);
				m_pTempElement->Draw(&aDC);
				return;
			}
			else
			{
				// Redraw the old element so it disappears from the view
				aDC.SetROP2(R2_NOTXORPEN);
				m_pTempElement->Draw(&aDC);
			}
		}

		m_pTempElement.reset(CreateElement());
		m_pTempElement->Draw(&aDC);
	}
}

CElement* CPaintorView::CreateElement(void) const
{
	CPaintorDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	COLORREF color = static_cast<COLORREF> (pDoc->GetElementColor());
	COLORREF fillColor = static_cast<COLORREF> (pDoc->GetElementFillColor());
	int penWidth(pDoc->GetPenWidth());

	switch (pDoc->GetElementType())
	{
	case ElementType::LINE :
		return new CLine(m_FirstPoint, m_SecondPoint, color, fillColor, penWidth);

	case ElementType::RECTANGLE :
		return new CRectangle(m_FirstPoint, m_SecondPoint, color, fillColor, penWidth);

	case ElementType::CIRCLE :
		return new CCircle(m_FirstPoint, m_SecondPoint, color, fillColor, penWidth);

	case ElementType::CURVE :
		return new CCurve(m_FirstPoint, m_SecondPoint, color, fillColor, penWidth);

	default:
		AfxMessageBox(_T("Bad Element code"), MB_OK);
		AfxAbort();
		return nullptr;
	}
}

void CPaintorView::MoveElement(CClientDC & aDC, const CPoint & point)
{
	CSize distance = point - m_CursorPos;
	m_CursorPos = point;
	std::shared_ptr<CElement> selectElemnet = GetDocument()->GetSelectElement();

	if (selectElemnet)
	{
		CPaintorDoc * pDoc = GetDocument();
		pDoc->UpdateAllViews(this, 0L, selectElemnet.get());

		if (typeid(*(selectElemnet.get())) == typeid(CText))
		{
			CRect oldRect = selectElemnet->GetEnclosingRect();
			aDC.LPtoDP(oldRect);
			selectElemnet->Move(distance);
			oldRect.top -= 2;
			oldRect.bottom += 2;
			oldRect.left -= 2;
			oldRect.right += 2;
			InvalidateRect(&oldRect);
			selectElemnet->Draw(&aDC, selectElemnet);
		}
		else
		{
			aDC.SetROP2(R2_NOTXORPEN);
			selectElemnet->Draw(&aDC, selectElemnet);
			selectElemnet->Move(distance);
			selectElemnet->Draw(&aDC, selectElemnet);
		}
		
		pDoc->UpdateAllViews(this, 0, selectElemnet.get());
	}
}

void CPaintorView::ExitMoveElementMode()
{
	if (m_MoveMode)
	{
		m_MoveMode = false;
		GetDocument()->RemoveSelectElement();
		Invalidate();
		UpdateWindow();
		//pDoc->UpdateAllViews(nullptr, 0, pElement.get());
		GetDocument()->SetModifiedFlag();
	}
}

void CPaintorView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (pHint)
	{
		CClientDC aDC(this);
		OnPrepareDC(&aDC);

		CRect aRect = static_cast<CElement*>(pHint)->GetEnclosingRect();
		aDC.LPtoDP(aRect);
		InvalidateRect(aRect);
	}
	else
	{
		InvalidateRect(nullptr);
	}
}


void CPaintorView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize DocSize(3000, 3000);

	// Set mapping mode and document size
	SetScrollSizes(MM_LOENGLISH, DocSize);
}


void CPaintorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_CONTEXT_MENU);
	
	CMenu * pContext(nullptr);

	if (GetDocument()->GetSelectElement())
	{
		pContext = menu.GetSubMenu(0);
	}
	else
	{
		pContext = menu.GetSubMenu(1);

		// Check element menu items
		ElementType type = GetDocument()->GetElementType();
		menu.CheckMenuItem(ID_ELEMENT_LINE, (ElementType::LINE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_RECTANGLE, (ElementType::RECTANGLE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_CIRCLE, (ElementType::CIRCLE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_CURVE, (ElementType::CURVE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_TEXT, (ElementType::TEXT == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_SELECT, (ElementType::SELECT == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
	}
	ASSERT(pContext != nullptr);

	pContext->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}


void CPaintorView::OnElementMove()
{
	CClientDC aDC(this);
	OnPrepareDC(&aDC);
	GetCursorPos(&m_CursorPos);
	ScreenToClient(&m_CursorPos);
	aDC.DPtoLP(&m_CursorPos);
	m_FirstPos = m_CursorPos;
	m_MoveMode = true;
}


void CPaintorView::OnElementDelete()
{
	GetDocument()->DeleteElement();
}


void CPaintorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CClientDC aDC(this);
	OnPrepareDC(&aDC);

	if (m_MoveMode)
	{
		MoveElement(aDC, m_FirstPos);
		GetDocument()->RemoveSelectElement();
		GetDocument()->UpdateAllViews(nullptr);
	}
	else if (GetDocument()->GetElementType() == ElementType::SELECT)
	{
		aDC.DPtoLP(&point);

		GetDocument()->SetSelectElement(&aDC, point);
		
		/*auto pOldSelected(m_pSelected);        // Copy previous

		m_pSelected = GetDocument()->FindElement(point);

		if (m_pSelected != pOldSelected)
		{
			if (m_pSelected)
				GetDocument()->UpdateAllViews(nullptr, 0, m_pSelected.get());
			if (pOldSelected)
				GetDocument()->UpdateAllViews(nullptr, 0, pOldSelected.get());
		}*/
	}
	else
	{
		aDC.DPtoLP(&point);
		GetDocument()->RemoveSelectElement(point);

		/*if (m_pSelected != GetDocument()->FindElement(point))
		{
			m_pSelected.reset();
			GetDocument()->UpdateAllViews(nullptr);
		}*/
	}
}


void CPaintorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_MoveMode)
	{
		m_MoveMode = false;
	}
	else
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}
}


void CPaintorView::OnElementSendtoback()
{
	GetDocument()->SendToBack();
}


void CPaintorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CClientDC aDC(this);
	OnPrepareDC(&aDC);
	/*std::shared_ptr<CElement> pElement = nullptr;

	if (GetDocument()->GetElementList().size() > 0)
		pElement = std::shared_ptr<CElement>(*GetDocument()->GetElementList().begin());*/

	switch (nChar)
	{
		case VK_TAB:
			GetDocument()->SelectNextElement();
			break;

		case VK_LEFT:
		case VK_RIGHT:
		case VK_UP:
		case VK_DOWN:
			MoveElementByKB(nChar);
			break;
		case VK_DELETE:
			OnElementDelete();
			break;

		default:
			break;
	}
	
	//CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

LRESULT CPaintorView::OnSetMessage(WPARAM wParam, LPARAM lParam)
{
	SetMassage();

	return 0;
}

void CPaintorView::SetMassage()
{
	if (m_EditMode)
	{
		CClientDC aDC(this);
		CString inputString;
		CPaintorDoc * pDoc = GetDocument();

		OnPrepareDC(&aDC);
		m_EditMode = false;
		aDC.DPtoLP(&m_crtEditTextRect);
		m_Text->GetWindowText(inputString);

		if (inputString.GetLength() > 0)
		{
			std::shared_ptr<CElement> pTextElement = std::make_shared<CText>(m_crtEditTextRect.TopLeft(), m_crtEditTextRect.BottomRight(), inputString, static_cast<COLORREF>(pDoc->GetElementColor()), static_cast<COLORREF>(pDoc->GetElementColor()), static_cast<LOGFONT>(pDoc->GetElementFont()));
			pDoc->AddElement(pTextElement);

			Invalidate();
			UpdateWindow();
			pDoc->UpdateAllViews(nullptr, 0, pTextElement.get());
		}

		delete m_Text;
	}
}

void CPaintorView::MoveElementByKB(UINT nChar)
{
	std::shared_ptr<CElement> selectElemnet = GetDocument()->GetSelectElement();

	if (selectElemnet)
	{
		CClientDC aDC(this);
		OnPrepareDC(&aDC);
		CSize direction(0, 0);

		switch (nChar)
		{
			case VK_LEFT:
				direction.cx -= 2;
				break;

			case VK_RIGHT:
				direction.cx += 2;
				break;

			case VK_UP:
				direction.cy += 2;
				break;

			case VK_DOWN:
				direction.cy -= 2;
				break;

			default:
				break;
		}

		m_CursorPos = selectElemnet.get()->GetEnclosingRect().TopLeft();
		MoveElement(aDC, m_CursorPos + direction);
	}
}
