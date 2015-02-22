
// RobotArmsDlg.cpp : 구현 파일
//
#include "stdafx.h"
#include "RobotArms.h"
#include "RobotArmsDlg.h"
#include "afxdialogex.h"
#include "SerialComDlg.h"
#include "SettingPageOne.h"
#include "SettingPageTwo.h"
#include "SettingPageThree.h"
#include "RevisionPageOne.h"
#include "RevisionPageTwo.h"
#include "RevisionPageThree.h"
#include "GrapTouchPen.h"
#include "MyInverseKinematic.h"
//#include "TEST.h"
//#include "MyButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.


	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRobotArmsDlg 대화 상자




CRobotArmsDlg::CRobotArmsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRobotArmsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CRobotArmsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_HOME, m_btn_home);
	DDX_Control(pDX, IDC_BTN_INFO, m_btn_info);
	DDX_Control(pDX, IDC_BTN_DEST, m_btn_dest);
	DDX_Control(pDX, IDC_BTN_DMB, m_btn_dmb);
	DDX_Control(pDX, IDC_BTN_DISP, m_btn_disp);
	DDX_Control(pDX, IDC_BTN_CLIMATE, m_btn_climate);
	DDX_Control(pDX, IDC_BTN_AUDIO, m_btn_audio);
	DDX_Control(pDX, IDC_BTN_NAVI, m_btn_navi);
	DDX_Control(pDX, IDC_BTN_SCROLL_UP, m_btn_scroll_up);
	DDX_Control(pDX, IDC_BTN_SCROLL_DOWN, m_btn_scroll_down);
	DDX_Control(pDX, IDC_BTN_MAP, m_btn_map);
	DDX_Control(pDX, IDC_BTN_MENU, m_btn_menu);
	DDX_Control(pDX, IDC_LIST_SCENARIO, m_list_scenario);
	DDX_Control(pDX, IDC_BTN_SCENARIO_EXECUTE, m_btn_scenario_execute);
	DDX_Control(pDX, IDC_BTN_SCENARIO_PAUSE, m_btn_scenario_pause);
	DDX_Control(pDX, IDC_BTN_SCENARIO_DELETE, m_btn_scenario_delete);
	DDX_Control(pDX, IDC_CHECK_SCENARIO, m_chkbox_scenario);
	DDX_Control(pDX, IDC_CHECK_REPEAT, m_chkbox_scenario_repeat);
}

BEGIN_MESSAGE_MAP(CRobotArmsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SERIAL_COM_BTN, &CRobotArmsDlg::OnBnClickedSerialComBtn)
	ON_BN_CLICKED(IDC_BTN_HOME, &CRobotArmsDlg::OnBnClickedBtnHome)
	ON_BN_CLICKED(IDC_BTN_NAVI, &CRobotArmsDlg::OnBnClickedBtnNavi)
	ON_BN_CLICKED(IDC_BTN_DEST, &CRobotArmsDlg::OnBnClickedBtnDest)
	ON_BN_CLICKED(IDC_BTN_CLIMATE, &CRobotArmsDlg::OnBnClickedBtnClimate)
	ON_BN_CLICKED(IDC_BTN_AUDIO, &CRobotArmsDlg::OnBnClickedBtnAudio)
	ON_BN_CLICKED(IDC_BTN_DMB, &CRobotArmsDlg::OnBnClickedBtnDmb)
	ON_BN_CLICKED(IDC_BTN_INFO, &CRobotArmsDlg::OnBnClickedBtnInfo)
	ON_BN_CLICKED(IDC_BTN_DISP, &CRobotArmsDlg::OnBnClickedBtnDisp)
	ON_BN_CLICKED(IDC_BTN_SCROLL_DOWN, &CRobotArmsDlg::OnBnClickedBtnScrollDown)
	ON_BN_CLICKED(IDC_BTN_SCROLL_UP, &CRobotArmsDlg::OnBnClickedBtnScrollUp)
	ON_BN_CLICKED(IDC_LOCATION_SETTING_BTN, &CRobotArmsDlg::OnBnClickedLocationSettingBtn)
	ON_BN_CLICKED(IDC_LOCATION_REVISION_BTN, &CRobotArmsDlg::OnBnClickedLocationRevisionBtn)
	ON_BN_CLICKED(IDC_BTN_GRAP, &CRobotArmsDlg::OnBnClickedBtnGrap)
	ON_BN_CLICKED(IDC_BTN_MAP, &CRobotArmsDlg::OnBnClickedBtnMap)
	ON_BN_CLICKED(IDC_BTN_MENU, &CRobotArmsDlg::OnBnClickedBtnMenu)
	ON_BN_CLICKED(IDC_BTN_SCENARIO_EXECUTE, &CRobotArmsDlg::OnBnClickedBtnScenarioExecute)
	ON_BN_CLICKED(IDC_BTN_SCENARIO_PAUSE, &CRobotArmsDlg::OnBnClickedBtnScenarioPause)
	ON_BN_CLICKED(IDC_BTN_SCENARIO_DELETE, &CRobotArmsDlg::OnBnClickedBtnScenarioDelete)
