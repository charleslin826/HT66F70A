; PROGRAM : IAR.ASM  		        				By Steven                    
; FUNCTION: Indirect Addressing DEMO PROGRAM        2017.0512      		  
#INCLUDE    HT66F70A.INC 
;=================================================================================
MY_DATA    .SECTION		'DATA'          ;== DATA SECTION == 
Array1		DB 128 dup(?)        		;Reserve 128 Byte with Start Address -> Array 
RAMBANK 2  	MY_DATABack
MY_DATABack .SECTION	'DATA'          ;== DATA SECTION == 
Array2		DB 128 dup(?)        		;Reserve 128 Byte with Start Address -> Array 
;========================================================================================
MY_CODE    .SECTION	 at 0	'CODE'     	;== PROGRAM SECTION == 
MAIN:
		MOV		A,0AFh					;DISABLE WDT
		MOV		WDTC,A
		MOV		a,OFFSET Array1			;MP0�û��ȫ��VBANK0
		MOV		MP0,A
		MOV		a,128
LOOP1:		
		CLR		IAR0					;�NMP0�ҫ��V����}���e�M��0
		INC		MP0
		SDZ		ACC
		JMP		LOOP1
;=======================================================================		
		MOV		A,Low OFFSET Array2		;�_�I1
		MOV		MP1L,A					
		MOV		A,High OFFSET Array2
		MOV		MP1H,A		
		MOV		a,128
LOOP2:		
		SET		IAR1					;�NMP1�ҫ��V����}���e�]��FF
		INC		MP1L
		SDZ		ACC
		JMP		LOOP2
		JMP		$						;�_�I2					
;=======================================================================		
		END