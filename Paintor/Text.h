#pragma once
#include "Element.h"


class CText :
	public CElement
{
	DECLARE_SERIAL(CText)
public:
	~CText();
	CText(const CPoint & start, const CPoint & end, const CString & aString, COLORREF color, COLORREF fillColor, const LOGFONT& lfFont);
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override;
	virtual void Move(const CSize & aSize) override;
	virtual void Serialize(CArchive& ar) override;	

protected:
	CString m_String;
	LOGFONT m_lfFont;
	CText(void);
};

