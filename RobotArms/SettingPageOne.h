#pragma once
#include "Resource.h"


// CSettingPageOne ��ȭ �����Դϴ�.

class CSettingPageOne : public CPropertyPage
{
	DECLARE_DYNAMIC(CSettingPageOne)

public:
	CSettingPageOne();
	virtual ~CSettingPageOne();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETTING_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	UINT m_radio;
	afx_msg void RadioCtrl(UINT ID);
};
