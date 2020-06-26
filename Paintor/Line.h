#pragma once
#include "Element.h"

class CLine :
	public CElement
{
	DECLARE_SERIAL(CLine)
public:
	CLine(const CPoint& start, const CPoint& end, COLORREF color, COLORREF fillColor , int penWidth);
	virtual ~CLine();

	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override;
	virtual void Move(const CSize & aSize) override;
	virtual void Serialize(CArchive& ar) override;
	
protected:
	CPoint m_EndPoint;

protected:
	CLine();
};

