	.const

rax_ONE	qword	1

	.code 
	
; extern "C" int factorial(int n);

factorial_	proc

	cmp rcx, 1
	jl fail

	cmp rcx, 1
	je done

	push rcx
	sub rcx, 1
	
	call factorial_

	pop rcx
	imul rax, rcx
	ret

	fail:
		mov rax, 0
		ret

	done:
		mov rax, rcx
		ret

factorial_	endp


	end