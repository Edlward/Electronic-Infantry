/************************************************************************************
  File Name     :  mpu6050_hmc5883l_process.c 
  cpu           :  STM32F405RGT6
  Create Date   :  2016/6/29
  Author        :  yf
  Description   :  ��Ҫ��Ϊ�˶��ռ����ļ��ٶ���������ͨ�˲�ȥ����Ƶ�񵴣�
									 �Լ�����mahony�˲�����Ԫ�����¡�
									 �ȶ�����mpu6050�������˲��������ٶ���������ֵ�˲����õ�realֵ������
									 �����Ƶ������ǽ��ٶ����ݣ�
									 Ȼ�����˿��ټ��� 1/Sqrt(x)�ĺ�����
									 Ȼ�����˳�ʼ����Ԫ��������
									 �����˸�����Ԫ��������
									 
									 mpu6050_hmc5883l_process.h�ж�����
									 ��άACCEL_AVERAGE_DATA
									 ��άGYRO_RADIAN_DATA
									 ��AHRS_DATA��������ά����ϵ�µļ��ٶȡ��ٶȡ�λ�Ƽ�ŷ���Ǻ���Ԫ����
-------------------------------Revision Histroy-----------------------------------
No   Version    Date     Revised By       Item       Description   
1     1.1       6/28       yf   			    ���ݴ���
2     1.2       6/29       gyf 					
3     1.3       6/29       yf 					  ע��			   
************************************************************************************/
#include "main.h"

ACCEL_AVERAGE_DATA   Accel_Raw_Average_Data; //���ٶȵ�ƽ��ֵ
GYRO_RADIAN_DATA     Gyro_Radian_Data;//����������
AHRS_DATA        AHRS_Data = {0.,0.,0., 0.,0.,0., 1,0,0,0, 0.,0.,0.};

volatile uint32_t lastUpdate, now; // �������ڼ��� ��λ us

