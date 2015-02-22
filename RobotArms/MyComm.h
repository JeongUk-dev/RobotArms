
#pragma once

#include <afxmt.h>

#define MAXBUF			50000
#define InBufSize		50000
#define OutBufSize		50000
#define ASCII_XON		0x11
#define ASCII_XOFF		0x13
#define WM_MYRECEIVE	(WM_USER+1)
#define WM_MYCLOSE		(WM_USER+2)


// CMyComm 명령 대상입니다.

class CMyComm : public CCmdTarget
{
	DECLARE_DYNAMIC(CMyComm)

public:
	CMyComm();
	virtual ~CMyComm();

public:
	HANDLE  m_hComDev;		//COM 포트 핸들
	HWND    m_hWnd;

	BOOL    m_bIsOpenned;
	CString m_sComPort;		// Comport
	CString m_sBaudRate;	// Baud Rate
	CString m_sParity;		// Parity Bit
	CString m_sDataBit;		// Data Bit
	CString m_sStopBit;		// Stop Bit
	BOOL    m_bFlowChk;		// Flow Check

	OVERLAPPED m_OLR,m_OLW;	// Read, Write
	char	m_sInBuf[MAXBUF*2];
	int		m_nLength;
	CEvent* m_pEvent;

	// Operations
public:
	void Clear();
	int	 Receive(LPSTR inbuf, int len);
	BOOL Send(LPCTSTR outbuf, int len);
	BOOL Create(HWND hWnd);
	void HandleClose();
	void Close();
	void ResetSerial();
	CMyComm(CString port,CString baudrate,CString parity,CString databit,CString stopbit);


protected:
	DECLARE_MESSAGE_MAP()
};


