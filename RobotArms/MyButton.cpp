// MyButton.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RobotArms.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()	// ��ư�� �� ��ġ �� �ʱ�ȭ
{
	x_coord=NULL;
	y_coord=NULL;
	z_coord=NULL;
	grip_angle=NULL;
}

CMyButton::CMyButton(const CMyButton &b)	// ��ư�� ������ ������ ���� ������ �������̵�
{
	*this=b;
}

CMyButton::CMyButton(float x, float y, float z, float angle)	// �����ڿ� ���� ��ư�� �� ��ġ �� ����
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



// CMyButton �޽��� ó�����Դϴ�.


