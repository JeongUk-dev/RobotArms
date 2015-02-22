#pragma once


// CRevisionPageThree 대화 상자입니다.

class CRevisionPageThree : public CPropertyPage
{
	DECLARE_DYNAMIC(CRevisionPageThree)

public:
	CRevisionPageThree();
	virtual ~CRevisionPageThree();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LOCATION_REVISION_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
};
