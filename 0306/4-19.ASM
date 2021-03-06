; Generated by holtek-gcc v3.18, Tue Apr 10 11:43:05 2018
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
#line 35 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
_PAUSE .section 'code'
_PAUSE proc
    local _PAUSE_2 db 1 dup(?)	; 0,1
	mov _PAUSE_2[0],a
#pragma debug variable 8 2 _PAUSE_2+0 "i"
#line 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
	clr ra
	jmp _L2
_L3:
#line 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF 20000>263690
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	ERRMESSAGE 'the value 20000of the argument exceeds the maxinum 263690'
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF 20000<0
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	ERRMESSAGE 'the value 20000 of the argument exceeds the mininum 0'
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF 20000==0
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	JMP $
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF (20000>=1) AND (20000<( 4 + __PBP__ * 2))
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	NOP
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF (20000>=2) AND (20000<( 4 + __PBP__ * 2))
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	NOP
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF (20000>=3) AND (20000<( 4 + __PBP__ * 2))
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	NOP
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF (20000>=4) AND (20000<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	NOP
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF (20000>=5) AND (20000<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	NOP
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF (20000>=6) AND (20000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	NOP
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF (20000>=7) AND (20000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	NOP
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF (20000>=8) AND (20000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 2 )
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	NOP
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF (20000==9)  AND ( __PBP__ > 2 )
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	NOP
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF (20000< ( 8 + __PBP__ * 2)) AND (20000>( 3 + __PBP__ * 2))
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	fcall __DELAY3 + ( 7 + __PBP__ * 2) -20000
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF (20000< ( 0404h + __PBP__ * 2)) AND (20000>( 7 + __PBP__ * 2))
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	MOV A,(20000-( 4 + __PBP__ * 2))/4
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	fcall __DELAYX3 + 3 -((20000-( 4 + __PBP__ * 2)) MOD 4) 
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF (20000< ( 040bh + __PBP__ * 2)) AND (20000> ( 0403h + __PBP__ * 2))
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	MOV A,0 
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	fcall __DELAYX6 + ( 040ah + __PBP__ * 2) -20000
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF (20000 >= ( 040bh + __PBP__ * 2)) AND ((((20000-( 9 + __PBP__ * 2))%0402h)/4+1)>256)
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	MOV A,(20000-( 9 + __PBP__ * 2))/0402h
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	MOV _builtin_holtek_delay_2,A
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	MOV A,0
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	fcall __DELAYY5 +5- (((20000-( 9 + __PBP__ * 2))%0402h)%6) 
	ENDIF
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	IF (20000 >= ( 040bh + __PBP__ * 2)) AND ((((20000-( 9 + __PBP__ * 2))%0402h)/4+1)<=256)
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	MOV A,(20000-( 9 + __PBP__ * 2))/0402h
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	MOV _builtin_holtek_delay_2,A
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	MOV A,((20000-( 9 + __PBP__ * 2))%0402h)/4+1
;# 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c" 1
	fcall __DELAYY3 +3-(((20000-( 9 + __PBP__ * 2))%0402h)%4) 
	ENDIF
	inc ra
_L2:
	mov a,ra
	sub a,_PAUSE_2[0]
	snz z
	jmp _L3
	ret
_PAUSE endp
#line 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
#pragma debug scope 1 1
___pd equ [30]
public _Display029
#pragma debug scope 3 1
#line 28 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
_Display029 .section 'code'
_Display029 proc
    local _Display029_2 db 2 dup(?)	; 0,2
#pragma debug variable 8 3 _Display029_2+1 "i"
	mov a,10
	mov _Display029_2[0],a
#line 29 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
	clr _Display029_2[1]
_L7:
#line 30 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
	mov a,low offset _SEG_TAB
	add a,_Display029_2[1]
	mov mp,a
	mov a,high offset _SEG_TAB
	clr sbp
	adcm a,sbp
	fcall _Crom2Prom
	mov [30],a
#line 31 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
	mov a,10
	fcall _PAUSE
#line 29 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
	inc _Display029_2[1]
	sdz _Display029_2[0]
	jmp _L7
	ret
_Display029 endp
#line 29 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
#pragma debug scope 1 1
___wdtc equ [62]
___pdc equ [31]
___smod equ [58]
public _main
#pragma debug scope 4 1
#line 12 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
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
    local _main_2 db 1 dup(?)
#pragma debug variable 8 4 _main_2+0 "Mode"
#line 13 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
	mov a,175
	mov [62],a
#line 14 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
	clr [30]
	clr [31]
_L10:
#line 16 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
	set [58].0
#line 17 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
	fcall _Display029
#line 18 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
	mov a,64
	mov _main_2[0],a
_L11:
#line 20 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
	mov a,30
	andm a,[58]
#line 21 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
	mov a,_main_2[0]
	orm a,[58]
#line 22 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
	fcall _Display029
#line 23 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
	mov a,32
	addm a,_main_2[0]
#line 24 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
	sz _main_2[0]
	jmp _L11
	jmp _L10
	jmp $
_main endp

@dummy proc
	call _main
@dummy endp

#line 24 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
#pragma debug scope 1 1
public _SEG_TAB
@crom	.section 'crom'
#line 6 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
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
#line 12 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\4-19.c"
@code .section at 0 'code'
	clr bp
	jmp _main_startup1


; 
; Generated by holtek-gcc v3.18, Tue Apr 10 11:43:05 2018
; Rebuild 126
; end of file
