/************************************************************************************
  File Name     :  main.c 
  cpu           :  STM32F405RGT6
  Create Date   :  2016/6/29
  Author        :  yf
  Description   :   main������Ҫ���ڳ���ӿڣ����а�����ʼ�����ֺ͵��̿��Ƽ����䲿�֣�
										main.hͷ�ļ���Ҫ�����˼������п�����ü�ս�����ֲ��������ã�������
										��̨�ĽǶȲ�������̨����PID���������̵�����࣬Ħ���ֵ���ٶ��Լ�
										NVIC�����ã�����һЩ���ú����Ķ��塣
										
  
-------------------------------Revision Histroy-----------------------------------
No   Version    Date     Revised By       Item       Description   
1     1.1       6/28       yf   					main����	 ������ʼ�����ֺ͵��̿��Ƽ����䲿��
2     1.2       6/29       gyf 
3     1.3       6/29       yf 						ע��						
************************************************************************************/	
#include "main.h"

char buffer1[32];//���ڴ���printf����Ҫ�����ã�


int main(void)
{   
		
		Initialization();
	
		while(1)
		{	
		
				if(DBUS_Det(dbus))//rc�����ж�
			{
				#ifdef RM35
				move_control(dbus.rc.ch0, dbus.rc.ch1, dbus.rc.ch2, dbus.rc.s1, dbus.key.v);
				#endif
				
				BLDC_control(dbus.rc.s2, dbus.mouse.r);
				Fire(dbus.rc.s2,dbus.mouse.l);				
				
			}
			//���ڲ�������
			//delay_ms(50);

		//	delay_ms(20);
	//	int	g=GetQuadEncoderDiff();
			//	ShootMotorSpeedSet((int)Velocity_Control_Shoot(g,10));
		//	sprintf(buffer1,"%d %d\n",g,PWM3);
			//sprintf(buffer1,"%d %d\n",Yaw.thisAngle,Pitch.thisAngle);
		//	printf(buffer1);
			
		}
}
