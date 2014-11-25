;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file


delayHalf	.macro
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			.endm

delayMicro	.macro
			delayHalf
			delayHalf
			.endm


;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section
            .retainrefs                     ; Additionally retain any sections
                                            ; that have references to current
                                            ; section
;-------------------------------------------------------------------------------



tryCommand:	mov.b	#001h,r5
			xor.b	r11,r11
			xor.b	r12,r12
			xor.b	r13,r13
			xor.b	r14,r14
			Call #SendCommand
			bic.b	#001h,&P1DIR
			;bic.b	#02h,&P1OUT
			mov.w #32000,r5

			Call #readByte
			cmp.b #33h,r5
			jz tryCommand

			mov.b r6,r11
delayLoop1
			bit.b	#1,&P1IN
			jz	delayLoop1

			Call #readByte
			cmp.b #33h,r5
			jz tryCommand

			mov.b r6,r12

delayLoop2
			bit.b	#1,&P1IN
			jz	delayLoop2

			Call #readByte
			cmp.b #33h,r5
			jz tryCommand

			mov.b r6,r13

delayLoop3
			bit.b	#1,&P1IN
			jz	delayLoop3

			Call #readByte
			cmp.b #33h,r5
			jz tryCommand

			mov.b r6,r14

			mov.w #276h,r10
			mov.b r11,0(r10)
			mov.b r12,1(r10)
			mov.b r13,2(r10)
			mov.b r14,3(r10)

			ret

SendCommand	;Command in r5

			bis.b	#001h,&P1DIR
			bis.b	#001h,&P1OUT

			mov.w 	#0080h,r6

			delayMicro
			delayMicro
			delayMicro
			delayMicro

SendCommandLoop
			bic.b #001h,&P1OUT		;5

			bit.b r6,r5				;1
			jz SendCommandZero		;2
SendCommandOne
			delayHalf				;8

			bis.b #001h,&P1OUT		;5

			delayMicro				;16
			delayMicro				;16

			jmp SendCommandNext		;2

SendCommandZero
			delayMicro				;16
			delayMicro				;16
			delayHalf				;8

			bis.b #001,&P1OUT		;5

			nop
			nop						;2

SendCommandNext		;9 Cycles Left 16-2-5

			nop
			nop
			nop
			nop
			nop
			nop						;6
			RRA	r6					;1
			jnc SendCommandLoop		;2
SendCommandEnd
			bic.b #001h,&P1OUT		;5

			delayHalf				;8
			nop
			nop
			nop						;3

			bis.b #001h,&P1OUT		;5

			ret

readBit
readBitLoop1
			bit.b	#1,&P1IN
			jz	readBitLoop1

readBitLoop2
			bit.b	#1,&P1IN
			jnz	readBitLoop2

			delayMicro
			delayHalf

			mov.b	&P1IN,r5
			ret

readByte
			mov.w #32000,r4
			xor.b r6,r6


readByteLoop
			sub.w #1,r4 		;2
			jz endByte			;2
			bit.b	#1,&P1IN	;5
			jnz readByteLoop	;2

			delayMicro
			delayHalf

			mov.b &P1IN,r5
			rrc.b r5
			rrc.b r5	;7
			and.b #80h,r5
			bis.b r5,r6

			Call #readBit
			rrc.b r5
			rrc.b r5	;7
			rrc.b r5	;6
			and.b #40h,r5
			bis.b r5,r6

			Call #readBit
			rrc.b r5
			rrc.b r5	;7
			rrc.b r5	;6
			rrc.b r5	;5
			and.b #20h,r5
			bis.b r5,r6

			Call #readBit
			rrc.b r5
			rrc.b r5	;7
			rrc.b r5	;6
			rrc.b r5	;5
			rrc.b r5	;4
			and.b #10h,r5
			bis.b r5,r6

			Call #readBit
			rrc.b r5
			rrc.b r5	;7
			rrc.b r5	;6
			rrc.b r5	;5
			rrc.b r5	;4
			rrc.b r5	;3
			and.b #8h,r5
			bis.b r5,r6

			Call #readBit
			rrc.b r5
			rrc.b r5	;7
			rrc.b r5	;6
			rrc.b r5	;5
			rrc.b r5	;4
			rrc.b r5	;3
			rrc.b r5	;2
			and.b #4h,r5
			bis.b r5,r6

			Call #readBit
			rrc.b r5
         rrc.b r5 ;7
         rrc.b r5 ;6
         rrc.b r5 ;5
         rrc.b r5 ;4
         rrc.b r5 ;3
         rrc.b r5 ;2
         rrc.b r5 ;1
			and.b #2h,r5
			bis.b r5,r6

			Call #readBit
			and.b #1h,r5
			bis.b r5,r6

			ret

endByte
			mov.b #33h,r5
			ret

	.global tryCommand

;-------------------------------------------------------------------------------
;           Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect 	.stack

