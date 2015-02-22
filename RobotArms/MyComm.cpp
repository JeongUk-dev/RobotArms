// MyComm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RobotArms.h"
#include "SerialComDlg.h"
#include "MyComm.h"


// CMyComm

IMPLEMENT_DYNAMIC(CMyComm, CCmdTarget)


CMyComm::CMyComm()
{
}

CMyComm::~CMyComm()
{
	if (m_bIsOpenned)
		Close();
	delete m_pEvent;
}
CMyComm::CMyComm(CString port,CString baudrate,CString parity,CString databit,CString stopbit)
{
	m_sComPort = port;					// Comport
	m_sBaudRate = baudrate;				// Baud Rate
	m_sParity = parity;					// Parity Bit
	m_sDataBit = databit;				// Data Bit
	m_sStopBit = stopbit;				// Stop Bit
	m_bFlowChk = 1;						// Flow Check
	m_bIsOpenned = FALSE;				// 통신포트가 열려 있는지
	m_nLength = 0;						// 받는 데이터의 길이
	memset(m_sInBuf,0,MAXBUF*2);		// Receive Buffer 초기화
	m_pEvent = new CEvent(FALSE,TRUE);	// 쓰레드에서 사용할 이벤트
}

void CMyComm::ResetSerial()
{
	DCB                              dcb;
	DWORD      DErr;
	COMMTIMEOUTS           CommTimeOuts;

	if (!m_bIsOpenned)
		return;
	
	ClearCommError(m_hComDev,&DErr,NULL);	// 통신포트의 모든 에러를 리셋
	SetupComm(m_hComDev,InBufSize,OutBufSize);	// 통신포트의Input/Output Buffer 사이즈를 설정
	PurgeComm(m_hComDev,PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);	// 모든 Rx/Tx 동작을 제한하고 또한 Buffer의 내용을 버림

	// set up for overlapped I/O
	CommTimeOuts.ReadIntervalTimeout = MAXDWORD ; // 통신 선로상에서 한바이트가 전송되고 또한 바이트가 전송되기까지의 시간
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0 ;	  // Read doperation 에서 TimeOut을 사용하지 않음
	CommTimeOuts.ReadTotalTimeoutConstant = 0 ;

	// CBR_9600 is approximately 1byte/ms. For our purposes, allow
	// double the expected time per character for a fudge factor.
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 1000;
	SetCommTimeouts(m_hComDev, &CommTimeOuts);     // 통신포트의TimeOut을설정           


	memset(&dcb,0,sizeof(DCB));
	dcb.DCBlength = sizeof(DCB);

	GetCommState(m_hComDev, &dcb);		// 통신포트의 DCB를 얻음

	dcb.fBinary = TRUE;		 // DCB를 설정(DCB: 시리얼통신의 제어 파라메터, MSDN 참조)	
	dcb.fParity = TRUE;

	if (m_sBaudRate == "300")
		dcb.BaudRate = CBR_300;
	else if (m_sBaudRate == "600")
		dcb.BaudRate = CBR_600;
	else if (m_sBaudRate == "1200")
		dcb.BaudRate = CBR_1200;
	else if (m_sBaudRate == "2400")
		dcb.BaudRate = CBR_2400;
	else if (m_sBaudRate == "4800")
		dcb.BaudRate = CBR_4800;
	else if (m_sBaudRate == "9600")
		dcb.BaudRate = CBR_9600;
	else if (m_sBaudRate == "14400")
		dcb.BaudRate = CBR_14400;
	else if (m_sBaudRate == "19200")
		dcb.BaudRate = CBR_19200;
	else if (m_sBaudRate == "28800")
		dcb.BaudRate = CBR_38400;
	else if (m_sBaudRate == "33600")
		dcb.BaudRate = CBR_38400;
	else if (m_sBaudRate == "38400")
		dcb.BaudRate = CBR_38400;
	else if (m_sBaudRate == "56000")
		dcb.BaudRate = CBR_56000;
	else if (m_sBaudRate == "57600")
		dcb.BaudRate = CBR_57600;
	else if (m_sBaudRate == "115200")
		dcb.BaudRate = CBR_115200;
	else if (m_sBaudRate == "128000")
		dcb.BaudRate = CBR_128000;
	else if (m_sBaudRate == "256000")
		dcb.BaudRate = CBR_256000;
	else if (m_sBaudRate == "PCI_9600")
		dcb.BaudRate = 1075;
	else if (m_sBaudRate == "PCI_19200")
		dcb.BaudRate = 2212;
	else if (m_sBaudRate == "PCI_38400")
		dcb.BaudRate = 4300;
	else if (m_sBaudRate == "PCI_57600")
		dcb.BaudRate = 6450;
	else if (m_sBaudRate == "PCI_500K")
		dcb.BaudRate = 56000;


	if (m_sParity == "None")
		dcb.Parity = NOPARITY;
	else if (m_sParity == "Even")
		dcb.Parity = EVENPARITY;
	else if (m_sParity == "Odd")
		dcb.Parity = ODDPARITY;
	else if (m_sParity == "Space")
		dcb.Parity = SPACEPARITY;

	if (m_sDataBit == "5 Bit")
		dcb.ByteSize = 5;
	else if (m_sDataBit == "6 Bit")
		dcb.ByteSize = 6;          
	else if (m_sDataBit == "7 Bit")
		dcb.ByteSize = 7;          
	else if (m_sDataBit == "8 Bit")
		dcb.ByteSize = 8;                             

	if (m_sStopBit == "1 Bit")
		dcb.StopBits = ONESTOPBIT;
	else if (m_sStopBit == "1.5 Bit")
		dcb.StopBits = ONE5STOPBITS;
	else if (m_sStopBit == "2 Bit")
		dcb.StopBits = TWOSTOPBITS;

	dcb.fRtsControl = RTS_CONTROL_ENABLE;	
	dcb.fDtrControl = DTR_CONTROL_ENABLE;
	dcb.fOutxDsrFlow = FALSE;

	if (m_bFlowChk) {
		dcb.fOutX = FALSE;
		dcb.fInX = FALSE;
		dcb.XonLim = 2048;
		dcb.XoffLim = 1024;
	}
	else {
		dcb.fOutxCtsFlow = TRUE;
		dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
	}

	SetCommState(m_hComDev, &dcb);		// 설정된 DCB로 통신포트의 제어 파라메터를 설정
	SetCommMask(m_hComDev,EV_RXCHAR);	 // Input Buffer에 데이터가 들어왔을 때 이벤트가 발생하도록 설정

}

