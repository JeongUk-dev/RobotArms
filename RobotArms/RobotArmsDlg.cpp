
// RobotArmsDlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.


	// �����Դϴ�.
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


// CRobotArmsDlg ��ȭ ����




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


// CRobotArmsDlg �޽��� ó����

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

		
	m_bDo = TRUE;		/* �ó����� ������ �÷��� */

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


// �ø��� ��� ������ ���� ���̾�α� ����
void CRobotArmsDlg::OnBnClickedSerialComBtn()
{
	
	SerialComDlg.DoModal();
}


// Ȩ ��ư�� ������ ��
void CRobotArmsDlg::OnBnClickedBtnHome()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // �ó������� �߰� �� ������ üũ
	
	switch(iState){

	case BST_INDETERMINATE:	// üũ �Ǿ� ���� �ʰų� �ʱ� ���� �� �� ��ư�� �ó������� �߰����� �ʰ� ���� �Ѵ�.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_home);	// Ȩ��ư ��ġ ������ ��� �ִ� ��ü�� ���ڷ� ��ư ���� �Լ� ȣ��
		break;

	case BST_CHECKED:	// �ó����� ����Ʈ�� �߰�.
		m_list_scenario.AddString("BUTTON : Home");	//�ó����� ����Ʈ�� ��Ÿ���� ����Ʈ �ڽ��� Ȩ ��ư ���� �߰�.
		m_btnArray.Add(m_btn_home);	// �ó����� ��ư�迭�� Ȩ ��ư ���� �߰�.
		break;
	}

}


