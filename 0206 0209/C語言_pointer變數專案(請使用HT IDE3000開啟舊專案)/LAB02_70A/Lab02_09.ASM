; Generated by holtek-gcc v3.18, Fri Feb 09 16:11:04 2018
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
public _main
#pragma debug scope 2 1
#line 7 "C:\Users\YVTC\Desktop\LAB02_70A\Lab02_09.c"
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
    local _main_2 db 14 dup(?)
#pragma debug variable 10 2 _main_2+6 "x"
#pragma debug variable 10 2 _main_2+2 "temp"
#pragma debug array 42 12 3 2
#pragma debug variable 42 2 _main_2+8 "Array"
#pragma debug pointer 43 12 2
#pragma debug variable 43 2 _main_2+0 "ptr1"
#pragma debug variable 43 2 _main_2+4 "ptr2"
	mov a,4
	mov _main_2[6],a
	clr _main_2[7]
	clr _main_2[8]
	clr _main_2[9]
	mov a,1
	mov _main_2[10],a
	clr _main_2[11]
	mov a,2
	mov _main_2[12],a
	clr _main_2[13]
#line 9 "C:\Users\YVTC\Desktop\LAB02_70A\Lab02_09.c"
	mov a,low offset _main_2
	mov ra,a
	mov a,high offset _main_2
	mov rb,a
	mov a,6
	add a,ra
	mov _main_2[0],a
	mov a,0
	adc a,rb
	mov _main_2[1],a
#line 10 "C:\Users\YVTC\Desktop\LAB02_70A\Lab02_09.c"
	mov a,_main_2[0]
	mov ra,a
	mov a,_main_2[1]
	mov rb,a
	mov a,ra
	mov mp,a
	mov a,rb
	mov sbp,a
	fcall _Crom2Prom
	mov _main_2[2],a
	fcall _Crom2PromNext
	mov _main_2[3],a
#line 11 "C:\Users\YVTC\Desktop\LAB02_70A\Lab02_09.c"
;# 11 "C:\Users\YVTC\Desktop\LAB02_70A\Lab02_09.c" 1
	nop
#line 12 "C:\Users\YVTC\Desktop\LAB02_70A\Lab02_09.c"
	mov a,low offset _main_2
	mov ra,a
	mov a,high offset _main_2
	mov rb,a
	mov a,8
	add a,ra
	mov _main_2[4],a
	mov a,0
	adc a,rb
	mov _main_2[5],a
#line 13 "C:\Users\YVTC\Desktop\LAB02_70A\Lab02_09.c"
	mov a,_main_2[4]
	mov ra,a
	mov a,_main_2[5]
	mov rb,a
	mov a,2
	add a,ra
	mov _main_2[4],a
	mov a,0
	adc a,rb
	mov _main_2[5],a
	mov a,ra
	mov mp,a
	mov a,rb
	mov sbp,a
	fcall _Crom2Prom
	mov _main_2[2],a
	fcall _Crom2PromNext
	mov _main_2[3],a
#line 14 "C:\Users\YVTC\Desktop\LAB02_70A\Lab02_09.c"
;# 14 "C:\Users\YVTC\Desktop\LAB02_70A\Lab02_09.c" 1
	nop
#line 15 "C:\Users\YVTC\Desktop\LAB02_70A\Lab02_09.c"
	mov a,_main_2[4]
	mov ra,a
	mov a,_main_2[5]
	mov rb,a
	mov a,ra
	mov mp,a
	mov a,rb
	mov sbp,a
	fcall _Crom2Prom
	mov _main_2[2],a
	fcall _Crom2PromNext
	mov _main_2[3],a
#line 16 "C:\Users\YVTC\Desktop\LAB02_70A\Lab02_09.c"
;# 16 "C:\Users\YVTC\Desktop\LAB02_70A\Lab02_09.c" 1
	nop
	jmp $
_main endp

@dummy proc
	call _main
@dummy endp

#line 16 "C:\Users\YVTC\Desktop\LAB02_70A\Lab02_09.c"
#pragma debug scope 1 1
#line 7 "C:\Users\YVTC\Desktop\LAB02_70A\Lab02_09.c"
@code .section at 0 'code'
	clr bp
	jmp _main_startup1


; 
; Generated by holtek-gcc v3.18, Fri Feb 09 16:11:04 2018
; Rebuild 126
; end of file
