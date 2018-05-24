; PROGRAM : SUM1To1000.ASM      	By Steven                    
; FUNCTION: BCD DEMO PROGRAM      	2017.0512   
; ANS=500500(Dec) ==> 73A14 (Hex)  		  
#INCLUDE    HT66F70A.INC 
;=================================================================================
MY_DATA    .SECTION		'DATA'    	;== DATA SECTION == 
SUM    	DB   	3 DUP	(?)  
X		DB   	2 DUP	(?) 
L1    	DB      ?
L2		DB 		?                 	
;========================================================================================
MY_CODE    .SECTION	 at 0	'CODE' 	;== PROGRAM SECTION == 
		MOV		A,0AFh				;DISABLE WDT
		MOV		WDTC,A
		CLR		SUM[0]
		CLR		SUM[1]
		CLR		SUM[2] ;15-17 ���M���T��byte
		MOV		A,1	
		MOV		X[0],A  ;�s��1
		CLR		X[1]	
		MOV		A,10
		MOV		L1,A	;�ۥ[ ���h�ۥ[10��
LOOP1:		
		MOV		A,100	;�~�h �ۥ[�@�ʦ� ���G�O1000
		MOV		L2,A
LOOP:		
		MOV		A,X[0]	
		ADDM	A,SUM[0]	
		MOV		A,X[1]
		ADCM	A,SUM[1] ;�i��ɩ�찪�K�줸
		CLR		ACC
		ADCM	A,SUM[2]
		MOV		A,1
		ADDM	A,X[0]
		CLR		ACC
		ADCM	A,X[1]
		SDZ		L2
		JMP		LOOP
		SDZ		L1
		JMP		LOOP1
		JMP		$