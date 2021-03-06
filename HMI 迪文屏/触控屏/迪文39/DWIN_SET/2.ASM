﻿  ; DWIN OS
  ;R245,定时器4C倒计时;R246,赋值4CH为FF;R247,4C返回到的值
  ;R248,上电初始化标志
  ;R249,RTC秒的变化比较
  ;R250,R251,上一次触摸屏幕计时
  ;R252，R253,历史编号序号1-100，最多保存100条
  ;R254,编号序号初始赋值0
  ;R255,保存分两步
  
  
  
  
    
    IJNE	R245,0,SSTART			;标志位R245,计算检测单元第4个的时间
    CALL	READING
    CALL	PASSWORD
    CALL	PASSWORD_CHANGE
    CALL	DORMANCY_READ
    CALL	DOR_TIME
    CALL	SPECCY
    CALL	COMPAER_ONE
    CALL	ORDER_H
    CALL	ORDER_M
    END
 ;==============  密码登录  ================   
PASSWORD:   
	LDWR	R0,510H
    MOVXR	R80,1,1
    IJNE	R81,1,PASS_RET
    LDWR	R80,0
    MOVXR	R80,0,1
    LDWR	R0,500H
    MOVXR	R80,1,2
	LDWR	R4,0011H
    LDWR	R6,0001H
    LDWR	R0,510H
    MOVXL	2,2
    MOVXR	R84,1,2
    TESTS	R80,R84,4
    IJNE	R0,0,ERROR_1
    LDWR	R88,12
    MOVRD	R88,3,2
ERROR_1:
	LDWR	R0,500H
	LDBR	R80,0,4
    MOVXR	R80,0,2   
PASS_RET:
    RET
 ;----------  更改密码  ---------------   
PASSWORD_CHANGE:
	LDWR	R0,12H
    MOVXR	R80,1,1
    IJNE	R81,1,CHANGE_RET
    LDWR	R80,0
    MOVXR	R80,0,1
    LDWR	R0,505H
	LDWR	R4,0011H
    LDWR	R6,0001H
    MOVXL	3,2   
CHANGE_RET:
	RET    
;=========== 休眠时间计时 =================
DORMANCY_READ:
	MOVDR	5,R90,1
	IJNE	R90,5AH,TTT
	LDBR	R90,0,1
	MOVRD	R90,5,1
	LDWR	R250,0
	LDBR	R170,40H,1
	MOVRD	R170,1,1
	RET
TTT:
	MOVDR	26H,R91,1
	CJNE	R91,R249,1
	GOTO	D_RET
	MOV		R91,R249,1
	INC		R250,1,1
	LDBR	R150,0,16
	LDWR	R0,50H
	MOVXR	R152,1,1
	LDWR	R156,60
	MAC		R150,R154,R158
	JS		R250,R164,D_RET
	LDBR	R170,0,1
	MOVRD	R170,1,1
D_RET:
	RET
;----------- 更改休眠时间 ------------------
DOR_TIME:
	LDWR	R0,11H
    MOVXR	R80,1,1
    IJNE	R81,1,TIME_RET
    LDWR	R80,0
    MOVXR	R80,0,1
    LDWR	R0,50H
    LDWR	R4,0011H
    LDWR	R6,0003H
    MOVXL	3,1    
 TIME_RET:
 	RET
;========== 检测4个单元，均正常进入主界面 ==========    
SPECCY:

	CALL	SPECCY1
	CALL	SPECCY2
	CALL	SPECCY3
	CALL	SPECCY4
	RET
	
SPECCY1:	
	MOVDR	4,R10,1
	IJNE	R10,1,SPE_RET1    
	LDWR	R10,1
	LDWR	R0,0001H
	MOVXR	R12,1,1
	JS		R12,R10,SPE_RET1
	LDWR	R22,2
	MOVRD	R22,3,2
	
SPE_RET1:
	RET	
SPECCY2:	
	MOVDR	4,R10,1
	IJNE	R10,3,SPE_RET2
	LDWR	R10,1
	LDWR	R0,0002H
	MOVXR	R14,1,1
	JS		R14,R10,SPE_RET2
	LDWR	R22,4
	MOVRD	R22,3,2
	
SPE_RET2:
	RET	
SPECCY3:	
	MOVDR	4,R10,1
	IJNE	R10,5,SPE_RET3
	LDWR	R10,1
	LDWR	R0,0003H 
	MOVXR	R16,1,1
	JS		R16,R10,SPE_RET3
	LDWR	R22,6
	MOVRD	R22,3,2
	
SPE_RET3:
	RET	
