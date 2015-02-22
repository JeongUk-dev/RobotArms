// RevisionPageOne.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RobotArms.h"
#include "RevisionPageOne.h"
#include "afxdialogex.h"
#include "RobotArmsDlg.h"

// CRevisionPageOne ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRevisionPageOne, CPropertyPage)

CRevisionPageOne::CRevisionPageOne()
	: CPropertyPage(CRevisionPageOne::IDD)
{
	m_psp.dwFlags ^= PSP_HASHELP;	// ���� ��ư ����
}

CRevisionPageOne::~CRevisionPageOne()
{
}

void CRevisionPageOne::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_HOME, (int&)m_radio);
}


BEGIN_MESSAGE_MAP(CRevisionPageOne, CPropertyPage)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_HOME, IDC_RADIO_SCROLL_DOWN, RadioCtrl)
END_MESSAGE_MAP()


// CRevisionPageOne �޽��� ó�����Դϴ�.


BOOL CRevisionPageOne::OnSetActive()
{
	GetParent()->SetWindowText("��ġ���� ������ - Step 1");	// ������ ù �������� Ÿ��Ʋ
	CPropertySheet *p_sheet = (CPropertySheet *)GetParent();
	p_sheet->SetWizardButtons(PSWIZB_NEXT);	// ������ ��ư ����

	return CPropertyPage::OnSetActive();
}

// �������� ���� ��ư�� ���� �� ������ ��ư�� ����.
LRESULT CRevisionPageOne::OnWizardNext()	
{
	CRobotArmsDlg *pMain = (CRobotArmsDlg *)AfxGetApp()->GetMainWnd();	// ���α׷��� ���� �ڵ��� ������

	switch(m_radio)	// ������ ��ư�� ����
	{
		case 0:	// Ȩ
			if(pMain->m_btn_home.x_coord==NULL)
			{
				AfxMessageBox(_T("��ư�� �������� �ʾҽ��ϴ�."));
				return -1;
			} else pMain->ButtonFlag=0;
			break;
		case 1:	// �׺�
			if(pMain->m_btn_navi.x_coord==NULL)
			{
				AfxMessageBox(_T("��ư�� �������� �ʾҽ��ϴ�."));
				return -1;
			} else pMain->ButtonFlag=1;
			break;
		case 2:	// ��
			if(pMain->m_btn_map.x_coord==NULL)
			{
				AfxMessageBox(_T("��ư�� �������� �ʾҽ��ϴ�."));
				return -1;
			} else pMain->ButtonFlag=2;
			break;
		case 3:	// ����Ƽ���̼�
			if(pMain->m_btn_dest.x_coord==NULL)
			{
				AfxMessageBox(_T("��ư�� �������� �ʾҽ��ϴ�."));
				return -1;
			} else pMain->ButtonFlag=3;
			break;
		case 4:	// Ŭ������Ʈ
			if(pMain->m_btn_climate.x_coord==NULL)
			{
				AfxMessageBox(_T("��ư�� �������� �ʾҽ��ϴ�."));
				return -1;
			} else pMain->ButtonFlag=4;
			break;
		case 5:	// �����
			if(pMain->m_btn_audio.x_coord==NULL)
			{
				AfxMessageBox(_T("��ư�� �������� �ʾҽ��ϴ�."));
				return -1;
			} else pMain->ButtonFlag=5;
			break;
		case 6:	// �𿥺�
			if(pMain->m_btn_dmb.x_coord==NULL)
			{
				AfxMessageBox(_T("��ư�� �������� �ʾҽ��ϴ�."));
				return -1;
			} else pMain->ButtonFlag=6;
			break;
		case 7:	// �޴�
			if(pMain->m_btn_menu.x_coord==NULL)
			{
				AfxMessageBox(_T("��ư�� �������� �ʾҽ��ϴ�."));
				return -1;
			} else pMain->ButtonFlag=7;
			break;
		case 8:	// ����
			if(pMain->m_btn_info.x_coord==NULL)
			{
				AfxMessageBox(_T("��ư�� �������� �ʾҽ��ϴ�."));
				return -1;
			} else pMain->ButtonFlag=8;
			break;
		case 9:	// ���÷���
			if(pMain->m_btn_disp.x_coord==NULL)
			{
				AfxMessageBox(_T("��ư�� �������� �ʾҽ��ϴ�."));
				return -1;
			} else pMain->ButtonFlag=9;
			break;
		case 10:	// ��ũ�� ��
			if(pMain->m_btn_scroll_up.x_coord==NULL)
			{
				AfxMessageBox(_T("��ư�� �������� �ʾҽ��ϴ�."));
				return -1;
			} else pMain->ButtonFlag=10;
			break;
		case 11:	// ��ũ�� �ٿ�
			if(pMain->m_btn_scroll_down.x_coord==NULL)
			{
				AfxMessageBox(_T("��ư�� �������� �ʾҽ��ϴ�."));
				return -1;
			} else pMain->ButtonFlag=11;
			break;
		default:	// �ƹ� ��ư�� �������� �ʾ��� ��.
			AfxMessageBox(_T("��ư�� �������� �ʾҽ��ϴ�."));
			return -1;
			break;
	}

	return CPropertyPage::OnWizardNext();
}


void CRevisionPageOne::RadioCtrl(UINT ID)
{
	UpdateData(TRUE);

}
