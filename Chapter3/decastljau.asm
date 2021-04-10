
;https://stackoverflow.com/questions/33751509/external-assembly-file-in-visual-studio
extern PPMStart:near
extern PPMAddPixel:proc

mTestEcho MACRO
	ECHO ** Test Echo with Nothing **
ENDM

point struct
x	qword ?
y	qword ?
z	qword ?
point ends

	.const

r8_ONE	real8	1.0

	.code 
	
; extern "C" int deCasteljau_(double t, struct point* b1, struct point* b2, struct point* outb);
; *outb =   *b1 * (1.0 - t) + *b2 * t;

deCasteljau_	proc
	mTestEcho

	vmovsd qword ptr [r9 + point.y], xmm0
	vmovsd qword ptr [r9 + point.z], xmm0

	vmovsd xmm2, [r8_ONE]
	vsubsd xmm1, xmm2, xmm0
	
	vmovsd xmm2, qword ptr [rdx + point.x]
	vmulsd xmm2, xmm2, xmm1
	vmovsd xmm3,  qword ptr [r8 + point.x]
	vmulsd xmm3, xmm3, xmm0
	vaddsd xmm2, xmm2, xmm3
	vmovsd qword ptr [r9 + point.x], xmm2

	vmovsd xmm2, qword ptr [rdx + point.y]
	vmulsd xmm2, xmm2, xmm1
	vmovsd xmm3,  qword ptr [r8 + point.y]
	vmulsd xmm3, xmm3, xmm0
	vaddsd xmm2, xmm2, xmm3
	vmovsd qword ptr [r9 + point.y], xmm2

	vmovsd xmm2, qword ptr [rdx + point.z]
	vmulsd xmm2, xmm2, xmm1
	vmovsd xmm3,  qword ptr [r8 + point.z]
	vmulsd xmm3, xmm3, xmm0
	vaddsd xmm2, xmm2, xmm3
	vmovsd qword ptr [r9 + point.z], xmm2

	push rcx
	push rdx
	push r8

	mov rcx, 123
	mov rdx, 321
	mov r8, 456 

	call PPMAddPixel
	;add rsp, 8
	pop r8
	pop rdx
	pop rcx ; Return the calculated result
	
	mov rax, 1	;
	ret
deCasteljau_	endp
	end