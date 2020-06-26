
// PaintorDoc.h : CPaintorDoc 類別的介面
//


#pragma once

#include "ElementType.h"
#include "ElementColor.h"
#include "Element.h"
#include <string>
#include <memory>
#include <list>


typedef std::list<std::shared_ptr<CElement>>::const_iterator PaintorIterator;


class CPaintorDoc : public CDocument
{
protected: // 僅從序列化建立
	CPaintorDoc();
	DECLARE_DYNCREATE(CPaintorDoc)

// 屬性
public:

// 作業
public:
	

// 覆寫
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 程式碼實作
public:
	virtual ~CPaintorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void AddElement(std::shared_ptr<CElement>& pElement)
	{
		m_Paintor.push_back(pElement);
		UpdateAllViews(nullptr, 0, pElement.get());
		SetModifiedFlag();
	}
	void DeleteElement()
	{ 
		if (m_pSelected)
		{
			m_Paintor.remove(m_pSelected);
			m_pSelected.reset();
			UpdateAllViews(nullptr, 0, m_pSelected.get());
			SetModifiedFlag();
		}
	}

	void DrawElemt(CDC *pDC)
	{
		for (std::shared_ptr<CElement> pElement : m_Paintor)
			if (pDC->RectVisible(pElement->GetEnclosingRect()))
				pElement->Draw(pDC, m_pSelected);
	}

	void SetSelectElement(CDC *pDC, CPoint point);
	std::shared_ptr<CElement> GetSelectElement() const { return m_pSelected; }
	void RemoveSelectElement(CPoint point)
	{
		if (m_pSelected)
		{
			if (m_pSelected != FindElement(point))
				RemoveSelectElement();
		}
	}
	void RemoveSelectElement()
	{
		if (m_pSelected)
		{
			m_pSelected.reset();
			UpdateAllViews(nullptr, 0, m_pSelected.get());
		}
	}

//	PaintorIterator begin() const { return std::begin(m_Paintor); }
//	PaintorIterator end() const { return std::end(m_Paintor); }

//	std::list<std::shared_ptr<CElement>> GetElementList() const { return m_Paintor; }

	std::shared_ptr<CElement> FindElement(const CPoint& point) const
	{
		std::shared_ptr<CElement> ptr = nullptr;

		for (auto & pElement : m_Paintor)
		{
			if (pElement->GetEnclosingRect().PtInRect(point))
				ptr = pElement;
		}
		return ptr;
	}
	
	void SelectNextElement()
	{
		if (m_pSelected)
		{
			auto pOldSelected(m_pSelected);
			m_pSelected.reset();
			m_pSelected = FindNextElement(pOldSelected);
			UpdateAllViews(nullptr);
		}
		else if (m_Paintor.size() > 0)
		{
			m_pSelected = std::shared_ptr<CElement>(*m_Paintor.begin());
			UpdateAllViews(nullptr);
		}
	}

	void SendToBack()
	{
		if (m_pSelected)
		{
			m_Paintor.remove(m_pSelected);
			m_Paintor.push_front(m_pSelected);
			SetModifiedFlag();
		}
	}
	ElementType GetElementType()const { return m_Element; }
	COLORREF GetElementColor()const { return m_Color; }
	COLORREF GetElementFillColor()const { return m_FillColor; }
	int GetPenWidth() const { return m_PenWidth; }
	LOGFONT GetElementFont() const { return m_lfFont; }

protected:
	std::shared_ptr<CElement> FindNextElement(std::shared_ptr<CElement> & pElement) const
	{
		std::shared_ptr<CElement> ptr = nullptr;

		if (m_Paintor.size() > 0)
		{
			int findFlag = 0;

			for (auto & tempElement : m_Paintor)
			{
				if (findFlag == 1)
				{
					ptr = tempElement;
					break;
				}

				if (pElement.get() == tempElement.get())
					findFlag = 1;
			}

			if (ptr == nullptr)
				ptr = std::shared_ptr<CElement>(*m_Paintor.begin());
		}
		return ptr;
	}

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 為搜尋處理常式設定搜尋內容的 Helper 函式
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnColor();
	afx_msg void OnElementLine();
	afx_msg void OnElementRectangle();
	afx_msg void OnElementCircle();
	afx_msg void OnElementCurve();

protected:
	ElementType m_Element;         // Current element type
	COLORREF m_Color;              // Current drawing color
	COLORREF m_FillColor;          // Current filling color
	int m_PenWidth;                // Current pen width
	LOGFONT m_lfFont;              // Current font
	std::list<std::shared_ptr<CElement>> m_Paintor;     // A list containing the paintor
	std::shared_ptr<CElement> m_pSelected;

public:
	afx_msg void OnUpdateElementLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementRectangle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementCurve(CCmdUI *pCmdUI);
	afx_msg void OnPenWidth();
	afx_msg void OnElementText();
	afx_msg void OnUpdateElementText(CCmdUI *pCmdUI);
	afx_msg void OnFillcolor();
	afx_msg void OnPenType();
	afx_msg void OnSelect();
	afx_msg void OnUpdateSelect(CCmdUI *pCmdUI);
};
