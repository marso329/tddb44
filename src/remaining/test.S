L4:			# WRITE_INT
		push	rbp
		mov	rcx, rsp
		push	[rbp-8]
		push	rcx
		mov	rbp, rcx
		sub	rsp, 264
		mov	rax, 0
		mov	rcx, [rdp-16]	
		mov	[rcx+96], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+0]
		mov	rcx, [rdp-16]	
		mov	rcx, [rcx+768]
		cmp	rax, rcx
		je	L14
		mov	rax, 0
		jmp	L15
		L14:
		mov	rax, 1
		L15:
		mov	rcx, [rdp-16]	
		mov	[rcx+104], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+832]
		cmp	rax, 0
		je	L6
		mov	rax, 48
		push	rax
		call	L1	 # WRITE
		add	rsp, 8
		jmp	L5
		jmp	L7
L6:
L7:
		mov	rax, 0
		mov	rcx, [rdp-16]	
		mov	[rcx+112], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+0]
		mov	rcx, [rdp-16]	
		mov	rcx, [rcx+896]
		cmp	rax, rcx
		jl	L16
		mov	rax, 0
		jmp	L17
		L16:
		mov	rax, 1
		L17:
		mov	rcx, [rdp-16]	
		mov	[rcx+120], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+960]
		cmp	rax, 0
		je	L8
		mov	rax, 45
		push	rax
		call	L1	 # WRITE
		add	rsp, 8
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+0]
		neg	rax
		mov	rcx, [rdp-16]	
		mov	[rcx+128], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+1024]
		mov	rcx, [rdp-16]	
		mov	[rcx+0], rax
		jmp	L9
L8:
L9:
		mov	rax, 0
		mov	rcx, [rdp-16]	
		mov	[rcx+136], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+1088]
		mov	rcx, [rdp-16]	
		mov	[rcx+88], rax
L10:
		mov	rax, 0
		mov	rcx, [rdp-16]	
		mov	[rcx+144], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+0]
		mov	rcx, [rdp-16]	
		mov	rcx, [rcx+1152]
		cmp	rax, rcx
		jg	L18
		mov	rax, 0
		jmp	L19
		L18:
		mov	rax, 1
		L19:
		mov	rcx, [rdp-16]	
		mov	[rcx+152], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+1216]
		cmp	rax, 0
		je	L11
		mov	rax, 10
		mov	rcx, [rdp-16]	
		mov	[rcx+160], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+0]
		mov	rcx, [rdp-16]	
		mov	rcx, [rcx+1280]
		cqo
		idiv	rax, rcx
		mov	rcx, [rdp-16]	
		mov	[rcx+168], rdx
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+1344]
		mov	rcx, [rdp-16]	
		mov	[rcx+0], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+0]
		mov	rcx, 48
		add	rax, rcx
		mov	rcx, [rdp-16]	
		mov	[rcx+176], rax
		mov	rcx, [rdp-16]	
		sub	rcx, 32
		mov	rax, rcx
		mov	rcx, [rdp-16]	
		mov	rcx, [rcx+704]
		imul	rcx, 8
		sub	rax, rcx
		mov	rcx, [rdp-16]	
		mov	[rcx+184], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+1408]
		mov	rcx, [rdp-16]	
		mov	rcx, [rcx+1472]
		mov	[rcx], rax
		mov	rax, 1
		mov	rcx, [rdp-16]	
		mov	[rcx+192], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+704]
		mov	rcx, [rdp-16]	
		mov	rcx, [rcx+1536]
		add	rax, rcx
		mov	rcx, [rdp-16]	
		mov	[rcx+200], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+1600]
		mov	rcx, [rdp-16]	
		mov	[rcx+88], rax
		mov	rax, 10
		mov	rcx, [rdp-16]	
		mov	[rcx+208], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+0]
		mov	rcx, [rdp-16]	
		mov	rcx, [rcx+1664]
		cqo
		idiv	rax, rcx
		mov	rcx, [rdp-16]	
		mov	[rcx+216], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+1728]
		mov	rcx, [rdp-16]	
		mov	[rcx+0], rax
		jmp	L10
L11:
L12:
		mov	rax, 0
		mov	rcx, [rdp-16]	
		mov	[rcx+224], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+704]
		mov	rcx, [rdp-16]	
		mov	rcx, [rcx+1792]
		cmp	rax, rcx
		jg	L20
		mov	rax, 0
		jmp	L21
		L20:
		mov	rax, 1
		L21:
		mov	rcx, [rdp-16]	
		mov	[rcx+232], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+1856]
		cmp	rax, 0
		je	L13
		mov	rax, 1
		mov	rcx, [rdp-16]	
		mov	[rcx+240], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+704]
		mov	rcx, [rdp-16]	
		mov	rcx, [rcx+1920]
		sub	rax, rcx
		mov	rcx, [rdp-16]	
		mov	[rcx+248], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+1984]
		mov	rcx, [rdp-16]	
		mov	[rcx+88], rax
		mov	rcx, [rdp-16]	
		sub	rcx, 32
		mov	rax, rcx
		mov	rcx, [rdp-16]	
		mov	rcx, [rcx+704]
		imul	rcx, 8
		sub	rax, rcx
		mov	rax, [rax]
		mov	rcx, [rdp-16]	
		mov	[rcx+256], rax
		mov	rcx, [rdp-16]	
		mov	rax, [rcx+2048]
		push	rax
		call	L1	 # WRITE
		add	rsp, 8
		jmp	L12
L13:
L5:
		leave
		ret
L3:			# MAIN
		push	rbp
		mov	rcx, rsp
		push	rcx
		mov	rbp, rcx
		sub	rsp, 8
		mov	rax, 23
		mov	rcx, [rdp-8]	
		mov	[rcx+0], rax
		mov	rcx, [rdp-8]	
		mov	rax, [rcx+0]
		push	rax
		call	L4	 # WRITE_INT
		add	rsp, 8
L22:
		leave
		ret
