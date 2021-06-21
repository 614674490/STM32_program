#ifndef  _CONFIG_H
#define  _CONFIG_H

#define INFANTRY                     3       // �������  1 ����һ 2 ������ 3 ������ 4 ������ 
#define DEBUG_MODE                   0       //1 ��������ģʽ��ֻ����Ħ�����벦�������   0 ����������ģʽ 
#define DIALPOSITIONORSPEED          1        //1 �������λ�û�   0��������ٶȻ�
#define CHASSIS_FEEDBACK             2        //1���ò���ϵ ͳ    2 ���õ�����  0 �����ù��ʱջ�
#define SHOOT_FEEDBACK               0        //1���ò���ϵͳ(������ȼ�)    2 ��ʱ������  3����ϵͳ(ֻ�Ƕ�ȡ�ȼ�)  0 �����������ջ�

#define ACCELERA_TIME               52000     //����б��ʱ��

//#define SONEBULLET_DISTANCE         1800    //һ���ӵ�����Ƶ�������ж�(һ��)
//#define MONEBULLET_DISTANCE         2600    //һ���ӵ�����Ƶ�������ж�(����)
//#define LONEBULLET_DISTANCE         3500    //һ���ӵ�����Ƶ�������ж�(����)

//#define STHREEBULLET_DISTANCE       1500    //�����ӵ�����Ƶ�������ж�(һ��)
//#define MTHREEBULLET_DISTANCE       2200    //�����ӵ�����Ƶ�������ж�(����)
//#define LTHREEBULLET_DISTANCE       3000    //�����ӵ�����Ƶ�������ж�(����)


#define SONEBULLET_DISTANCE         1200    //һ���ӵ�����Ƶ�������ж�(һ��)
#define MONEBULLET_DISTANCE         1800    //һ���ӵ�����Ƶ�������ж�(����)
#define LONEBULLET_DISTANCE         2700    //һ���ӵ�����Ƶ�������ж�(����)

#define STHREEBULLET_DISTANCE       800    //�����ӵ�����Ƶ�������ж�(һ��)
#define MTHREEBULLET_DISTANCE       1100    //�����ӵ�����Ƶ�������ж�(����)
#define LTHREEBULLET_DISTANCE       1600    //�����ӵ�����Ƶ�������ж�(����)



//#define SONEBULLET_DISTANCE         800    //һ���ӵ�����Ƶ�������ж�(һ��)
//#define MONEBULLET_DISTANCE         1400    //һ���ӵ�����Ƶ�������ж�(����)
//#define LONEBULLET_DISTANCE         2200    //һ���ӵ�����Ƶ�������ж�(����)

//#define STHREEBULLET_DISTANCE       600    //�����ӵ�����Ƶ�������ж�(һ��)
//#define MTHREEBULLET_DISTANCE       1100    //�����ӵ�����Ƶ�������ж�(����)
//#define LTHREEBULLET_DISTANCE       1700    //�����ӵ�����Ƶ�������ж�(����)
//#define SONEBULLET_DISTANCE         2100    //һ���ӵ�����Ƶ�������ж�(һ��)
//#define MONEBULLET_DISTANCE         2800    //һ���ӵ�����Ƶ�������ж�(����)
//#define LONEBULLET_DISTANCE         3800    //һ���ӵ�����Ƶ�������ж�(����)

