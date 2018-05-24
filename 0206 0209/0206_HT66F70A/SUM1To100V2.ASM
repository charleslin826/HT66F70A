; PROGRAM : SUM1To100V2.ASM            By Steven                    
; FUNCTION: BCD DEMO PROGRAM         2017.0512      		  
#INCLUDE    HT66F70A.INC 
;=================================================================================
MY_DATA    .SECTION		'DATA'    	;== DATA SECTION == ���{���į��W�@�Ӹ��n �Ьݿ�X���W�� ROM RAM ��Total Used
SUM    	DB   	2 DUP	(?)         ;DUP�O�ƻsduplication ���r2=�ƻs2��  ==>>SUM[0] SUM[1]
X    	DB      ?                  	;;;�������O�q100�}�l�[��1  �ϹL�� �����
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
		ADDM	A,SUM[0]		;SUM[0]=A+SUM[0] (100+99+...+1) {���[�W�L256�|�i���C}
		CLR		ACC				;�M��ACC EQU 05H  ����gA�]���|�P�O��Syntax error ���i�H�g��[05H]{�����֥[��A���O�����m}
		ADCM	A,SUM[1]		;A=A+SUM[1]+C�Ȧs��SUM[1]�֥[��A�H�ζi��X��C�ۥ[ �N���G�s��A
		SDZ		X				;�N�Ȧs��-1�A�Y���G��0�h���L�U�@�� 99/98.../1/0
		JMP		LOOP
		JMP		$
		
		;�̫���[��U���ܼ� SUM[1]=19  *256(2^8) + SUM[0]=186 = 4864+186=5050  //OR  16�i��0x13ba = 5050