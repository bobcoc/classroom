
// classroom.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CclassroomApp: 
// �йش����ʵ�֣������ classroom.cpp
//

class CclassroomApp : public CWinApp
{
public:
	CclassroomApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CclassroomApp theApp;