; Generated by holtek-gcc v3.18, Tue Apr 10 11:44:28 2018
; 
; Configuration:
;       with long instruction
;       Multi-ROM, Multi-RAM
;       bits_per_rom_unit:16
;       with mp1
;       with tbhp, address(0x9)
;          Use tabrd-const
;       
; SFR address of long-instruction arch:
;    mp0 = -1,1,0
;    mp1 = 4,3,2
;    mp2 = 14,13,12
;    tbp = 9,7,8
;    acc = 5
;    pcl = 6
;    status = 10
;    bp = 11
;    intc = 48
;       
;       
; use 'tabrdc' instead of 'tabrd'
;       

#pragma translator "holtek-gcc 4.6.4" "3.18" "build 20130711"
; Rebuild 126

ir equ [2]
mp equ [3]
sbp equ [4]
acc equ [5]
bp equ [11]
tblp equ [7]
tbhp equ [9]
status equ [10]
c equ [10].0
ac equ [10].1
z equ [10].2
ov equ [10].3
cz equ [10].6
sc equ [10].7
intc equ [48]

extern ra:byte
extern rb:byte
extern rc:byte
extern rd:byte
extern re:byte
extern rf:byte
extern rg:byte
extern rh:byte
extern _Crom2Prom:near
extern _Crom2PromNext:near

RAMBANK 0 @BITDATASEC, @BITDATASEC1
@HCCINIT	.section 'data'
@HCCINIT0	.section 'data'
@BITDATASEC	 .section 'data'
@BITDATASEC1	 .section 'data'

#pragma debug scope 1 1
	extern __DELAY3:near
	extern __DELAYX3:near
	extern __DELAYX6:near
	extern __DELAYY5:near
	extern __DELAYY3:near
	extern _builtin_holtek_delay_2:byte
public _PAUSE
#pragma debug scope 2 1
#line 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
_PAUSE .section 'code'
_PAUSE proc
    local _PAUSE_2 db 1 dup(?)	; 0,1
	mov _PAUSE_2[0],a
#pragma debug variable 8 2 _PAUSE_2+0 "i"
#line 37 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	mov a,_Mode[0]
	sub a,64
	sz z
	jmp _L3
	sub a,(96)-(64)
	sz z
	jmp _L4
#line 37 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	mov a,_Mode[0]
	sub a,128
	sz z
	jmp _L5
	sub a,(160)-(128)
	sz z
	jmp _L6
	mov a,_Mode[0]
	sub a,192
	sz z
	jmp _L7
	mov a,_Mode[0]
	sub a,224
	snz z
	jmp _L1
	clr ra
	jmp _L9
_L7:
	clr ra
	jmp _L10
_L6:
	clr ra
	jmp _L11
_L5:
	clr ra
	jmp _L12
_L4:
	clr ra
	jmp _L13
_L3:
	clr ra
