// RevisionPageOne.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RobotArms.h"
#include "RevisionPageOne.h"
#include "afxdialogex.h"
#include "RobotArmsDlg.h"

// CRevisionPageOne 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRevisionPageOne, CPropertyPage)

CRevisionPageOne::CRevisionPageOne()
	: CPropertyPage(CRevisionPageOne::IDD)
{
	m_psp.dwFlags ^= PSP_HASHELP;	// 도움말 버튼 제거
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


// CRevisionPageOne 메시지 처리기입니다.


BOOL CRevisionPageOne::OnSetActive()
{
	GetParent()->SetWindowText("위치보정 마법사 - Step 1");	// 마법사 첫 페이지의 타이틀
	CPropertySheet *p_sheet = (CPropertySheet *)GetParent();
	p_sheet->SetWizardButtons(PSWIZB_NEXT);	// 마법사 버튼 설정

	return CPropertyPage::OnSetActive();
}

// 마법사의 다음 버튼을 누를 때 수정할 버튼을 설정.
LRESULT CRevisionPageOne::OnWizardNext()	
{
	CRobotArmsDlg *pMain = (CRobotArmsDlg *)AfxGetApp()->GetMainWnd();	// 프로그램의 메인 핸들을 가져옴

	switch(m_radio)	// 보정할 버튼을 선택
	{
		case 0:	// 홈
			if(pMain->m_btn_home.x_coord==NULL)
			{
				AfxMessageBox(_T("버튼이 설정되지 않았습니다."));
				return -1;
			} else pMain->ButtonFlag=0;
			break;
		case 1:	// 네비
			if(pMain->m_btn_navi.x_coord==NULL)
			{
				AfxMessageBox(_T("버튼이 설정되지 않았습니다."));
				return -1;
			} else pMain->ButtonFlag=1;
			break;
		case 2:	// 맵
			if(pMain->m_btn_map.x_coord==NULL)
			{
				AfxMessageBox(_T("버튼이 설정되지 않았습니다."));
				return -1;
			} else pMain->ButtonFlag=2;
			break;
		case 3:	// 데스티네이션
			if(pMain->m_btn_dest.x_coord==NULL)
			{
				AfxMessageBox(_T("버튼이 설정되지 않았습니다."));
				return -1;
			} else pMain->ButtonFlag=3;
			break;
		case 4:	// 클리메이트
			if(pMain->m_btn_climate.x_coord==NULL)
			{
				AfxMessageBox(_T("버튼이 설정되지 않았습니다."));
				return -1;
			} else pMain->ButtonFlag=4;
			break;
		case 5:	// 오디오
			if(pMain->m_btn_audio.x_coord==NULL)
			{
				AfxMessageBox(_T("버튼이 설정되지 않았습니다."));
				return -1;
			} else pMain->ButtonFlag=5;
			break;
		case 6:	// 디엠비
			if(pMain->m_btn_dmb.x_coord==NULL)
			{
				AfxMessageBox(_T("버튼이 설정되지 않았습니다."));
				return -1;
			} else pMain->ButtonFlag=6;
			break;
		case 7:	// 메뉴
			if(pMain->m_btn_menu.x_coord==NULL)
			{
				AfxMessageBox(_T("버튼이 설정되지 않았습니다."));
				return -1;
			} else pMain->ButtonFlag=7;
			break;
		case 8:	// 인포
			if(pMain->m_btn_info.x_coord==NULL)
			{
				AfxMessageBox(_T("버튼이 설정되지 않았습니다."));
				return -1;
			} else pMain->ButtonFlag=8;
			break;
		case 9:	// 디스플레이
			if(pMain->m_btn_disp.x_coord==NULL)
			{
				AfxMessageBox(_T("버튼이 설정되지 않았습니다."));
				return -1;
			} else pMain->ButtonFlag=9;
			break;
		case 10:	// 스크롤 업
			if(pMain->m_btn_scroll_up.x_coord==NULL)
			{
				AfxMessageBox(_T("버튼이 설정되지 않았습니다."));
				return -1;
			} else pMain->ButtonFlag=10;
			break;
		case 11:	// 스크롤 다운
			if(pMain->m_btn_scroll_down.x_coord==NULL)
			{
				AfxMessageBox(_T("버튼이 설정되지 않았습니다."));
				return -1;
			} else pMain->ButtonFlag=11;
			break;
		default:	// 아무 버튼을 선택하지 않았을 때.
			AfxMessageBox(_T("버튼을 선택하지 않았습니다."));
			return -1;
			break;
	}

	return CPropertyPage::OnWizardNext();
}


void CRevisionPageOne::RadioCtrl(UINT ID)
{
	UpdateData(TRUE);

}
