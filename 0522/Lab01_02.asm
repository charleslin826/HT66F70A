; PROGRAM : Lab01                         		By Steven                    
; FUNCTION: LED SCANNING DEMO PROGRAM           2017.0512
; 載入定義檔之方便性與易讀性！若要改成其他PORT控制，麻煩～   
#INCLUDE    HT66F70A.INC 		  
;=================================================================================
MY_DATA    .SECTION		'DATA'          ;== DATA SECTION == 
DEL1    DB       ?                  	;DELAY LOOP COUNT 1 
DEL2    DB       ?                  	;DELAY LOOP COUNT 2 
DEL3	DB   	 ?        				;DELAY LOOP COUNT 3 
;========================================================================================
MY_CODE    .SECTION		'CODE'     		;== PROGRAM SECTION == 
        ORG     00H                    	;HT66Fxx RESET VECTOR 
MAIN: 
		MOV		A,0AFh					;DISABLE WDT
		MOV		WDTC,A
		CLR		PCC          			;CONFIG LED_PORT AS O/P MODE 
		SET		PC           			;SET INITIAL LED STATE
		CLR		C                  		;SET CARRY FLAG (STATUS.0) 
RIGHT:             
		RRC		PC        				;SHIFT RIGHT 
		MOV 	A,100         			;SET DELAY FACTOR 
		CALL	DELAY               	;DELAY 100*1mS 
		SZ  	PC.0          			;IS ALL LEDs HAVE BEEN LIT? 
		JMP		RIGHT               	;NO. CONTINUE RIGHT SHIFT. 
LEFT:   
		RLC     PC    					;SHIFT LEFT 
		MOV		A,200         			;SET DALAY FACTOR 
		CALL	DELAY               	;DELAY 200*1mS 
		SZ		PC.7          			;IS ALL LEDs HAVE BEEN LIT? 
		JMP		LEFT                	;NO. CONTINUE LEFT SHIFT. 
		JMP		RIGHT               	;REPEAT THE RIGHT PROCESS. 
;========================================================================================
; PROC	: DELAY
; FUNC	: DEALY ABOUT ACC*1mS @fSYS=8MHz  (1996×Acc)+2 Cycles!
; PARA	: ACC : DELAY FACTOR
; REG	: DEL1,DEL2,DEL3
;======================================================================================== 
DELAY  	PROC
		MOV		DEL1,A					;SET DEL1 COUNTER	
DEL_1:  MOV		A,3		        	                   	
        MOV		DEL2,A					;SET DEL2 COUNTER 
DEL_2:	MOV		A,220
		MOV		DEL3,A					;SET DEL3 COUNTER
DEL_3:  SDZ		DEL3                  	;DEL3 DOWN COUNT
        JMP		DEL_3                      
        SDZ		DEL2                  	;DEL2 DOWN COUNT
        JMP		DEL_2                   
		SDZ		DEL1					;DEL1 DOWN COUNT
		JMP		DEL_1
        RET
DELAY	ENDP