//#define STHREEBULLET_DISTANCE       1800    //�����ӵ�����Ƶ�������ж�(һ��)
//#define MTHREEBULLET_DISTANCE       2300    //�����ӵ�����Ƶ�������ж�(����)
//#define LTHREEBULLET_DISTANCE       3100    //�����ӵ�����Ƶ�������ж�(����)
#if INFANTRY==1
#define POWER_KP                   1.5f     //���ʻ�KPֵ
#define POWER_KI                   0.32f     //���ʻ�KIֵ����ɼ���������
#define POWER_KD                   0.15f     //���ʻ�KDֵ
//#define POWER_KP                   1.5f     //���ʻ�KPֵ
//#define POWER_KI                   0.3f     //���ʻ�KIֵ
//#define POWER_KD                   0.3f     //���ʻ�KDֵ
//#define POWER_KD                   0.12f     //���ʻ�KDֵ
#elif INFANTRY==2
#define POWER_KP                   1.5f     //���ʻ�KPֵ
#define POWER_KI                   0.3f     //���ʻ�KIֵ����ɼ���������
#define POWER_KD                   0.12f    //���ʻ�KDֵ
#elif INFANTRY==3
#define POWER_KP                   1.5f     //���ʻ�KPֵ
#define POWER_KI                   0.32f     //���ʻ�KIֵ����ɼ���������
#define POWER_KD                   0.15f    //���ʻ�KDֵ
#endif
#define PTZ_LOCK_ANGLE               2.6f    //��̨�����Ƕ�
#define REDIAL_BULLET_SPEED          3       //����������ٶȼ���ٶ�
#define KEY_PRESS_DELAY              30    //������Ӧ��ʱʱ��
#define FRICITION_CLOSE_DELAY        75      //Ħ���ֹر���ʱʱ��
#define TWIST_DELAY                  160     //Ť��Ƶ�ʣ��������ڣ�
#define TWIST_ANGLE                  35      //Ť���Ƕȣ��������ڣ�
#define AVOID_ANGLE                  35      //�����Ƕȣ��������ڣ�


#define FASTSPEED_OFFSET             0.78f   //���ٳ�����ϵ��
#define HIGHSPEED_OFFSET             0.85f  //���ٳ�����ϵ��
#define LOWSPEED_OFFSET              0.9f   //���ٳ�����ϵ��

#define ONE_KP                       1.2f   //һ���ӵ�λ�û�KP   1.5F
#define ONE_KD                       0.18f    //һ���ӵ�λ�û�KD
#define THREE_KP                     0.55f    //�����ӵ�λ�û�KP
#define THREE_KD                     0        //�����ӵ�λ�û�KD

#define POWER_VOLTAGE                24.0f   //��Դ��ѹ
#define POWER_LIMIT_UP               18     //�����������  //100
#define CURRENT_OFFSET               1000.0f //��������ϵ��
#if INFANTRY == 1               //����һ������


/**********************   �ӵ�λ���������޸ġ�  ***********************/
		#define      SLOW_ONEBULLET_HEAT          18   //һ�ŵ����ӵ�������    
		#define   	 FAST_ONEBULLET_HEAT          30   //һ�Ÿ����ӵ�������  

		#define 		 SLOW_THREEBULLET_HEAT        54   //���ŵ����ӵ�������   
		#define 		 FAST_THREEBULLET_HEAT        85   //���Ÿ����ӵ�������  

		#define      DIAL_ONE_POSITION       	    5040 //һ���ӵ���λ��
    #define      DIAL_THREE_POSITION     	    15150//�����ӵ���λ��
		#define      DIAL_BACK_POSITION         	2000 //������λ��
#if		DIALPOSITIONORSPEED==1
		#define      LOW_ONE_TIME                30000//һ���ӵ���ʱ�䣨���� 20m/s��
		#define      FAST_ONE_TIME               15000//һ���ӵ���ʱ�䣨���� 17m/s��	
		#define      LOW_THREE_TIME              105000//�����ӵ���ʱ�䣨���� 20m/s��
		#define      FAST_THREE_TIME             45000//�����ӵ���ʱ�䣨���� 17m/s ��		
#else		
		#define      LOW_ONE_TIME                35000 //һ���ӵ���ʱ�䣨���� 20m/s ��
		#define      FAST_ONE_TIME               19000 //һ���ӵ���ʱ�䣨���� 17m/s ��
		#define      LOW_THREE_TIME              120000//�����ӵ���ʱ�䣨���� 20m/s ��
		#define      FAST_THREE_TIME             58000 //�����ӵ���ʱ�䣨���� 17m/s��
		#define      DIAL_SPEED                  4150 //�ٶȻ������ٶ�
		#define      DIAL_ONE_DELAY               11  //һ���ӵ�����ʱ
		#define      DIAL_THREE_DELAY             40  //�����ӵ�����ʱ
