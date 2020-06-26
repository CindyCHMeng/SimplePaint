// Element.cpp : 實作檔
//

#include "stdafx.h"
#include "Paintor.h"
#include "Element.h"


// CElement

IMPLEMENT_SERIAL(CElement, CObject, VERSION_NUMBER)

CElement::CElement()
{
}

CElement::CElement(const CPoint& start, COLORREF color, COLORREF fillColor, int penWidth) 
	: m_StartPoint(start), m_PenWidth(penWidth), m_Color(color), m_FillColor(fillColor)
{

}

CElement::~CElement()
{
}


// CElement 成員函式

void CElement::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_StartPoint
			<< m_PenWidth
			<< m_Color
			<< m_FillColor
			<< m_EnclosingRect;
	}
	else
	{
		ar >> m_StartPoint
			>> m_PenWidth
			>> m_Color
			>> m_FillColor
			>> m_EnclosingRect;
	}
}