#pragma once
#include "Resource.h"


// CSettingPageThree ��ȭ �����Դϴ�.

class CSettingPageThree : public CPropertyPage
{
	DECLARE_DYNAMIC(CSettingPageThree)

public:
	CSettingPageThree();
	virtual ~CSettingPageThree();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETTING_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
};
