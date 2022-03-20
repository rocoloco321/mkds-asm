//ansub_020008F8:
//	push {r0-r14}
//	bl StartHook
//	pop {r0-r14}
//	bx r1 //NitroMain


//install exception handler
arepl_020366D0:
	ldr r1,=ExceptionHandler
	ldr r2,=0x021701BC
	str r1, [r2]
	mov r1, #0
	bx lr