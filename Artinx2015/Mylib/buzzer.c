#include "main.h"
/************************************************************************************
  File Name     :  buzzer.c 
  cpu           :  STM32F405RGT6
  Create Date   :  2016/6/29
  Author        :  yf
  Description   :  δʹ�ã�����
									----Buzzer----PA5-----'1' is on,'0' is off
									 BUZZER��������Ҫ�����ڵ���
									 buzzer.h����Ҫ�����˿�ݸı�LED�ĺ��� ��BUZZER_ON()��
									 BUZZER_OFF()��BUZZER_TOGGLE()����
-------------------------------Revision Histroy-----------------------------------
No   Version    Date     Revised By       Item       Description   
1     1.1       6/28       yf   			 BUZZER���ú���	 ����BUZZER��GPIO����ʼ��
2     1.2       6/29       gyf 
3     1.3       6/29       yf 					 ע��			   	�ò���δʹ��
************************************************************************************/	

void Buzzer_Configuration(void)
{
    GPIO_InitTypeDef gpio;
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	gpio.GPIO_Pin = GPIO_Pin_5;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&gpio);
    
    BUZZER_OFF();
}
