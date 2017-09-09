/************************************************************************************
  File Name     :  shoot_control.c 
  cpu           :  STM32F405RGT6
  Create Date   :  2016/6/29
  Author        :  yf
  Description   :  ����ң�����ͼ����˫��������ƣ�һ��ת��Ħ���֣�rub_flag��λ������ת�����������
									 shoot_flag��λ����������ȼ�����һЩ��
										
									 

-------------------------------Revision Histroy-----------------------------------
No   Version    Date     Revised By       Item       Description   
1     1.1       6/28       yf   			  �����������	
2     1.2       6/29       gyf 
3     1.3       6/29       yf 					  ע��	
4     1.4       7/1        yf    ShootMotor_Velocity_Control  ��������ٶȻ�����
************************************************************************************/
#include "main.h"

uint8_t last_s2;//s2����һ��key
uint8_t last_pressr;
int rub_flag;//s2-1λ����״̬
int shoot_flag;//s2-2λ����״̬


//��������ٶȻ����ƺ�����ShootMotor_Velocity_Control(float TargetShootSpeed)���ĸ�timer�������Ҫ���ǣ��漰������pid��ֵ
void ShootMotor_Velocity_Control(float TargetShootSpeed)
{
	 s32 PWM_Output;
	 PWM_Output = (s32)Velocity_Control_Shoot((float)(GetQuadEncoderDiff()) ,TargetShootSpeed);
	 ShootMotorSpeedSet(PWM_Output);
}

//rc��key����Ħ����BLDC����
void BLDC_control(uint8_t s2, uint8_t press_r)
{	
	//���̼�λ����
	
	//int key_G = KEY_PRESSED_OFFSET_SHIFT & v; if (key_G!=0) key_G=1;

	if (rub_flag == 1 && ( (s2==1 && last_s2!=s2) || (press_r == 1 && last_pressr!=press_r) ))
  {
    //pwm���Ƶ��2312 close��
			PWM1=1000;
			PWM2=1000;
	  	rub_flag=0;
		  LASER_OFF();
  }
  else if (rub_flag == 0 && ( (s2==1 && last_s2!=s2) || (press_r == 1 && last_pressr!=press_r) ))
  {
    
		//pwm���Ƶ��2312 open��
    		PWM1=RUB_SPEED;
				PWM2=RUB_SPEED;
    		rub_flag=1;
		    LASER_ON();
	}
	last_s2=s2;
	last_pressr=press_r;
}


//rc��mouse���Ʋ����������������
void Fire(uint8_t s2, uint8_t press_l)
{
	shoot_flag=0;
	if ((rub_flag == 1) && ( (s2==2) || (press_l == 1) ))
  {

    shoot_flag=1;
		
	}
  if (shoot_flag == 1)
	{ 
		int	g=GetQuadEncoderDiff();
		ShootMotorSpeedSet((int)Velocity_Control_Shoot(g,SHOOT_SPEED));
		//printf("%d %d\n",g,PWM3);
	}
	else if(shoot_flag == 0)
	{ PWM3=0;}
	delay_ms(20);
	last_s2=s2;
}
