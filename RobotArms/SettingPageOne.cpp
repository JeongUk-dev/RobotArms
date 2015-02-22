// SettingPageOne.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RobotArms.h"
#include "SettingPageOne.h"
#include "afxdialogex.h"
#include "RobotArmsDlg.h"

// CSettingPageOne ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSettingPageOne, CPropertyPage)

CSettingPageOne::CSettingPageOne()
	: CPropertyPage(CSettingPageOne::IDD)
{
	m_psp.dwFlags ^= PSP_HASHELP;	// ���� ��ư ����
}

CSettingPageOne::~CSettingPageOne()
{
}

void CSettingPageOne::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_HOME_RADIO, (int&)m_radio);
}


BEGIN_MESSAGE_MAP(CSettingPageOne, CPropertyPage)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_HOME_RADIO, IDC_MENU_RADIO, RadioCtrl)
END_MESSAGE_MAP()


// CSettingPageOne �޽��� ó�����Դϴ�.


BOOL CSettingPageOne::OnSetActive()
{
	GetParent()->SetWindowText("��ġ���� ������ - Step 1");	// ������ Ÿ��Ʋ ����
	CPropertySheet *p_sheet = (CPropertySheet *)GetParent();
	p_sheet->SetWizardButtons(PSWIZB_NEXT);	// ������ ��ư ����
		
	return CPropertyPage::OnSetActive();
}

LRESULT CSettingPageOne::OnWizardNext()
{
	CRobotArmsDlg *pMain = (CRobotArmsDlg*)AfxGetApp()->GetMainWnd();
	// ��ư ����
	switch (m_radio)
	{
		case 0:	// Ȩ
			pMain->ButtonFlag=0;
			break; 
		case 1:	// �׺�
			pMain->ButtonFlag=1;
			break; 
		case 2:	//����Ƽ���̼�
			pMain->ButtonFlag=2;
			break; 
		case 3:	// Ŭ������Ʈ
			pMain->ButtonFlag=3;
			break; 
		case 4:	// �����
			pMain->ButtonFlag=4;
			break; 
		case 5:	// �𿥺�
			pMain->ButtonFlag=5;
			break;
		case 6: // ����
			pMain->ButtonFlag=6;
			break;
		case 7:	// ���÷���
			pMain->ButtonFlag=7;
			break;
		case 8:	// ��ũ�� ��
			pMain->ButtonFlag=8;
			break;
		case 9:	// ��ũ�� �ٿ�
			pMain->ButtonFlag=9;
			break;
		case 10:// ��
			pMain->ButtonFlag=10;
			break;
		case 11:// �޴�
			pMain->ButtonFlag=11;
			break;
		default:
			AfxMessageBox(_T("��ư�� �������� �ʾҽ��ϴ�."));
			return -1;
			break;

	}
	return CPropertyPage::OnWizardNext();
}


void CSettingPageOne::RadioCtrl(UINT ID)
{
	UpdateData(TRUE);
}