// �׺� ��ư�� ������ ��
void CRobotArmsDlg::OnBnClickedBtnNavi()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // �ó������� �߰� �� ������ üũ


	switch(iState){

	case BST_INDETERMINATE:	// üũ �Ǿ� ���� �ʰų� �ʱ� ���� �� �� ��ư�� �ó������� �߰����� �ʰ� ���� �Ѵ�.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_navi);	// �׺� ��ư ��ġ ������ ��� �ִ� ��ü�� ���ڷ� ��ư ���� �Լ� ȣ��

		break;

	case BST_CHECKED:	// �ó����� ����Ʈ�� �߰�.
		m_list_scenario.AddString("BUTTON : Navigation");	//�ó����� ����Ʈ�� ��Ÿ���� ����Ʈ �ڽ��� �׺� ��ư ���� �߰�.
		m_btnArray.Add(m_btn_navi);	// �ó����� ��ư�迭�� �׺� ��ư ���� �߰�.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnDest()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // �ó������� �߰� �� ������ üũ



	switch(iState){

	case BST_INDETERMINATE:	// üũ �Ǿ� ���� �ʰų� �ʱ� ���� �� �� ��ư�� �ó������� �߰����� �ʰ� ���� �Ѵ�.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_dest);	// ����Ƽ���̼� ��ư ��ġ ������ ��� �ִ� ��ü�� ���ڷ� ��ư ���� �Լ� ȣ��

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Destination");
		m_btnArray.Add(m_btn_dest);	// �ó����� ��ư�迭�� ����Ƽ���̼� ��ư ���� �߰�.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnClimate()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // �ó������� �߰� �� ������ üũ


	switch(iState){

	case BST_INDETERMINATE:	// üũ �Ǿ� ���� �ʰų� �ʱ� ���� �� �� ��ư�� �ó������� �߰����� �ʰ� ���� �Ѵ�.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_climate);	// Ŭ������Ʈ ��ư ��ġ ������ ��� �ִ� ��ü�� ���ڷ� ��ư ���� �Լ� ȣ��

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Climate");
		m_btnArray.Add(m_btn_climate);	// �ó����� ��ư�迭�� Ŭ������Ʈ ��ư ���� �߰�.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnAudio()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // �ó������� �߰� �� ������ üũ


	switch(iState){

	case BST_INDETERMINATE:	// üũ �Ǿ� ���� �ʰų� �ʱ� ���� �� �� ��ư�� �ó������� �߰����� �ʰ� ���� �Ѵ�.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_audio);	// ����� ��ư ��ġ ������ ��� �ִ� ��ü�� ���ڷ� ��ư ���� �Լ� ȣ��

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Audio");
		m_btnArray.Add(m_btn_audio);	// �ó����� ��ư�迭�� ����� ��ư ���� �߰�.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnDmb()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // �ó������� �߰� �� ������ üũ


	switch(iState){

	case BST_INDETERMINATE:	// üũ �Ǿ� ���� �ʰų� �ʱ� ���� �� �� ��ư�� �ó������� �߰����� �ʰ� ���� �Ѵ�.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_dmb);	// �𿥺� ��ư ��ġ ������ ��� �ִ� ��ü�� ���ڷ� ��ư ���� �Լ� ȣ��

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : DMB");
		m_btnArray.Add(m_btn_dmb);	// �ó����� ��ư�迭�� �𿥺� ��ư ���� �߰�.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnInfo()
{

	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // �ó������� �߰� �� ������ üũ

	switch(iState){

	case BST_INDETERMINATE:	// üũ �Ǿ� ���� �ʰų� �ʱ� ���� �� �� ��ư�� �ó������� �߰����� �ʰ� ���� �Ѵ�.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_info);	// ���� ��ư ��ġ ������ ��� �ִ� ��ü�� ���ڷ� ��ư ���� �Լ� ȣ��

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Information");
		m_btnArray.Add(m_btn_info);	// �ó����� ��ư�迭�� ���� ��ư ���� �߰�.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnDisp()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // �ó������� �߰� �� ������ üũ

	switch(iState){

	case BST_INDETERMINATE:	// üũ �Ǿ� ���� �ʰų� �ʱ� ���� �� �� ��ư�� �ó������� �߰����� �ʰ� ���� �Ѵ�.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_disp);	// ���÷��� ��ư ��ġ ������ ��� �ִ� ��ü�� ���ڷ� ��ư ���� �Լ� ȣ��
		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Display");
		m_btnArray.Add(m_btn_disp);	// �ó����� ��ư�迭�� ���÷��� ��ư ���� �߰�.
		break;
	}
}

void CRobotArmsDlg::OnBnClickedBtnMap()
{
	
	UpdateData(TRUE);
	int iState;
	iState = m_chkbox_scenario.GetCheck(); // �ó������� �߰� �� ������ üũ



	switch(iState){

	case BST_INDETERMINATE:	// üũ �Ǿ� ���� �ʰų� �ʱ� ���� �� �� ��ư�� �ó������� �߰����� �ʰ� ���� �Ѵ�.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_map);	// �� ��ư ��ġ ������ ��� �ִ� ��ü�� ���ڷ� ��ư ���� �Լ� ȣ��

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Map");
		m_btnArray.Add(m_btn_map);	// �ó����� ��ư�迭�� �� ��ư ���� �߰�.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnMenu()
{
	
	UpdateData(TRUE);
	int iState;
	iState = m_chkbox_scenario.GetCheck(); // �ó������� �߰� �� ������ üũ


	switch(iState){

	case BST_INDETERMINATE:	// üũ �Ǿ� ���� �ʰų� �ʱ� ���� �� �� ��ư�� �ó������� �߰����� �ʰ� ���� �Ѵ�.
	case BST_UNCHECKED:
		ButtonMotion(m_btn_menu);	// �޴� ��ư ��ġ ������ ��� �ִ� ��ü�� ���ڷ� ��ư ���� �Լ� ȣ��
		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Menu");
		m_btnArray.Add(m_btn_menu);	// �ó����� ��ư�迭�� �޴� ��ư ���� �߰�.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnScrollDown()
{
	
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // �ó������� �߰� �� ������ üũ

	switch(iState){

	case BST_INDETERMINATE:	// üũ �Ǿ� ���� �ʰų� �ʱ� ���� �� �� ��ư�� �ó������� �߰����� �ʰ� ���� �Ѵ�.
	case BST_UNCHECKED:
		ScrollDownMotion();

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Scroll Down");
		m_btnArray.Add(m_btn_scroll_down);	// �ó����� ��ư�迭�� ��ũ�� �ٿ� ��ư ���� �߰�.
		break;
	}
}


void CRobotArmsDlg::OnBnClickedBtnScrollUp()
{
	
	UpdateData(TRUE);
	int iState = m_chkbox_scenario.GetCheck(); // �ó������� �߰� �� ������ üũ


	switch(iState){
	case BST_INDETERMINATE:	// üũ �Ǿ� ���� �ʰų� �ʱ� ���� �� �� ��ư�� �ó������� �߰����� �ʰ� ���� �Ѵ�.
	case BST_UNCHECKED:
		ScrollUpMotion();

		break;

	case BST_CHECKED:
		m_list_scenario.AddString("BUTTON : Scroll Up");
		m_btnArray.Add(m_btn_scroll_up);	// �ó����� ��ư�迭�� ��ũ�� �� ��ư ���� �߰�.
		break;
	}
}

// ��ġ ���� ������ �ҷ�����
void CRobotArmsDlg::OnBnClickedLocationSettingBtn()
{
	
	CPropertySheet setting;

	m_page_one1 = new CSettingPageOne;
	m_page_two1 = new CSettingPageTwo;
	m_page_three1 = new CSettingPageThree;

	//���򸻹�ư ����
	setting.m_psh.dwFlags &= ~PSH_HASHELP;
	

	setting.AddPage(m_page_one1);
	setting.AddPage(m_page_two1);
	setting.AddPage(m_page_three1);

	setting.SetWizardMode();
	if(ID_WIZFINISH==setting.DoModal())
	{
		// ������ ����
		delete m_page_one1;
		delete m_page_two1;
		delete m_page_three1;
	}else if(IDCANCEL){
		arm_park();	// ������ ���� ��� Ŭ�� �� �κ� ��ġ �ʱ�ȭ
	}

}

// ��ġ ���� ������ �ҷ�����
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
		// ������ ����
		delete m_page_one2;
		delete m_page_two2;
		delete m_page_three2;
	}else if (IDCANCEL)
	{
		arm_park();	// ������ ���� ��� Ŭ�� �� �κ� ��ġ �ʱ�ȭ
	}

}

// ���� ��� ���� ���̾�α� �ҷ�����
void CRobotArmsDlg::OnBnClickedBtnGrap()
{
	
	pen.DoModal();
}




// �ó����� ���� �Լ�
void CRobotArmsDlg::OnBnClickedBtnScenarioExecute()
{
	UpdateData(TRUE);
	int iState;
	iState = m_chkbox_scenario_repeat.GetCheck();

	switch(iState)
	{
		case BST_INDETERMINATE:
		case BST_UNCHECKED:
			StartThread(UNREPEAT);	// �ó������� �ݺ����� �ʴ� �����带 ȣ��
			break;

		case BST_CHECKED:
			StartThread(REPEAT);	// �ó������� �ݺ��ϴ� �����带 ȣ��
			break;
	}
}

// �ó����� ���� ��ư
void CRobotArmsDlg::OnBnClickedBtnScenarioPause()
{
	if(m_pThread != NULL)
		StopThread();	// �������� �ó����� �����带 ����
}

// �ó����� ����Ʈ �ڽ��� �迭�� �ʱ�ȭ.
void CRobotArmsDlg::OnBnClickedBtnScenarioDelete()
{
	m_list_scenario.ResetContent();
	m_btnArray.RemoveAll();
}


// �⺻���� ��ư�鿡 ���� ���� �Լ�
void CRobotArmsDlg::ButtonMotion(CMyButton m_button)
{
	// ���ⱸ�� �˰����� �̿��� �κ��� �۵�
	Sleep(100);
	set_Arm_Motion(m_button.z_coord, m_button.x_coord, m_button.y_coord, m_button.grip_angle);	// ������ ��ġ�� �̵�
	Sleep(1500);
	set_Arm_Motion(m_button.z_coord, (m_button.x_coord + 7.0F), m_button.y_coord, m_button.grip_angle);	// �гο� ��ġ
	Sleep(500);
	set_Arm_Motion(m_button.z_coord, m_button.x_coord, m_button.y_coord, m_button.grip_angle);	// ������ ��ġ�� �̵�
	Sleep(500);
	arm_park();	// �κ��� ��ġ�� �ʱ�ȭ
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
	set_Arm_Motion(m_btn_scroll_up.z_coord, m_btn_scroll_up.x_coord, m_btn_scroll_up.y_coord, m_btn_scroll_up.grip_angle);	// ������ ��ġ�� �̵�
	Sleep(1500);
	set_Arm_Motion(m_btn_scroll_up.z_coord, (m_btn_scroll_up.x_coord + 7.0F), m_btn_scroll_up.y_coord, m_btn_scroll_up.grip_angle);	//�г� ��ġ
	Sleep(1000);
	set_Arm_Motion(m_btn_scroll_up.z_coord, (m_btn_scroll_up.x_coord + 7.0F), (m_btn_scroll_up.y_coord - 40.0F), m_btn_scroll_up.grip_angle - 20);	//��ũ�Ѹ�
	Sleep(700);
	arm_park();
}

// �ó����� ���� �ݺ� �Լ�
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

// �Ϲ� �ó����� ���� �Լ�
void CRobotArmsDlg::UnRepeatScenario()
{
	// �ó����� ����Ʈ�� ��� ��ư���� ����
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
	//AfxMessageBox(_T("�ó������� ���ƽ��ϴ�."));
}



// �ó����� �ݺ� ������
UINT CRobotArmsDlg::RepeatScenarioThread(LPVOID pThreadParam)
{
	THREADPARAM *pParam = (THREADPARAM*)pThreadParam;

	CRobotArmsDlg *pRobotArmsDlg = (CRobotArmsDlg*)pParam->pWnd;
	BOOL *pDo = pParam->pDo;

	delete pParam;

	while(*pDo){

		pRobotArmsDlg->RepeatScenario();	//�ó����� ���� �ݺ� �Լ� ȣ��.
	}

	return 0;
}

// �Ϲ� �ó����� ������
UINT CRobotArmsDlg::UnRepeatScenarioThread(LPVOID pThreadParam)
{
	THREADPARAM *pParam = (THREADPARAM*)pThreadParam;

	CRobotArmsDlg *pRobotArmsDlg = (CRobotArmsDlg*)pParam->pWnd;
	BOOL *pDo = pParam->pDo;

	delete pParam;

	while(*pDo){

		pRobotArmsDlg->UnRepeatScenario();	// �ó����� 1ȸ ���� �Լ� ȣ��.
	}

	return 0;
}

// ������ ����
void CRobotArmsDlg::StartThread(BOOL state)
{
	THREADPARAM *pThreadParam = new THREADPARAM;
	pThreadParam->pWnd = (CRobotArmsDlg*)AfxGetApp()->GetMainWnd();
	pThreadParam->pDo = &m_bDo;

	// ���ڿ� ���� �ó����� ���� �Լ� ������ ����
	if(state == REPEAT)	m_pThread = AfxBeginThread(RepeatScenarioThread,pThreadParam);	// �ݺ�
	else if(state == UNREPEAT)	m_pThread = AfxBeginThread(UnRepeatScenarioThread,pThreadParam); // 1ȸ
}

// ������ ����
void CRobotArmsDlg::StopThread(void)
{
	TerminateThread(m_pThread->m_hThread, 0);
	m_pThread = NULL;
	arm_park();		// �κ� ��ġ �ʱ�ȭ
	AfxMessageBox(_T("�ó������� ����Ǿ����ϴ�."));
}
