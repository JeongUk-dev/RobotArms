#include "SerialComDlg.h"
#include "SettingPageOne.h"
#include "SettingPageTwo.h"
#include "SettingPageThree.h"
#include "RevisionPageOne.h"
#include "RevisionPageTwo.h"
#include "RevisionPageThree.h"
#include "MyButton.h"
#include "afxwin.h"
#include "GrapTouchPen.h"

// RobotArmsDlg.h : 헤더 파일
//
#define REPEAT 1
#define UNREPEAT 0

#pragma once

typedef struct tagThreadParam{

	CWnd *pWnd; // RobotArmDlg 포인터 담을 함수
	BOOL *pDo; // RobotArmDlg 쓰레드 정지용 플래그 담을 포인터 변수
}THREADPARAM;

// CRobotArmsDlg 대화 상자
class CRobotArmsDlg : public CDialogEx
{
// 생성입니다.
public:
	CRobotArmsDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	CSerialComDlg SerialComDlg;
	CGrapTouchPen pen;
// 대화 상자 데이터입니다.
	enum { IDD = IDD_ROBOTARMS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

private:
	CSettingPageOne* m_page_one1;		// 위치 설정 첫번째 페이지 객체
	CSettingPageTwo* m_page_two1;		// 위치 설정 두번째 페이지 객체
	CSettingPageThree* m_page_three1;	// 위치 설정 세번째 페이지 객체

	CRevisionPageOne* m_page_one2;		// 위치 보정 첫번째 페이지 객체
	CRevisionPageTwo* m_page_two2;		// 위치 보정 두번째 페이지 객체
	CRevisionPageThree* m_page_three2;	// 위치 보정 세번째 페이지 객체

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSerialComBtn();			//시리얼 통신 다이얼로그 버튼
	afx_msg void OnBnClickedLocationSettingBtn();	//위치 설정 다이얼로그 버튼
	afx_msg void OnBnClickedLocationRevisionBtn();	//위치 보정 다이얼로그 버튼
	afx_msg void OnBnClickedBtnGrap();				//펜 그립 다이얼로그 버튼

	afx_msg void OnBnClickedBtnHome();				//홈 동작 버튼
	afx_msg void OnBnClickedBtnNavi();				//네비 동작 버튼
	afx_msg void OnBnClickedBtnDest();				//데스트 동작 버튼
	afx_msg void OnBnClickedBtnClimate();			//클리메이트 동작 버튼
	afx_msg void OnBnClickedBtnAudio();				//오디오 동작 버튼
	afx_msg void OnBnClickedBtnDmb();				//디엠비 동작 버튼
	afx_msg void OnBnClickedBtnInfo();				//인포 동작 버튼
	afx_msg void OnBnClickedBtnDisp();				//디스플레이 동작 버튼
	afx_msg void OnBnClickedBtnScrollDown();		//스크롤 다운 동작 버튼
	afx_msg void OnBnClickedBtnScrollUp();			//스크롤 업 동작 버튼
	afx_msg void OnBnClickedBtnMap();				//맵 동작 버튼
	afx_msg void OnBnClickedBtnMenu();				//메뉴 동작 버튼

	void ButtonMotion(CMyButton m_button);						// 버튼동작 함수
	void ScrollDownMotion();
	void ScrollUpMotion();
	CMyButton m_btn_home;		//홈 버튼 위치 저장 객체
	CMyButton m_btn_navi;		//네비 버튼 위치 저장 객체
	CMyButton m_btn_map;		//맵 버튼 위치 저장 객체
	CMyButton m_btn_dest;		//데스트 버튼 위치 저장 객체
	CMyButton m_btn_climate;	//클리메이트 버튼 위치 저장 객체
	CMyButton m_btn_audio;		//오디오 버튼 위치 저장 객체
	CMyButton m_btn_dmb;		//디엠피 버튼 위치 저장 객체
	CMyButton m_btn_menu;		//메뉴 버튼 위치 저장 객체
	CMyButton m_btn_info;		//인포 버튼 위치 저장 객체
	CMyButton m_btn_disp;		//디스플레이 버튼 위치 저장 객체
	CMyButton m_btn_scroll_down;//스크롤 다운 버튼 위치 저장 객체
	CMyButton m_btn_scroll_up;	//스크롤 업 버튼 위치 저장 객체
	CMyButton *MyButton;		//버튼 포인터
	int ButtonFlag;				//위치 설정 또는 위치 보정 마법사에서 각 버튼을 분류하기 위한 flag 변수


	//시나리오 리소스
	CArray<CMyButton, CMyButton&> m_btnArray;	// 시나리오를 구성할 각 버튼정보를 담는 리스트
	CListBox m_list_scenario;					// 시나리오 리스트박스 객체 변수
	CButton m_btn_scenario_execute;				// 시나리오 실행 버튼
	CButton m_btn_scenario_pause;				// 시나리오 종료 버튼
	CButton m_btn_scenario_delete;				// 시나리오 리스트 내용 삭제 버튼
	CButton m_chkbox_scenario;					// 각 버튼들을 시나리오 리스트에 추가 할 것인지 체크 박스
	CButton m_chkbox_scenario_repeat;			// 시나리오를 반복 할 것인지 체크 박스
	
	afx_msg void OnBnClickedBtnScenarioExecute();	// 시나리오 실행 버튼
	afx_msg void OnBnClickedBtnScenarioPause();		// 시나리오 종료 버튼
	afx_msg void OnBnClickedBtnScenarioDelete();	// 시나리오 리스트 삭제 버튼


	BOOL m_bDo; // 쓰레드 정지플래그
	CWinThread* m_pThread; // 쓰레드 포인터
	static UINT RepeatScenarioThread(LPVOID pThreadParam);		// 쓰레드 함수
	static UINT UnRepeatScenarioThread(LPVOID pThreadParam);	// 쓰레드 함수
	afx_msg void StartThread(BOOL state);						// 쓰레드 시작 사용자 정의 함수
	afx_msg void StopThread();									// 쓰레드 정지 사용자 정의 함수
	afx_msg void RepeatScenario();								// 쓰레드 함수 내에서 실행할 함수
	afx_msg void UnRepeatScenario();							// 쓰레드 함수 내에서 실행할 함수
	
};
