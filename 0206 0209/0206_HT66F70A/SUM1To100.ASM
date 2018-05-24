; PROGRAM : SUM1To100.ASM            By Steven                    
; FUNCTION: BCD DEMO PROGRAM         2017.0512      		  
#INCLUDE    HT66F70A.INC 
;=================================================================================
MY_DATA    .SECTION		'DATA'    	;== DATA SECTION == 
SUM_HI 	DB   	?         
SUM_LO 	DB   	?         
X    	DB      ?                  	
;========================================================================================
MY_CODE    .SECTION	 at 0	'CODE' 	;== PROGRAM SECTION == 
		MOV		A,0AFh				;DISABLE WDT
		MOV		WDTC,A
		CLR		SUM_HI
		CLR		SUM_LO
		CLR		X
LOOP:		
		MOV		A,X
		ADDM	A,SUM_LO	
		CLR		ACC
		ADCM	A,SUM_HI
		INC		X
		MOV		A,100		;(line 22-24)是用來設定X=100的時候停止 100之前反轉到 到100時跳過25行(回到LOOP)
		SUB		A,X         ;(line 22-24)是用來設定X=100的時候停止
		SZ		C			;(line 22-24)是用來設定X=100的時候停止
		JMP		LOOP
		JMP		$			;這邊要設中斷點(行數上面按一下break point) 週期=1014  否則會無限迴圈