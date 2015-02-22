// SerialCom.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RobotArms.h"
#include "SerialComDlg.h"
#include "afxdialogex.h"
#include "MyInverseKinematic.h"


// CSerialCom ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSerialComDlg, CDialogEx)

CSerialComDlg::CSerialComDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSerialComDlg::IDD, pParent)
	, m_str_comport(_T(""))
	, m_str_baudrate(_T(""))
	, m_str_databits(_T(""))
	, m_str_stopbits(_T(""))
	, m_str_paritybits(_T(""))
	//, comport_state(false)
{

}

CSerialComDlg::~CSerialComDlg()
{
}

void CSerialComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM_PORT_COMBO, m_comport_combo_list);
	DDX_Control(pDX, IDC_BAUD_RATE_COMBO, m_baudrate_combo_list);
	DDX_Control(pDX, IDC_DATA_BITS_COMBO, m_databits_combo_list);
	DDX_Control(pDX, IDC_STOP_BITS_COMBO, m_stopbits_combo_list);
	DDX_Control(pDX, IDC_PARITY_BITS_COMBO, m_paritybits_combo_list);
	DDX_CBString(pDX, IDC_COM_PORT_COMBO, m_str_comport);
	DDX_CBString(pDX, IDC_BAUD_RATE_COMBO, m_str_baudrate);
	//  DDX_Control(pDX, IDC_DATA_BITS_COMBO, m_databits_combox_list);
	DDX_CBString(pDX, IDC_DATA_BITS_COMBO, m_str_databits);
	DDX_CBString(pDX, IDC_STOP_BITS_COMBO, m_str_stopbits);
	DDX_CBString(pDX, IDC_PARITY_BITS_COMBO, m_str_paritybits);
}


BEGIN_MESSAGE_MAP(CSerialComDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CONN_CANCEL_BTN, &CSerialComDlg::OnBnClickedConnCancelBtn)

	ON_MESSAGE(WM_MYCLOSE, &CSerialComDlg::OnThreadClosed)
	ON_MESSAGE(WM_MYRECEIVE,&CSerialComDlg::OnReceive)

	ON_BN_CLICKED(IDC_CONNECT_BTN, &CSerialComDlg::OnBnClickedConnectBtn)
	ON_CBN_SELCHANGE(IDC_COM_PORT_COMBO, &CSerialComDlg::OnCbnSelchangeComPortCombo)
	ON_CBN_SELCHANGE(IDC_BAUD_RATE_COMBO, &CSerialComDlg::OnCbnSelchangeBaudRateCombo)
	ON_CBN_SELCHANGE(IDC_PARITY_BITS_COMBO, &CSerialComDlg::OnCbnSelchangeParityBitsCombo)
	ON_CBN_SELCHANGE(IDC_STOP_BITS_COMBO, &CSerialComDlg::OnCbnSelchangeStopBitsCombo)
	ON_CBN_SELCHANGE(IDC_DATA_BITS_COMBO, &CSerialComDlg::OnCbnSelchangeDataBitsCombo)
END_MESSAGE_MAP()


// CSerialCom �޽��� ó�����Դϴ�.
LRESULT CSerialComDlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	//overlapped i/o �ڵ����ݴ´�.
	((CMyComm*)lpara)->HandleClose();
	delete ((CMyComm*)lpara);

	return 0;
}
LRESULT CSerialComDlg::OnReceive(WPARAM length, LPARAM lpara)
{
	CString str;
	char data[20000];
	if(m_comm)
	{
		m_comm->Receive(data,length); //length ���̸�ŭ�����͸��޴´�.
		data[length]=_T('\0');
		str+=_T("\r\n");
		for(int i = 0;i<length;i++)
		{
			str += data[i];
		}
		str = "";
		//UpdateData(FALSE);
	}
	return 0;
} 

