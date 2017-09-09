/************************************************************************************
  File Name     :  timer.c 
  cpu           :  STM32F405RGT6
  Create Date   :  2016/6/29
  Author        :  yf
  Description   :  timer�����ã�ռ��TIMER6��TIMER2��TIMER3��
									 //Timer 2 32-bit counter (Regard as time counter) 
									 //Timer Clock is 168MHz / 4 * 2 = 84M
									 ����timer6�����жϿ�����̨��ʱ��Ϊ100/84ms��
									 timer2��������ʱ����ʱ��Ϊ1MHz��
									 timer3�����жϿ��Ƶ��̣�ʱ��Ϊ
									 ��Ҫע�����timer���жϿ��Ƶģ���Ҫ���жϿ���ʹ�ܷ���main��ʼ���ĺ���
									 
-------------------------------Revision Histroy-----------------------------------
No   Version    Date     Revised By       Item       Description   
1     1.1       6/28       yf   			 timer���ú���	����TIM��ʼ�����жϼ�nvic������
2     1.2       6/29       gyf 				 �޸�timer6�ж�ʱ�䣬����timer3�ж�
3     1.3       6/29       yf 					  ע��			   
************************************************************************************/
#include "main.h"

void TIM6_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  tim;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
    
	  NVIC_Set(TIM6_Channel,TIM6_PreemptionPriority,TIM6_SubPriority,ENABLE);

    tim.TIM_Prescaler = 5000-1;//
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    tim.TIM_Period = 20;// 5ms=84
    TIM_TimeBaseInit(TIM6,&tim);
}

void TIM6_Start(void)
{
    TIM_Cmd(TIM6, ENABLE);	 
    TIM_ITConfig(TIM6, TIM_IT_Update,ENABLE);
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);	
}
void TIM6_DAC_IRQHandler(void)  
{
    if (TIM_GetITStatus(TIM6,TIM_IT_Update)!= RESET) 
	{
        TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
        TIM_ClearFlag(TIM6, TIM_FLAG_Update);	
        Gimbal_Control();	
	//	LED_RED_TOGGLE();
    }
}
 

void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef tim;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    tim.TIM_Period = 0xFFFFFFFF;
    tim.TIM_Prescaler = 84 - 1;	 //1M ��ʱ��  
    tim.TIM_ClockDivision = TIM_CKD_DIV1;	
    tim.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_ARRPreloadConfig(TIM2, ENABLE);	
    TIM_TimeBaseInit(TIM2, &tim);

    TIM_Cmd(TIM2,ENABLE);	
}
void TIM2_IRQHandler(void)
{
	 // printf("in!\n");
	  if (TIM_GetITStatus(TIM2,TIM_IT_Update)!= RESET) 
		{
			  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
        TIM_ClearFlag(TIM2, TIM_FLAG_Update);
			  LED_RED_TOGGLE();
		}
} 

uint32_t Get_Time_Micros(void)
{
	return TIM2->CNT;
}
