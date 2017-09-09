/************************************************************************************
  File Name     :  led.c 
  cpu           :  STM32F405RGT6
  Create Date   :  2016/6/29
  Author        :  yf
  Description   :  ----LED_GREEN----PC1-----'0' is on,'1' is off 
									 ----LED_RED------PC2-----'0' is on,'1' is off 
									 LED��������Ҫ�����ڵ��ԣ�Led_Configuration(void)�������������̵ƺ�
									 ���GPIO����ʼ��
									 led.h����Ҫ�����˿�ݸı�LED�ĺ��� ��LED_GREEN_OFF()��
									 LED_GREEN_ON()��LED_GREEN_TOGGLE()�����Ӧ��ɫLED����
-------------------------------Revision Histroy-----------------------------------
No   Version    Date     Revised By       Item       Description   
1     1.1       6/28       yf   			 Led���ú���	 �����̵ƺͺ��GPIO����ʼ��
2     1.2       6/29       gyf 
3     1.3       6/29       yf 					 ע��			   	
************************************************************************************/	
#include "main.h"

void Led_Configuration(void)
{
  GPIO_InitTypeDef gpio;
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&gpio);
    
  LED_GREEN_OFF();
  LED_RED_OFF();
}
