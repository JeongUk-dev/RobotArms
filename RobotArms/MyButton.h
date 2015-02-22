#pragma once


// CMyButton

class CMyButton : public CButton
{
	DECLARE_DYNAMIC(CMyButton)

public:
	CMyButton();
	CMyButton(const CMyButton &b);
	CMyButton(float x, float y, float z, float angle);
	virtual ~CMyButton();

protected:
	DECLARE_MESSAGE_MAP()

public:
	float x_coord;		// x ��ǥ
	float y_coord;		// y ��ǥ
	float z_coord;		// z ��ǥ
	float grip_angle;	// �׸� ����

public:
	const CMyButton& operator=(const CMyButton& b)	//������ ������ ���� ������ �������̵�
	{
		x_coord = b.x_coord;
		y_coord = b.y_coord;
		z_coord = b.z_coord;
		grip_angle = b.grip_angle;

		return *this;
	}
	
};