void MPU6050_Data_Filter(void)  //����FIFO��˼����ƽ��ֵ
	{
    unsigned int i=0;
    static unsigned int first_flag = 0;
    static unsigned int filter_cnt = 0;    //������ٶȼ��˲��Ĵ���
    
    long temp_accel_x = 0; //������ż��ٶȼ�X��ԭ�����ݵ��ۼӺ�
    long temp_accel_y = 0; //������ż��ٶȼ�Y��ԭ�����ݵ��ۼӺ�
    long temp_accel_z = 0; //������ż��ٶȼ�Z��ԭ�����ݵ��ۼӺ�
    
    static short accel_x_buffer[10] = {0}; //������ż��ٶȼ�X�����10�����ݵ�����
    static short accel_y_buffer[10] = {0}; //������ż��ٶȼ�Y�����10�����ݵ�����
    static short accel_z_buffer[10] = {0}; //������ż��ٶȼ�Z�����10�����ݵ�����
    
    if(first_flag == 0) //�����һ�ν����ú��������������ƽ����������г�ʼ��
    {
        first_flag = 1; //�Ժ��ٽ���
        for(i=0;i<10;i++)
        {
            accel_x_buffer[i] = MPU6050_Raw_Data.Accel_X;
            accel_y_buffer[i] = MPU6050_Raw_Data.Accel_Y;
            accel_z_buffer[i] = MPU6050_Raw_Data.Accel_Z;
        }
    }
    else  //������ǵ�һ����
    {
        accel_x_buffer[filter_cnt] = MPU6050_Raw_Data.Accel_X;
        accel_y_buffer[filter_cnt] = MPU6050_Raw_Data.Accel_Y;
        accel_z_buffer[filter_cnt] = MPU6050_Raw_Data.Accel_Z;   
        
        filter_cnt ++;
        if(filter_cnt == 10)
        {
            filter_cnt = 0;
        }        
    }
    
    for(i=0;i<10;i++)
    {
        temp_accel_x += accel_x_buffer[i];
        temp_accel_y += accel_y_buffer[i];
        temp_accel_z += accel_z_buffer[i];
    }
    
    Accel_Raw_Average_Data.X = (float)temp_accel_x / 10.0;
    Accel_Raw_Average_Data.Y = (float)temp_accel_y / 10.0;
    Accel_Raw_Average_Data.Z = (float)temp_accel_z / 10.0;
		
		MPU6050_Real_Data.Accel_X = -(float)(Accel_Raw_Average_Data.X)/8192.0f; //��datasheet 30 of 47
    MPU6050_Real_Data.Accel_Y = -(float)(Accel_Raw_Average_Data.Y)/8192.0f; //��datasheet 30 of 47
    MPU6050_Real_Data.Accel_Z = (float)(Accel_Raw_Average_Data.Z)/8192.0f; //��datasheet 30 of 47
    
    Gyro_Radian_Data.X = (float)(MPU6050_Real_Data.Gyro_X  * (3.14159265/180.0));
    Gyro_Radian_Data.Y = (float)(MPU6050_Real_Data.Gyro_Y  * (3.14159265/180.0));
    Gyro_Radian_Data.Z = (float)(MPU6050_Real_Data.Gyro_Z  * (3.14159265/180.0));
}
/**************************Fast inverse square-rootʵ�ֺ���********************************************
*����ԭ��:	   float invSqrt(float x)
*��������:	   ���ټ��� 1/Sqrt(x) 	
��������� Ҫ�����ֵ
��������� ���
*******************************************************************************/
float invSqrt(float x) {
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}
void q_initialization(){
		
		unsigned int i;
		
		const unsigned int countnum=1000;
					
		float temp_ini_ax=0;
		float temp_ini_ay=0;
		float temp_ini_az=0;
		float temp_ini_mx=0;
		float temp_ini_my=0;
		float temp_ini_mz=0;
		
		float ini_theta,ini_phi,ini_psi;	
		
		float q0,q1,q2,q3;
		float norm;
																
	  //LED_RED_ON();
	
	  for(i=0; i<countnum; i++)
		{
		MPU6050_ReadData();//��ȡδ�˲�����                                              
    MPU6050_Data_Filter();//��Ҫ��mpu6050���ٶȼƵľ�ֵ�˲��������ǻ�����ת��
		HMC5883L_ReadData();
				
		temp_ini_ax = temp_ini_ax + MPU6050_Real_Data.Accel_X;
    temp_ini_ay = temp_ini_ay + MPU6050_Real_Data.Accel_Y;
    temp_ini_az = temp_ini_az + MPU6050_Real_Data.Accel_Z;
				
		temp_ini_mx = temp_ini_mx + HMC5883L_Real_Data.Mag_X;
    temp_ini_my = temp_ini_my + HMC5883L_Real_Data.Mag_Y;
    temp_ini_mz = temp_ini_mz + HMC5883L_Real_Data.Mag_Z;	
		}
		
		temp_ini_ax = temp_ini_ax / countnum ;
		temp_ini_ay = temp_ini_ay / countnum ;
		temp_ini_az = temp_ini_az / countnum ;
		temp_ini_mx = temp_ini_mx / countnum ;
		temp_ini_my = temp_ini_my / countnum ;
		temp_ini_mz = temp_ini_mz / countnum ;
		
		ini_theta=-atan(temp_ini_ax/1.07);//rad
		ini_phi=atan(temp_ini_ay/temp_ini_az);
		
		ini_psi=atan(-(temp_ini_my*cos(ini_phi)-temp_ini_mz*sin(ini_phi))/(temp_ini_mx*cos(ini_theta)+temp_ini_my*sin(ini_theta)*sin(ini_phi)+temp_ini_mz*sin(ini_theta)*cos(ini_phi)));
		//ini_psi=atan(temp_ini_my/temp_ini_mx);
		
		q0 = cos(ini_phi/2.0f)*cos(ini_theta/2.0f)*cos(ini_psi/2.0f)+sin(ini_phi/2.0f)*sin(ini_theta/2.0f)*sin(ini_psi/2.0f);
		q1 = sin(ini_phi/2.0f)*cos(ini_theta/2.0f)*cos(ini_psi/2.0f)-cos(ini_phi/2.0f)*sin(ini_theta/2.0f)*sin(ini_psi/2.0f);
		q2 = cos(ini_phi/2.0f)*sin(ini_theta/2.0f)*cos(ini_psi/2.0f)+sin(ini_phi/2.0f)*cos(ini_theta/2.0f)*sin(ini_psi/2.0f);
		q3 = cos(ini_phi/2.0f)*cos(ini_theta/2.0f)*sin(ini_psi/2.0f)+sin(ini_phi/2.0f)*sin(ini_theta/2.0f)*cos(ini_psi/2.0f);
			
			
		norm = invSqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
		q0 = q0 * norm;
		q1 = q1 * norm;
		q2 = q2 * norm;
		q3 = q3 * norm;
		
		AHRS_Data.q0=q0;
		AHRS_Data.q1=q1;
		AHRS_Data.q2=q2;
		AHRS_Data.q3=q3;
				
		AHRS_Data.EulerAngle_Pitch = asin(-2 * q1 * q3 + 2 * q0* q2) * (180.0/3.14159265); //theta
		AHRS_Data.EulerAngle_Roll  = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1) * (180.0/3.14159265); //phi
		AHRS_Data.EulerAngle_Yaw= atan2( 2 * q1 * q2 + 2 * q0 * q3,1.0 - 2.0 * ( q2 * q2 + q3 * q2 ) ) * (180.0/3.14159265);//psi
		
		//LED_RED_OFF();
		
}



