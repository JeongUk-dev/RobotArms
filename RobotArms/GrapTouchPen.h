#pragma once
#include "Resource.h"


// CGrapTouchPen 대화 상자입니다.

class CGrapTouchPen : public CDialogEx
{
	DECLARE_DYNAMIC(CGrapTouchPen)

public:
	CGrapTouchPen(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGrapTouchPen();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GRAP_PEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit1();
	CEdit m_Servo4Edit;
	int m_intServo4;
	CSliderCtrl m_Servo4Slider;
};
