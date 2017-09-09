/************************************************************************************
  File Name     :  gimbal_control.c 
  cpu           :  STM32F405RGT6
  Create Date   :  2016/6/29
  Author        :  yf
  Description   :  ���6623��̨pithc��yaw���˶������¶��ϵĿ��ơ�
									 ����������������̨��2DOF����PIDλ�û��Ŀ��ƣ�
									 Ȼ������̨Զ�̿��ƺ�����ң�����ͼ��󣩣��������ȼ�����һЩ��
									 

-------------------------------Revision Histroy-----------------------------------
No   Version    Date     Revised By       Item       Description   
1     1.1       6/28       yf   			  ������̨����	
2     1.2       6/29       gyf 
3     1.3       6/29       yf 					  ע��			   
************************************************************************************/
#include "main.h"

//��ʼ����̨�Ƕ�
M6623 Yaw = {YAW_LEFT,YAW_RIGHT,YAW_MID,0,0,0,0,YAW_MID,0,0};
M6623 Pitch = {PITCH_DOWN,PITCH_UP,PITCH_MID,0,0,0,0,PITCH_MID,0,0};

/*********************************************************************
Name��          void Gimbal_Control(void)  

Description��  ��̨���Ƴ���
               �����˶�����Ϊ��ֵ
*********************************************************************/
void Gimbal_Control(void)  
{
	//�⻷PID����
	//����λ�ñջ������
	Yaw.position_output = Position_Control_205(Yaw.thisAngle,Yaw.targetAngle);
	//�ڻ�PID����
  Yaw.velocity_output = Velocity_Control_205(-MPU6050_Real_Data.Gyro_Z ,Yaw.position_output);

	//����λ�ñջ������
	Pitch.position_output = Position_Control_206(Pitch.thisAngle,Pitch.targetAngle);
	//�ڻ�PID����
  Pitch.velocity_output = Velocity_Control_206(-MPU6050_Real_Data.Gyro_Y ,Pitch.position_output);
	Cmd_ESC(Yaw.velocity_output,Pitch.velocity_output);
	
}

/*********************************************************************
Name��         void Trigger_Control(int16_t x, int16_t y, uint16_t ch3)

Description��  ��̨Զ�̿��Ƴ���ң�����ͼ��̣�            
*********************************************************************/

void Trigger_Control(int16_t x, int16_t y, uint16_t ch3)
{
				//��ʱ����yaw��
				if (Yaw.targetAngle < Yaw.minAngle){Yaw.targetAngle=Yaw.minAngle;}
				if (Yaw.targetAngle > Yaw.maxAngle){Yaw.targetAngle=Yaw.maxAngle;}

			
				if (y>3) {Pitch.targetAngle += -15;}
        if (y<-3) {Pitch.targetAngle += 15;}
				Pitch.targetAngle += (ch3-1024)/33;
			
				if (Pitch.targetAngle < Pitch.minAngle){Pitch.targetAngle=Pitch.minAngle;}
				if (Pitch.targetAngle > Pitch.maxAngle){Pitch.targetAngle=Pitch.maxAngle;}		
			
}
