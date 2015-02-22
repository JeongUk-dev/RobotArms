// SettingPageOne.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RobotArms.h"
#include "SettingPageOne.h"
#include "afxdialogex.h"
#include "RobotArmsDlg.h"

// CSettingPageOne 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSettingPageOne, CPropertyPage)

CSettingPageOne::CSettingPageOne()
	: CPropertyPage(CSettingPageOne::IDD)
{
	m_psp.dwFlags ^= PSP_HASHELP;	// 도움말 버튼 제거
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


// CSettingPageOne 메시지 처리기입니다.


BOOL CSettingPageOne::OnSetActive()
{
	GetParent()->SetWindowText("위치설정 마법사 - Step 1");	// 마법사 타이틀 설정
	CPropertySheet *p_sheet = (CPropertySheet *)GetParent();
	p_sheet->SetWizardButtons(PSWIZB_NEXT);	// 마법사 버튼 설정
		
	return CPropertyPage::OnSetActive();
}

LRESULT CSettingPageOne::OnWizardNext()
{
	CRobotArmsDlg *pMain = (CRobotArmsDlg*)AfxGetApp()->GetMainWnd();
	// 버튼 선택
	switch (m_radio)
	{
		case 0:	// 홈
			pMain->ButtonFlag=0;
			break; 
		case 1:	// 네비
			pMain->ButtonFlag=1;
			break; 
		case 2:	//데스티네이션
			pMain->ButtonFlag=2;
			break; 
		case 3:	// 클리메이트
			pMain->ButtonFlag=3;
			break; 
		case 4:	// 오디오
			pMain->ButtonFlag=4;
			break; 
		case 5:	// 디엠비
			pMain->ButtonFlag=5;
			break;
		case 6: // 인포
			pMain->ButtonFlag=6;
			break;
		case 7:	// 디스플레이
			pMain->ButtonFlag=7;
			break;
		case 8:	// 스크롤 업
			pMain->ButtonFlag=8;
			break;
		case 9:	// 스크롤 다운
			pMain->ButtonFlag=9;
			break;
		case 10:// 맵
			pMain->ButtonFlag=10;
			break;
		case 11:// 메뉴
			pMain->ButtonFlag=11;
			break;
		default:
			AfxMessageBox(_T("버튼을 선택하지 않았습니다."));
			return -1;
			break;

	}
	return CPropertyPage::OnWizardNext();
}


void CSettingPageOne::RadioCtrl(UINT ID)
{
	UpdateData(TRUE);
}