_L14:
#line 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	mov a,ra
	sub a,_PAUSE_2[0]
	sz z
	jmp _L1
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 312>263690
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	ERRMESSAGE 'the value 312of the argument exceeds the maxinum 263690'
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 312<0
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	ERRMESSAGE 'the value 312 of the argument exceeds the mininum 0'
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 312==0
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	JMP $
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (312>=1) AND (312<( 4 + __PBP__ * 2))
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (312>=2) AND (312<( 4 + __PBP__ * 2))
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (312>=3) AND (312<( 4 + __PBP__ * 2))
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (312>=4) AND (312<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (312>=5) AND (312<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (312>=6) AND (312<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (312>=7) AND (312<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (312>=8) AND (312<( 4 + __PBP__ * 2))  AND ( __PBP__ > 2 )
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (312==9)  AND ( __PBP__ > 2 )
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (312< ( 8 + __PBP__ * 2)) AND (312>( 3 + __PBP__ * 2))
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAY3 + ( 7 + __PBP__ * 2) -312
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (312< ( 0404h + __PBP__ * 2)) AND (312>( 7 + __PBP__ * 2))
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(312-( 4 + __PBP__ * 2))/4
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYX3 + 3 -((312-( 4 + __PBP__ * 2)) MOD 4) 
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (312< ( 040bh + __PBP__ * 2)) AND (312> ( 0403h + __PBP__ * 2))
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,0 
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYX6 + ( 040ah + __PBP__ * 2) -312
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (312 >= ( 040bh + __PBP__ * 2)) AND ((((312-( 9 + __PBP__ * 2))%0402h)/4+1)>256)
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(312-( 9 + __PBP__ * 2))/0402h
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV _builtin_holtek_delay_2,A
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,0
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYY5 +5- (((312-( 9 + __PBP__ * 2))%0402h)%6) 
	ENDIF
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (312 >= ( 040bh + __PBP__ * 2)) AND ((((312-( 9 + __PBP__ * 2))%0402h)/4+1)<=256)
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(312-( 9 + __PBP__ * 2))/0402h
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV _builtin_holtek_delay_2,A
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,((312-( 9 + __PBP__ * 2))%0402h)/4+1
;# 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYY3 +3-(((312-( 9 + __PBP__ * 2))%0402h)%4) 
	ENDIF
	inc ra
	jmp _L14
_L13:
#line 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	mov a,ra
	sub a,_PAUSE_2[0]
	sz z
	jmp _L1
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 625>263690
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	ERRMESSAGE 'the value 625of the argument exceeds the maxinum 263690'
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 625<0
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	ERRMESSAGE 'the value 625 of the argument exceeds the mininum 0'
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 625==0
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	JMP $
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (625>=1) AND (625<( 4 + __PBP__ * 2))
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (625>=2) AND (625<( 4 + __PBP__ * 2))
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (625>=3) AND (625<( 4 + __PBP__ * 2))
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (625>=4) AND (625<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (625>=5) AND (625<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (625>=6) AND (625<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (625>=7) AND (625<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (625>=8) AND (625<( 4 + __PBP__ * 2))  AND ( __PBP__ > 2 )
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (625==9)  AND ( __PBP__ > 2 )
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (625< ( 8 + __PBP__ * 2)) AND (625>( 3 + __PBP__ * 2))
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAY3 + ( 7 + __PBP__ * 2) -625
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (625< ( 0404h + __PBP__ * 2)) AND (625>( 7 + __PBP__ * 2))
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(625-( 4 + __PBP__ * 2))/4
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYX3 + 3 -((625-( 4 + __PBP__ * 2)) MOD 4) 
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (625< ( 040bh + __PBP__ * 2)) AND (625> ( 0403h + __PBP__ * 2))
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,0 
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYX6 + ( 040ah + __PBP__ * 2) -625
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (625 >= ( 040bh + __PBP__ * 2)) AND ((((625-( 9 + __PBP__ * 2))%0402h)/4+1)>256)
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(625-( 9 + __PBP__ * 2))/0402h
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV _builtin_holtek_delay_2,A
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,0
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYY5 +5- (((625-( 9 + __PBP__ * 2))%0402h)%6) 
	ENDIF
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (625 >= ( 040bh + __PBP__ * 2)) AND ((((625-( 9 + __PBP__ * 2))%0402h)/4+1)<=256)
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(625-( 9 + __PBP__ * 2))/0402h
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV _builtin_holtek_delay_2,A
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,((625-( 9 + __PBP__ * 2))%0402h)/4+1
;# 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYY3 +3-(((625-( 9 + __PBP__ * 2))%0402h)%4) 
	ENDIF
	inc ra
	jmp _L13
_L12:
#line 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	mov a,ra
	sub a,_PAUSE_2[0]
	sz z
	jmp _L1
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 1250>263690
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	ERRMESSAGE 'the value 1250of the argument exceeds the maxinum 263690'
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 1250<0
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	ERRMESSAGE 'the value 1250 of the argument exceeds the mininum 0'
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 1250==0
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	JMP $
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (1250>=1) AND (1250<( 4 + __PBP__ * 2))
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (1250>=2) AND (1250<( 4 + __PBP__ * 2))
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (1250>=3) AND (1250<( 4 + __PBP__ * 2))
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (1250>=4) AND (1250<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (1250>=5) AND (1250<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (1250>=6) AND (1250<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (1250>=7) AND (1250<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (1250>=8) AND (1250<( 4 + __PBP__ * 2))  AND ( __PBP__ > 2 )
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (1250==9)  AND ( __PBP__ > 2 )
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (1250< ( 8 + __PBP__ * 2)) AND (1250>( 3 + __PBP__ * 2))
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAY3 + ( 7 + __PBP__ * 2) -1250
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (1250< ( 0404h + __PBP__ * 2)) AND (1250>( 7 + __PBP__ * 2))
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(1250-( 4 + __PBP__ * 2))/4
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYX3 + 3 -((1250-( 4 + __PBP__ * 2)) MOD 4) 
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (1250< ( 040bh + __PBP__ * 2)) AND (1250> ( 0403h + __PBP__ * 2))
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,0 
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYX6 + ( 040ah + __PBP__ * 2) -1250
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (1250 >= ( 040bh + __PBP__ * 2)) AND ((((1250-( 9 + __PBP__ * 2))%0402h)/4+1)>256)
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(1250-( 9 + __PBP__ * 2))/0402h
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV _builtin_holtek_delay_2,A
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,0
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYY5 +5- (((1250-( 9 + __PBP__ * 2))%0402h)%6) 
	ENDIF
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (1250 >= ( 040bh + __PBP__ * 2)) AND ((((1250-( 9 + __PBP__ * 2))%0402h)/4+1)<=256)
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(1250-( 9 + __PBP__ * 2))/0402h
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV _builtin_holtek_delay_2,A
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,((1250-( 9 + __PBP__ * 2))%0402h)/4+1
;# 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYY3 +3-(((1250-( 9 + __PBP__ * 2))%0402h)%4) 
	ENDIF
	inc ra
	jmp _L12
_L11:
#line 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	mov a,ra
	sub a,_PAUSE_2[0]
	sz z
	jmp _L1
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 2500>263690
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	ERRMESSAGE 'the value 2500of the argument exceeds the maxinum 263690'
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 2500<0
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	ERRMESSAGE 'the value 2500 of the argument exceeds the mininum 0'
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 2500==0
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	JMP $
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (2500>=1) AND (2500<( 4 + __PBP__ * 2))
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (2500>=2) AND (2500<( 4 + __PBP__ * 2))
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (2500>=3) AND (2500<( 4 + __PBP__ * 2))
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (2500>=4) AND (2500<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (2500>=5) AND (2500<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (2500>=6) AND (2500<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (2500>=7) AND (2500<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (2500>=8) AND (2500<( 4 + __PBP__ * 2))  AND ( __PBP__ > 2 )
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (2500==9)  AND ( __PBP__ > 2 )
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (2500< ( 8 + __PBP__ * 2)) AND (2500>( 3 + __PBP__ * 2))
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAY3 + ( 7 + __PBP__ * 2) -2500
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (2500< ( 0404h + __PBP__ * 2)) AND (2500>( 7 + __PBP__ * 2))
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(2500-( 4 + __PBP__ * 2))/4
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYX3 + 3 -((2500-( 4 + __PBP__ * 2)) MOD 4) 
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (2500< ( 040bh + __PBP__ * 2)) AND (2500> ( 0403h + __PBP__ * 2))
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,0 
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYX6 + ( 040ah + __PBP__ * 2) -2500
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (2500 >= ( 040bh + __PBP__ * 2)) AND ((((2500-( 9 + __PBP__ * 2))%0402h)/4+1)>256)
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(2500-( 9 + __PBP__ * 2))/0402h
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV _builtin_holtek_delay_2,A
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,0
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYY5 +5- (((2500-( 9 + __PBP__ * 2))%0402h)%6) 
	ENDIF
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (2500 >= ( 040bh + __PBP__ * 2)) AND ((((2500-( 9 + __PBP__ * 2))%0402h)/4+1)<=256)
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(2500-( 9 + __PBP__ * 2))/0402h
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV _builtin_holtek_delay_2,A
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,((2500-( 9 + __PBP__ * 2))%0402h)/4+1
;# 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYY3 +3-(((2500-( 9 + __PBP__ * 2))%0402h)%4) 
	ENDIF
	inc ra
	jmp _L11
_L10:
#line 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	mov a,ra
	sub a,_PAUSE_2[0]
	sz z
	jmp _L1
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 5000>263690
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	ERRMESSAGE 'the value 5000of the argument exceeds the maxinum 263690'
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 5000<0
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	ERRMESSAGE 'the value 5000 of the argument exceeds the mininum 0'
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 5000==0
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	JMP $
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (5000>=1) AND (5000<( 4 + __PBP__ * 2))
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (5000>=2) AND (5000<( 4 + __PBP__ * 2))
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (5000>=3) AND (5000<( 4 + __PBP__ * 2))
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (5000>=4) AND (5000<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (5000>=5) AND (5000<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (5000>=6) AND (5000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (5000>=7) AND (5000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (5000>=8) AND (5000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 2 )
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (5000==9)  AND ( __PBP__ > 2 )
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (5000< ( 8 + __PBP__ * 2)) AND (5000>( 3 + __PBP__ * 2))
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAY3 + ( 7 + __PBP__ * 2) -5000
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (5000< ( 0404h + __PBP__ * 2)) AND (5000>( 7 + __PBP__ * 2))
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(5000-( 4 + __PBP__ * 2))/4
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYX3 + 3 -((5000-( 4 + __PBP__ * 2)) MOD 4) 
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (5000< ( 040bh + __PBP__ * 2)) AND (5000> ( 0403h + __PBP__ * 2))
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,0 
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYX6 + ( 040ah + __PBP__ * 2) -5000
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (5000 >= ( 040bh + __PBP__ * 2)) AND ((((5000-( 9 + __PBP__ * 2))%0402h)/4+1)>256)
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(5000-( 9 + __PBP__ * 2))/0402h
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV _builtin_holtek_delay_2,A
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,0
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYY5 +5- (((5000-( 9 + __PBP__ * 2))%0402h)%6) 
	ENDIF
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (5000 >= ( 040bh + __PBP__ * 2)) AND ((((5000-( 9 + __PBP__ * 2))%0402h)/4+1)<=256)
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(5000-( 9 + __PBP__ * 2))/0402h
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV _builtin_holtek_delay_2,A
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,((5000-( 9 + __PBP__ * 2))%0402h)/4+1
;# 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYY3 +3-(((5000-( 9 + __PBP__ * 2))%0402h)%4) 
	ENDIF
	inc ra
	jmp _L10
_L9:
#line 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	mov a,ra
	sub a,_PAUSE_2[0]
	sz z
	jmp _L1
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 10000>263690
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	ERRMESSAGE 'the value 10000of the argument exceeds the maxinum 263690'
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 10000<0
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	ERRMESSAGE 'the value 10000 of the argument exceeds the mininum 0'
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF 10000==0
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	JMP $
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (10000>=1) AND (10000<( 4 + __PBP__ * 2))
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (10000>=2) AND (10000<( 4 + __PBP__ * 2))
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (10000>=3) AND (10000<( 4 + __PBP__ * 2))
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (10000>=4) AND (10000<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (10000>=5) AND (10000<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (10000>=6) AND (10000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (10000>=7) AND (10000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (10000>=8) AND (10000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 2 )
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (10000==9)  AND ( __PBP__ > 2 )
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	NOP
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (10000< ( 8 + __PBP__ * 2)) AND (10000>( 3 + __PBP__ * 2))
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAY3 + ( 7 + __PBP__ * 2) -10000
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (10000< ( 0404h + __PBP__ * 2)) AND (10000>( 7 + __PBP__ * 2))
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(10000-( 4 + __PBP__ * 2))/4
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYX3 + 3 -((10000-( 4 + __PBP__ * 2)) MOD 4) 
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (10000< ( 040bh + __PBP__ * 2)) AND (10000> ( 0403h + __PBP__ * 2))
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,0 
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYX6 + ( 040ah + __PBP__ * 2) -10000
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (10000 >= ( 040bh + __PBP__ * 2)) AND ((((10000-( 9 + __PBP__ * 2))%0402h)/4+1)>256)
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(10000-( 9 + __PBP__ * 2))/0402h
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV _builtin_holtek_delay_2,A
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,0
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYY5 +5- (((10000-( 9 + __PBP__ * 2))%0402h)%6) 
	ENDIF
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	IF (10000 >= ( 040bh + __PBP__ * 2)) AND ((((10000-( 9 + __PBP__ * 2))%0402h)/4+1)<=256)
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,(10000-( 9 + __PBP__ * 2))/0402h
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV _builtin_holtek_delay_2,A
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	MOV A,((10000-( 9 + __PBP__ * 2))%0402h)/4+1
;# 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c" 1
	fcall __DELAYY3 +3-(((10000-( 9 + __PBP__ * 2))%0402h)%4) 
	ENDIF
	inc ra
	jmp _L9
_L1:
	ret
_PAUSE endp
#line 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
#pragma debug scope 1 1
___pd equ [30]
public _Display029
#pragma debug scope 3 1
#line 29 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
_Display029 .section 'code'
_Display029 proc
    local _Display029_2 db 2 dup(?)	; 0,2
#pragma debug variable 8 3 _Display029_2+1 "i"
	mov a,10
	mov _Display029_2[0],a
#line 30 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	clr _Display029_2[1]
_L24:
#line 31 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	mov a,low offset _SEG_TAB
	add a,_Display029_2[1]
	mov mp,a
	mov a,high offset _SEG_TAB
	clr sbp
	adcm a,sbp
	fcall _Crom2Prom
	mov [30],a
#line 32 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	mov a,10
	fcall _PAUSE
#line 30 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	inc _Display029_2[1]
	sdz _Display029_2[0]
	jmp _L24
	ret
_Display029 endp
#line 30 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
#pragma debug scope 1 1
___wdtc equ [62]
___pdc equ [31]
___smod equ [58]
public _main
#pragma debug scope 4 1
#line 13 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
IFDEF WITH_DEFAULT_STARTUP
extern _main_initial0:near
extern _main_startup:near
ENDIF

ROMBANK 0 @start
@start .section com_l 'code'
_main_startup1:
@start .section com_e 'code'
	mov a,bank _main
	mov bp,a
	jmp _main

_main .section 'code'
_main proc
#line 14 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	mov a,175
	mov [62],a
#line 15 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	clr [30]
	clr [31]
_L27:
#line 17 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	set [58].0
#line 18 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	fcall _Display029
#line 19 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	mov a,64
	mov _Mode[0],a
_L28:
#line 21 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	mov a,30
	andm a,[58]
#line 22 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	mov a,_Mode[0]
	orm a,[58]
#line 23 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	fcall _Display029
#line 24 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	mov a,_Mode[0]
	add a,32
	mov ra,a
	mov a,ra
	mov _Mode[0],a
#line 25 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
	sz ra
	jmp _L28
	jmp _L27
	jmp $
_main endp

@dummy proc
	call _main
@dummy endp

#line 25 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
#pragma debug scope 1 1
#line 11 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
public _Mode
@HCCINIT0_Mode .section 'data'
_Mode	db 0
#pragma debug variable 8 1 _Mode "Mode"

@HCCINIT .section 'data'
public _SEG_TAB
@crom	.section 'crom'
#line 6 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
@crom	.section	'crom'
_SEG_TAB:
#pragma debug array 42 8 10 1
#pragma debug variable 42 1 _SEG_TAB "SEG_TAB"
	db 63
	db 6
	db 91
	db 79
	db 102
	db 109
	db 125
	db 7
	db 127
	db 103
#pragma debug struct_begin 43 "__pd_bits"
#pragma debug field 21 8 0 1 "__pd0" ;0,1
#pragma debug field 21 8 0 1 "__pd1" ;1,1
#pragma debug field 21 8 0 1 "__pd2" ;2,1
#pragma debug field 21 8 0 1 "__pd3" ;3,1
#pragma debug field 21 8 0 1 "__pd4" ;4,1
#pragma debug field 21 8 0 1 "__pd5" ;5,1
#pragma debug field 21 8 0 1 "__pd6" ;6,1
#pragma debug field 21 8 0 1 "__pd7" ;7,1
#pragma debug struct_end
#pragma debug union_begin 44 ""
#pragma debug field 2 43 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 44 1 ___pd "__pd" 1
#pragma debug struct_begin 45 "__pdc_bits"
#pragma debug field 21 8 0 1 "__pdc0" ;0,1
#pragma debug field 21 8 0 1 "__pdc1" ;1,1
#pragma debug field 21 8 0 1 "__pdc2" ;2,1
#pragma debug field 21 8 0 1 "__pdc3" ;3,1
#pragma debug field 21 8 0 1 "__pdc4" ;4,1
#pragma debug field 21 8 0 1 "__pdc5" ;5,1
#pragma debug field 21 8 0 1 "__pdc6" ;6,1
#pragma debug field 21 8 0 1 "__pdc7" ;7,1
#pragma debug struct_end
#pragma debug union_begin 46 ""
#pragma debug field 2 45 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 46 1 ___pdc "__pdc" 1
#pragma debug struct_begin 47 "__smod_bits"
#pragma debug field 21 8 0 1 "__hlclk" ;0,1
#pragma debug field 21 8 0 1 "__idlen" ;1,1
#pragma debug field 21 8 0 1 "__hto" ;2,1
#pragma debug field 21 8 0 1 "__lto" ;3,1
#pragma debug field 21 8 0 1 "__fsten" ;4,1
#pragma debug field 21 8 0 1 "__cks0" ;5,1
#pragma debug field 21 8 0 1 "__cks1" ;6,1
#pragma debug field 21 8 0 1 "__cks2" ;7,1
#pragma debug struct_end
#pragma debug union_begin 48 ""
#pragma debug field 2 47 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 48 1 ___smod "__smod" 1
#pragma debug struct_begin 49 "__wdtc_bits"
#pragma debug field 21 8 0 1 "__ws0" ;0,1
#pragma debug field 21 8 0 1 "__ws1" ;1,1
#pragma debug field 21 8 0 1 "__ws2" ;2,1
#pragma debug field 21 8 0 1 "__we0" ;3,1
#pragma debug field 21 8 0 1 "__we1" ;4,1
#pragma debug field 21 8 0 1 "__we2" ;5,1
#pragma debug field 21 8 0 1 "__we3" ;6,1
#pragma debug field 21 8 0 1 "__we4" ;7,1
#pragma debug struct_end
#pragma debug union_begin 50 ""
#pragma debug field 2 49 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 50 1 ___wdtc "__wdtc" 1
#line 13 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19_Test.c"
@code .section at 0 'code'
	clr bp
	jmp _main_startup1


; 
; Generated by holtek-gcc v3.18, Tue Apr 10 11:44:28 2018
; Rebuild 126
; end of file
