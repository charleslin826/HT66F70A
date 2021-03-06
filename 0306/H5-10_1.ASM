; Generated by holtek-gcc v3.18, Tue May 15 13:06:21 2018
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
public _BitReverse
#pragma debug scope 2 1
#line 64 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
_BitReverse .section 'code'
_BitReverse proc
    local _BitReverse_2 db 2 dup(?)	; 0,2
	mov _BitReverse_2[0],a
#pragma debug variable 8 2 _BitReverse_2+0 "data"
	mov a,5
	mov _BitReverse_2[1],a
	clr ra
#line 65 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	clr rh
#line 66 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,1
	mov rd,a
	clr re
_L4:
#line 66 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,rh
	mov rf,a
	clr rg
	mov a,_BitReverse_2[0]
	mov rb,a
	clr rc
	inca rh
	jmp _LI1
_LI2:
	clr c
	sz rc.7
	set c
	rrc rc
	rrc rb
_LI1:
	sdz acc
	jmp _LI2
	snz rb.0
	jmp _L2
	mov a,4
	subm a,rf
	mov a,0
	sbcm a,rg
	mov a,rd
	mov rb,a
	mov a,re
	mov rc,a
	inca rf
	jmp _LI3
_LI4:
	clr c
	rlc rb
	rlc rc
_LI3:
	sdz acc
	jmp _LI4
	mov a,rb
	orm a,ra
_L2:
#line 65 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	inc rh
	sdz _BitReverse_2[1]
	jmp _L4
#line 69 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,ra
	ret
_BitReverse endp
#line 69 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
#pragma debug scope 1 1
___pgc equ [43]
___ph equ [46]
___pg equ [42]
public _LCMWrite4
#pragma debug scope 3 1
#line 81 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
_LCMWrite4 .section 'code'
_LCMWrite4 proc
public _LCMWrite4_2
    local _LCMWrite4_2 db 2 dup(?)	; 1,1
	mov _LCMWrite4_2[1],a
#pragma debug variable 8 3 _LCMWrite4_2+1 "DCFlag"
#pragma debug variable 8 3 _LCMWrite4_2+0 "CD"
#line 82 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,240
	orm a,[43]
#line 83 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	clr [46].0
	set [46].1
#line 84 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
;# 84 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	nop
_L11:
#line 86 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	set [46].2
;# 86 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	nop
#line 87 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,[42]
	mov ra,a
#line 88 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	clr [46].2
#line 89 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,240
	andm a,ra
#line 90 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	set [46].2
;# 90 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	nop
#line 91 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	swapa [42]
	and a,0fh
	mov rb,a
	mov a,rb
	orm a,ra
#line 92 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	clr [46].2
#line 93 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	sz ra.7
	jmp _L11
#line 94 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,15
	andm a,[43]
#line 95 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	clr [46].1
#line 96 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_LCMWrite4_2[1]
	and a,1
	mov rb,a
	clr [46].0
	mov a,rb
	orm a,[46]
#line 97 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,15
	andm a,[42]
#line 98 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_LCMWrite4_2[0]
	and a,240
	mov rb,a
	mov a,rb
	orm a,[42]
#line 99 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	set [46].2
;# 99 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	nop
	clr [46].2
#line 100 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,15
	andm a,[42]
#line 101 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_LCMWrite4_2[0]
	mov rb,a
	clr rc
	mov a,4
_LI5:
	clr c
	rlc rb
	rlc rc
	sdz acc
	jmp _LI5
	mov a,rb
	orm a,[42]
#line 102 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	set [46].2
;# 102 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	nop
	clr [46].2
#line 104 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,ra
	ret
_LCMWrite4 endp
#line 104 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
#pragma debug scope 1 1
___phc equ [47]
public _LCMInit
#pragma debug scope 4 1
#line 71 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
_LCMInit .section 'code'
_LCMInit proc
	clr [46].2
	clr [46].1
	clr [46].0
#line 72 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	clr [47].2
	clr [47].1
	clr [47].0
