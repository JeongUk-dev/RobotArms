#include <afxstr.h>

// 로봇팔 각 관절에 대한 길이
#define BASE_HGT 61.93
#define HUMERUS 146.05
#define ULNA 187.325
#define GRIPPER 85.725


#define SERVO_MIN_US 600
#define SERVO_MID_US 1500
#define SERVO_MAX_US 2400
#define SERVO_MIN_DEG 0.0
#define SERVO_MID_DEG 90.0
#define SERVO_MAX_DEG 180.0

#define BAS_MIN 0.0         // Fully CCW
#define BAS_MID 90.0
#define BAS_MAX 180.0       // Fully CW

#define SHL_MIN 20.0        // Max forward motion
#define SHL_MID 81.0
#define SHL_MAX 140.0       // Max rearward motion

#define ELB_MIN 20.0        // Max upward motion
#define ELB_MID 88.0
#define ELB_MAX 165.0       // Max downward motion

#define WRI_MIN 0.0         // Max downward motion
#define WRI_MID 93.0
#define WRI_MAX 180.0       // Max upward motion

#define GRI_MIN 25.0        // Fully open
#define GRI_MID 90.0
#define GRI_MAX 165.0       // Fully closed



#define SPEED_MIN 0.5
#define SPEED_MAX 1.5
#define SPEED_DEFAULT 1.0
#define SPEED_INCREMENT 0.25


#define Y_MIN 100.0         // mm



#define IK_SUCCESS 0
#define IK_ERROR 1          // Desired position not possible

#define PARK_MIDPOINT 1     // Servos at midpoints
#define PARK_READY 2        // Arm at Ready-To-Run position


#define READY_X 0.0
#define READY_Y 170.0
#define READY_Z 45.0
#define READY_GA 0.0
#define READY_G GRI_MID






// 매크로 정의
#define round(x) floor(x+0.5)
#define ftl(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define M_PI       3.14159265358979323846
#define radians(x) ( x * ( M_PI / 180.0f )) 
#define degrees(x) ( x * ( 180.0f / M_PI ))

// 각 모터 정의
#define BAS_SERVO "#0"
#define SHL_SERVO "#1"
#define ELB_SERVO "#2"
#define WRI_SERVO "#3"
#define GRI_SERVO "#4"

static float hum_sq = HUMERUS*HUMERUS;
static float uln_sq = ULNA*ULNA;
static float X = READY_X;         // Left/right distance (mm) from base centerline - 0 is straight
static float Y = READY_Y;          // Distance (mm) out from base center
static float Z = READY_Z;          // Height (mm) from surface (i.e. X/Y plane)
static float GA = READY_GA;        // Gripper angle. Servo degrees, relative to X/Y plane - 0 is horizontal
static float G = READY_G;          // Gripper jaw opening. Servo degrees - midpoint is halfway open


// 팔 데이터 구조체
static struct{
	float x_coord;
	float y_coord;
	float z_coord;
	float gripper_angle;
	int gripper_servo;
}ArmData;

static CString BASE = "";
static CString SHOULDER = "";
static CString ELBOW = "";
static CString WRIST = "";

void set_Arm(float x, float y, float z, float grip_angle_d);
void set_Arm_Motion(float x, float y, float z, float grip_angle_d);
void arm_park();
int deg_to_us(float value);
float map_float(float x, float in_min, float in_max, float out_min, float out_max);
