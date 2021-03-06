; Generated by holtek-gcc v3.18, Tue Apr 10 09:00:59 2018
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
___wdtc equ [62]
___pcs2 equ [362]
___tm2c0 equ [81]
___tm2c1 equ [82]
___tm2rp equ [87]
___tm2al equ [85]
___tm2ah equ [86]
___adcr0 equ [104]
___adcr1 equ [105]
___pas2 equ [354]
___intc1 equ [49]
___intc0 equ [48]
public _main
#pragma debug scope 2 1
#line 7 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
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
#line 8 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	mov a,175
	mov [62],a
#line 9 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	mov a,1
	lmov [362],a
#line 10 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	clr [81]
	mov a,168
	mov [82],a
#line 11 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	mov a,160
	mov [87],a
#line 12 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	mov a,208
	mov [85],a
	mov a,7
	mov [86],a
#line 13 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	set [81].3
#line 15 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	mov a,4
	mov [104],a
#line 16 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	mov a,6
	mov [105],a
#line 17 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	mov a,3
	lmov [354],a
#line 18 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	set [49].3
	set [48].0
#line 19 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	set [104].7
	clr [104].7
_L2:
	jmp _L2
	jmp $
_main endp

@dummy proc
	call _main
@dummy endp

#line 19 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
#pragma debug scope 1 1
___adrh equ [107]
___mfi0 equ [52]
public _ISR_ADC
#pragma debug scope 3 1
#line 25 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
rombank 0 @ISR_ADC_code
@ISR_ADC_code .section at 28 'code'
	mov r1,a
	mov a,bp
	clr bp
	jmp _ISR_ADC
ROMBANK 0 _ISR_ADC
#pragma debug scope 1 1
@dummy28 proc
	call _ISR_ADC
@dummy28 endp
#pragma debug scope 4 1
_ISR_ADC .section 'code'
_ISR_ADC proc
	mov r2,a
	mov a, status
	mov r3,a
#line 27 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	mov a,[107]
	mov rd,a
	clr re
	mov a,re
	mov _builtin_holtek_mant1[1],a
	mov a,rd
	mov _builtin_holtek_mant1[0],a
	fcall _builtin_holtek_itod
	mov a,_builtin_holtek_mant12p[0]
	mov rg,a
	mov a,_builtin_holtek_mant1[2]
	mov rf,a
	mov a,_builtin_holtek_mant1[1]
	mov re,a
	mov a,_builtin_holtek_mant1[0]
	mov rd,a
	mov a,rg
	mov _builtin_holtek_mant12p[0],a
	mov a,rf
	mov _builtin_holtek_mant1[2],a
	mov a,re
	mov _builtin_holtek_mant1[1],a
	mov a,rd
	mov _builtin_holtek_mant1[0],a
	mov a,65
	mov _builtin_holtek_mant12p[1],a
	mov a,122
	mov _builtin_holtek_mant2[2],a
	mov a,0
	mov _builtin_holtek_mant2[1],a
	mov a,0
	mov _builtin_holtek_mant2[0],a
	fcall _builtin_holtek_dtmul
	mov a,_builtin_holtek_mant12p[0]
	mov rg,a
	mov a,_builtin_holtek_mant1[2]
	mov rf,a
	mov a,_builtin_holtek_mant1[1]
	mov re,a
	mov a,_builtin_holtek_mant1[0]
	mov rd,a
	mov a,rg
	mov _builtin_holtek_mant12p[0],a
	mov a,rf
	mov _builtin_holtek_mant1[2],a
	mov a,re
	mov _builtin_holtek_mant1[1],a
	mov a,rd
	mov _builtin_holtek_mant1[0],a
	mov a,68
	mov _builtin_holtek_mant12p[1],a
	mov a,122
	mov _builtin_holtek_mant2[2],a
	mov a,0
	mov _builtin_holtek_mant2[1],a
	mov a,0
	mov _builtin_holtek_mant2[0],a
	fcall _builtin_holtek_dtadd
	mov a,_builtin_holtek_mant12p[0]
	mov rg,a
	mov a,_builtin_holtek_mant1[2]
	mov rf,a
	mov a,_builtin_holtek_mant1[1]
	mov re,a
	mov a,_builtin_holtek_mant1[0]
	mov rd,a
	mov a,rg
	mov _builtin_holtek_mant12p[0],a
	mov a,rf
	mov _builtin_holtek_mant1[2],a
	mov a,re
	mov _builtin_holtek_mant1[1],a
	mov a,rd
	mov _builtin_holtek_mant1[0],a
	fcall _builtin_holtek_dtol
	mov a,_builtin_holtek_mant12p[0]
	mov rg,a
	mov a,_builtin_holtek_mant1[2]
	mov rf,a
	mov a,_builtin_holtek_mant1[1]
	mov re,a
	mov a,_builtin_holtek_mant1[0]
	mov rd,a