void CMyComm::Close()
{
	if (!m_bIsOpenned)
		return;

	m_bIsOpenned = FALSE;
	SetCommMask(m_hComDev, 0);
	EscapeCommFunction(m_hComDev, CLRDTR);
	PurgeComm(m_hComDev, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
	Sleep(500);

}

UINT CommThread(LPVOID lpData)
{
	extern short g_nRemoteStatus;
	DWORD       ErrorFlags;
	COMSTAT     ComStat;
	DWORD      EvtMask ;
	char            buf[MAXBUF];
	DWORD      Length;
	int              size;
	int              insize = 0;

	CMyComm* Comm = (CMyComm*)lpData;	 // 통신클래스의 객체포인터를 얻음

	while (Comm->m_bIsOpenned)	// 통신포트가 열려 있다면
	{
		EvtMask = 0;
		Length = 0;
		insize = 0;
		memset(buf,'\0',MAXBUF);
		WaitCommEvent(Comm->m_hComDev,&EvtMask, NULL);	// 이벤트를 기다림
		ClearCommError(Comm->m_hComDev, &ErrorFlags, &ComStat);
		if ((EvtMask & EV_RXCHAR) && ComStat.cbInQue)	// EV_RXCHAR에서 이벤트가 발생하면
		{
			if (ComStat.cbInQue > MAXBUF)
				size = MAXBUF;
			else
				size = ComStat.cbInQue;
			do
			{
				ClearCommError(Comm->m_hComDev, &ErrorFlags, &ComStat);
				if (!ReadFile(Comm->m_hComDev,buf+insize,size,&Length,&(Comm->m_OLR)))	// overlapped I/O를 통해 데이터를 읽음
				{
					// 에러
					TRACE("Error in ReadFile\n");
					if (GetLastError() == ERROR_IO_PENDING)
					{
						if (WaitForSingleObject(Comm->m_OLR.hEvent, 1000) != WAIT_OBJECT_0)
							Length = 0;
						else
							GetOverlappedResult(Comm->m_hComDev,&(Comm->m_OLR),&Length,FALSE);
					}
					else
						Length = 0;
				}
				insize += Length;
			} while ((Length!=0) && (insize<size));
			ClearCommError(Comm->m_hComDev, &ErrorFlags, &ComStat);

			if (Comm->m_nLength + insize > MAXBUF*2)
				insize = (Comm->m_nLength + insize) - MAXBUF*2;

			Comm->m_pEvent->ResetEvent();	// 이벤트 발생을 잠시 중단하고 input buffer에 데이터를 복사
			memcpy(Comm->m_sInBuf+Comm->m_nLength,buf,insize);
			Comm->m_nLength += insize;
			Comm->m_pEvent->SetEvent();		// 복사가 끝나면 다시 이벤트를 활성화 시키고
			LPARAM temp=(LPARAM)Comm;
			SendMessage(Comm->m_hWnd,WM_MYRECEIVE,Comm->m_nLength,temp);	 // 데이터가 들어왔다는 메시지를 발생
		}
	}
	PurgeComm(Comm->m_hComDev, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
	LPARAM temp=(LPARAM)Comm;
	SendMessage(Comm->m_hWnd,WM_MYCLOSE,0,temp);	// 쓰레드가 종료될 때 종료 메시지를 보냄
	return 0;
}

void CMyComm::HandleClose()
{
	CloseHandle(m_hComDev);
	CloseHandle(m_OLR.hEvent);
	CloseHandle(m_OLW.hEvent);

}

BOOL CMyComm::Create(HWND hWnd)
{
	m_hWnd = hWnd;	// 메시지를 보낼때 사용

	m_hComDev = CreateFile(m_sComPort, GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,
		NULL);	// 시리얼 포트 오픈

	if (m_hComDev!=INVALID_HANDLE_VALUE)	 // 포트가 정상적으로 열리면 
		m_bIsOpenned = TRUE;				// 성공
	else
		return FALSE;						// 실패하고 빠져나감

	ResetSerial();			// 시리얼 포트를 설정값대로 초기화

	m_OLW.Offset = 0;			// Write OVERLAPPED structure 초기화
	m_OLW.OffsetHigh = 0;
	m_OLR.Offset = 0;			// Read OVERLAPPED structure 초기화
	m_OLR.OffsetHigh = 0;

	m_OLR.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL); // Overlapped 구조체의 이벤트를 생성
	if (m_OLR.hEvent == NULL) {
		CloseHandle(m_OLR.hEvent);
		return FALSE;
	}
	m_OLW.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (m_OLW.hEvent == NULL) {
		CloseHandle(m_OLW.hEvent);
		return FALSE;
	}
	AfxBeginThread(CommThread,(LPVOID)this);	// 시리얼 데이터를 받기위한 스레드 생성
	EscapeCommFunction(m_hComDev, SETDTR);		// DTR (Data Terminal Ready) signal 을 보냄
	return TRUE;

}

BOOL CMyComm::Send(LPCTSTR outbuf, int len)
{
	BOOL          bRet=TRUE;
	DWORD       ErrorFlags;
	COMSTAT     ComStat;

	DWORD       BytesWritten;
	DWORD       BytesSent=0;

	ClearCommError(m_hComDev, &ErrorFlags, &ComStat);	// 통신 포트의 모든 에러를 리셋
	if (!WriteFile(m_hComDev, outbuf, len, &BytesWritten, &m_OLW))	// overlapped I/O를 통하여 outbuf의 내용을 len길이 만큼 전송
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			if (WaitForSingleObject(m_OLW.hEvent,1000) != WAIT_OBJECT_0)
				bRet=FALSE;
			else
				GetOverlappedResult(m_hComDev, &m_OLW, &BytesWritten, FALSE);
		}
		else /* I/O error */
			bRet=FALSE; /* ignore error */
	}

	ClearCommError(m_hComDev, &ErrorFlags, &ComStat);	// 다시 한번 통신포트의 모든 에러를 리셋

	return bRet;

}

