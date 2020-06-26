
// PaintorDoc.cpp : CPaintorDoc ���O����@
//

#include "stdafx.h"
// SHARED_HANDLERS �i�H�w�q�b��@�w���B�Y�ϩM�j�M�z�����B�z�`����
// ATL �M�פ��A�ä��\�P�ӱM�צ@�Τ��{���X�C
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


// CPaintorDoc �غc/�Ѻc

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

	// TODO:  �b���[�J���s��l�Ƶ{���X
	// (SDI ���|���Φ����)

	return TRUE;
}




// CPaintorDoc �ǦC��

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

// �Y�Ϫ��䴩
void CPaintorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �ק�o�q�{���X�Hø�s��󪺸��
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

// �j�M�B�z�`�����䴩
void CPaintorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// �]�w�Ӧۤ���ƪ��j�M���e�C
	// ���e�������ӥH ";" �j�}

	// �d��:     strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CPaintorDoc �E�_

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


// CPaintorDoc �R�O


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