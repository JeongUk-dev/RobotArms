#pragma once
#include "Resource.h"


// CSettingPageThree 대화 상자입니다.

class CSettingPageThree : public CPropertyPage
{
	DECLARE_DYNAMIC(CSettingPageThree)

public:
	CSettingPageThree();
	virtual ~CSettingPageThree();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETTING_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
};
