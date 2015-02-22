// SettingPageTwo.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RobotArms.h"
#include "SettingPageTwo.h"
#include "afxdialogex.h"
#include "RobotArmsDlg.h"
#include "MyButton.h"
#include "MyInverseKinematic.h"
// CSettingPageTwo 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSettingPageTwo, CPropertyPage)

CSettingPageTwo::CSettingPageTwo()
	: CPropertyPage(CSettingPageTwo::IDD)
{
	m_psp.dwFlags ^= PSP_HASHELP;	
	// 위치 설정 마법사가 나타날 때 로봇의 초기 위치 좌표값
	m_intEdit_x = 170000;	// x : 170.000
	ArmData.x_coord = (float)m_intEdit_x / 1000.0F;
	m_intEdit_y = 10000;	// y : 10.000
	ArmData.y_coord = (float)m_intEdit_y / 1000.0F;
	m_intEdit_z = 0;		// z : 0
	ArmData.z_coord = (float)m_intEdit_z / 1000.0F;
	m_intEdit_GRIP_ANGLE = -20;
	ArmData.gripper_angle = (float)m_intEdit_GRIP_ANGLE;
}

CSettingPageTwo::~CSettingPageTwo()
{

}

void CSettingPageTwo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SETTING_EDIT_X, m_intEdit_x);
	DDX_Text(pDX, IDC_SETTING_EDIT_Y, m_intEdit_y);
	DDX_Text(pDX, IDC_SETTING_EDIT_Z, m_intEdit_z);
	DDX_Text(pDX, IDC_EDIT_GRIP_ANGLE, m_intEdit_GRIP_ANGLE);
	DDX_Control(pDX, IDC_SETTING_SLIDER_Y, m_SliderCtrl_Y);
	DDX_Control(pDX, IDC_SETTING_SLIDER_X, m_SliderCtrl_X);
	DDX_Control(pDX, IDC_SETTING_SLIDER_Z, m_SliderCtrl_Z);
	DDX_Control(pDX, IDC_SETTING_EDIT_X, m_EditCtrl_X);
	DDX_Control(pDX, IDC_SETTING_EDIT_Y, m_EditCtrl_Y);
	DDX_Control(pDX, IDC_SETTING_EDIT_Z, m_EditCtrl_Z);
	DDX_Control(pDX, IDC_EDIT_GRIP_ANGLE, m_ctrlEdit_GRIP_ANGLE);
	DDX_Control(pDX, IDC_SPIN_GRIP, m_spinGripAngle);
}


BEGIN_MESSAGE_MAP(CSettingPageTwo, CPropertyPage)
	ON_WM_HSCROLL()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_GRIP, &CSettingPageTwo::OnDeltaposSpinGrip)
	ON_EN_CHANGE(IDC_SETTING_EDIT_X, &CSettingPageTwo::OnChangeSettingEditX)
	ON_EN_CHANGE(IDC_SETTING_EDIT_Y, &CSettingPageTwo::OnChangeSettingEditY)
	ON_EN_CHANGE(IDC_SETTING_EDIT_Z, &CSettingPageTwo::OnChangeSettingEditZ)
END_MESSAGE_MAP()


// CSettingPageTwo 메시지 처리기입니다.
BOOL CSettingPageTwo::OnSetActive()
{
	GetParent()->SetWindowText("위치설정 마법사 - Step 2");
	CPropertySheet *p_sheet = (CPropertySheet *)GetParent();
	ASSERT_KINDOF(CPropertySheet, p_sheet);
	p_sheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);

	return CPropertyPage::OnSetActive();
}


BOOL CSettingPageTwo::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// x, y, z 축에 대한 슬라이더 컨트롤 범위 설정
	m_SliderCtrl_X.SetRange(130000, 300000);	// x : 130.000 ~ 300.000
	m_SliderCtrl_X.SetPos((int)((ArmData.x_coord) * 1000));
	m_SliderCtrl_X.SetTicFreq(10000);

	m_SliderCtrl_Y.SetRange(-30000, 150000);			// y : -30.000 ~ 150.000
	m_SliderCtrl_Y.SetPos((int)((ArmData.y_coord) * 1000));
	m_SliderCtrl_Y.SetTicFreq(10000);

	m_SliderCtrl_Z.SetRange(-90000,90000);		// z : -90.000 ~ 90.000
	m_SliderCtrl_Z.SetPos((int)((ArmData.z_coord) * 1000));
	m_SliderCtrl_Z.SetTicFreq(10000);

	m_spinGripAngle.SetRange(90,-90);	// -90 ~ 90
	m_spinGripAngle.SetPos(ArmData.gripper_angle);

	m_strCoord_x.Format("%.3f",ArmData.x_coord);
	m_strCoord_y.Format("%.3f",ArmData.y_coord);
	m_strCoord_z.Format("%.3f",ArmData.z_coord);

	SetDlgItemText(IDC_SETTING_EDIT_X,m_strCoord_x);
	SetDlgItemText(IDC_SETTING_EDIT_Y,m_strCoord_y);
	SetDlgItemText(IDC_SETTING_EDIT_Z,m_strCoord_z);

	// 로봇을 설정하기 위한 위치(초기 위치)로 이동.
	set_Arm(ArmData.z_coord, ArmData.x_coord, ArmData.y_coord, ArmData.gripper_angle);


	return TRUE;  // return TRUE unless you set the focus to a control

}


