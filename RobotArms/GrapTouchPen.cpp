// GrapTouchPen.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RobotArms.h"
#include "GrapTouchPen.h"
#include "afxdialogex.h"
#include "RobotArmsDlg.h"

// CGrapTouchPen ��ȭ �����Դϴ�.

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




// �����̴��ٰ� ��ũ�� �� �� ����ȴ�.
void CGrapTouchPen::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	CRobotArmsDlg *pMain = (CRobotArmsDlg*)AfxGetApp()->GetMainWnd();	// ���� ���α׷��� ������ �ڵ��� �����´�.
	CString str;
	str.Format("%d", m_Servo4Slider.GetPos());	// �����̴� ���� ��ġ�� �����´�.
	m_Servo4Edit.SetWindowText(str);	// ���� �ڽ��� ��ġ ���� ǥ��.
	CString m_Servo4 = "#4 ";
	m_Servo4+=_T("P"+str+"T1500"+"\r");	// �κ� ���� �׸��� �ش��ϴ� ���͸� �����̱� ���� Ŀ�ǵ�
	pMain->SerialComDlg.m_comm->Send(m_Servo4, m_Servo4.GetLength());	// �ø��� ������� Ŀ�ǵ带 �����Ѵ�.
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

// ���̾�α� �ʱ�ȭ
BOOL CGrapTouchPen::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Servo4Slider.SetRange(500,2500);	// �����̴� �� ���� ����

	// ��ġ �� ����
	if(m_intServo4==NULL)
		m_Servo4Slider.SetPos(1500);
	else
		m_Servo4Slider.SetPos(m_intServo4);
	
	return TRUE;
}


void CGrapTouchPen::OnChangeEdit1()
{
	if(UpdateData(TRUE))	//�����̴� ���� ��ġ�� ���� �� ���� ���� �ڽ��� ���� ����.
		m_Servo4Slider.SetPos(m_intServo4);
}
