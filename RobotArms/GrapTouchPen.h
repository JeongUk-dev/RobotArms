#pragma once
#include "Resource.h"


// CGrapTouchPen ��ȭ �����Դϴ�.

class CGrapTouchPen : public CDialogEx
{
	DECLARE_DYNAMIC(CGrapTouchPen)

public:
	CGrapTouchPen(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGrapTouchPen();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GRAP_PEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit1();
	CEdit m_Servo4Edit;
	int m_intServo4;
	CSliderCtrl m_Servo4Slider;
};