END_MESSAGE_MAP()


// CRobotArmsDlg 메시지 처리기

BOOL CRobotArmsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

		
	m_bDo = TRUE;		/* 시나리오 쓰레드 플래그 */

	return TRUE;
}

void CRobotArmsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


void CRobotArmsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;


		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR CRobotArmsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 시리얼 통신 설정을 위한 다이얼로그 띄우기
void CRobotArmsDlg::OnBnClickedSerialComBtn()
{
	
	SerialComDlg.DoModal();
}


// 홈 버튼을 눌렀을 시
void CRobotArmsDlg::OnBnClickedBtnHome()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // 시나리오에 추가 할 것인지 체크
	
	switch(iState){

	case BST_INDETERMINATE:	// 체크 되어 있지 않거나 초기 상태 일 때 버튼은 시나리오에 추가되지 않고 동작 한다.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_home);	// 홈버튼 위치 정보를 담고 있는 객체를 인자로 버튼 동작 함수 호출
		break;

	case BST_CHECKED:	// 시나리오 리스트에 추가.
		m_list_scenario.AddString("BUTTON : Home");	//시나리오 리스트를 나타내는 리스트 박스에 홈 버튼 동작 추가.
		m_btnArray.Add(m_btn_home);	// 시나리오 버튼배열에 홈 버튼 동작 추가.
		break;
	}

}


