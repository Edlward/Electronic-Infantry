#ifndef __MAIN_H__
#define __MAIN_H__

//���峵��,��Ҫ��Ӧ�������̨
#define CAR_A
//�����Զ���
#define AUTO_TRACK
//CAR1 RM35-ROBOMODULE_NEW
//CAR2 RM35-ROBOMODULE_NEW
//CAR3 RM3510

//���幤�������ģʽ
//#define DEBUG



//���ݳ��Ŷ���
#ifdef CAR1
//������̵����������
#define ROBOMODULE_NEW

//��̨�Ƕ�
#define YAW_LEFT 2900
#define YAW_RIGHT	5400
#define YAW_MID 4100
#define PITCH_UP 2600
#define PITCH_DOWN 1800
#define PITCH_MID 2100

//��̨PID
#define YAW_205_VEL_P 20.0
#define YAW_205_VEL_D 0.0
#define YAW_205_POS_P 3.5
#define YAW_205_POS_I 0.0
#define YAW_205_POS_D 0.1
#define PITCH_206_VEL_P 15.0
#define PITCH_206_VEL_D 5.0
#define PITCH_206_POS_P 2.0
#define PITCH_206_POS_I 0.0
#define PITCH_206_POS_D 0.0
//���岦������ٶ�
#define SHOOT_SPEED  10   //0-10000
#endif

#ifdef CAR2 
//������̵����������
#define ROBOMODULE_NEW

//��̨�Ƕ�
#define YAW_LEFT 1450
#define YAW_RIGHT	5550
#define YAW_MID 3400
#define PITCH_UP 3250
#define PITCH_DOWN 2250
#define PITCH_MID 2500
//��̨PID
#define YAW_205_VEL_P 20.0
#define YAW_205_VEL_D 0.0
#define YAW_205_POS_P 2.0
#define YAW_205_POS_I 0.0
#define YAW_205_POS_D 0.1
#define PITCH_206_VEL_P 20.0
#define PITCH_206_VEL_D 0.0
#define PITCH_206_POS_P 1.0
#define PITCH_206_POS_I 0.0
#define PITCH_206_POS_D 0.0

#endif

#ifdef CAR3 
//������̵��
#define RM3510 

//��̨�Ƕ�
#define YAW_LEFT 1450
#define YAW_RIGHT	5550
#define YAW_MID 3400
#define PITCH_UP 3250
#define PITCH_DOWN 2050
#define PITCH_MID 2500
//��̨PID
#define YAW_205_VEL_P 20.0
#define YAW_205_VEL_D 0.0
#define YAW_205_POS_P 2.0
#define YAW_205_POS_I 0.0
#define YAW_205_POS_D 0.1
#define PITCH_206_VEL_P 20.0
#define PITCH_206_VEL_D 0.0
#define PITCH_206_POS_P 1.0
#define PITCH_206_POS_I 0.0
#define PITCH_206_POS_D 1.0
//���岦������ٶ�
#define SHOOT_SPEED  10   //0-10000
#endif

#ifdef CAR_HERO   //Ӣ�۳�
	//������̵��
	#define RM3510 

	//��̨�Ƕ�
	#define YAW_LEFT -850
	#define YAW_RIGHT	3150
	#define YAW_MID 1095
	#define PITCH_UP 2400
	#define PITCH_DOWN 1320
	#define PITCH_MID 1550
	//��̨PID
	#define YAW_205_VEL_P 20.0
	#define YAW_205_VEL_D 0.0
	#define YAW_205_POS_P 2.0
	#define YAW_205_POS_I 0.0
	#define YAW_205_POS_D 0.1
	#define PITCH_206_VEL_P 20.0
	#define PITCH_206_VEL_D 0.0
	#define PITCH_206_POS_P 1.0
	#define PITCH_206_POS_I 0.0
	#define PITCH_206_POS_D 1.0
	
	//����RM3510��pid
	#define ESC_820R_VEL_P 10.0//10.0
	#define ESC_820R_VEL_I 0.0
	#define ESC_820R_VEL_D 0.5//0.5
	#define ESC_820R_POS_P 10.0//10.0
	#define ESC_820R_POS_I 0.0
	#define ESC_820R_POS_D 0.0


	#define SHOOT_SPEED  10   //0-10000
#endif

#ifdef CAR_A
	//������̵��
	#define RM3510 

	//��̨�Ƕ�
	#define YAW_LEFT 750
	#define YAW_RIGHT	4880
	#define YAW_MID 2800
	#define PITCH_UP 775
	#define PITCH_DOWN -300
	#define PITCH_MID 150
	//��̨PID
	#define YAW_205_VEL_P 20.0
	#define YAW_205_VEL_D 0.0
	#define YAW_205_POS_P 2.0
	#define YAW_205_POS_I 0.0
	#define YAW_205_POS_D 0.1
	#define PITCH_206_VEL_P 20.0
	#define PITCH_206_VEL_D 0.0
	#define PITCH_206_POS_P 1.0
	#define PITCH_206_POS_I 0.0
	#define PITCH_206_POS_D 1.0
	
	//����RM3510��pid
	#define ESC_820R_VEL_P 10.0//10.0
	#define ESC_820R_VEL_I 0.0
	#define ESC_820R_VEL_D 0.5//0.5
	#define ESC_820R_POS_P 10.0//10.0
	#define ESC_820R_POS_I 0.0
	#define ESC_820R_POS_D 0.0

	#define SHOOT_SPEED  13   //0-10000
#endif