SPECCY4:	
	MOVDR	4,R10,1
	IJNE	R10,7,SPE_RET4
	LDWR	R10,1
	LDWR	R0,0004H
	MOVXR	R18,1,1
	JS		R18,R10,SPE_RET4
	LDWR	R22,8
	MOVRD	R22,3,2
	
	LDBR	R11,1,1
	AND		R11,R13,1
	AND		R11,R15,1
	AND		R11,R17,1
	AND		R11,R19,1
	
	IJNE	R11,1,COUNT_SECOND
	LDWR	R22,9
	MOVRD	R22,3,2
	
SPE_RET4: 
	RET
COUNT_SECOND:
	LDBR	R246,FFH,1
	MOVRD	R246,4CH,1
	LDBR	R245,1,1
SSTART:	
	MOVDR	4CH,R247,1
	IJNE	R247,0,END1
	
	LDBR	R245,0,1
	LDWR	R22,0	
	MOVRD	R22,3,2	
	RET	
END1:
	END
	
;==========  上电读取部分固定的数据信息 =========    
READING: 
	LDWR	R4,0011H
	LDWR	R6,0
	LDWR	R0,4100H
	MOVXL	2,1
	MOVXR	R150,1,1
	LDWR	R152,5AA5H
	TESTS	R150,R152,2
	IJNE	R0,0,WRITE_1		 ;第一次初始密码和休眠时间
	IJNE	R254,0,WRITE_2
	
	IJNE  	R248,0,SAVE_INFOR	
    LDBR  	R248,1,1			  ;标志位R248
 	COMSET 	0,651  			      ;COM1初始,9600bps
 	
 	LDWR	R4,0011H
	LDWR	R6,1
	LDWR	R0,4201H
	MOVXL	2,3H
	
	LDWR	R0,4203H
	LDWR	R2,0050H			 ;0060003，休眠时间
	MOVXX	1
	
 	RET
WRITE_1:
	LDBR	R254,1,1	
	LDWR	R10,5AA5H
	LDWR	R12,1
	LDWR	R14,E240H
	LDWR	R16,5
	LDBR	R18,0,10
	LDWR	R0,4120H
	MOVXR	R10,0,5
	LDWR	R4,0011H
	LDWR	R6,0
	MOVXL	3,5
	RET
WRITE_2:
	LDBR	R254,0,1	
	LDWR	R150,0
	LDWR	R0,3300H
	MOVXR	R150,0,1
	LDWR	R4,0011H
	LDWR	R6,20H
	MOVXL	3,1
	RET
;----------------------           
 SAVE_INFOR:	           
	RET
;========== 进入一次测试界面 ===================== 
COMPAER_ONE:
		LDWR	R0,001AH		
  		MOVXR	R30,1,1
  		IJNE	R31,1,COMPARE_RET
  		LDWR	R30,0
  		MOVXR	R30,0,1
  		
  		LDWR 	R4,11H         ;;;读上一次历史编号
	    LDWR 	R6,10H
	    LDWR	R0,300H
  	    MOVXL 	2,6	          
 		MOVXR	R201,1,6	
RI:	
	MOVDR	20H,R50,3		;;;比较时间是否为同一天
	BITS	R52,0304H       ;;;日
	    LDWR	R50,0
	    LDWR	R0,0300H
	    MOVXR	R50,0,1
	    LDWR	R50,0
	    LDWR	R0,0301H
	    MOVXR	R50,0,1
	    LDWR	R50,1
	    LDWR	R0,0302H
	    MOVXR	R50,0,1
	    LDWR	R50,1
	    LDWR	R0,0303H
	    MOVXR	R50,0,1
	BITI	R61,0300H
	    LDWR	R50,0
	    LDWR	R0,0304H
	    MOVXR	R50,0,1
	    LDWR	R50,0
	    LDWR	R0,0305H
	    MOVXR	R50,0,1
	    LDWR	R50,1
	    LDWR	R0,0306H
	    MOVXR	R50,0,1
	    LDWR	R50,1
	    LDWR	R0,0307H
	    MOVXR	R50,0,1
	BITI	R62,0304H
			CJNE	R61,R207,2			;比较日的前一位数是否相同
			CJNE	R62,R208,1			;比较日的后一位数是否相同
	        GOTO	YUE
  		MOV		R61,R207,2				;日不同则日的两位ASC码R61  R62给R207  R208
  		LDBR	R209,30H,3				;
  		
  YUE:	
	MOVDR	20H,R50,3		;;;比较时间是否为同一天
	BITS	R51,0304H       ;;;月
	    LDWR	R50,0
	    LDWR	R0,0300H
	    MOVXR	R50,0,1
	    LDWR	R50,0
	    LDWR	R0,0301H
	    MOVXR	R50,0,1
	    LDWR	R50,1
	    LDWR	R0,0302H
	    MOVXR	R50,0,1
	    LDWR	R50,1
	    LDWR	R0,0303H
	    MOVXR	R50,0,1
	BITI	R61,0300H
	    LDWR	R50,0
	    LDWR	R0,0304H
	    MOVXR	R50,0,1
	    LDWR	R50,0
	    LDWR	R0,0305H
	    MOVXR	R50,0,1
	    LDWR	R50,1
	    LDWR	R0,0306H
	    MOVXR	R50,0,1
	    LDWR	R50,1
	    LDWR	R0,0307H
	    MOVXR	R50,0,1
	BITI	R62,0304H
			CJNE	R61,R205,2
			CJNE	R62,R206,1
	        GOTO	NIAN
  		MOV		R61,R205,2		;月不同则月的两位ASC码R61  R62给R205  R206
  		LDBR	R209,30H,3		;R209 R210 R211的ASC码从000开始
  		
