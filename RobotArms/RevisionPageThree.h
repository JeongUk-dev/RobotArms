#pragma once


// CRevisionPageThree ��ȭ �����Դϴ�.

class CRevisionPageThree : public CPropertyPage
{
	DECLARE_DYNAMIC(CRevisionPageThree)

public:
	CRevisionPageThree();
	virtual ~CRevisionPageThree();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LOCATION_REVISION_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
};
