// MySlider.cpp : ���� �����Դϴ�.
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



// CMySlider �޽��� ó�����Դϴ�.


//���콺�� Ŭ���Ǿ��� ���
void CMySlider::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetThumbRect(&rect);
	if(rect.PtInRect(point)) //�簢�� ���� ������ Ȯ���ϴ� PtlnRect(point);
		m_bSelected = true; //�����̵��� �簢�� ���̶�� true
	else
		m_bSelected = false; //�����̵��� �簢�� ���̶�� false

	CSliderCtrl::OnMButtonDown(nFlags, point);
}


void CMySlider::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bSelected = false; //���콺���� ���� �������� false ó��
	int nPos = GetPos(); //��ġ ���� ������
	m_sliderCtrl->SetPos(nPos);

	CString str;
	str.Format(_T("%d"), nPos); //str.Fromat() �� �̿��Ͽ� int���� CString���� ����
	CSecondPage* pMain = (CSecondPage*)AfxGetMainWnd(); //main�� ���� �״�� ȣ�� ��
	pMain->m_strValue.SetString(str); //ȣ�� �Ͽ� m_strValue�� SetString�� �ϱ� ���ؼ�

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
		str.Format(_T("%d"), nPos); //str.Fromat() �� �̿��Ͽ� int���� CString���� ����
		CSecondPage* pMain = (CSecondPage*)AfxGetMainWnd(); //main�� ���� �״�� ȣ�� ��
		pMain->m_strValue.SetString(str); //ȣ�� �Ͽ� m_strValue�� SetString�� �ϱ� ���ؼ�
	}

	CSliderCtrl::OnMouseMove(nFlags, point);


	void CMySlider::setMySlider(CSliderCtrl* m_pSliderCtrl)
	{
		m_sliderCtrl = m_pSliderCtrl;
	}

}