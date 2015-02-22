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
	float x_coord;		// x 좌표
	float y_coord;		// y 좌표
	float z_coord;		// z 좌표
	float grip_angle;	// 그립 각도

public:
	const CMyButton& operator=(const CMyButton& b)	//포인터 대입을 위한 연산자 오버라이딩
	{
		x_coord = b.x_coord;
		y_coord = b.y_coord;
		z_coord = b.z_coord;
		grip_angle = b.grip_angle;

		return *this;
	}
	
};