#line 28 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	mov a,231
	sub a,rd
	mov a,3
	sbc a,re
	sz c
	jmp _L9
#line 29 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	mov a,136
	sub a,rd
	mov a,19
	sbc a,re
	sz c
	jmp _L8
	mov a,-120
	mov rd,a
	mov a,19
	mov re,a
	jmp _L8
_L9:
#line 28 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	mov a,-24
	mov rd,a
	mov a,3
	mov re,a
_L8:
#line 30 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	snz [52].6
	jmp _L8
#line 31 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	clr [52].6
#line 32 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	mov a,rd
	mov [85],a
#line 33 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	mov a,re
	mov [86],a
#line 34 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
	set [104].7
	clr [104].7
	mov a,r2
	mov bp,a
	mov a,r3
	mov status,a
	mov a,r1
	reti
_ISR_ADC endp

#line 34 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
#pragma debug scope 1 1
#pragma debug struct_begin 42 "__intc0_bits"
#pragma debug field 21 8 0 1 "__emi" ;0,1
#pragma debug field 21 8 0 1 "__int0e" ;1,1
#pragma debug field 21 8 0 1 "__int1e" ;2,1
#pragma debug field 21 8 0 1 "__cp0e" ;3,1
#pragma debug field 21 8 0 1 "__int0f" ;4,1
#pragma debug field 21 8 0 1 "__int1f" ;5,1
#pragma debug field 21 8 0 1 "__cp0f" ;6,1
#pragma debug field 21 8 0 1 ;7,1
#pragma debug struct_end
#pragma debug union_begin 43 ""
#pragma debug field 2 42 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 43 1 ___intc0 "__intc0" 1
#pragma debug struct_begin 44 "__intc1_bits"
#pragma debug field 21 8 0 1 "__cp1e" ;0,1
#pragma debug field 21 8 0 1 "__mf0e" ;1,1
#pragma debug field 21 8 0 1 "__mf1e" ;2,1
#pragma debug field 21 8 0 1 "__ade" ;3,1
#pragma debug field 21 8 0 1 "__cp1f" ;4,1
#pragma debug field 21 8 0 1 "__mf0f" ;5,1
#pragma debug field 21 8 0 1 "__mf1f" ;6,1
#pragma debug field 21 8 0 1 "__adf" ;7,1
#pragma debug struct_end
#pragma debug union_begin 45 ""
#pragma debug field 2 44 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 45 1 ___intc1 "__intc1" 1
#pragma debug struct_begin 46 "__mfi0_bits"
#pragma debug field 21 8 0 1 "__t0pe" ;0,1
#pragma debug field 21 8 0 1 "__t0ae" ;1,1
#pragma debug field 21 8 0 1 "__t2pe" ;2,1
#pragma debug field 21 8 0 1 "__t2ae" ;3,1
#pragma debug field 21 8 0 1 "__t0pf" ;4,1
#pragma debug field 21 8 0 1 "__t0af" ;5,1
#pragma debug field 21 8 0 1 "__t2pf" ;6,1
#pragma debug field 21 8 0 1 "__t2af" ;7,1
#pragma debug struct_end
#pragma debug union_begin 47 ""
#pragma debug field 2 46 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 47 1 ___mfi0 "__mfi0" 1
#pragma debug struct_begin 48 "__wdtc_bits"
#pragma debug field 21 8 0 1 "__ws0" ;0,1
#pragma debug field 21 8 0 1 "__ws1" ;1,1
#pragma debug field 21 8 0 1 "__ws2" ;2,1
#pragma debug field 21 8 0 1 "__we0" ;3,1
#pragma debug field 21 8 0 1 "__we1" ;4,1
#pragma debug field 21 8 0 1 "__we2" ;5,1
#pragma debug field 21 8 0 1 "__we3" ;6,1
#pragma debug field 21 8 0 1 "__we4" ;7,1
#pragma debug struct_end
#pragma debug union_begin 49 ""
#pragma debug field 2 48 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 49 1 ___wdtc "__wdtc" 1
#pragma debug struct_begin 50 "__tm2c0_bits"
#pragma debug field 21 8 0 3 ;0,3
#pragma debug field 21 8 0 1 "__t2on" ;3,1
#pragma debug field 21 8 0 1 "__t2ck0" ;4,1
#pragma debug field 21 8 0 1 "__t2ck1" ;5,1
#pragma debug field 21 8 0 1 "__t2ck2" ;6,1
#pragma debug field 21 8 0 1 "__t2pau" ;7,1
#pragma debug struct_end
#pragma debug union_begin 51 ""
#pragma debug field 2 50 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 51 1 ___tm2c0 "__tm2c0" 1
#pragma debug struct_begin 52 "__tm2c1_bits"
#pragma debug field 21 8 0 1 "__t2cclr" ;0,1
#pragma debug field 21 8 0 1 "__t2dpx" ;1,1
#pragma debug field 21 8 0 1 "__t2pol" ;2,1
#pragma debug field 21 8 0 1 "__t2oc" ;3,1
#pragma debug field 21 8 0 1 "__t2io0" ;4,1
#pragma debug field 21 8 0 1 "__t2io1" ;5,1
#pragma debug field 21 8 0 1 "__t2m0" ;6,1
#pragma debug field 21 8 0 1 "__t2m1" ;7,1
#pragma debug struct_end
#pragma debug union_begin 53 ""
#pragma debug field 2 52 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 53 1 ___tm2c1 "__tm2c1" 1
#pragma debug variable 8 1 ___tm2al "__tm2al" 1
#pragma debug variable 8 1 ___tm2ah "__tm2ah" 1
#pragma debug variable 8 1 ___tm2rp "__tm2rp" 1
#pragma debug struct_begin 54 "__adcr0_bits"
#pragma debug field 21 8 0 1 "__acs0" ;0,1
#pragma debug field 21 8 0 1 "__acs1" ;1,1
#pragma debug field 21 8 0 1 "__acs2" ;2,1
#pragma debug field 21 8 0 1 "__acs3" ;3,1
#pragma debug field 21 8 0 1 "__acs4" ;4,1
#pragma debug field 21 8 0 1 "__adoff" ;5,1
#pragma debug field 21 8 0 1 "__eocb" ;6,1
#pragma debug field 21 8 0 1 "__start" ;7,1
#pragma debug struct_end
#pragma debug union_begin 55 ""
#pragma debug field 2 54 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 55 1 ___adcr0 "__adcr0" 1
#pragma debug struct_begin 56 "__adcr1_bits"
#pragma debug field 21 8 0 1 "__adck0" ;0,1
#pragma debug field 21 8 0 1 "__adck1" ;1,1
#pragma debug field 21 8 0 1 "__adck2" ;2,1
#pragma debug field 21 8 0 1 ;3,1
#pragma debug field 21 8 0 1 "__vrefs" ;4,1
#pragma debug field 21 8 0 1 "__adrfs" ;5,1
#pragma debug field 21 8 0 1 "__vbgen" ;6,1
#pragma debug field 21 8 0 1 ;7,1
#pragma debug struct_end
#pragma debug union_begin 57 ""
#pragma debug field 2 56 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 57 1 ___adcr1 "__adcr1" 1
#pragma debug variable 8 1 ___adrh "__adrh" 1
#pragma debug struct_begin 58 "__pas2_bits"
#pragma debug field 21 8 0 1 "__pa4s0" ;0,1
#pragma debug field 21 8 0 1 "__pa4s1" ;1,1
#pragma debug field 21 8 0 1 "__pa4s2" ;2,1
#pragma debug field 21 8 0 1 "__pa4s3" ;3,1
#pragma debug field 21 8 0 1 "__pa5s0" ;4,1
#pragma debug field 21 8 0 1 "__pa5s1" ;5,1
#pragma debug field 21 8 0 1 "__pa5s2" ;6,1
#pragma debug field 21 8 0 1 "__pa5s3" ;7,1
#pragma debug struct_end
#pragma debug union_begin 59 ""
#pragma debug field 2 58 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 59 1 ___pas2 "__pas2" 1
#pragma debug struct_begin 60 "__pcs2_bits"
#pragma debug field 21 8 0 1 "__pc4s0" ;0,1
#pragma debug field 21 8 0 1 "__pc4s1" ;1,1
#pragma debug field 21 8 0 1 "__pc4s2" ;2,1
#pragma debug field 21 8 0 1 "__pc4s3" ;3,1
#pragma debug field 21 8 0 1 "__pc5s0" ;4,1
#pragma debug field 21 8 0 1 "__pc5s1" ;5,1
#pragma debug field 21 8 0 1 "__pc5s2" ;6,1
#pragma debug field 21 8 0 1 "__pc5s3" ;7,1
#pragma debug struct_end
#pragma debug union_begin 61 ""
#pragma debug field 2 60 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 61 1 ___pcs2 "__pcs2" 1
extern r1:byte
extern r2:byte
extern r3:byte
#line 7 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0327\SG90_T.c"
@code .section at 0 'code'
	clr bp
	jmp _main_startup1

extern _builtin_holtek_mant1:byte
extern _builtin_holtek_mant12p:byte
extern _builtin_holtek_itod:near
extern _builtin_holtek_mant2:byte
extern _builtin_holtek_dtmul:near
extern _builtin_holtek_dtadd:near
extern _builtin_holtek_dtol:near

; 
; Generated by holtek-gcc v3.18, Tue Apr 10 09:00:59 2018
; Rebuild 126
; end of file
