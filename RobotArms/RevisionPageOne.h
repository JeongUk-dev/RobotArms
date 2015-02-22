#pragma once
#include "Resource.h"


// CRevisionPageOne 대화 상자입니다.

class CRevisionPageOne : public CPropertyPage
{
	DECLARE_DYNAMIC(CRevisionPageOne)

public:
	CRevisionPageOne();
	virtual ~CRevisionPageOne();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LOCATION_REVISION_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	UINT m_radio;
	afx_msg void RadioCtrl(UINT ID);
};