void AHRS_Calculate( 					float gyro_x,
															float gyro_y,
                              float gyro_z,
                              float accel_x,
                              float accel_y,
                              float accel_z,
															float mag_x,
															float mag_y,
															float mag_z)
{		 
				float q0,q1,q2,q3;
	
				float q0q0;
        float q0q1;
        float q0q2;
        float q0q3;
        float q1q1;
        float q1q2;
        float q1q3;
        float q2q2;  
        float q2q3;
        float q3q3;  
			
				static float exInt = 0;
				static float eyInt = 0;
				static float ezInt = 0;
				
				const float kp_const = 15.0; //
				float kp;
				const float ki = 0.5; //0.0;
				const float g = 1.07;
				const float gravity = 9.8085;
				unsigned int stationary = 0;
				
				float halfT; //�������ڵ�һ��ֵ
				
				float norm; //������ģ
				
				float hx,hy,hz;
				float bx,bz;
				float wx,wy,wz;
			
				float vx,vy,vz;
				
				float ex,ey,ez;

				float ax,ay,az; //���ٶ�������ģ�ı�ֵ 
				float gx,gy,gz; //������
				float mx,my,mz;//������
				
				float accel_xn;
				float accel_yn;
				float accel_zn;
				
				static float vel_xn;
				static float vel_yn;
				static float vel_zn;
				
				static float pos_xn;
				static float pos_yn;
				static float pos_zn;
				
				 
		
				//ʱ��ȷ��
				now = Get_Time_Micros();  //��ȡʱ�� ��λ��us   
				if(now<lastUpdate)
				{
				printf("timeerror \n");
				}
				else	
				{
						halfT =  (float)(now - lastUpdate) / 2000000.0f;
				}
				lastUpdate = now;	//����ʱ��
				
				q0=AHRS_Data.q0;
				q1=AHRS_Data.q1;
				q2=AHRS_Data.q2;
				q3=AHRS_Data.q3;
				
				q0q0 = q0*q0;
        q0q1 = q0*q1;
        q0q2 = q0*q2;
        q0q3 = q0*q3;
        q1q1 = q1*q1;
        q1q2 = q1*q2;
        q1q3 = q1*q3;
        q2q2 = q2*q2;   
        q2q3 = q2*q3;
        q3q3 = q3*q3;  
				
						
				//��һ��ʵ�ʼ��ٶ�����
				stationary = abs(sqrt(accel_x * accel_x + accel_y * accel_y + accel_z * accel_z)-g)<0.04f;
				
				norm = invSqrt(accel_x * accel_x + accel_y * accel_y + accel_z * accel_z);
				ax = accel_x * norm;
				ay = accel_y * norm;
				az = accel_z * norm;
				
				//sprintf(buffer1,"%d\n",stationary);
				//printf(buffer1);
				
				//��һ��ʵ�ʴ���������
				norm = invSqrt(mag_x * mag_x + mag_y * mag_y + mag_z * mag_z);
				mx = mag_x * norm;
				my = mag_y * norm;
				mz = mag_z * norm;
				
				
				//����ο��µĴ�����, 
				hx = 2.0f*mx*(0.5f - q2q2 - q3q3) + 2.0f*my*(q1q2 - q0q3) + 2.0f*mz*(q1q3 + q0q2);
				hy = 2.0f*mx*(q1q2 + q0q3) + 2.0f*my*(0.5f - q1q1 - q3q3) + 2.0f*mz*(q2q3 - q0q1);
				hz = 2.0f*mx*(q1q3 - q0q2) + 2.0f*my*(q2q3 + q0q1) + 2.0f*mz*(0.5f - q1q1 - q2q2);         
				bx = sqrt((hx*hx) + (hy*hy));
				bz = hz;

				wx = 2.0f*bx*(0.5f - q2q2 - q3q3) + 2.0f*bz*(q1q3 - q0q2);
				wy = 2.0f*bx*(q1q2 - q0q3) + 2.0f*bz*(q0q1 + q2q3);
				wz = 2.0f*bx*(q0q2 + q1q3) + 2.0f*bz*(0.5f - q1q1 - q2q2); 
				
				
				//����ο��µļ��ٶ�ֵ
				vx = 2.0f * (q1q3 - q0q2);
				vy = 2.0f * (q0q1 + q2q3);
				vz = q0q0 - q1q1 - q2q2 + q3q3;
				
				
				//��������ֵ
				ex = (ay*vz - az*vy) + (my*wz - mz*wy);
				ey = (az*vx - ax*vz) + (mz*wx - mx*wz);
				ez = (ax*vy - ay*vx) + (mx*wy - my*wx);
				//ex = (ay*vz - az*vy) ;
				//ey = (az*vx - ax*vz) ;
				//ez = (ax*vy - ay*vx) ;
				
				if(stationary)
				{
					ex = (ay*vz - az*vy) + (my*wz - mz*wy);
					ey = (az*vx - ax*vz) + (mz*wx - mx*wz);
					ez = (ax*vy - ay*vx) + (mx*wy - my*wx);
						
				}
				else
					{
						ex =(my*wz - mz*wy);
						ey =(mz*wx - mx*wz);
						ez =(mx*wy - my*wx);
					}
				
				kp = kp_const;
				
				if(ex != 0.0f && ey != 0.0f && ez != 0.0f)
				{   
					exInt = exInt + ki*ex;
					eyInt = eyInt + ki*ey;
					ezInt = ezInt + ki*ez;
				
					gx = gyro_x + kp*ex + exInt;
					gy = gyro_y + kp*ey + eyInt;
					gz = gyro_z + kp*ez + ezInt;
					
				}
				
				q0 = q0 + (      - q1*gx - q2*gy - q3*gz)*halfT;
				q1 = q1 + (q0*gx         + q2*gz - q3*gy)*halfT;
				q2 = q2 + (q0*gy - q1*gz         + q3*gx)*halfT;
				q3 = q3 + (q0*gz + q1*gy - q2*gx        )*halfT;
				
				norm = invSqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
				q0 = q0 * norm;
				q1 = q1 * norm;
				q2 = q2 * norm;
				q3 = q3 * norm;
				
				accel_xn = accel_x*(q0q0+q1q1-q2q2-q3q3) + accel_y*(2*q1q2-2*q0q3)+ accel_z*(2*q0q2+2*q1q3);
				accel_yn = accel_x*(2*q1q2+2*q0q3) + accel_y*(q0q0-q1q1+q2q2-q3q3)+ accel_z*(2*q2q3-2*q0q1);
				accel_zn = accel_x*(2*q1q3-2*q0q2) + accel_y*(2*q0q1+2*q2q3)+ accel_z*(q0q0-q1q1-q2q2+q3q3);
				
				//nxyz-������
				if(abs(accel_xn)<0.06){accel_xn=0;}
				if(abs(accel_yn)<0.06){accel_yn=0;}
				//sprintf(buffer1,"%f \r %f \r %f \n",accel_xn,accel_yn,accel_zn);
				//printf(buffer1);
				vel_xn = vel_xn + accel_xn/g * gravity * 2* halfT;
				vel_yn = vel_yn + accel_yn/g * gravity* 2* halfT;
				vel_zn = vel_zn + (accel_zn-g)* gravity * 2* halfT;
				
				if(stationary)
				{
					vel_xn = 0;
					vel_yn = 0;
					vel_zn = 0;
				}
				//sprintf(buffer1,"%f \r %f \r %f \n",vel_xn,vel_yn,vel_zn);
				//printf(buffer1);
				
				pos_xn = pos_xn + vel_xn * 2 * halfT;
				pos_yn = pos_yn + vel_yn * 2 * halfT;
				pos_zn = pos_zn + vel_zn * 2 * halfT;
				
				//sprintf(buffer1,"%f \r %f \r %f \n",pos_xn*1000,pos_yn*1000,pos_zn*1000);
				//printf(buffer1);
				
				AHRS_Data.Acce_Nav_x=accel_xn;
				AHRS_Data.Acce_Nav_y=accel_yn;
				AHRS_Data.Acce_Nav_z=accel_zn;
				
				AHRS_Data.Vel_Nav_x=vel_xn;
				AHRS_Data.Vel_Nav_y=vel_yn;
				AHRS_Data.Vel_Nav_z=vel_zn;
				
				AHRS_Data.Pos_Nav_x=pos_xn;
				AHRS_Data.Pos_Nav_y=pos_yn;
				AHRS_Data.Pos_Nav_z=pos_zn;
				
			
			//��Ԫ��ת��Ϊŷ����
				AHRS_Data.q0=q0;
				AHRS_Data.q1=q1;
				AHRS_Data.q2=q2;
				AHRS_Data.q3=q3;
				
				AHRS_Data.EulerAngle_Pitch = asin(-2 * q1q3 + 2 * q0q2) * (180.0/3.14159265); 
				AHRS_Data.EulerAngle_Roll  = atan2(2 * q2q3 + 2 * q0q1, -2 * q1q1 - 2 * q2q2 + 1) * (180.0/3.14159265); 
				AHRS_Data.EulerAngle_Yaw= atan2( 2 * q1q2 + 2 * q0q3,1.0 - 2.0 * ( q2q2 + q3q3 ) ) * (180.0/3.14159265);//��׼
				//sprintf(buffer1,"%f \r %f \r %f \n",AHRS_Data.EulerAngle_Roll,AHRS_Data.EulerAngle_Pitch,AHRS_Data.EulerAngle_Yaw);
				//printf(buffer1);
}

