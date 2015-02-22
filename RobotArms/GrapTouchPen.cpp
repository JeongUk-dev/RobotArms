// GrapTouchPen.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RobotArms.h"
#include "GrapTouchPen.h"
#include "afxdialogex.h"
#include "RobotArmsDlg.h"

// CGrapTouchPen 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGrapTouchPen, CDialogEx)

CGrapTouchPen::CGrapTouchPen(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGrapTouchPen::IDD, pParent)
{

	m_intServo4 = 1500;
}

CGrapTouchPen::~CGrapTouchPen()
{
}

void CGrapTouchPen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Servo4Edit);
	DDX_Text(pDX, IDC_EDIT1, m_intServo4);
	DDV_MinMaxInt(pDX, m_intServo4, 500, 2500);
	DDX_Control(pDX, IDC_SLIDER1, m_Servo4Slider);
}


BEGIN_MESSAGE_MAP(CGrapTouchPen, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT1, &CGrapTouchPen::OnChangeEdit1)
END_MESSAGE_MAP()




// 슬라이더바가 스크롤 될 때 실행된다.
void CGrapTouchPen::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	CRobotArmsDlg *pMain = (CRobotArmsDlg*)AfxGetApp()->GetMainWnd();	// 현재 프로그램의 윈도우 핸들을 가져온다.
	CString str;
	str.Format("%d", m_Servo4Slider.GetPos());	// 슬라이더 바의 위치를 가져온다.
	m_Servo4Edit.SetWindowText(str);	// 에딧 박스에 위치 값을 표시.
	CString m_Servo4 = "#4 ";
	m_Servo4+=_T("P"+str+"T1500"+"\r");	// 로봇 팔의 그립에 해당하는 모터를 움직이기 위한 커맨드
	pMain->SerialComDlg.m_comm->Send(m_Servo4, m_Servo4.GetLength());	// 시리얼 통신으로 커맨드를 전송한다.
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

// 다이얼로그 초기화
BOOL CGrapTouchPen::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Servo4Slider.SetRange(500,2500);	// 슬라이더 바 범위 설정

	// 위치 값 설정
	if(m_intServo4==NULL)
		m_Servo4Slider.SetPos(1500);
	else
		m_Servo4Slider.SetPos(m_intServo4);
	
	return TRUE;
}


void CGrapTouchPen::OnChangeEdit1()
{
	if(UpdateData(TRUE))	//슬라이더 바의 위치가 변할 때 마다 에딧 박스의 값을 변경.
		m_Servo4Slider.SetPos(m_intServo4);
}
