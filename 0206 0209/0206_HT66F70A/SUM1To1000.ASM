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
		CLR		SUM[2] ;15-17 先清除三個byte
		MOV		A,1	
		MOV		X[0],A  ;存放1
		CLR		X[1]	
		MOV		A,10
		MOV		L1,A	;相加 內層相加10次
LOOP1:		
		MOV		A,100	;外層 相加一百次 結果是1000
		MOV		L2,A
LOOP:		
		MOV		A,X[0]	
		ADDM	A,SUM[0]	
		MOV		A,X[1]
		ADCM	A,SUM[1] ;進位時放到高八位元
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