BOOL CSerialComDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_comport_combo_list.AddString(_T("COM1"));
	m_comport_combo_list.AddString(_T("COM2"));
	m_comport_combo_list.AddString(_T("COM3"));
	m_comport_combo_list.AddString(_T("COM4"));
	m_comport_combo_list.AddString(_T("COM5"));
	m_comport_combo_list.AddString(_T("COM6"));
	m_comport_combo_list.AddString(_T("COM7"));
	m_comport_combo_list.AddString(_T("COM8"));
	m_comport_combo_list.AddString(_T("COM9"));
	m_comport_combo_list.AddString(_T("COM10"));
	m_comport_combo_list.AddString(_T("COM11"));
	m_comport_combo_list.AddString(_T("COM12"));
	m_comport_combo_list.AddString(_T("COM13"));
	m_comport_combo_list.AddString(_T("COM14"));
	m_comport_combo_list.AddString(_T("COM15"));

	m_baudrate_combo_list.AddString(_T("2400"));
	m_baudrate_combo_list.AddString(_T("9600"));
	m_baudrate_combo_list.AddString(_T("38400"));
	m_baudrate_combo_list.AddString(_T("115200"));

	m_databits_combo_list.AddString(_T("5 Bit"));
	m_databits_combo_list.AddString(_T("6 Bit"));
	m_databits_combo_list.AddString(_T("7 Bit"));
	m_databits_combo_list.AddString(_T("8 Bit"));

	m_paritybits_combo_list.AddString(_T("None"));
	m_paritybits_combo_list.AddString(_T("Odd"));
	m_paritybits_combo_list.AddString(_T("Even"));
	m_paritybits_combo_list.AddString(_T("Space"));

	m_stopbits_combo_list.AddString(_T("1 Bit"));
	m_stopbits_combo_list.AddString(_T("1.5 Bit"));
	m_stopbits_combo_list.AddString(_T("2 Bit"));

	m_comm = NULL; 

	comport_state=false;
	GetDlgItem(IDC_CONNECT_BTN)->SetWindowText(_T("����"));
	m_str_comport = _T("COM1");
	m_str_baudrate = _T("115200");
	m_str_paritybits = _T("None");
	m_str_databits = _T("8 Bit");
	m_str_stopbits = _T("1 Bit");
	UpdateData(FALSE); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CSerialComDlg::OnBnClickedConnCancelBtn()
{
	
	EndDialog(0);

}


void CSerialComDlg::OnBnClickedConnectBtn()
{
	
	if(comport_state)
	{
		if(m_comm)        //����Ʈ�������ϸ�
		{
			m_comm->Close();
			m_comm = NULL;
			AfxMessageBox(_T("COM ��Ʈ����"));
			comport_state=false;
			GetDlgItem(IDC_CONNECT_BTN)->SetWindowText(_T("����"));
			//GetDlgItem(IDC_BT_SEND)->EnableWindow(false);
			//GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(false);

		}
	}
	else
	{
		m_comm= new CMyComm(_T("\\\\.\\")+m_str_comport, m_str_baudrate, m_str_paritybits, m_str_databits, m_str_stopbits);         // initial Comm port
		if(      m_comm->Create(GetSafeHwnd()) != 0) //�����Ʈ���������������ڵ����ѱ��.
		{
			AfxMessageBox(_T("COM ��Ʈ����"));
			comport_state=true;
			GetDlgItem(IDC_CONNECT_BTN)->SetWindowText(_T("����"));
			//GetDlgItem(IDC_BT_SEND)->EnableWindow(true);
			//GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(true);


			// �ø��� ������ �Է��ϱ�.


			arm_park();


		}
		else
		{
			AfxMessageBox(_T("ERROR!"));
		}

	}


}


void CSerialComDlg::OnCbnSelchangeComPortCombo()
{
	
	UpdateData();
}


void CSerialComDlg::OnCbnSelchangeBaudRateCombo()
{
	
	UpdateData();
}


void CSerialComDlg::OnCbnSelchangeParityBitsCombo()
{
	
	UpdateData();
}


void CSerialComDlg::OnCbnSelchangeStopBitsCombo()
{
	
	UpdateData();
}


void CSerialComDlg::OnCbnSelchangeDataBitsCombo()
{
	
	UpdateData();
}