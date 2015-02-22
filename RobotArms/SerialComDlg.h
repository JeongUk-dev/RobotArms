#pragma once
#include <afxwin.h>
#include "MyComm.h"
#include "Resource.h"


// CSerialCom ��ȭ �����Դϴ�.

class CSerialComDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSerialComDlg)

public:
	CMyComm* m_comm;
	LRESULT      OnThreadClosed(WPARAM length, LPARAM lpara);
	LRESULT      OnReceive(WPARAM length, LPARAM lpara);
	CSerialComDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSerialComDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SERIAL_COM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	BOOL comport_state;
	CComboBox m_comport_combo_list;
	CComboBox m_baudrate_combo_list;
	CComboBox m_databits_combo_list;
	CComboBox m_stopbits_combo_list;
	CComboBox m_paritybits_combo_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedConnCancelBtn();
	CString m_str_comport;
	CString m_str_baudrate;
	CString m_str_databits;
	CString m_str_stopbits;
	CString m_str_paritybits;
	CEdit m_edit_rcv_view;
	afx_msg void OnBnClickedConnectBtn();
	afx_msg void OnCbnSelchangeComPortCombo();
	afx_msg void OnCbnSelchangeBaudRateCombo();
	afx_msg void OnCbnSelchangeParityBitsCombo();
	afx_msg void OnCbnSelchangeStopBitsCombo();
	afx_msg void OnCbnSelchangeDataBitsCombo();
};
