
// RobotArms.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "Resource.h"		// �� ��ȣ�Դϴ�.


// CRobotArmsApp:
// �� Ŭ������ ������ ���ؼ��� RobotArms.cpp�� �����Ͻʽÿ�.
//

class CRobotArmsApp : public CWinApp
{
public:
	CRobotArmsApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CRobotArmsApp theApp;