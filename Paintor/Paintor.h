
// Paintor.h : Paintor ���ε{�����D���Y��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"       // �D�n�Ÿ�


// CPaintorApp:
// �аѾ\��@�����O�� Paintor.cpp
//

class CPaintorApp : public CWinApp
{
public:
	CPaintorApp();


// �мg
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �{���X��@
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPaintorApp theApp;