int CMyComm::Receive(LPSTR inbuf, int len)
{
	CSingleLock lockObj((CSyncObject*) m_pEvent,FALSE);
	// argument value is not valid
	if (len == 0)
		return -1;
	else if  (len > MAXBUF)
		return -1;

	if (m_nLength == 0)
	{
		inbuf[0] = '\0';
		return 0;
	}
	else if (m_nLength <= len)	// 정상적이라면 본루틴으로 들어와 실제 들어온 데이터의 길이 만큼 Input Buffer에서 데이터를 읽음
	{
		lockObj.Lock();
		memcpy(inbuf,m_sInBuf,m_nLength);
		memset(m_sInBuf,0,MAXBUF*2);
		int tmp = m_nLength;
		m_nLength = 0;
		lockObj.Unlock();
		return tmp;
	}
	else
	{
		lockObj.Lock();
		memcpy(inbuf,m_sInBuf,len);
		memmove(m_sInBuf,m_sInBuf+len,MAXBUF*2-len);
		m_nLength -= len;
		lockObj.Unlock();
		return len;
	}
}

void CMyComm::Clear()
{
	PurgeComm(m_hComDev, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
	memset(m_sInBuf,0,MAXBUF*2);
	m_nLength = 0;

} 
BEGIN_MESSAGE_MAP(CMyComm, CCmdTarget)
END_MESSAGE_MAP()

