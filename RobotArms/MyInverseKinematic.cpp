#include "StdAfx.h"
#include <math.h>
#include "MyInverseKinematic.h"
#include "RobotArmsDlg.h"

// 역기구학 알고리즘 적용.

//z is height, y is distance from base center out, x is side to side. y,z can only be positive
void set_Arm(float x, float y, float z, float grip_angle_d)
{
	//grip angle in radians for use in calculations
	float grip_angle_r = radians(grip_angle_d);    

	// Base angle and radial distance from x,y coordinates
	float bas_angle_r = atan2(x, y);
	float rdist = sqrt((x * x) + (y * y));

	// rdist is y coordinate for the arm
	y = rdist;

	// Grip offsets calculated based on grip angle
	float grip_off_z = (sin(grip_angle_r)) * GRIPPER;
	float grip_off_y = (cos(grip_angle_r)) * GRIPPER;

	// Wrist position
	float wrist_z = (z - grip_off_z) - BASE_HGT;
	float wrist_y = y - grip_off_y;

	// Shoulder to wrist distance (AKA sw)
	float s_w = (wrist_z * wrist_z) + (wrist_y * wrist_y);
	float s_w_sqrt = sqrt(s_w);

	// s_w angle to ground
	float a1 = atan2(wrist_z, wrist_y);

	// s_w angle to humerus
	float a2 = acos(((hum_sq - uln_sq) + s_w) / (2 * HUMERUS * s_w_sqrt));

	// Shoulder angle
	float shl_angle_r = a1 + a2;


	float shl_angle_d = degrees(shl_angle_r);

	// Elbow angle
	float elb_angle_r = acos((hum_sq + uln_sq - s_w) / (2 * HUMERUS * ULNA));

	float elb_angle_d = degrees(elb_angle_r);
	float elb_angle_dn = -(180.0 - elb_angle_d);

	// Wrist angle
	float wri_angle_d = (grip_angle_d - elb_angle_dn) - shl_angle_d;

	// 모터의 각도 계산
	// 모터의 중간 위치를 가지고 모터의 상대 위치를 계산
	float bas_pos = BAS_MID + degrees(bas_angle_r);
	float shl_pos = SHL_MID + (shl_angle_d - 90.0);
	float elb_pos = ELB_MID - (elb_angle_d - 90.0);
	float wri_pos = WRI_MID + wri_angle_d;

	// 계산된 모터의 위치가 범위를 벗어날 때 오류를 출력.
	if (bas_pos < BAS_MIN || bas_pos > BAS_MAX || shl_pos < SHL_MIN || shl_pos > SHL_MAX || elb_pos < ELB_MIN || elb_pos > ELB_MAX || wri_pos < WRI_MIN || wri_pos > WRI_MAX){
		AfxMessageBox("Move Error !");
		return ;
	}

	BASE.Format("P%d",deg_to_us(bas_pos));
	SHOULDER.Format("P%d",deg_to_us(shl_pos));
	ELBOW.Format("P%d",deg_to_us(elb_pos));
	WRIST.Format("P%d",deg_to_us(wri_pos));

	CString str;

	str = BAS_SERVO + BASE + SHL_SERVO + SHOULDER + ELB_SERVO + ELBOW + WRI_SERVO + WRIST + "\r\n";

	CRobotArmsDlg *pMain = (CRobotArmsDlg*)AfxGetApp()->GetMainWnd();
	pMain->SerialComDlg.m_comm->Send(str,str.GetLength());

	//Sleep(100);

}

void set_Arm_Motion(float x, float y, float z, float grip_angle_d)
{
	//grip angle in radians for use in calculations
	float grip_angle_r = radians(grip_angle_d);    

	// Base angle and radial distance from x,y coordinates
	float bas_angle_r = atan2(x, y);
	float rdist = sqrt((x * x) + (y * y));

	// rdist is y coordinate for the arm
	y = rdist;

	// Grip offsets calculated based on grip angle
	float grip_off_z = (sin(grip_angle_r)) * GRIPPER;
	float grip_off_y = (cos(grip_angle_r)) * GRIPPER;

	// Wrist position
	float wrist_z = (z - grip_off_z) - BASE_HGT;
	float wrist_y = y - grip_off_y;

	// Shoulder to wrist distance (AKA sw)
	float s_w = (wrist_z * wrist_z) + (wrist_y * wrist_y);
	float s_w_sqrt = sqrt(s_w);

	// s_w angle to ground
	float a1 = atan2(wrist_z, wrist_y);

	// s_w angle to humerus
	float a2 = acos(((hum_sq - uln_sq) + s_w) / (2 * HUMERUS * s_w_sqrt));

	// Shoulder angle
	float shl_angle_r = a1 + a2;


	float shl_angle_d = degrees(shl_angle_r);

	// Elbow angle
	float elb_angle_r = acos((hum_sq + uln_sq - s_w) / (2 * HUMERUS * ULNA));

	float elb_angle_d = degrees(elb_angle_r);
	float elb_angle_dn = -(180.0 - elb_angle_d);

	// Wrist angle
	float wri_angle_d = (grip_angle_d - elb_angle_dn) - shl_angle_d;

	// 모터의 각도 계산
	// 모터의 중간 위치를 가지고 모터의 상대 위치를 계산
	float bas_pos = BAS_MID + degrees(bas_angle_r);
	float shl_pos = SHL_MID + (shl_angle_d - 90.0);
	float elb_pos = ELB_MID - (elb_angle_d - 90.0);
	float wri_pos = WRI_MID + wri_angle_d;

	// 계산된 모터의 위치가 범위를 벗어날 때 오류를 출력.
	if (bas_pos < BAS_MIN || bas_pos > BAS_MAX || shl_pos < SHL_MIN || shl_pos > SHL_MAX || elb_pos < ELB_MIN || elb_pos > ELB_MAX || wri_pos < WRI_MIN || wri_pos > WRI_MAX){
		AfxMessageBox("Move Error !");
		return ;
	}

	BASE.Format("P%d",deg_to_us(bas_pos));
	SHOULDER.Format("P%d",deg_to_us(shl_pos));
	ELBOW.Format("P%d",deg_to_us(elb_pos));
	WRIST.Format("P%d",deg_to_us(wri_pos));

	CString str;

	str = BAS_SERVO + BASE + SHL_SERVO + SHOULDER + ELB_SERVO + ELBOW + WRI_SERVO + WRIST + " S250" + " T500"+ "\r\n";

	CRobotArmsDlg *pMain = (CRobotArmsDlg*)AfxGetApp()->GetMainWnd();
	pMain->SerialComDlg.m_comm->Send(str,str.GetLength());

	//Sleep(100);

}

// 로봇 팔 초기 위치 설정
void arm_park(){	
	set_Arm_Motion(0.0, 170.0, 10.0, (int)-30);
	
}

int deg_to_us(float value)
{
	// Apply basic constraints
	if (value < SERVO_MIN_DEG) value = SERVO_MIN_DEG;
	if (value > SERVO_MAX_DEG) value = SERVO_MAX_DEG;

	// 계산된 각도를 모터의 펄스 신호로 변환
	return(round(map_float(value, SERVO_MIN_DEG, SERVO_MAX_DEG, (float)SERVO_MIN_US, (float)SERVO_MAX_US)));      
}

// Same logic as native map() function, just operates on float instead of long
float map_float(float value_x, float in_min, float in_max, float out_min, float out_max)
{
	return ((value_x - in_min) * (out_max - out_min) / (in_max - in_min)) + out_min;
}