#endif			
		#define      NORMAL_FRICITION_ON_SPEED   1700   //��ͨĦ���ֻ����ٶ� ��Vave=25m/s��
    #define      LOW_FRICITION_ON_SPEED      1380   //�����Ħ���ֻ����ٶ�(Vave=18/s)		
/***********************    ���ʻ������޸ġ�   ************************/		
		#define      POWER_LIMIT_VALUE      	 76       //����ģʽ�µĹ���
		#define      KEY_LOWSPEED_KP     	  NORMAL_ZHI_LOWSPEED_KP//����ģʽ��KP
    #define      KEY_HIGHSPEED_KP     	NORMAL_ZHI_HIGHSPEED_KP//����ģʽ��KP
		#define      FRICITION_ON_SPEED   	NORMAL_FRICITION_ON_SPEED//Ħ���ֿ����ٶ�
		
/***********************    ��̨�����޸ġ�   ************************/				
		#define      PITCH_INITIAL_VALUE     5080    //Pitch���ʼֵ
		#define      YAW_INITIAL_VALUE       6170    //Yaw���ʼֵ
		#define      PITCH_UP_LIMIT          14.5f   //pitch����
		#define      PITCH_DOWM_LIMIT        -7.5f  //pitch����
/***********************   �����ǲ����޸ġ�   ************************/		
    #define      AXSET                   -5    //���ٶȼ�x��
		#define      AYSET                   6  //���ٶȼ�y��
		#define      AZSET                   159    //���ٶȼ�z��
		#define      GXSET                   -8    //������x��
		#define      GYSET                   1     //������y��
		#define      GZSET                   -7    //������z��

#endif

#if INFANTRY == 2               //������������

		#define      SLOW_ONEBULLET_HEAT          19   //һ�ŵ����ӵ�������    
		#define   	 FAST_ONEBULLET_HEAT          27   //һ�Ÿ����ӵ�������  

		#define 		 SLOW_THREEBULLET_HEAT        57   //���ŵ����ӵ�������   
		#define 		 FAST_THREEBULLET_HEAT        81   //���Ÿ����ӵ�������   

	  #define      DIAL_ONE_POSITION       5040 //һ���ӵ���λ��
    #define      DIAL_THREE_POSITION     15150//�����ӵ���λ��
		#define      DIAL_BACK_POSITION      2000 //������λ��
		
#if		DIALPOSITIONORSPEED==1
		#define      LOW_ONE_TIME                30000//һ���ӵ���ʱ�䣨���� 20m/s��
		#define      FAST_ONE_TIME               15000//һ���ӵ���ʱ�䣨���� 17m/s��	
		#define      LOW_THREE_TIME              105000//�����ӵ���ʱ�䣨���� 20m/s��
		#define      FAST_THREE_TIME             45000//�����ӵ���ʱ�䣨���� 17m/s ��		
#else		
		#define      LOW_ONE_TIME                35000 //һ���ӵ���ʱ�䣨���� 20m/s ��
		#define      FAST_ONE_TIME               19000 //һ���ӵ���ʱ�䣨���� 17m/s ��
		#define      LOW_THREE_TIME              120000//�����ӵ���ʱ�䣨���� 20m/s ��
		#define      FAST_THREE_TIME             58000 //�����ӵ���ʱ�䣨���� 17m/s��
		#define      DIAL_SPEED                  4150 //�ٶȻ������ٶ�
		#define      DIAL_ONE_DELAY               11  //һ���ӵ�����ʱ
		#define      DIAL_THREE_DELAY             40  //�����ӵ�����ʱ
#endif			
		
		#define      NORMAL_FRICITION_ON_SPEED   1820   //��ͨĦ���ֻ����ٶ� ��Vave=25m/s��
    #define      LOW_FRICITION_ON_SPEED      1440   //�����Ħ���ֻ����ٶ�(Vave=18/s)				
/***********************    ���ʻ������޸ġ�   ************************/		
		#define      POWER_LIMIT_VALUE      	 76       //����ģʽ�µĹ���
		#define      KEY_LOWSPEED_KP       NORMAL_ZHI_LOWSPEED_KP//����ģʽ��KP
    #define      KEY_HIGHSPEED_KP      NORMAL_ZHI_HIGHSPEED_KP//����ģʽ��KP
		#define      FRICITION_ON_SPEED    NORMAL_FRICITION_ON_SPEED//Ħ���ֿ����ٶ�
