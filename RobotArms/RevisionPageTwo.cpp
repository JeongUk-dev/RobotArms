// RevisionPageTwo.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RobotArms.h"
#include "RevisionPageTwo.h"
#include "afxdialogex.h"
#include "RobotArmsDlg.h"
#include "MyButton.h"
#include "MyInverseKinematic.h"
// CRevisionPageTwo 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRevisionPageTwo, CPropertyPage)

CRevisionPageTwo::CRevisionPageTwo()
	: CPropertyPage(CRevisionPageTwo::IDD)
{
	m_psp.dwFlags ^= PSP_HASHELP;	// 도움말 버튼 제거
}

CRevisionPageTwo::~CRevisionPageTwo()
{
}

void CRevisionPageTwo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_REVISION_EDIT_X, m_intEdit_x);
	DDX_Text(pDX, IDC_REVISION_EDIT_Y, m_intEdit_y);
	DDX_Text(pDX, IDC_REVISION_EDIT_Z, m_intEdit_z);
	DDX_Text(pDX, IDC_REVISION_EDIT_GRIP_ANGLE, m_intEdit_GRIP_ANGLE);
	DDX_Control(pDX, IDC_REVISION_SLIDER_Y, m_SliderCtrl_Y);
	DDX_Control(pDX, IDC_REVISION_SLIDER_X, m_SliderCtrl_X);
	DDX_Control(pDX, IDC_REVISION_SLIDER_Z, m_SliderCtrl_Z);
	DDX_Control(pDX, IDC_REVISION_EDIT_X, m_EditCtrl_X);
	DDX_Control(pDX, IDC_REVISION_EDIT_Y, m_EditCtrl_Y);
	DDX_Control(pDX, IDC_REVISION_EDIT_Z, m_EditCtrl_Z);
	DDX_Control(pDX, IDC_REVISION_EDIT_GRIP_ANGLE, m_ctrlEdit_GRIP_ANGLE);
	DDX_Control(pDX, IDC_SPIN_GRIP, m_spinGripAngle);
}


BEGIN_MESSAGE_MAP(CRevisionPageTwo, CPropertyPage)
	ON_WM_HSCROLL()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_GRIP, &CRevisionPageTwo::OnDeltaposSpinGrip)
	ON_EN_CHANGE(IDC_REVISION_EDIT_X, &CRevisionPageTwo::OnChangeRevisionEditX)
	ON_EN_CHANGE(IDC_REVISION_EDIT_Y, &CRevisionPageTwo::OnChangeRevisionEditY)
	ON_EN_CHANGE(IDC_REVISION_EDIT_Z, &CRevisionPageTwo::OnChangeRevisionEditZ)
END_MESSAGE_MAP()


// CRevisionPageTwo 메시지 처리기입니다.


BOOL CRevisionPageTwo::OnSetActive()
{
	GetParent()->SetWindowText("위치보정 마법사 - Step 2");	// 마법사의 타이틀 설정
	CPropertySheet *p_sheet = (CPropertySheet *)GetParent();
	ASSERT_KINDOF(CPropertySheet, p_sheet);
	p_sheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);	// 이전, 다음 버튼 생성

	return CPropertyPage::OnSetActive();
}