NIAN:	
	MOVDR	20H,R50,3		;;;比较时间是否为同一天
	BITS	R50,0304H       ;;;年
	    LDWR	R50,0
	    LDWR	R0,0300H
	    MOVXR	R50,0,1
	    LDWR	R50,0
	    LDWR	R0,0301H
	    MOVXR	R50,0,1
	    LDWR	R50,1
	    LDWR	R0,0302H
	    MOVXR	R50,0,1
	    LDWR	R50,1
	    LDWR	R0,0303H
	    MOVXR	R50,0,1
	BITI	R61,0300H
	    LDWR	R50,0
	    LDWR	R0,0304H
	    MOVXR	R50,0,1
	    LDWR	R50,0
	    LDWR	R0,0305H
	    MOVXR	R50,0,1
	    LDWR	R50,1
	    LDWR	R0,0306H
	    MOVXR	R50,0,1
	    LDWR	R50,1
	    LDWR	R0,0307H
	    MOVXR	R50,0,1
	BITI	R62,0304H
			CJNE	R61,R203,2
			CJNE	R62,R204,1
	        GOTO	BIANHAO
  		MOV		R61,R203,2			;年不同则年的两位ASC码R61  R62给R203  R204
  		LDBR	R209,30H,3 		
  		
  	BIANHAO:
  			LDBR	R201,32H,1
  			LDBR	R202,30H,1		;R201 R202是20？（年的前两位）
  			LDBR	R212,00H,1		;R212赋值FF，不显示这一字节
	  			INC		R211,0,1	;编号的最低位在原来的基础上加1
	  			IJNE	R211,3AH,7
	  			LDBR	R211,30H,1
	  			INC		R210,0,1
	  			IJNE	R210,3AH,4
	  			LDBR	R210,30H,1
	  			INC		R209,0,1
	  			IJNE	R209,3AH,1
	  			LDBR	R209,30H,1
  			LDWR	R0,0110H		;显示这编号
  			MOVXR	R201,0,6
  			LDWR 	R4,11H         ;;;保存最新的历史编号
	    	LDWR 	R6,10H
	        MOVXL   3,6
COMPARE_RET:
		RET
;==============  动作和状态指令 =========
ORDER_H:
	LDWR	R0,0136H		
  	MOVXR	R30,1,1
  	IJNE	R31,1,6
  	LDWR	R30,0
  	MOVXR	R30,0,1					;开始检测
  	LDWR	R101,5AA5H
	LDWR	R103,F101H
 	COMTXI	0,R101,4
    RET
    
    LDWR	R0,0006H		
  	MOVXR	R30,1,1
  	IJNE	R31,1,6
  	LDWR	R30,0					;血糖高
  	MOVXR	R30,0,1	
  	LDWR	R101,5AA5H
	LDWR	R103,F102H
 	COMTXI	0,R101,4
	RET
	
	LDWR	R0,0007H		
  	MOVXR	R30,1,1
  	IJNE	R31,1,6
  	LDWR	R30,0					;血糖低
  	MOVXR	R30,0,1
  	LDWR	R101,5AA5H
	LDWR	R103,F103H
 	COMTXI	0,R101,4
 	RET

	LDWR	R0,0020H		
  	MOVXR	R30,1,1
  	IJNE	R31,1,6
  	LDWR	R30,0
  	MOVXR	R30,0,1	
  	LDWR	R101,5AA5H				;关机
	LDWR	R103,F105H
 	COMTXI	0,R101,4
 	RET
 	
 	LDWR	R0,0013H		
  	MOVXR	R30,1,1
  	IJNE	R31,1,6
  	LDWR	R30,0
  	MOVXR	R30,0,1	
  	LDWR	R101,5AA5H				;自动
	LDWR	R103,F106H
 	COMTXI	0,R101,4
 	RET
 	
 	IJNE	R31,2,6
  	LDWR	R30,0
  	MOVXR	R30,0,1	
  	LDWR	R101,5AA5H				;手动
	LDWR	R103,F107H
 	COMTXI	0,R101,4
 	RET
 	
 	LDWR	R0,0002H		
  	MOVXR	R30,1,1
  	IJNE	R31,1,6
  	LDWR	R30,0
  	MOVXR	R30,0,1	
  	LDWR	R101,5AA5H				;显示单元指令
	LDWR	R103,F1ABH
 	COMTXI	0,R101,4
 	RET
