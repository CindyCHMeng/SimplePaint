
// PaintorDoc.cpp : CPaintorDoc 類別的實作
//

#include "stdafx.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "Paintor.h"
#endif

#include "PaintorDoc.h"

#include <propkey.h>
#include "PenDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPaintorDoc

IMPLEMENT_DYNCREATE(CPaintorDoc, CDocument)

BEGIN_MESSAGE_MAP(CPaintorDoc, CDocument)
	ON_COMMAND(ID_COLOR, &CPaintorDoc::OnColor)
	ON_COMMAND(ID_ELEMENT_LINE, &CPaintorDoc::OnElementLine)
	ON_COMMAND(ID_ELEMENT_RECTANGLE, &CPaintorDoc::OnElementRectangle)
	ON_COMMAND(ID_ELEMENT_CIRCLE, &CPaintorDoc::OnElementCircle)
	ON_COMMAND(ID_ELEMENT_CURVE, &CPaintorDoc::OnElementCurve)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_LINE, &CPaintorDoc::OnUpdateElementLine)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_RECTANGLE, &CPaintorDoc::OnUpdateElementRectangle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CIRCLE, &CPaintorDoc::OnUpdateElementCircle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CURVE, &CPaintorDoc::OnUpdateElementCurve)
	ON_COMMAND(ID_PEN_WIDTH, &CPaintorDoc::OnPenWidth)
	ON_COMMAND(ID_ELEMENT_TEXT, &CPaintorDoc::OnElementText)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_TEXT, &CPaintorDoc::OnUpdateElementText)
	ON_COMMAND(ID_FILLCOLOR, &CPaintorDoc::OnFillcolor)
	ON_COMMAND(ID_PEN_TYPE, &CPaintorDoc::OnPenType)
	ON_COMMAND(ID_SELECT, &CPaintorDoc::OnSelect)
	ON_UPDATE_COMMAND_UI(ID_SELECT, &CPaintorDoc::OnUpdateSelect)
END_MESSAGE_MAP()


// CPaintorDoc 建構/解構

CPaintorDoc::CPaintorDoc()
	: m_Element(ElementType::LINE), m_Color(0), m_PenWidth(0), m_FillColor(0), m_pSelected(nullptr)
{
	memset(&m_lfFont, 0x00, sizeof(m_lfFont));

	lstrcpy(m_lfFont.lfFaceName, _T("Calibri"));
	m_lfFont.lfWeight = 700;
	m_lfFont.lfWidth = 20;
	m_lfFont.lfHeight = -500;
	m_lfFont.lfEscapement = 0;
	m_lfFont.lfUnderline = FALSE;
	m_lfFont.lfItalic = FALSE;
	m_lfFont.lfStrikeOut = FALSE;
	m_lfFont.lfCharSet = GB2312_CHARSET;
}

CPaintorDoc::~CPaintorDoc()
{
}

BOOL CPaintorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此加入重新初始化程式碼
	// (SDI 文件會重用此文件)

	return TRUE;
}




// CPaintorDoc 序列化

void CPaintorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_Color
			<< m_FillColor
			<< static_cast<int> (m_Element)
			<< m_PenWidth
			<< *m_lfFont.lfFaceName
			<< m_lfFont.lfWeight
			<< m_lfFont.lfWidth
			<< m_lfFont.lfHeight
			<< m_lfFont.lfEscapement
			<< m_lfFont.lfUnderline
			<< m_lfFont.lfItalic
			<< m_lfFont.lfStrikeOut
			<< m_lfFont.lfCharSet;

		ar << m_Paintor.size();

		for (auto & pElement : m_Paintor)
			ar << pElement.get();
	}
	else
	{
		int elementType(0);
		size_t elementCount(0);

		ar >> m_Color
			>> m_FillColor
			>> elementType
			>> m_PenWidth
			>> *m_lfFont.lfFaceName
			>> m_lfFont.lfWeight
			>> m_lfFont.lfWidth
			>> m_lfFont.lfHeight
			>> m_lfFont.lfEscapement
			>> m_lfFont.lfUnderline
			>> m_lfFont.lfItalic
			>> m_lfFont.lfStrikeOut
			>> m_lfFont.lfCharSet
			>> elementCount;

		m_Element = static_cast<ElementType> (elementType);
		

		CElement * pElement;
		for (size_t i = 0; i < elementCount; i++)
		{
			ar >> pElement;
			m_Paintor.push_back(std::shared_ptr<CElement>(pElement));
		}
	}
}

