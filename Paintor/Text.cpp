#include "stdafx.h"
#include "Text.h"


IMPLEMENT_SERIAL(CText, CElement, VERSION_NUMBER)

CText::CText()
{
}


CText::CText(const CPoint& start, const CPoint& end, const CString & aString, COLORREF color, COLORREF fillColor, const LOGFONT& lfFont)
	: CElement(start, color, fillColor)
{
	memcpy(&m_lfFont, &lfFont, sizeof(LOGFONT));

	m_String = aString;

	m_EnclosingRect = CRect(start, end);
	m_EnclosingRect.NormalizeRect();
}

CText::~CText()
{
}

void CText::Draw(CDC* pDC, std::shared_ptr<CElement> pElement)
{
	CFont font;

	font.CreatePointFontIndirect(&m_lfFont);
	CFont* pOldFont = pDC->SelectObject(&font);

	pDC->SetTextColor(this == pElement.get() ? SELECT_COLOR : m_Color);
	pDC->SetBkMode(TRANSPARENT);
	pDC->ExtTextOut(m_StartPoint.x, m_StartPoint.y, 0, nullptr, m_String, nullptr);
	pDC->SelectObject(pOldFont);
}

void CText::Move(const CSize & aSize)
{
	m_StartPoint += aSize;
	m_EnclosingRect += aSize;
}

void CText::Serialize(CArchive & ar)
{
	CElement::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_String
			<< *m_lfFont.lfFaceName
			<< m_lfFont.lfWeight
			<< m_lfFont.lfWidth
			<< m_lfFont.lfHeight
			<< m_lfFont.lfEscapement
			<< m_lfFont.lfUnderline
			<< m_lfFont.lfItalic
			<< m_lfFont.lfStrikeOut
			<< m_lfFont.lfCharSet;		
	}
	else
	{
		ar >> m_String
			>> *m_lfFont.lfFaceName
			>> m_lfFont.lfWeight
			>> m_lfFont.lfWidth
			>> m_lfFont.lfHeight
			>> m_lfFont.lfEscapement
			>> m_lfFont.lfUnderline
			>> m_lfFont.lfItalic
			>> m_lfFont.lfStrikeOut
			>> m_lfFont.lfCharSet;	
	}
}