;=============  打印和保存 =======================
ORDER_M:
;--- 检测页面的打印	----------	
		LDWR	R0,0137H		
  		MOVXR	R30,1,1
  		IJNE	R31,1,DATA_1	;打印键按下
  		LDWR	R30,0
  		MOVXR	R30,0,1
  		
  		LDWR	R101,5AA5H
		LDBR	R103,F2H,1
		LDWR	R0,0110H
	    MOVXR	R50,1,6
	    MOV		R50,R104,11
	    
	    MOVDR	20H,R50,7
	    MOV		R50,R115,3			;打印的日期年月日
	    MOV		R54,R118,3			;打印的日期时分秒
	   
	    LDWR	R0,0170H	    
	    MOVXR	R50,1,3
	    MOV		R51,R121,1
	    MOV		R53,R122,1
	    MOV		R55,R123,1
	   
	    COMTXI	0,R101,23
		RET
	    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;实时测试存储;;;;;;;;;;;;;;;;;;;;;;;;	
DATA_1:
		LDWR	R0,3400H
		LDWR	R4,0011H
		LDWR	R6,20H
		MOVXL	2,1
		MOVXR	R252,1,1			;历史编号的序号1-100
		
		LDWR	R0,0138H		
  		MOVXR	R30,1,1
  		IJNE	R31,1,DATA_2
  		
  		IJNE	R255,0,10
  		LDBR	R255,1,1
  		
  		IJNE	R253,100,1
 		LDWR	R252,0
 		INC		R252,1,1
 		LDWR	R0,3400H
 		MOVXR	R252,0,1
		LDWR	R4,0011H
		LDWR	R6,20H				;历史编号序号加1
		MOVXL	3,1
		RET
  		
  		LDBR	R255,0,1
  		LDWR	R0,0138H
  		LDWR	R30,0
  		MOVXR	R30,0,1
  		LDWR	R101,5AA5H
		LDBR	R103,F2H,1 		
		LDWR	R0,0110H
	    MOVXR	R50,1,6			;编号
	    MOV		R50,R104,11
	    	    
	    MOVDR	20H,R50,7
	    MOV		R50,R115,3
	    MOV		R54,R118,3		;时间
	  
	    LDWR	R0,0170H	    
	    MOVXR	R50,1,3
	    MOV		R51,R121,1
	    MOV		R53,R122,1
	    MOV		R55,R123,1
	   
 		LDBR	R170,0,16
		MOV		R252,R172,2
		LDWR	R176,35
		MAC		R170,R174,R178
		MOV		R182,R170,4
		LDWR	R174,0070H
		LDWR	R176,0
		ADD		R170,R174,R178
		MOV		R182,R4,4
		
		LDWR	 R0,0300H        
 		MOVXR	 R101,0,35
		MOVXL	3,35
    	    
		RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;实时测试返回;;;;;;;;;;;;;;;;;;;;;;;;

DATA_2: 
		LDWR	R0,0139H		
  		MOVXR	R30,1,1
  		IJNE	R31,1,DATA_3
  		LDWR	R30,0
  		MOVXR	R30,0,1
  		
		LDWR	R0,0110H
		LDBR	R50,0,20
		MOVXR	R50,0,10
		LDWR	R0,0170H
		LDBR	R50,0,6
		MOVXR	R50,0,3
		
		RET 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;报警;;;;;;;;;;;;;;;;;;;;;;;;