BOOL CRevisionPageTwo::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_SliderCtrl_X.SetRange(130000, 300000);	// x좌표 슬라이더 바의 범위 설정. 130.000 ~ 300.000
	m_SliderCtrl_X.SetTicFreq(10000);
	m_SliderCtrl_Y.SetRange(-30000, 150000);			// y좌표 슬라이더 바의 범위 설정. -30.000 ~ 150.000
	m_SliderCtrl_Y.SetTicFreq(10000);
	m_SliderCtrl_Z.SetRange(-90000,90000);		// z좌표 슬라이더 바의 범위 설정. -90.000 ~ 90.000
	m_SliderCtrl_Z.SetTicFreq(10000);
	m_spinGripAngle.SetRange(90,-90);			// 그립 각도 범위 설정 -90 ~ 90

	CRobotArmsDlg *pMain = (CRobotArmsDlg *)AfxGetApp()->GetMainWnd();
	// 수정할 버튼
	switch(pMain->ButtonFlag)	// 각 좌표 위치를 환산하여 각 컨트롤에 위치.
	{
		case 0: //home
			ArmData.x_coord = pMain->m_btn_home.x_coord;
			ArmData.y_coord = pMain->m_btn_home.y_coord;
			ArmData.z_coord = pMain->m_btn_home.z_coord;
			ArmData.gripper_angle = pMain->m_btn_home.grip_angle;

			break;

		case 1: //navi
			ArmData.x_coord = pMain->m_btn_navi.x_coord;
			ArmData.y_coord = pMain->m_btn_navi.y_coord;
			ArmData.z_coord = pMain->m_btn_navi.z_coord;
			ArmData.gripper_angle = pMain->m_btn_navi.grip_angle;
			break;
		case 2: //map
			ArmData.x_coord = pMain->m_btn_map.x_coord;
			ArmData.y_coord = pMain->m_btn_map.y_coord;
			ArmData.z_coord = pMain->m_btn_map.z_coord;
			ArmData.gripper_angle = pMain->m_btn_map.grip_angle;
			break;
		case 3: //dest
			ArmData.x_coord = pMain->m_btn_dest.x_coord;
			ArmData.y_coord = pMain->m_btn_dest.y_coord;
			ArmData.z_coord = pMain->m_btn_dest.z_coord;
			ArmData.gripper_angle = pMain->m_btn_dest.grip_angle;
			break;
		case 4: //climate
			ArmData.x_coord = pMain->m_btn_climate.x_coord;
			ArmData.y_coord = pMain->m_btn_climate.y_coord;
			ArmData.z_coord = pMain->m_btn_climate.z_coord;
			ArmData.gripper_angle = pMain->m_btn_climate.grip_angle;
			break;
		case 5: //audio
			ArmData.x_coord = pMain->m_btn_audio.x_coord;
			ArmData.y_coord = pMain->m_btn_audio.y_coord;
			ArmData.z_coord = pMain->m_btn_audio.z_coord;
			ArmData.gripper_angle = pMain->m_btn_audio.grip_angle;
			break;
		case 6: //dmb
			ArmData.x_coord = pMain->m_btn_dmb.x_coord;
			ArmData.y_coord = pMain->m_btn_dmb.y_coord;
			ArmData.z_coord = pMain->m_btn_dmb.z_coord;
			ArmData.gripper_angle = pMain->m_btn_dmb.grip_angle;
			break;
		case 7: //menu
			ArmData.x_coord = pMain->m_btn_menu.x_coord;
			ArmData.y_coord = pMain->m_btn_menu.y_coord;
			ArmData.z_coord = pMain->m_btn_menu.z_coord;
			ArmData.gripper_angle = pMain->m_btn_menu.grip_angle;
			break;
		case 8: //info
			ArmData.x_coord = pMain->m_btn_info.x_coord;
			ArmData.y_coord = pMain->m_btn_info.y_coord;
			ArmData.z_coord = pMain->m_btn_info.z_coord;
			ArmData.gripper_angle = pMain->m_btn_info.grip_angle;
			break;
		case 9: //disp
			ArmData.x_coord = pMain->m_btn_disp.x_coord;
			ArmData.y_coord = pMain->m_btn_disp.y_coord;
			ArmData.z_coord = pMain->m_btn_disp.z_coord;
			ArmData.gripper_angle = pMain->m_btn_disp.grip_angle;
			break;
		case 10: //scroll up
			ArmData.x_coord = pMain->m_btn_scroll_up.x_coord;
			ArmData.y_coord = pMain->m_btn_scroll_up.y_coord;
			ArmData.z_coord = pMain->m_btn_scroll_up.z_coord;
			ArmData.gripper_angle = pMain->m_btn_scroll_up.grip_angle;
			break;
		case 11: //scroll down
			ArmData.x_coord = pMain->m_btn_scroll_down.x_coord;
			ArmData.y_coord = pMain->m_btn_scroll_down.y_coord;
			ArmData.z_coord = pMain->m_btn_scroll_down.z_coord;
			ArmData.gripper_angle = pMain->m_btn_scroll_down.grip_angle;
			break;
		default:
			break;

	}
	m_SliderCtrl_X.SetPos((int)(ArmData.x_coord * 1000));
	m_SliderCtrl_Y.SetPos((int)(ArmData.y_coord * 1000));
	m_SliderCtrl_Z.SetPos((int)(ArmData.z_coord * 1000));
	m_spinGripAngle.SetPos(ArmData.gripper_angle);

	// 좌표값을 문자열로 변환
	m_strCoord_x.Format("%.3f", (ArmData.x_coord));
	m_strCoord_y.Format("%.3f", (ArmData.y_coord));
	m_strCoord_z.Format("%.3f", (ArmData.z_coord));

	// 에딧 박스에 값을 나타냄
	SetDlgItemText(IDC_REVISION_EDIT_X,m_strCoord_x);	
	SetDlgItemText(IDC_REVISION_EDIT_Y,m_strCoord_y);
	SetDlgItemText(IDC_REVISION_EDIT_Z,m_strCoord_z);

	// 설정되어 있는 위치로 로봇을 이동.
	set_Arm_Motion(ArmData.z_coord, ArmData.x_coord, ArmData.y_coord, ArmData.gripper_angle);

	
	return TRUE;
}


