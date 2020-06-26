#include "stdafx.h"
#include "Circle.h"
#include <cmath>


IMPLEMENT_SERIAL(CCircle, CElement, VERSION_NUMBER)

CCircle::CCircle()
{
}

CCircle::CCircle(const CPoint& start, const CPoint& end, COLORREF color, COLORREF fillColor, int penWidth)
	: CElement(start, color, fillColor, penWidth)
{
	// Calculate the radius using floating-point values
	long radius = static_cast<long> (sqrt(static_cast<double> ((end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y))));

	if (radius < 1L)
		radius = 1L;

	// Define left-top and right-bottom points of rectangle for MM_TEXT mode
	m_StartPoint = CPoint(start.x - radius, start.y - radius);
	m_BottomRight = CPoint(start.x + radius, start.y + radius);

	// Define the enclosing rectangle
	m_EnclosingRect = CRect(m_StartPoint, m_BottomRight);
	int width(penWidth == 0 ? 1 : penWidth);
	m_EnclosingRect.InflateRect(width, width);
}

CCircle::~CCircle()
{
}

void CCircle::Draw(CDC* pDC, std::shared_ptr<CElement> pElement)
{
	CPen aPen;
	CreatePen(aPen, pElement);
	CBrush aBrush;
	CreateBrush(aBrush, pElement);

	CPen * pOldPen = pDC->SelectObject(&aPen);
	CBrush * pOldBrush = pDC->SelectObject(&aBrush);
	//CBrush * pOldBrush = dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));

	pDC->Ellipse(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

void CCircle::Move(const CSize & aSize)
{
	m_StartPoint += aSize;
	m_BottomRight += aSize;
	m_EnclosingRect += aSize;
}

void CCircle::Serialize(CArchive & ar)
{
	CElement::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_BottomRight;
	}
	else
	{
		ar >> m_BottomRight;
	}
}