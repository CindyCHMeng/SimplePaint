
// MainFrm.h : CMainFrame 類別的介面
//

#pragma once

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// 屬性
public:

// 作業
public:

// 覆寫
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 程式碼實作
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控制列內嵌的成員
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 產生的訊息對應函式
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