void CRevisionPageTwo::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CRobotArmsDlg *pMain = (CRobotArmsDlg *)AfxGetApp()->GetMainWnd();

	if (pScrollBar != NULL)
	{
		if(pScrollBar->m_hWnd == m_SliderCtrl_X.m_hWnd)	// x 슬라이더 바
		{
			ArmData.x_coord = (float)m_SliderCtrl_X.GetPos() / 1000.0F;	// 현재 위치를 받아옴
			m_strCoord_x.Format("%.3f",ArmData.x_coord);				// 문자열로 변환
			SetDlgItemText(IDC_REVISION_EDIT_X,m_strCoord_x);			// 에딧 박스에 출력
		}
		else if(pScrollBar->m_hWnd == m_SliderCtrl_Y.m_hWnd)	// y 슬라이더 바
		{
			ArmData.y_coord = (float)m_SliderCtrl_Y.GetPos() / 1000.0F;
			m_strCoord_y.Format("%.3f",ArmData.y_coord);
			SetDlgItemText(IDC_REVISION_EDIT_Y,m_strCoord_y);
		}
		else if (pScrollBar->m_hWnd == m_SliderCtrl_Z.m_hWnd) // z 슬라이더 바
		{
			ArmData.z_coord = (float)m_SliderCtrl_Z.GetPos() / 1000.0F;
			m_strCoord_z.Format("%.3f",ArmData.z_coord);
			SetDlgItemText(IDC_REVISION_EDIT_Z,m_strCoord_z);
		}
	}
	set_Arm(ArmData.z_coord, ArmData.x_coord, ArmData.y_coord, ArmData.gripper_angle);	// 조정된 좌표로 로봇을 위치 시킴

	//UpdateData(FALSE);
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
	
}


void CRevisionPageTwo::OnDeltaposSpinGrip(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	
	pNMUpDown->iDelta = -pNMUpDown->iDelta;

	// 스핀컨트롤에 의한 각도 조정
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
	
	ArmData.gripper_angle = (float)m_intEdit_GRIP_ANGLE;	// 그립 각도를 가져옴
	CWnd *SpinEdit = m_spinGripAngle.GetBuddy();
	CString str;
	str.Format("%d",m_intEdit_GRIP_ANGLE);	// 각도를 문자열로 변환
	SpinEdit->SetWindowTextA(str);			// 에딧 박스에 출력

	set_Arm(ArmData.z_coord, ArmData.x_coord, ArmData.y_coord, ArmData.gripper_angle);	// 각도 조정한 결과로 로봇을 위치 시킴

	*pResult = 0;
}

LRESULT CRevisionPageTwo::OnWizardNext(void)
{
	CRobotArmsDlg *pMain = (CRobotArmsDlg *)AfxGetApp()->GetMainWnd();

	
	CMyButton *button = new CMyButton(ArmData.x_coord, ArmData.y_coord, ArmData.z_coord, ArmData.gripper_angle);	
	pMain->MyButton = button;	// 현재 보정한 각 값들을 임시버튼에 저장

	arm_park();	// 로봇 초기 위치로
	return CPropertyPage::OnWizardNext();
}


void CRevisionPageTwo::OnChangeRevisionEditX()
{
	if(UpdateData(TRUE))
		m_SliderCtrl_X.SetPos((int)((ArmData.x_coord) * 1000));
}


void CRevisionPageTwo::OnChangeRevisionEditY()
{
	if(UpdateData(TRUE))
		m_SliderCtrl_Y.SetPos((int)((ArmData.y_coord) * 1000));
}


void CRevisionPageTwo::OnChangeRevisionEditZ()
{
	if(UpdateData(TRUE))
		m_SliderCtrl_Z.SetPos((int)((ArmData.z_coord) * 1000));
}
