// MyButton.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RobotArms.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()	// 버튼의 각 위치 값 초기화
{
	x_coord=NULL;
	y_coord=NULL;
	z_coord=NULL;
	grip_angle=NULL;
}

CMyButton::CMyButton(const CMyButton &b)	// 버튼의 포인터 대입을 위한 연산자 오버라이딩
{
	*this=b;
}

CMyButton::CMyButton(float x, float y, float z, float angle)	// 생성자에 따른 버튼의 각 위치 값 설정
{
	x_coord = x;
	y_coord = y;
	z_coord = z;
	grip_angle = angle;

}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
END_MESSAGE_MAP()



// CMyButton 메시지 처리기입니다.


