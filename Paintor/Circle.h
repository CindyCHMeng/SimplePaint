#pragma once
#include "Element.h"

class CCircle :
	public CElement
{
	DECLARE_SERIAL(CCircle)
public:
	CCircle(const CPoint& start, const CPoint& end, COLORREF color, COLORREF fillColor, int penWidth);
	~CCircle();
	
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override;
	virtual void Move(const CSize & aSize) override;
	virtual void Serialize(CArchive& ar) override;
	
protected:
	CPoint m_BottomRight;
	CCircle();
};

