#pragma once
#include "Resource.h"


// CRevisionPageOne ��ȭ �����Դϴ�.

class CRevisionPageOne : public CPropertyPage
{
	DECLARE_DYNAMIC(CRevisionPageOne)

public:
	CRevisionPageOne();
	virtual ~CRevisionPageOne();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LOCATION_REVISION_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	UINT m_radio;
	afx_msg void RadioCtrl(UINT ID);
};