#ifdef SHARED_HANDLERS

// 縮圖的支援
void CPaintorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改這段程式碼以繪製文件的資料
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜尋處理常式的支援
void CPaintorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 設定來自文件資料的搜尋內容。
	// 內容部分應該以 ";" 隔開

	// 範例:     strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPaintorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPaintorDoc 診斷

#ifdef _DEBUG
void CPaintorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPaintorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPaintorDoc 命令


void CPaintorDoc::OnColor()
{
	CColorDialog DLG(m_Color);

	if (IDOK == DLG.DoModal())
	{
		m_Color = DLG.GetColor();
		SetModifiedFlag();
	}
}

void CPaintorDoc::OnElementLine()
{
	m_Element = ElementType::LINE;
	SetModifiedFlag();
}


void CPaintorDoc::OnElementRectangle()
{
	m_Element = ElementType::RECTANGLE;
	SetModifiedFlag();
}


void CPaintorDoc::OnElementCircle()
{
	m_Element = ElementType::CIRCLE;
	SetModifiedFlag();
}


void CPaintorDoc::OnElementCurve()
{
	m_Element = ElementType::CURVE;
	SetModifiedFlag();
}


void CPaintorDoc::OnUpdateElementLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::LINE);
}


void CPaintorDoc::OnUpdateElementRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::RECTANGLE);
}


void CPaintorDoc::OnUpdateElementCircle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::CIRCLE);
}


void CPaintorDoc::OnUpdateElementCurve(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::CURVE);
}


void CPaintorDoc::OnPenWidth()
{
	CPenDialog aDlg;

	aDlg.m_PenWidth = m_PenWidth;

	if (aDlg.DoModal() == IDOK)
	{
		m_PenWidth = aDlg.m_PenWidth;
		SetModifiedFlag();
	}
}


void CPaintorDoc::OnElementText()
{
	m_Element = ElementType::TEXT;
	SetModifiedFlag();
}


void CPaintorDoc::OnUpdateElementText(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::TEXT);
}


void CPaintorDoc::OnFillcolor()
{
	CColorDialog DLG(m_FillColor);

	if (IDOK == DLG.DoModal())
	{
		m_FillColor = DLG.GetColor();
		SetModifiedFlag();
	}
}


void CPaintorDoc::OnPenType()
{
	m_lfFont.lfHeight = -m_lfFont.lfHeight;
	m_lfFont.lfHeight /= 10;

	CFontDialog DLG(&m_lfFont);
	
	if (IDOK == DLG.DoModal())
	{
		DLG.GetCurrentFont(&m_lfFont);
		m_lfFont.lfHeight = -m_lfFont.lfHeight;
		m_lfFont.lfHeight *= 10;

		m_Color = DLG.GetColor();
		SetModifiedFlag();
	}
}


void CPaintorDoc::OnSelect()
{
	m_Element = ElementType::SELECT;
	SetModifiedFlag();
}


void CPaintorDoc::OnUpdateSelect(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::SELECT);
}

void CPaintorDoc::SetSelectElement(CDC *pDC, CPoint point)
{
	auto pOldSelected(m_pSelected);        // Copy previous

	m_pSelected = FindElement(point);

	if (m_pSelected != pOldSelected)
	{
		if (m_pSelected)
			UpdateAllViews(nullptr, 0, m_pSelected.get());
		if (pOldSelected)
			UpdateAllViews(nullptr, 0, pOldSelected.get());
	}
}