// MySlider.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RobotArms.h"
#include "MySlider.h"

#include "SecondPage.h"

// CMySlider

IMPLEMENT_DYNAMIC(CMySlider, CSliderCtrl)

CMySlider::CMySlider()
{

}

CMySlider::~CMySlider()
{
}


BEGIN_MESSAGE_MAP(CMySlider, CSliderCtrl)
END_MESSAGE_MAP()



// CMySlider 메시지 처리기입니다.


//마우스가 클릭되었을 경우
void CMySlider::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetThumbRect(&rect);
	if(rect.PtInRect(point)) //사각형 안의 값인지 확인하는 PtlnRect(point);
		m_bSelected = true; //슬라이드의 사각형 안이라면 true
	else
		m_bSelected = false; //슬라이드의 사각형 밖이라면 false

	CSliderCtrl::OnMButtonDown(nFlags, point);
}


void CMySlider::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bSelected = false; //마우스에서 손이 떨어지면 false 처리
	int nPos = GetPos(); //위치 값을 가져옴
	m_sliderCtrl->SetPos(nPos);

	CString str;
	str.Format(_T("%d"), nPos); //str.Fromat() 을 이용하여 int값을 CString으로 변경
	CSecondPage* pMain = (CSecondPage*)AfxGetMainWnd(); //main의 값을 그대로 호출 함
	pMain->m_strValue.SetString(str); //호출 하여 m_strValue에 SetString을 하기 위해서

	CSliderCtrl::OnLButtonUp(nFlags, point);
}


void CMySlider::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_bSelected && m_sliderCtrl)
	{
		int nPos = GetPos();
		m_sliderCtrl->SetPos(nPos);

		CString str;
		str.Format(_T("%d"), nPos); //str.Fromat() 을 이용하여 int값을 CString으로 변경
		CSecondPage* pMain = (CSecondPage*)AfxGetMainWnd(); //main의 값을 그대로 호출 함
		pMain->m_strValue.SetString(str); //호출 하여 m_strValue에 SetString을 하기 위해서
	}

	CSliderCtrl::OnMouseMove(nFlags, point);


	void CMySlider::setMySlider(CSliderCtrl* m_pSliderCtrl)
	{
		m_sliderCtrl = m_pSliderCtrl;
	}

}