void CSettingPageTwo::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	
	CRobotArmsDlg *pMain = (CRobotArmsDlg*)AfxGetApp()->GetMainWnd();

	if(pScrollBar != NULL)
	{
		if(pScrollBar->m_hWnd == m_SliderCtrl_X.m_hWnd)	// x 슬라이더 바
		{
			ArmData.x_coord = (float)m_SliderCtrl_X.GetPos() / 1000.0F;	// 현재 위치를 받아옴
			m_strCoord_x.Format("%.3f",ArmData.x_coord);				// 문자열로 변환
			SetDlgItemText(IDC_SETTING_EDIT_X,m_strCoord_x);			// 에딧 박스에 출력
		}
		else if(pScrollBar->m_hWnd == m_SliderCtrl_Y.m_hWnd)	// y 슬라이더 바
		{
			ArmData.y_coord = (float)m_SliderCtrl_Y.GetPos() / 1000.0F;
			m_strCoord_y.Format("%.3f",ArmData.y_coord);
			SetDlgItemText(IDC_SETTING_EDIT_Y,m_strCoord_y);
		}
		else if (pScrollBar->m_hWnd == m_SliderCtrl_Z.m_hWnd) // z 슬라이더 바
		{
			ArmData.z_coord = (float)m_SliderCtrl_Z.GetPos() / 1000.0F;
			m_strCoord_z.Format("%.3f",ArmData.z_coord);
			SetDlgItemText(IDC_SETTING_EDIT_Z,m_strCoord_z);
		}
	}
	set_Arm(ArmData.z_coord, ArmData.x_coord, ArmData.y_coord, ArmData.gripper_angle);	// 조정된 좌표로 로봇을 위치 시킴

	UpdateData(FALSE);
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CSettingPageTwo::OnDeltaposSpinGrip(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	pNMUpDown->iDelta = -pNMUpDown->iDelta;

	// 스핀 컨트롤에 따른 그립 값 설정
	if (pNMUpDown->iDelta > 0)
	{
		if( m_intEdit_GRIP_ANGLE >= 90 )
			return ;
		m_intEdit_GRIP_ANGLE++;
	} 
	else
	{
		if(m_intEdit_GRIP_ANGLE <= -90)
			return ;
		m_intEdit_GRIP_ANGLE--;
	}

	ArmData.gripper_angle = (float)m_intEdit_GRIP_ANGLE;
	CWnd *SpinEdit = m_spinGripAngle.GetBuddy();
	CString str;
	str.Format("%d",m_intEdit_GRIP_ANGLE);
	SpinEdit->SetWindowTextA(str);

	set_Arm(ArmData.z_coord, ArmData.x_coord, ArmData.y_coord, ArmData.gripper_angle);	// 설정한 그립 각도로 로봇을 이동 시킴

	*pResult = 0;
}


LRESULT CSettingPageTwo::OnWizardNext()
{
	CRobotArmsDlg *pMain = (CRobotArmsDlg*)AfxGetApp()->GetMainWnd();

	// 설정한 위치 좌표값을 임시 버튼에 저장.
	CMyButton *button = new CMyButton(ArmData.x_coord,ArmData.y_coord,ArmData.z_coord,ArmData.gripper_angle);
	pMain->MyButton = button;

	arm_park(); // 로봇팔 위치 초기로.
	return CPropertyPage::OnWizardNext();
}


void CSettingPageTwo::OnChangeSettingEditX()
{
	if(UpdateData(TRUE))
		m_SliderCtrl_X.SetPos((int)((ArmData.x_coord) * 1000));
}


void CSettingPageTwo::OnChangeSettingEditY()
{
	if(UpdateData(TRUE))
		m_SliderCtrl_Y.SetPos((int)((ArmData.y_coord) * 1000));
}


void CSettingPageTwo::OnChangeSettingEditZ()
{
	if(UpdateData(TRUE))
		m_SliderCtrl_Z.SetPos((int)((ArmData.z_coord) * 1000));
}
