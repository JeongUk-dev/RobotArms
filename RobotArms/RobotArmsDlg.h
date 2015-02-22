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

// RobotArmsDlg.h : ��� ����
//
#define REPEAT 1
#define UNREPEAT 0

#pragma once

typedef struct tagThreadParam{

	CWnd *pWnd; // RobotArmDlg ������ ���� �Լ�
	BOOL *pDo; // RobotArmDlg ������ ������ �÷��� ���� ������ ����
}THREADPARAM;

// CRobotArmsDlg ��ȭ ����
class CRobotArmsDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CRobotArmsDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	CSerialComDlg SerialComDlg;
	CGrapTouchPen pen;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ROBOTARMS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

private:
	CSettingPageOne* m_page_one1;		// ��ġ ���� ù��° ������ ��ü
	CSettingPageTwo* m_page_two1;		// ��ġ ���� �ι�° ������ ��ü
	CSettingPageThree* m_page_three1;	// ��ġ ���� ����° ������ ��ü

	CRevisionPageOne* m_page_one2;		// ��ġ ���� ù��° ������ ��ü
	CRevisionPageTwo* m_page_two2;		// ��ġ ���� �ι�° ������ ��ü
	CRevisionPageThree* m_page_three2;	// ��ġ ���� ����° ������ ��ü

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSerialComBtn();			//�ø��� ��� ���̾�α� ��ư
	afx_msg void OnBnClickedLocationSettingBtn();	//��ġ ���� ���̾�α� ��ư
	afx_msg void OnBnClickedLocationRevisionBtn();	//��ġ ���� ���̾�α� ��ư
	afx_msg void OnBnClickedBtnGrap();				//�� �׸� ���̾�α� ��ư

	afx_msg void OnBnClickedBtnHome();				//Ȩ ���� ��ư
	afx_msg void OnBnClickedBtnNavi();				//�׺� ���� ��ư
	afx_msg void OnBnClickedBtnDest();				//����Ʈ ���� ��ư
	afx_msg void OnBnClickedBtnClimate();			//Ŭ������Ʈ ���� ��ư
	afx_msg void OnBnClickedBtnAudio();				//����� ���� ��ư
	afx_msg void OnBnClickedBtnDmb();				//�𿥺� ���� ��ư
	afx_msg void OnBnClickedBtnInfo();				//���� ���� ��ư
	afx_msg void OnBnClickedBtnDisp();				//���÷��� ���� ��ư
	afx_msg void OnBnClickedBtnScrollDown();		//��ũ�� �ٿ� ���� ��ư
	afx_msg void OnBnClickedBtnScrollUp();			//��ũ�� �� ���� ��ư
	afx_msg void OnBnClickedBtnMap();				//�� ���� ��ư
	afx_msg void OnBnClickedBtnMenu();				//�޴� ���� ��ư

	void ButtonMotion(CMyButton m_button);						// ��ư���� �Լ�
	void ScrollDownMotion();
	void ScrollUpMotion();
	CMyButton m_btn_home;		//Ȩ ��ư ��ġ ���� ��ü
	CMyButton m_btn_navi;		//�׺� ��ư ��ġ ���� ��ü
	CMyButton m_btn_map;		//�� ��ư ��ġ ���� ��ü
	CMyButton m_btn_dest;		//����Ʈ ��ư ��ġ ���� ��ü
	CMyButton m_btn_climate;	//Ŭ������Ʈ ��ư ��ġ ���� ��ü
	CMyButton m_btn_audio;		//����� ��ư ��ġ ���� ��ü
	CMyButton m_btn_dmb;		//���� ��ư ��ġ ���� ��ü
	CMyButton m_btn_menu;		//�޴� ��ư ��ġ ���� ��ü
	CMyButton m_btn_info;		//���� ��ư ��ġ ���� ��ü
	CMyButton m_btn_disp;		//���÷��� ��ư ��ġ ���� ��ü
	CMyButton m_btn_scroll_down;//��ũ�� �ٿ� ��ư ��ġ ���� ��ü
	CMyButton m_btn_scroll_up;	//��ũ�� �� ��ư ��ġ ���� ��ü
	CMyButton *MyButton;		//��ư ������
	int ButtonFlag;				//��ġ ���� �Ǵ� ��ġ ���� �����翡�� �� ��ư�� �з��ϱ� ���� flag ����


	//�ó����� ���ҽ�
	CArray<CMyButton, CMyButton&> m_btnArray;	// �ó������� ������ �� ��ư������ ��� ����Ʈ
	CListBox m_list_scenario;					// �ó����� ����Ʈ�ڽ� ��ü ����
	CButton m_btn_scenario_execute;				// �ó����� ���� ��ư
	CButton m_btn_scenario_pause;				// �ó����� ���� ��ư
	CButton m_btn_scenario_delete;				// �ó����� ����Ʈ ���� ���� ��ư
	CButton m_chkbox_scenario;					// �� ��ư���� �ó����� ����Ʈ�� �߰� �� ������ üũ �ڽ�
	CButton m_chkbox_scenario_repeat;			// �ó������� �ݺ� �� ������ üũ �ڽ�
	
	afx_msg void OnBnClickedBtnScenarioExecute();	// �ó����� ���� ��ư
	afx_msg void OnBnClickedBtnScenarioPause();		// �ó����� ���� ��ư
	afx_msg void OnBnClickedBtnScenarioDelete();	// �ó����� ����Ʈ ���� ��ư


	BOOL m_bDo; // ������ �����÷���
	CWinThread* m_pThread; // ������ ������
	static UINT RepeatScenarioThread(LPVOID pThreadParam);		// ������ �Լ�
	static UINT UnRepeatScenarioThread(LPVOID pThreadParam);	// ������ �Լ�
	afx_msg void StartThread(BOOL state);						// ������ ���� ����� ���� �Լ�
	afx_msg void StopThread();									// ������ ���� ����� ���� �Լ�
	afx_msg void RepeatScenario();								// ������ �Լ� ������ ������ �Լ�
	afx_msg void UnRepeatScenario();							// ������ �Լ� ������ ������ �Լ�
	
};
