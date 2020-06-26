#pragma once
#include <memory>
// CElement ©R¥O¥Ø¼Ð

static const COLORREF SELECT_COLOR(RGB(255, 0, 180));  // Highlight color
static const UINT VERSION_NUMBER = 1001;

class CElement : public CObject
{
	DECLARE_SERIAL(CElement)

protected :
	CPoint m_StartPoint;
	int m_PenWidth;
	COLORREF m_Color;
	COLORREF m_FillColor;
	CRect m_EnclosingRect;

public:
	virtual ~CElement();
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) {}
	virtual void Move(const CSize & aSize) {}
	virtual void Serialize(CArchive& ar) override;
	const CRect& GetEnclosingRect() const { return m_EnclosingRect; }
	
protected:
	CElement();
	CElement(const CPoint& start, COLORREF color, COLORREF fillColor, int penWidth = 1);
	void CreatePen(CPen & aPen, std::shared_ptr<CElement> pElement)
	{
		if (!aPen.CreatePen(PS_SOLID, m_PenWidth, this == pElement.get() ? SELECT_COLOR : m_Color))
		{
			AfxMessageBox(_T("Pen creation failed."), MB_OK);
			AfxAbort();
		}
	}
	void CreateBrush(CBrush & aBrush, std::shared_ptr<CElement> pElement)
	{
		if (!aBrush.CreateSolidBrush(this == pElement.get() ? SELECT_COLOR : m_FillColor))
		{
			AfxMessageBox(_T("Brush creation failed."), MB_OK);
			AfxAbort();
		}
	}
};