#ifdef CAR_B
	//������̵��
	#define RM3510 

	//��̨�Ƕ�
	#define YAW_LEFT 1480
	#define YAW_RIGHT	5630
	#define YAW_MID 3400
	#define PITCH_UP 5200
	#define PITCH_DOWN 3920
	#define PITCH_MID 4350
	//��̨PID
	#define YAW_205_VEL_P 20.0
	#define YAW_205_VEL_D 0.0
	#define YAW_205_POS_P 2.0
	#define YAW_205_POS_I 0.0
	#define YAW_205_POS_D 0.1
	#define PITCH_206_VEL_P 18.0
	#define PITCH_206_VEL_D 0.0
	#define PITCH_206_POS_P 1.0
	#define PITCH_206_POS_I 0.0
	#define PITCH_206_POS_D 1.0
	
	//����RM3510��pid
	#define ESC_820R_VEL_P 10.0//10.0
	#define ESC_820R_VEL_I 0.0
	#define ESC_820R_VEL_D 0.5//0.5
	#define ESC_820R_POS_P 10.0//10.0
	#define ESC_820R_POS_I 0.0
	#define ESC_820R_POS_D 0.0

	#define SHOOT_SPEED  10   //0-10000
#endif

#ifdef CAR_C
	//������̵��
	#define RM3510 

	//��̨�Ƕ�
	#define YAW_LEFT 1200
	#define YAW_RIGHT	5840
	#define YAW_MID 3550
	#define PITCH_UP 4980
	#define PITCH_DOWN 3820
	#define PITCH_MID 4320
	//��̨PID
	#define YAW_205_VEL_P 20.0
	#define YAW_205_VEL_D 0.0
	#define YAW_205_POS_P 2.0
	#define YAW_205_POS_I 0.0
	#define YAW_205_POS_D 0.1
	#define PITCH_206_VEL_P 20.0
	#define PITCH_206_VEL_D 0.0
	#define PITCH_206_POS_P 1.0
	#define PITCH_206_POS_I 0.0
	#define PITCH_206_POS_D 1.0
	
	//����RM3510��pid
#define ESC_820R_VEL_P 10.0//10.0
#define ESC_820R_VEL_I 0.0
#define ESC_820R_VEL_D 0.5//0.5
#define ESC_820R_POS_P 10.0//10.0
#define ESC_820R_POS_I 0.0
#define ESC_820R_POS_D 0.0

	#define SHOOT_SPEED  5   //0-10000
#endif

//�����˶��ٶȶ���
 #define NormalSpeed 180
 #define HighSpeed 230
 #define LowSpeed 50

//��������������Ϳ���֪����RM35�����
#ifdef ROBOMODULE_NEW
#define RM35
#endif

#ifdef ROBOMODULE_OLD
#define RM35
#endif


//֮�������ϰ�
//����Ħ�����ٶ�
#define RUB_SPEED    1400  //1000-2200



//ʱ��NVIC����
#define MPU6050_Channel EXTI4_IRQn
#define MPU6050_PreemptionPriority 0
#define MPU6050_SubPriority 0

#define HMC5883L_Channel EXTI3_IRQn
#define HMC5883L_PreemptionPriority 0
#define HMC5883L_SubPriority 0

#define CAN1_RX_Channel CAN1_RX0_IRQn
#define CAN1_RX_PreemptionPriority 0
#define CAN1_RX_SubPriority 0

#define CAN1_TX_Channel CAN1_TX_IRQn
#define CAN1_TX_PreemptionPriority 1
#define CAN1_TX_SubPriority 1

#define CAN2_RX_Channel CAN2_RX1_IRQn
#define CAN2_RX_PreemptionPriority 0
#define CAN2_RX_SubPriority 2

#define CAN2_TX_Channel CAN2_TX_IRQn
#define CAN2_TX_PreemptionPriority 0
#define CAN2_TX_SubPriority 0

#define DMA1_Channel DMA1_Stream1_IRQn
#define DMA1_PreemptionPriority 0
#define DMA1_SubPriority 2

#define USART3_Channel USART3_IRQn
#define USART3_PreemptionPriority 3
#define USART3_SubPriority 3

#define DMA2_Channel DMA2_Stream5_IRQn
#define DMA2_PreemptionPriority 0
#define DMA2_SubPriority 1

#define TIM6_Channel TIM6_DAC_IRQn
#define TIM6_PreemptionPriority 3
#define TIM6_SubPriority 2


//�����
#include "stm32f4xx.h"
//��ʼ��
#include "initialization.h"
//DBUS�����ʹ���
#include "dbus.h"
#include "usart1.h"
//Ħ���ֺͲ������
#include "pwm.h"
//CAN1��̨��CAN2���̵��
#include "can1.h"
#include "can2.h"
//����timer6���ڶ�ʱ�жϣ�timer2���ڼ�ʱ��
#include "timer.h"
//���ڱ���������
#include "encoder.h"
//NVIC
#include "nvic.h"
//���ڵ��Ժ���ROS������Ϣ
#include "usart3.h"
//����
#include "shoot_control.h"
#include "gimbal_control.h"
#include "chassis_control.h"
//PID
#include "pid_algorithm.h"
//MPU6050 HMC5883L��
#include "mpu6050_hmc5883l_driver.h"
#include "mpu6050_hmc5883l_i2c.h"
#include "mpu6050_hmc5883l_interrupt.h"
#include "mpu6050_hmc5883l_process.h"
//�������Ժ���ʱ
#include "led.h"
#include "buzzer.h"
#include "delay.h"
//����
#include "laser.h"
//����������
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
//���sdbus����Э��
#include <sdbus.h>

//���ú��� ȡ���ֵ�;���ֵ
#define abs(x) ((x)>0? (x):(-(x)))
#define maxs(a,b) (a>b? a:b)

//�������ڵ���printf
extern char buffer1[32];

#endif 