/***********************    ��̨�����޸ġ�   ************************/				
		#define      PITCH_UP_LIMIT          30  //pitch����
		#define      PITCH_DOWM_LIMIT        -10   //pitch����
		#define      PITCH_INITIAL_VALUE     1200 //Pitch���ʼֵ  2773   ԽСԽ����
		#define      YAW_INITIAL_VALUE       3985 //Yaw���ʼֵ3985
/***********************   �����ǲ����޸ġ�   ************************/	
    #define      AXSET                   130    //���ٶȼ�x��
		#define      AYSET                   0  //���ٶȼ�y��
		#define      AZSET                   250    //���ٶȼ�z��
		#define      GXSET                   -2    //������x��
		#define      GYSET                   15     //������y��
		#define      GZSET                   -24    //������z��

#endif


#if INFANTRY == 3               //������������
/**********************   �ӵ�λ���������޸ġ�  ***********************/

		#define      SLOW_ONEBULLET_HEAT          19   //һ�ŵ����ӵ�������    
		#define   	 FAST_ONEBULLET_HEAT          29   //һ�Ÿ����ӵ�������  

		#define 		 SLOW_THREEBULLET_HEAT        57   //���ŵ����ӵ�������   
		#define 		 FAST_THREEBULLET_HEAT        84   //���Ÿ����ӵ�������  

	  #define      DIAL_ONE_POSITION       5040 //һ���ӵ���λ��
    #define      DIAL_THREE_POSITION     15150//�����ӵ���λ��
		#define      DIAL_BACK_POSITION      2000 //������λ��

#if		DIALPOSITIONORSPEED==1
		#define      LOW_ONE_TIME                30000//һ���ӵ���ʱ�䣨���� 20m/s��
		#define      FAST_ONE_TIME               15000//һ���ӵ���ʱ�䣨���� 17m/s��	
		#define      LOW_THREE_TIME              105000//�����ӵ���ʱ�䣨���� 20m/s��
		#define      FAST_THREE_TIME             45000//�����ӵ���ʱ�䣨���� 17m/s ��		
#else		
		#define      LOW_ONE_TIME                35000 //һ���ӵ���ʱ�䣨���� 20m/s ��
		#define      FAST_ONE_TIME               19000 //һ���ӵ���ʱ�䣨���� 17m/s ��
		#define      LOW_THREE_TIME              120000//�����ӵ���ʱ�䣨���� 20m/s ��
		#define      FAST_THREE_TIME             58000 //�����ӵ���ʱ�䣨���� 17m/s��
		#define      DIAL_SPEED                  4150 //�ٶȻ������ٶ�
		#define      DIAL_ONE_DELAY               11  //һ���ӵ�����ʱ
		#define      DIAL_THREE_DELAY             40  //�����ӵ�����ʱ
#endif			
		
		#define      NORMAL_FRICITION_ON_SPEED   1430   //��ͨĦ���ֻ����ٶ� ��Vave=27m/s��
    #define      LOW_FRICITION_ON_SPEED      1225   //�����Ħ���ֻ����ٶ�(Vave=18/s)	
/***********************    ���ʻ������޸ġ�   ************************/		

		#define      POWER_LIMIT_VALUE      	 17       //����ģʽ�µĹ���
		#define      KEY_LOWSPEED_KP         NORMAL_ZHI_LOWSPEED_KP//����ģʽ��KP
    #define      KEY_HIGHSPEED_KP        NORMAL_ZHI_HIGHSPEED_KP//����ģʽ��KP
		#define      FRICITION_ON_SPEED      NORMAL_FRICITION_ON_SPEED //Ħ���ֿ����ٶ�
/***********************    ��̨�����޸ġ�   ************************/				
		#define      PITCH_UP_LIMIT          16.5f   //pitch����
		#define      PITCH_DOWM_LIMIT        -11.5f   //pitch����
		#define      PITCH_INITIAL_VALUE     6500 //Pitch���ʼֵ
		#define      YAW_INITIAL_VALUE       646 //Yaw���ʼֵ
