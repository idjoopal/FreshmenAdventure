// Festival.h : Festival ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CFestivalApp:
// �� Ŭ������ ������ ���ؼ��� Festival.cpp�� �����Ͻʽÿ�.
//

class CFestivalApp : public CWinApp
{
public:
	CFestivalApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFestivalApp theApp;