ALARM_G:	
        LDWR	R0,0136H		
  		MOVXR	R30,1,1
  		IJNE	R31,1,S_RET     ;报警键按下
  		LDWR	R30,0
  		MOVXR	R30,0,1
  		
  	    LDWR    R0,0170H
  	    MOVXR   R160,1,1
        LDWR    R162,0x003D
  		JS		R160,R162,ALARM_D
  		LDBR    R166,10,1
  		MOVRD   R166,2,1
  		LDBR	R166,0,1
  		MOVRD	R166,2,1
  		RET
ALARM_D:	
        LDWR    R162,0x0027
  		JS		R160,R162,A
  		RET
    A:
  		LDBR    R166,20,1
  		MOVRD   R166,2,1
  		LDBR	R166,0,1
  		MOVRD	R166,2,1
        RET
 S_RET:
         RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;查询;;;;;;;;;;;;;;;;;;;;;;;;
DATA_3:	
		LDWR	R0,00A1H		
  		MOVXR	R30,1,1
  		IJNE	R31,1,H
  		LDWR	R30,0
  		MOVXR	R30,0,1
                  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;当前输入 		
  		LDWR	R0,0070H
	    MOVXR	R210,1,6
	    IJNE   	R210,0,1		;编号不为0则扫描
	    RET
	    	     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;扫描历史
	      
 		LDWR 	R4,0070H
	    LDWR 	R6,35
	    LDWR	R0,2000H
   	    MOVXL 	0,DACH	 
   		
   		
   		LDWR	R192,2023H
 G:  	MOV		R192,R0,2
 		MOVXR	R101,1,35	
 			IJNE	R210,0,1
 			GOTO	N_RET
 			CJNE	R210,R104,11
 			CJNE	R211,R105,10
 			CJNE	R212,R106,9
 			CJNE	R213,R107,8
 			CJNE	R214,R108,7
 			CJNE	R215,R109,6
 			CJNE	R216,R110,5
 			CJNE	R217,R111,4
 			CJNE	R218,R112,3
 			CJNE	R219,R113,2
 			CJNE	R220,R114,1
 			GOTO	G1
	 N:	    INC 	R192,1,35    ;查询下一个序号的保存记录
	 		LDWR	R230,2DE1H
	    	TESTS 	R192,R230,2
	    	IJNE	R0,0,G
	    	LDWR 	R192,35  
	    	RET
	    	
	G1:	
		
		LDWR	R101,5AA5H
		LDBR	R103,F2H,1
		
;     	LDWR	R0,0210H
;		MOV		R104,R50,11
;		LDBR	R61,0,1
;	    MOVXR	R50,0,6
	   
	    LDWR	R0,0262H
	    MOV		R115,R50,3		;日期年月日
	    LDBR	R53,0,1
	    MOVXR	R50,0,2
	    LDWR	R0,0264H
	    MOV		R118,R50,3
	    LDBR	R53,0,1
	    MOVXR	R50,0,2
	    	    
	    LDWR	R0,0270H
	    LDBR	R50,0,6
	    MOV		R121,R51,1
	    MOV		R122,R53,1
	    MOV		R123,R55,1
	    MOVXR	R50,0,3
N_RET:	    
		RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;查询返回;;;;;;;;;;;;;;;;;;;;;;;;  
	H:	LDWR	R0,00A2H		
  		MOVXR	R30,1,1
  		IJNE	R31,1,SSS
  		LDWR	R30,0
  		MOVXR	R30,0,1
  		
		LDWR	R0,0070H
		LDBR	R50,0,20
		MOVXR	R50,0,10
		LDWR	R0,0270H
		LDBR	R50,0,6
		MOVXR	R50,0,3
		LDWR	R0,0262H
		LDBR	R50,0,6
		MOVXR	R50,0,3
		
		RET  
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;查询打印;;;;;;;;;;;;;;;;;;;;;;;;   
SSS:
		LDWR	R0,0237H		
  		MOVXR	R30,1,1
  		IJNE	R31,1,SS_RET
  		LDWR	R30,0
  		MOVXR	R30,0,1
  		
  		LDWR	R101,5AA5H
		LDBR	R103,F2H,1
		LDWR	R0,0070H			;编号
	    MOVXR	R50,1,6
	    MOV		R50,R104,11
	    LDWR	R0,0262H			;检测时间
	    MOVXR	R50,1,4
	    MOV		R50,R115,3
	    MOV		R54,R118,3
	    LDWR	R0,0270H
	    MOVXR	R50,1,3
	    MOV		R51,R121,1
	    MOV		R53,R122,1
	    MOV		R55,R123,1
	 
	    COMTXI	0,R101,23    
SS_RET:	    
		RET	
