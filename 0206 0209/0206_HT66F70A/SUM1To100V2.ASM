; PROGRAM : SUM1To100V2.ASM            By Steven                    
; FUNCTION: BCD DEMO PROGRAM         2017.0512      		  
#INCLUDE    HT66F70A.INC 
;=================================================================================
MY_DATA    .SECTION		'DATA'    	;== DATA SECTION == 此程式效能比上一個較好 請看輸出往上拉 ROM RAM 的Total Used
SUM    	DB   	2 DUP	(?)         ;DUP是複製duplication 紅字2=複製2次  ==>>SUM[0] SUM[1]
X    	DB      ?                  	;;;此版本是從100開始加到1  反過來 比較快
;========================================================================================
MY_CODE    .SECTION	 at 0	'CODE' 	;== PROGRAM SECTION == 
		MOV		A,0AFh				;DISABLE WDT
		MOV		WDTC,A
		CLR		SUM[0]
		CLR		SUM[1]
		MOV		A,100			;A=100
		MOV		X,A				;X=100
LOOP:		
		MOV		A,X				;A=X (100/99...1)
		ADDM	A,SUM[0]		;SUM[0]=A+SUM[0] (100+99+...+1) {當加超過256會進位到C}
		CLR		ACC				;清除ACC EQU 05H  不能寫A因為會判別成Syntax error 但可以寫成[05H]{此為累加器A的記憶體位置}
		ADCM	A,SUM[1]		;A=A+SUM[1]+C暫存器SUM[1]累加器A以及進位旗標C相加 將結果存至A
		SDZ		X				;將暫存器-1，若結果為0則跳過下一行 99/98.../1/0
		JMP		LOOP
		JMP		$
		
		;最後請觀察下面變數 SUM[1]=19  *256(2^8) + SUM[0]=186 = 4864+186=5050  //OR  16進位0x13ba = 5050