/***********************   �����ǲ����޸ġ�   ************************/	  //�����ǵĳ�ʼƫ��
    #define      AXSET                   -114    //���ٶȼ�x��
		#define      AYSET                   177  //���ٶȼ�y��
		#define      AZSET                   27    //���ٶȼ�z��
		#define      GXSET                   14    //������x��
		#define      GYSET                   13     //������y��
		#define      GZSET                   -14   //������z��

#endif

#if INFANTRY == 4                //�����Ĳ�����
/**********************   �ӵ�λ���������޸ġ�  ***********************/

		#define      SLOW_ONEBULLET_HEAT          18   //һ�ŵ����ӵ�������    
		#define   	 FAST_ONEBULLET_HEAT          21   //һ�Ÿ����ӵ�������  

		#define 		 SLOW_THREEBULLET_HEAT        54   //���ŵ����ӵ�������   
		#define 		 FAST_THREEBULLET_HEAT        63   //���Ÿ����ӵ�������    

	  #define      DIAL_ONE_POSITION       5040 //һ���ӵ���λ��
    #define      DIAL_THREE_POSITION     15150//�����ӵ���λ��
		#define      DIAL_BACK_POSITION      2000 //������λ��

#if		DIALPOSITIONORSPEED==1
		#define      LOW_ONE_TIME                30000//һ���ӵ���ʱ�䣨���� 20m/s��
		#define      FAST_ONE_TIME               15000//һ���ӵ���ʱ�䣨���� 17m/s��	
		#define      LOW_THREE_TIME              105000//�����ӵ���ʱ�䣨���� 20m/s��
		#define      FAST_THREE_TIME             45000//�����ӵ���ʱ�䣨���� 17m/s ��		
#else		
		#define      LOW_ONE_TIME                35000 //һ���ӵ���ʱ�䣨���� 20m/s ��
		#define      FAST_ONE_TIME               19000 //һ���ӵ���ʱ�䣨���� 17m/s ��
		#define      LOW_THREE_TIME              120000//�����ӵ���ʱ�䣨���� 20m/s ��
		#define      FAST_THREE_TIME             58000 //�����ӵ���ʱ�䣨���� 17m/s��
		#define      DIAL_SPEED                  4150 //�ٶȻ������ٶ�
		#define      DIAL_ONE_DELAY               11  //һ���ӵ�����ʱ
		#define      DIAL_THREE_DELAY             40  //�����ӵ�����ʱ
#endif			
		#define      NORMAL_FRICITION_ON_SPEED   1600   //��ͨĦ���ֻ����ٶ� ��Vave=21m/s��
    #define      LOW_FRICITION_ON_SPEED      1240   //�����Ħ���ֻ����ٶ�(Vave=18/s)	
/***********************    ���ʻ������޸ġ�   ************************/		
		#define      POWER_LIMIT_VALUE      	 76       //����ģʽ�µĹ���
		#define      KEY_LOWSPEED_KP         NORMAL_ZHI_LOWSPEED_KP//����ģʽ��KP
    #define      KEY_HIGHSPEED_KP        NORMAL_ZHI_HIGHSPEED_KP//����ģʽ��KP
		#define      FRICITION_ON_SPEED      NORMAL_FRICITION_ON_SPEED //Ħ���ֿ����ٶ�
/***********************    ��̨�����޸ġ�   ************************/				
		#define      PITCH_UP_LIMIT          13   //pitch����
		#define      PITCH_DOWM_LIMIT        -3.5f   //pitch����
		#define      PITCH_INITIAL_VALUE     6500 //Pitch���ʼֵ
		#define      YAW_INITIAL_VALUE       2680 //Yaw���ʼֵ
/***********************   �����ǲ����޸ġ�   ************************/	
    #define      AXSET                   -114    //���ٶȼ�x��
		#define      AYSET                   177  //���ٶȼ�y��
		#define      AZSET                   27    //���ٶȼ�z��
		#define      GXSET                   14    //������x��
		#define      GYSET                   13     //������y��
		#define      GZSET                   -14   //������z��

		
#endif





#endif




