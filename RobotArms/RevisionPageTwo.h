#pragma once
#include "afxwin.h"
//#include "afxcmn.h"


// CRevisionPageTwo ��ȭ �����Դϴ�.

class CRevisionPageTwo : public CPropertyPage
{
	DECLARE_DYNAMIC(CRevisionPageTwo)

public:
	CRevisionPageTwo();
	virtual ~CRevisionPageTwo();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LOCATION_REVISION_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	int m_intEdit_x;
	int m_intEdit_y;
	int m_intEdit_z;
	CSliderCtrl m_SliderCtrl_Y;
	CSliderCtrl m_SliderCtrl_X;
	CSliderCtrl m_SliderCtrl_Z;
	CEdit m_EditCtrl_X;
	CEdit m_EditCtrl_Y;
	CEdit m_EditCtrl_Z;
	CString m_strCoord_x;
	CString m_strCoord_y;
	CString m_strCoord_z;
	int m_intEdit_GRIP_ANGLE;
	CEdit m_ctrlEdit_GRIP_ANGLE;
	afx_msg void OnDeltaposSpinGrip(NMHDR *pNMHDR, LRESULT *pResult);
	CSpinButtonCtrl m_spinGripAngle;


	virtual LRESULT OnWizardNext();
	afx_msg void OnChangeRevisionEditX();
	afx_msg void OnChangeRevisionEditY();
	afx_msg void OnChangeRevisionEditZ();
};