// 네비 버튼을 눌렀을 시
void CRobotArmsDlg::OnBnClickedBtnNavi()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // 시나리오에 추가 할 것인지 체크


	switch(iState){

	case BST_INDETERMINATE:	// 체크 되어 있지 않거나 초기 상태 일 때 버튼은 시나리오에 추가되지 않고 동작 한다.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_navi);	// 네비 버튼 위치 정보를 담고 있는 객체를 인자로 버튼 동작 함수 호출

		break;

	case BST_CHECKED:	// 시나리오 리스트에 추가.
		m_list_scenario.AddString("BUTTON : Navigation");	//시나리오 리스트를 나타내는 리스트 박스에 네비 버튼 동작 추가.
		m_btnArray.Add(m_btn_navi);	// 시나리오 버튼배열에 네비 버튼 동작 추가.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnDest()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // 시나리오에 추가 할 것인지 체크



	switch(iState){

	case BST_INDETERMINATE:	// 체크 되어 있지 않거나 초기 상태 일 때 버튼은 시나리오에 추가되지 않고 동작 한다.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_dest);	// 데스티네이션 버튼 위치 정보를 담고 있는 객체를 인자로 버튼 동작 함수 호출

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Destination");
		m_btnArray.Add(m_btn_dest);	// 시나리오 버튼배열에 데스티네이션 버튼 동작 추가.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnClimate()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // 시나리오에 추가 할 것인지 체크


	switch(iState){

	case BST_INDETERMINATE:	// 체크 되어 있지 않거나 초기 상태 일 때 버튼은 시나리오에 추가되지 않고 동작 한다.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_climate);	// 클리메이트 버튼 위치 정보를 담고 있는 객체를 인자로 버튼 동작 함수 호출

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Climate");
		m_btnArray.Add(m_btn_climate);	// 시나리오 버튼배열에 클리메이트 버튼 동작 추가.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnAudio()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // 시나리오에 추가 할 것인지 체크


	switch(iState){

	case BST_INDETERMINATE:	// 체크 되어 있지 않거나 초기 상태 일 때 버튼은 시나리오에 추가되지 않고 동작 한다.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_audio);	// 오디오 버튼 위치 정보를 담고 있는 객체를 인자로 버튼 동작 함수 호출

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Audio");
		m_btnArray.Add(m_btn_audio);	// 시나리오 버튼배열에 오디오 버튼 동작 추가.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnDmb()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // 시나리오에 추가 할 것인지 체크


	switch(iState){

	case BST_INDETERMINATE:	// 체크 되어 있지 않거나 초기 상태 일 때 버튼은 시나리오에 추가되지 않고 동작 한다.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_dmb);	// 디엠비 버튼 위치 정보를 담고 있는 객체를 인자로 버튼 동작 함수 호출

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : DMB");
		m_btnArray.Add(m_btn_dmb);	// 시나리오 버튼배열에 디엠비 버튼 동작 추가.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnInfo()
{

	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // 시나리오에 추가 할 것인지 체크

	switch(iState){

	case BST_INDETERMINATE:	// 체크 되어 있지 않거나 초기 상태 일 때 버튼은 시나리오에 추가되지 않고 동작 한다.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_info);	// 인포 버튼 위치 정보를 담고 있는 객체를 인자로 버튼 동작 함수 호출

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Information");
		m_btnArray.Add(m_btn_info);	// 시나리오 버튼배열에 인포 버튼 동작 추가.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnDisp()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // 시나리오에 추가 할 것인지 체크

	switch(iState){

	case BST_INDETERMINATE:	// 체크 되어 있지 않거나 초기 상태 일 때 버튼은 시나리오에 추가되지 않고 동작 한다.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_disp);	// 디스플레이 버튼 위치 정보를 담고 있는 객체를 인자로 버튼 동작 함수 호출
		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Display");
		m_btnArray.Add(m_btn_disp);	// 시나리오 버튼배열에 디스플레이 버튼 동작 추가.
		break;
	}
}

void CRobotArmsDlg::OnBnClickedBtnMap()
{
	
	UpdateData(TRUE);
	int iState;
	iState = m_chkbox_scenario.GetCheck(); // 시나리오에 추가 할 것인지 체크



	switch(iState){

	case BST_INDETERMINATE:	// 체크 되어 있지 않거나 초기 상태 일 때 버튼은 시나리오에 추가되지 않고 동작 한다.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_map);	// 맵 버튼 위치 정보를 담고 있는 객체를 인자로 버튼 동작 함수 호출

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Map");
		m_btnArray.Add(m_btn_map);	// 시나리오 버튼배열에 맵 버튼 동작 추가.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnMenu()
{
	
	UpdateData(TRUE);
	int iState;
	iState = m_chkbox_scenario.GetCheck(); // 시나리오에 추가 할 것인지 체크


	switch(iState){

	case BST_INDETERMINATE:	// 체크 되어 있지 않거나 초기 상태 일 때 버튼은 시나리오에 추가되지 않고 동작 한다.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_menu);	// 메뉴 버튼 위치 정보를 담고 있는 객체를 인자로 버튼 동작 함수 호출
		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Menu");
		m_btnArray.Add(m_btn_menu);	// 시나리오 버튼배열에 메뉴 버튼 동작 추가.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnScrollDown()
{
	
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // 시나리오에 추가 할 것인지 체크

	switch(iState){

	case BST_INDETERMINATE:	// 체크 되어 있지 않거나 초기 상태 일 때 버튼은 시나리오에 추가되지 않고 동작 한다.
	case BST_UNCHECKED:
		ScrollDownMotion();

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Scroll Down");
		m_btnArray.Add(m_btn_scroll_down);	// 시나리오 버튼배열에 스크롤 다운 버튼 동작 추가.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnScrollUp()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // 시나리오에 추가 할 것인지 체크


	switch(iState){
	case BST_INDETERMINATE:	// 체크 되어 있지 않거나 초기 상태 일 때 버튼은 시나리오에 추가되지 않고 동작 한다.
	case BST_UNCHECKED:
		ScrollUpMotion();

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Scroll Up");
		m_btnArray.Add(m_btn_scroll_up);	// 시나리오 버튼배열에 스크롤 업 버튼 동작 추가.
		break;
	}
}

// 위치 설정 마법사 불러오기
void CRobotArmsDlg::OnBnClickedLocationSettingBtn()
{
	
	CPropertySheet setting;

	m_page_one1 = new CSettingPageOne;
	m_page_two1 = new CSettingPageTwo;
	m_page_three1 = new CSettingPageThree;

	//도움말버튼 제거
	setting.m_psh.dwFlags &= ~PSH_HASHELP;
	

	setting.AddPage(m_page_one1);
	setting.AddPage(m_page_two1);
	setting.AddPage(m_page_three1);

	setting.SetWizardMode();
	if(ID_WIZFINISH==setting.DoModal())
	{
		// 페이지 삭제
		delete m_page_one1;
		delete m_page_two1;
		delete m_page_three1;
	}else if(IDCANCEL){
		arm_park();	// 마법사 도중 취소 클릭 시 로봇 위치 초기화
	}

}

// 위치 보정 마법사 불러오기
void CRobotArmsDlg::OnBnClickedLocationRevisionBtn()
{
	
	CPropertySheet revision;

	m_page_one2 = new CRevisionPageOne;
	m_page_two2 = new CRevisionPageTwo;
	m_page_three2 = new CRevisionPageThree;

	revision.m_psh.dwFlags &= ~PSH_HASHELP;

	revision.AddPage(m_page_one2);
	revision.AddPage(m_page_two2);
	revision.AddPage(m_page_three2);

	revision.SetWizardMode();
	if(ID_WIZFINISH==revision.DoModal())
	{
		// 페이지 삭제
		delete m_page_one2;
		delete m_page_two2;
		delete m_page_three2;
	}else if (IDCANCEL)
	{
		arm_park();	// 마법사 도중 취소 클릭 시 로봇 위치 초기화
	}

}

// 펜을 쥐기 위한 다이얼로그 불러오기
void CRobotArmsDlg::OnBnClickedBtnGrap()
{
	
	pen.DoModal();
}




// 시나리오 실행 함수
void CRobotArmsDlg::OnBnClickedBtnScenarioExecute()
{
	UpdateData(TRUE);
	int iState;
	iState = m_chkbox_scenario_repeat.GetCheck();

	switch(iState)
	{
		case BST_INDETERMINATE:
		case BST_UNCHECKED:
			StartThread(UNREPEAT);	// 시나리오를 반복하지 않는 쓰레드를 호출
			break;

		case BST_CHECKED:
			StartThread(REPEAT);	// 시나리오를 반복하는 쓰레드를 호출
			break;
	}
}

// 시나리오 종료 버튼
void CRobotArmsDlg::OnBnClickedBtnScenarioPause()
{
	if(m_pThread != NULL)
		StopThread();	// 동작중인 시나리오 쓰레드를 종료
}

// 시나리오 리스트 박스와 배열을 초기화.
void CRobotArmsDlg::OnBnClickedBtnScenarioDelete()
{
	m_list_scenario.ResetContent();
	m_btnArray.RemoveAll();
}


// 기본적인 버튼들에 대한 동작 함수
void CRobotArmsDlg::ButtonMotion(CMyButton m_button)
{
	// 역기구학 알고리즘을 이용한 로봇팔 작동
	Sleep(100);
	set_Arm_Motion(m_button.z_coord, m_button.x_coord, m_button.y_coord, m_button.grip_angle);	// 설정한 위치로 이동
	Sleep(1500);
	set_Arm_Motion(m_button.z_coord, (m_button.x_coord + 7.0F), m_button.y_coord, m_button.grip_angle);	// 패널에 터치
	Sleep(500);
	set_Arm_Motion(m_button.z_coord, m_button.x_coord, m_button.y_coord, m_button.grip_angle);	// 설정한 위치로 이동
	Sleep(500);
	arm_park();	// 로봇의 위치를 초기화
	Sleep(200);
}
void CRobotArmsDlg::ScrollDownMotion()
{
	set_Arm_Motion(m_btn_scroll_down.z_coord, m_btn_scroll_down.x_coord, m_btn_scroll_down.y_coord, m_btn_scroll_down.grip_angle);
	Sleep(1500);
	set_Arm_Motion(m_btn_scroll_down.z_coord, (m_btn_scroll_down.x_coord + 7.0F), m_btn_scroll_down.y_coord, m_btn_scroll_down.grip_angle);
	Sleep(1000);
	set_Arm_Motion(m_btn_scroll_down.z_coord, (m_btn_scroll_down.x_coord + 7.0F), (m_btn_scroll_down.y_coord + 40.0F), m_btn_scroll_down.grip_angle + 20);
	Sleep(700);
	arm_park();
}
void CRobotArmsDlg::ScrollUpMotion()
{
	set_Arm_Motion(m_btn_scroll_up.z_coord, m_btn_scroll_up.x_coord, m_btn_scroll_up.y_coord, m_btn_scroll_up.grip_angle);	// 지정한 위치로 이동
	Sleep(1500);
	set_Arm_Motion(m_btn_scroll_up.z_coord, (m_btn_scroll_up.x_coord + 7.0F), m_btn_scroll_up.y_coord, m_btn_scroll_up.grip_angle);	//패널 터치
	Sleep(1000);
	set_Arm_Motion(m_btn_scroll_up.z_coord, (m_btn_scroll_up.x_coord + 7.0F), (m_btn_scroll_up.y_coord - 40.0F), m_btn_scroll_up.grip_angle - 20);	//스크롤링
	Sleep(700);
	arm_park();
}

// 시나리오 동작 반복 함수
void CRobotArmsDlg::RepeatScenario()
{
	while(1){

		for(int i = 0; i < m_btnArray.GetCount(); i++){
			if(m_btnArray.GetAt(i).z_coord == m_btn_scroll_down.z_coord && m_btnArray.GetAt(i).y_coord == m_btn_scroll_down.y_coord && m_btnArray.GetAt(i).z_coord == m_btn_scroll_down.z_coord && m_btnArray.GetAt(i).grip_angle == m_btn_scroll_down.grip_angle){
				ScrollDownMotion();
			}else if(m_btnArray.GetAt(i).z_coord == m_btn_scroll_up.z_coord && m_btnArray.GetAt(i).y_coord == m_btn_scroll_up.y_coord && m_btnArray.GetAt(i).z_coord == m_btn_scroll_up.z_coord && m_btnArray.GetAt(i).grip_angle == m_btn_scroll_up.grip_angle){
				ScrollUpMotion();
			}else {
				ButtonMotion(m_btnArray.ElementAt(i));
			}
			Sleep(1000);
		}

		Sleep(200);
	}
}

// 일반 시나리오 동작 함수
void CRobotArmsDlg::UnRepeatScenario()
{
	// 시나리오 리스트에 담긴 버튼들을 실행
	for(int i = 0; i < m_btnArray.GetCount(); i++){
		if(m_btnArray.GetAt(i).z_coord == m_btn_scroll_down.z_coord && m_btnArray.GetAt(i).y_coord == m_btn_scroll_down.y_coord && m_btnArray.GetAt(i).z_coord == m_btn_scroll_down.z_coord && m_btnArray.GetAt(i).grip_angle == m_btn_scroll_down.grip_angle){
			ScrollDownMotion();
		}else if(m_btnArray.GetAt(i).z_coord == m_btn_scroll_up.z_coord && m_btnArray.GetAt(i).y_coord == m_btn_scroll_up.y_coord && m_btnArray.GetAt(i).z_coord == m_btn_scroll_up.z_coord && m_btnArray.GetAt(i).grip_angle == m_btn_scroll_up.grip_angle){
			ScrollUpMotion();
		}else {
			ButtonMotion(m_btnArray.ElementAt(i));
		}
		Sleep(1000);
	}
	StopThread();
	//AfxMessageBox(_T("시나리오를 마쳤습니다."));
}



// 시나리오 반복 쓰레드
UINT CRobotArmsDlg::RepeatScenarioThread(LPVOID pThreadParam)
{
	THREADPARAM *pParam = (THREADPARAM*)pThreadParam;

	CRobotArmsDlg *pRobotArmsDlg = (CRobotArmsDlg*)pParam->pWnd;
	BOOL *pDo = pParam->pDo;

	delete pParam;

	while(*pDo){

		pRobotArmsDlg->RepeatScenario();	//시나리오 동작 반복 함수 호출.
	}

	return 0;
}

// 일반 시나리오 쓰레드
UINT CRobotArmsDlg::UnRepeatScenarioThread(LPVOID pThreadParam)
{
	THREADPARAM *pParam = (THREADPARAM*)pThreadParam;

	CRobotArmsDlg *pRobotArmsDlg = (CRobotArmsDlg*)pParam->pWnd;
	BOOL *pDo = pParam->pDo;

	delete pParam;

	while(*pDo){

		pRobotArmsDlg->UnRepeatScenario();	// 시나리오 1회 동작 함수 호출.
	}

	return 0;
}

// 쓰레드 생성
void CRobotArmsDlg::StartThread(BOOL state)
{
	THREADPARAM *pThreadParam = new THREADPARAM;
	pThreadParam->pWnd = (CRobotArmsDlg*)AfxGetApp()->GetMainWnd();
	pThreadParam->pDo = &m_bDo;

	// 인자에 따른 시나리오 동작 함수 쓰레드 생성
	if(state == REPEAT)	m_pThread = AfxBeginThread(RepeatScenarioThread,pThreadParam);	// 반복
	else if(state == UNREPEAT)	m_pThread = AfxBeginThread(UnRepeatScenarioThread,pThreadParam); // 1회
}

// 쓰레드 종료
void CRobotArmsDlg::StopThread(void)
{
	TerminateThread(m_pThread->m_hThread, 0);
	m_pThread = NULL;
	arm_park();		// 로봇 위치 초기화
	AfxMessageBox(_T("시나리오가 종료되었습니다."));
}
