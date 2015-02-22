#pragma once
#include "Resource.h"


// CSettingPageOne 대화 상자입니다.

class CSettingPageOne : public CPropertyPage
{
	DECLARE_DYNAMIC(CSettingPageOne)

public:
	CSettingPageOne();
	virtual ~CSettingPageOne();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETTING_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	UINT m_radio;
	afx_msg void RadioCtrl(UINT ID);
};
