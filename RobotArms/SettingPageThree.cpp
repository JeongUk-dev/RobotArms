// SettingPageThree.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RobotArms.h"
#include "SettingPageThree.h"
#include "afxdialogex.h"
#include "RobotArmsDlg.h"

// CSettingPageThree ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSettingPageThree, CPropertyPage)

CSettingPageThree::CSettingPageThree()
	: CPropertyPage(CSettingPageThree::IDD)
{
	m_psp.dwFlags ^= PSP_HASHELP;
}

CSettingPageThree::~CSettingPageThree()
{
}

void CSettingPageThree::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingPageThree, CPropertyPage)
END_MESSAGE_MAP()


// CSettingPageThree �޽��� ó�����Դϴ�.


BOOL CSettingPageThree::OnSetActive()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	GetParent()->SetWindowText("��ġ���� ������ - Step 3");
	CPropertySheet *p_sheet = (CPropertySheet *)GetParent();
	ASSERT_KINDOF(CPropertySheet, p_sheet);
	p_sheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);

	return CPropertyPage::OnSetActive();
}


BOOL CSettingPageThree::OnWizardFinish()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CRobotArmsDlg *pMain = (CRobotArmsDlg*)AfxGetApp()->GetMainWnd();
	
	// ������ ��ư
	switch (pMain->ButtonFlag)
	{
		case 0:	// Ȩ
			pMain->m_btn_home.x_coord = pMain->MyButton->x_coord;
			pMain->m_btn_home.y_coord = pMain->MyButton->y_coord;
			pMain->m_btn_home.z_coord = pMain->MyButton->z_coord;
			pMain->m_btn_home.grip_angle = pMain->MyButton->grip_angle;
			break;
		case 1:	// �׺�
			pMain->m_btn_navi.x_coord = pMain->MyButton->x_coord;
			pMain->m_btn_navi.y_coord = pMain->MyButton->y_coord;
			pMain->m_btn_navi.z_coord = pMain->MyButton->z_coord;
			pMain->m_btn_navi.grip_angle = pMain->MyButton->grip_angle;
			break;
		case 2:	// ����Ƽ���̼�
			pMain->m_btn_dest.x_coord = pMain->MyButton->x_coord;
			pMain->m_btn_dest.y_coord = pMain->MyButton->y_coord;
			pMain->m_btn_dest.z_coord = pMain->MyButton->z_coord;
			pMain->m_btn_dest.grip_angle = pMain->MyButton->grip_angle;
			break;
		case 3:	// Ŭ������Ʈ
			pMain->m_btn_climate.x_coord = pMain->MyButton->x_coord;
			pMain->m_btn_climate.y_coord = pMain->MyButton->y_coord;
			pMain->m_btn_climate.z_coord = pMain->MyButton->z_coord;
			pMain->m_btn_climate.grip_angle = pMain->MyButton->grip_angle;
			break;
		case 4:	// �����
			pMain->m_btn_audio.x_coord = pMain->MyButton->x_coord;
			pMain->m_btn_audio.y_coord = pMain->MyButton->y_coord;
			pMain->m_btn_audio.z_coord = pMain->MyButton->z_coord;
			pMain->m_btn_audio.grip_angle = pMain->MyButton->grip_angle;
			break;
		case 5:	// �𿥺�
			pMain->m_btn_dmb.x_coord = pMain->MyButton->x_coord;
			pMain->m_btn_dmb.y_coord = pMain->MyButton->y_coord;
			pMain->m_btn_dmb.z_coord = pMain->MyButton->z_coord;
			pMain->m_btn_dmb.grip_angle = pMain->MyButton->grip_angle;
			break;
		case 6:	// ����
			pMain->m_btn_info.x_coord = pMain->MyButton->x_coord;
			pMain->m_btn_info.y_coord = pMain->MyButton->y_coord;
			pMain->m_btn_info.z_coord = pMain->MyButton->z_coord;
			pMain->m_btn_info.grip_angle = pMain->MyButton->grip_angle;
			break;
		case 7:	// ���÷���
			pMain->m_btn_disp.x_coord = pMain->MyButton->x_coord;
			pMain->m_btn_disp.y_coord = pMain->MyButton->y_coord;
			pMain->m_btn_disp.z_coord = pMain->MyButton->z_coord;
			pMain->m_btn_disp.grip_angle = pMain->MyButton->grip_angle;
			break;
		case 8:	// ��ũ�� ��
			pMain->m_btn_scroll_up.x_coord = pMain->MyButton->x_coord;
			pMain->m_btn_scroll_up.y_coord = pMain->MyButton->y_coord;
			pMain->m_btn_scroll_up.z_coord = pMain->MyButton->z_coord;
			pMain->m_btn_scroll_up.grip_angle = pMain->MyButton->grip_angle;
			break;
		case 9:	// ��ũ�� �ٿ�
			pMain->m_btn_scroll_down.x_coord = pMain->MyButton->x_coord;
			pMain->m_btn_scroll_down.y_coord = pMain->MyButton->y_coord;
			pMain->m_btn_scroll_down.z_coord = pMain->MyButton->z_coord;
			pMain->m_btn_scroll_down.grip_angle = pMain->MyButton->grip_angle;
			break;
		case 10:// ��
			pMain->m_btn_map.x_coord = pMain->MyButton->x_coord;
			pMain->m_btn_map.y_coord = pMain->MyButton->y_coord;
			pMain->m_btn_map.z_coord = pMain->MyButton->z_coord;
			pMain->m_btn_map.grip_angle = pMain->MyButton->grip_angle;
			break;
		case 11:// �޴�
			pMain->m_btn_menu.x_coord = pMain->MyButton->x_coord;
			pMain->m_btn_menu.y_coord = pMain->MyButton->y_coord;
			pMain->m_btn_menu.z_coord = pMain->MyButton->z_coord;
			pMain->m_btn_menu.grip_angle = pMain->MyButton->grip_angle;
			break;
		default:
			AfxMessageBox("ERROR!");
			break;
	}



	return CPropertyPage::OnWizardFinish();
}
