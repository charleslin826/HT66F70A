; PROGRAM : SUM1To10.ASM            By Steven                    
; FUNCTION: BCD DEMO PROGRAM        2017.0512      		  
#INCLUDE    HT66F70A.INC 
;=================================================================================
MY_DATA    .SECTION		'DATA'     	;== DATA SECTION == 
SUM    	DB       ?                  	
X    	DB       ?               	;DELAY LOOP COUNT 2 
;========================================================================================
MY_CODE    .SECTION	 at 0	'CODE'	;== PROGRAM SECTION == 
		MOV		A,0AFh					;DISABLE WDT
		MOV		WDTC,A
		CLR		SUM					;SUM=0
		CLR		X					;X=0
LOOP:		
		MOV		A,SUM				;A=SUM=0
		ADD		A,X					;A=A+X=0
		MOV		SUM,a				;SUM=a
		INC		X					;X=X+1
		MOV		A,10				;A=10
		SUB		A,X					;A=A-X = 10-1=9          //C=0 if X > 10  (需要借位)
		SZ		C					;若C=0則跳到下一行
		JMP		LOOP				;跳回LOOP
		JMP		$					;代表這個指令的所在位置(PC=22) 