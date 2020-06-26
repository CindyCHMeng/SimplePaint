#pragma once
#include "Element.h"
#include <algorithm>


class CRectangle :
	public CElement
{
	DECLARE_SERIAL(CRectangle)
public:
	CRectangle(const CPoint& start, const CPoint& end, COLORREF color, COLORREF fillColor, int penWidth);
	virtual ~CRectangle();

	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override;
	virtual void Move(const CSize & aSize) override;
	virtual void Serialize(CArchive& ar) override;

protected:
	CPoint m_BottomRight;
	CRectangle();
};

