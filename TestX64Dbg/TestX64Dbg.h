// TestX64Dbg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestX64DbgApp:
// �йش����ʵ�֣������ TestX64Dbg.cpp
//

class CTestX64DbgApp : public CWinApp
{
public:
	CTestX64DbgApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestX64DbgApp theApp;