#line 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF 50000>263690
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	ERRMESSAGE 'the value 50000of the argument exceeds the maxinum 263690'
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF 50000<0
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	ERRMESSAGE 'the value 50000 of the argument exceeds the mininum 0'
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF 50000==0
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	JMP $
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (50000>=1) AND (50000<( 4 + __PBP__ * 2))
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (50000>=2) AND (50000<( 4 + __PBP__ * 2))
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (50000>=3) AND (50000<( 4 + __PBP__ * 2))
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (50000>=4) AND (50000<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (50000>=5) AND (50000<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (50000>=6) AND (50000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (50000>=7) AND (50000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (50000>=8) AND (50000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 2 )
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (50000==9)  AND ( __PBP__ > 2 )
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (50000< ( 8 + __PBP__ * 2)) AND (50000>( 3 + __PBP__ * 2))
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	fcall __DELAY3 + ( 7 + __PBP__ * 2) -50000
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (50000< ( 0404h + __PBP__ * 2)) AND (50000>( 7 + __PBP__ * 2))
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,(50000-( 4 + __PBP__ * 2))/4
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	fcall __DELAYX3 + 3 -((50000-( 4 + __PBP__ * 2)) MOD 4) 
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (50000< ( 040bh + __PBP__ * 2)) AND (50000> ( 0403h + __PBP__ * 2))
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,0 
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	fcall __DELAYX6 + ( 040ah + __PBP__ * 2) -50000
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (50000 >= ( 040bh + __PBP__ * 2)) AND ((((50000-( 9 + __PBP__ * 2))%0402h)/4+1)>256)
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,(50000-( 9 + __PBP__ * 2))/0402h
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV _builtin_holtek_delay_2,A
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,0
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	fcall __DELAYY5 +5- (((50000-( 9 + __PBP__ * 2))%0402h)%6) 
	ENDIF
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (50000 >= ( 040bh + __PBP__ * 2)) AND ((((50000-( 9 + __PBP__ * 2))%0402h)/4+1)<=256)
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,(50000-( 9 + __PBP__ * 2))/0402h
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV _builtin_holtek_delay_2,A
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,((50000-( 9 + __PBP__ * 2))%0402h)/4+1
;# 73 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	fcall __DELAYY3 +3-(((50000-( 9 + __PBP__ * 2))%0402h)%4) 
	ENDIF
#line 74 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,40
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 75 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,12
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 76 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,6
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 77 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,1
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF 3000>263690
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	ERRMESSAGE 'the value 3000of the argument exceeds the maxinum 263690'
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF 3000<0
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	ERRMESSAGE 'the value 3000 of the argument exceeds the mininum 0'
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF 3000==0
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	JMP $
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (3000>=1) AND (3000<( 4 + __PBP__ * 2))
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (3000>=2) AND (3000<( 4 + __PBP__ * 2))
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (3000>=3) AND (3000<( 4 + __PBP__ * 2))
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (3000>=4) AND (3000<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (3000>=5) AND (3000<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (3000>=6) AND (3000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (3000>=7) AND (3000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (3000>=8) AND (3000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 2 )
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (3000==9)  AND ( __PBP__ > 2 )
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (3000< ( 8 + __PBP__ * 2)) AND (3000>( 3 + __PBP__ * 2))
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	fcall __DELAY3 + ( 7 + __PBP__ * 2) -3000
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (3000< ( 0404h + __PBP__ * 2)) AND (3000>( 7 + __PBP__ * 2))
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,(3000-( 4 + __PBP__ * 2))/4
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	fcall __DELAYX3 + 3 -((3000-( 4 + __PBP__ * 2)) MOD 4) 
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (3000< ( 040bh + __PBP__ * 2)) AND (3000> ( 0403h + __PBP__ * 2))
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,0 
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	fcall __DELAYX6 + ( 040ah + __PBP__ * 2) -3000
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (3000 >= ( 040bh + __PBP__ * 2)) AND ((((3000-( 9 + __PBP__ * 2))%0402h)/4+1)>256)
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,(3000-( 9 + __PBP__ * 2))/0402h
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV _builtin_holtek_delay_2,A
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,0
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	fcall __DELAYY5 +5- (((3000-( 9 + __PBP__ * 2))%0402h)%6) 
	ENDIF
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (3000 >= ( 040bh + __PBP__ * 2)) AND ((((3000-( 9 + __PBP__ * 2))%0402h)/4+1)<=256)
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,(3000-( 9 + __PBP__ * 2))/0402h
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV _builtin_holtek_delay_2,A
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,((3000-( 9 + __PBP__ * 2))%0402h)/4+1
;# 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	fcall __DELAYY3 +3-(((3000-( 9 + __PBP__ * 2))%0402h)%4) 
	ENDIF
	ret
_LCMInit endp
#line 78 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
#pragma debug scope 1 1
public _PAUSE
#pragma debug scope 5 1
#line 106 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
_PAUSE .section 'code'
_PAUSE proc
    local _PAUSE_2 db 1 dup(?)	; 0,1
	mov _PAUSE_2[0],a
#pragma debug variable 8 5 _PAUSE_2+0 "i"
#line 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	clr ra
	jmp _L14
_L15:
#line 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF 20000>263690
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	ERRMESSAGE 'the value 20000of the argument exceeds the maxinum 263690'
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF 20000<0
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	ERRMESSAGE 'the value 20000 of the argument exceeds the mininum 0'
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF 20000==0
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	JMP $
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (20000>=1) AND (20000<( 4 + __PBP__ * 2))
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (20000>=2) AND (20000<( 4 + __PBP__ * 2))
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (20000>=3) AND (20000<( 4 + __PBP__ * 2))
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (20000>=4) AND (20000<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (20000>=5) AND (20000<( 4 + __PBP__ * 2)) AND ( __PBP__ > 0 )
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (20000>=6) AND (20000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (20000>=7) AND (20000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 1 )
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (20000>=8) AND (20000<( 4 + __PBP__ * 2))  AND ( __PBP__ > 2 )
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (20000==9)  AND ( __PBP__ > 2 )
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	NOP
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (20000< ( 8 + __PBP__ * 2)) AND (20000>( 3 + __PBP__ * 2))
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	fcall __DELAY3 + ( 7 + __PBP__ * 2) -20000
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (20000< ( 0404h + __PBP__ * 2)) AND (20000>( 7 + __PBP__ * 2))
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,(20000-( 4 + __PBP__ * 2))/4
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	fcall __DELAYX3 + 3 -((20000-( 4 + __PBP__ * 2)) MOD 4) 
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (20000< ( 040bh + __PBP__ * 2)) AND (20000> ( 0403h + __PBP__ * 2))
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,0 
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	fcall __DELAYX6 + ( 040ah + __PBP__ * 2) -20000
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (20000 >= ( 040bh + __PBP__ * 2)) AND ((((20000-( 9 + __PBP__ * 2))%0402h)/4+1)>256)
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,(20000-( 9 + __PBP__ * 2))/0402h
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV _builtin_holtek_delay_2,A
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,0
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	fcall __DELAYY5 +5- (((20000-( 9 + __PBP__ * 2))%0402h)%6) 
	ENDIF
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	IF (20000 >= ( 040bh + __PBP__ * 2)) AND ((((20000-( 9 + __PBP__ * 2))%0402h)/4+1)<=256)
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,(20000-( 9 + __PBP__ * 2))/0402h
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV _builtin_holtek_delay_2,A
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	MOV A,((20000-( 9 + __PBP__ * 2))%0402h)/4+1
;# 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c" 1
	fcall __DELAYY3 +3-(((20000-( 9 + __PBP__ * 2))%0402h)%4) 
	ENDIF
	inc ra
_L14:
	mov a,ra
	sub a,_PAUSE_2[0]
	snz z
	jmp _L15
	ret
_PAUSE endp
#line 107 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
#pragma debug scope 1 1
___wdtc equ [62]
public _main
#pragma debug scope 6 1
#line 20 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
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
    local _main_2 db 3 dup(?)
#line 21 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,175
	mov [62],a
#line 22 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	fcall _LCMInit
_L24:
#line 24 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,64
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
	mov a,64
	mov _main_2[0],a
#line 25 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	clr _main_2[1]
_L18:
	mov a,_main_2[1]
	mov rb,a
	clr rc
	sz acc.7
	set rc
	mov a,low offset _TAB_CGRAM
	add a,rb
	mov mp,a
	mov a,high offset _TAB_CGRAM
	adc a,rc
	mov sbp,a
	fcall _Crom2Prom
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
	inc _main_2[1]
	sdz _main_2[0]
	jmp _L18
	mov a,18
	mov _main_2[0],a
_L20:
	mov a,_main_2[0]
	add a,128
	mov _main_2[2],a
#line 27 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_main_2[2]
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 28 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	clr _LCMWrite4_2[0]
	mov a,1
	fcall _LCMWrite4
	mov a,1
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
	mov a,_main_2[0]
	add a,192
	mov _main_2[1],a
#line 29 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_main_2[1]
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 30 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,2
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
	mov a,3
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
#line 31 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,20
	fcall _PAUSE
#line 32 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_main_2[2]
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 33 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,4
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
	mov a,5
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
#line 34 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_main_2[1]
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 35 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,6
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
	mov a,7
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
#line 36 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,20
	fcall _PAUSE
#line 37 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_main_2[2]
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 38 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,32
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
	mov a,32
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
#line 39 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_main_2[1]
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 40 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,32
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
	mov a,32
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
#line 26 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	dec _main_2[0]
	siza _main_2[0]
	jmp _L20
#line 42 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,64
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
	mov a,64
	mov _main_2[0],a
#line 43 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	clr _main_2[1]
_L22:
#line 44 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_main_2[1]
	mov rb,a
	clr rc
	sz acc.7
	set rc
	mov a,low offset _TAB_CGRAM
	add a,rb
	mov mp,a
	mov a,high offset _TAB_CGRAM
	adc a,rc
	mov sbp,a
	fcall _Crom2Prom
	fcall _BitReverse
	mov ra,a
	mov a,ra
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
#line 43 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	inc _main_2[1]
	sdz _main_2[0]
	jmp _L22
	clr _main_2[0]
_L25:
	mov a,_main_2[0]
	add a,128
	mov _main_2[2],a
#line 46 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_main_2[2]
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 47 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,1
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
	clr _LCMWrite4_2[0]
	mov a,1
	fcall _LCMWrite4
	mov a,_main_2[0]
	add a,192
	mov _main_2[1],a
#line 48 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_main_2[1]
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 49 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,3
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
	mov a,2
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
#line 50 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,10
	fcall _PAUSE
#line 51 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_main_2[2]
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 52 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,5
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
	mov a,4
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
#line 53 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_main_2[1]
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 54 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,7
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
	mov a,6
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
#line 55 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,10
	fcall _PAUSE
#line 56 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_main_2[2]
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 57 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,32
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
	mov a,32
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
#line 58 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,_main_2[1]
	mov _LCMWrite4_2[0],a
	mov a,0
	fcall _LCMWrite4
#line 59 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	mov a,32
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
	mov a,32
	mov _LCMWrite4_2[0],a
	mov a,1
	fcall _LCMWrite4
#line 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
	inc _main_2[0]
	mov a,_main_2[0]
	sub a,20
	snz z
	jmp _L25
	jmp _L24
	jmp $
_main endp

@dummy proc
	call _main
@dummy endp

#line 45 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
#pragma debug scope 1 1
public _TAB_CGRAM
@crom	.section 'crom'
#line 6 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
@crom	.section	'crom'
_TAB_CGRAM:
#pragma debug array 42 8 64 1
#pragma debug variable 42 1 _TAB_CGRAM "TAB_CGRAM"
	db 0
	db 12
	db 30
	db 12
	db 6
	db 7
	db 7
	db 11
	db 0
	db 0
	db 0
	db 0
	db 0
	db 24
	db 4
	db 2
	db 17
	db 1
	db 1
	db 1
	db 2
	db 26
	db 12
	db 0
	db 16
	db 16
	db 8
	db 6
	db 3
	db 1
	db 1
	db 0
	db 0
	db 12
	db 30
	db 12
	db 6
	db 7
	db 6
	db 3
	db 0
	db 0
	db 0
	db 0
	db 0
	db 0
	db 16
	db 8
	db 5
	db 5
	db 3
	db 4
	db 4
	db 3
	db 15
	db 0
	db 8
	db 16
	db 16
	db 16
	db 8
	db 6
	db 12
	db 0
#pragma debug struct_begin 43 "__pg_bits"
#pragma debug field 21 8 0 1 "__pg0" ;0,1
#pragma debug field 21 8 0 1 "__pg1" ;1,1
#pragma debug field 21 8 0 1 "__pg2" ;2,1
#pragma debug field 21 8 0 1 "__pg3" ;3,1
#pragma debug field 21 8 0 1 "__pg4" ;4,1
#pragma debug field 21 8 0 1 "__pg5" ;5,1
#pragma debug field 21 8 0 1 "__pg6" ;6,1
#pragma debug field 21 8 0 1 "__pg7" ;7,1
#pragma debug struct_end
#pragma debug union_begin 44 ""
#pragma debug field 2 43 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 44 1 ___pg "__pg" 1
#pragma debug struct_begin 45 "__pgc_bits"
#pragma debug field 21 8 0 1 "__pgc0" ;0,1
#pragma debug field 21 8 0 1 "__pgc1" ;1,1
#pragma debug field 21 8 0 1 "__pgc2" ;2,1
#pragma debug field 21 8 0 1 "__pgc3" ;3,1
#pragma debug field 21 8 0 1 "__pgc4" ;4,1
#pragma debug field 21 8 0 1 "__pgc5" ;5,1
#pragma debug field 21 8 0 1 "__pgc6" ;6,1
#pragma debug field 21 8 0 1 "__pgc7" ;7,1
#pragma debug struct_end
#pragma debug union_begin 46 ""
#pragma debug field 2 45 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 46 1 ___pgc "__pgc" 1
#pragma debug struct_begin 47 "__ph_bits"
#pragma debug field 21 8 0 1 "__ph0" ;0,1
#pragma debug field 21 8 0 1 "__ph1" ;1,1
#pragma debug field 21 8 0 1 "__ph2" ;2,1
#pragma debug field 21 8 0 1 "__ph3" ;3,1
#pragma debug field 21 8 0 1 "__ph4" ;4,1
#pragma debug field 21 8 0 1 "__ph5" ;5,1
#pragma debug field 21 8 0 2 ;6,2
#pragma debug struct_end
#pragma debug union_begin 48 ""
#pragma debug field 2 47 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 48 1 ___ph "__ph" 1
#pragma debug struct_begin 49 "__phc_bits"
#pragma debug field 21 8 0 1 "__phc0" ;0,1
#pragma debug field 21 8 0 1 "__phc1" ;1,1
#pragma debug field 21 8 0 1 "__phc2" ;2,1
#pragma debug field 21 8 0 1 "__phc3" ;3,1
#pragma debug field 21 8 0 1 "__phc4" ;4,1
#pragma debug field 21 8 0 1 "__phc5" ;5,1
#pragma debug field 21 8 0 2 ;6,2
#pragma debug struct_end
#pragma debug union_begin 50 ""
#pragma debug field 2 49 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 50 1 ___phc "__phc" 1
#pragma debug struct_begin 51 "__wdtc_bits"
#pragma debug field 21 8 0 1 "__ws0" ;0,1
#pragma debug field 21 8 0 1 "__ws1" ;1,1
#pragma debug field 21 8 0 1 "__ws2" ;2,1
#pragma debug field 21 8 0 1 "__we0" ;3,1
#pragma debug field 21 8 0 1 "__we1" ;4,1
#pragma debug field 21 8 0 1 "__we2" ;5,1
#pragma debug field 21 8 0 1 "__we3" ;6,1
#pragma debug field 21 8 0 1 "__we4" ;7,1
#pragma debug struct_end
#pragma debug union_begin 52 ""
#pragma debug field 2 51 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 52 1 ___wdtc "__wdtc" 1
#line 20 "C:\Users\YVTC\Desktop\單晶片微控制器(一)\0515\H5-10_1.c"
@code .section at 0 'code'
	clr bp
	jmp _main_startup1


; 
; Generated by holtek-gcc v3.18, Tue May 15 13:06:21 2018
; Rebuild 126
; end of file
