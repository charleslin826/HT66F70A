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
		MOV		A,100		;(line 22-24)�O�Ψӳ]�wX=100���ɭ԰��� 100���e����� ��100�ɸ��L25��(�^��LOOP)
		SUB		A,X         ;(line 22-24)�O�Ψӳ]�wX=100���ɭ԰���
		SZ		C			;(line 22-24)�O�Ψӳ]�wX=100���ɭ԰���
		JMP		LOOP
		JMP		$			;�o��n�]���_�I(��ƤW�����@�Ubreak point) �g��=1014  �_�h�|�L���j��