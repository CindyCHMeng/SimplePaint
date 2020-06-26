#pragma once
#include "Element.h"
#include <vector>

class CCurve :
	public CElement
{
	DECLARE_SERIAL(CCurve)
public:
	CCurve(const CPoint& first, const CPoint& second, COLORREF color, COLORREF fillColor, int penWidth);
	~CCurve();

	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override;
	virtual void Move(const CSize & aSize) override;
	void AddSegment(const CPoint& point);     // Add a segment to the curve
	virtual void Serialize(CArchive& ar) override;

protected:
	std::vector<CPoint> m_Points;
	CCurve();
};

