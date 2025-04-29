use64

efi_mem_cpy:
	push	rbp	;
	mov	rbp, rsp	;,
	sub	rsp, 40	;,
	mov	qword [rbp-24], rdi	; dest, dest
	mov	qword [rbp-32], rsi	; src, src
	mov	dword [rbp-36], edx	; size, size
	cmp	qword [rbp-24], 0	; dest,
	je	.L2	;,
	cmp	qword [rbp-32], 0	; src,
	jne	.L3	;,

.L2:
	mov	eax, 0	; _8,
	jmp	.L4	;

.L3:
	mov	rax, qword [rbp-24]	; tmp104, dest
	mov	qword [rbp-8], rax	; dest_data, tmp104
	mov	rax, qword [rbp-32]	; tmp105, src
	mov	qword [rbp-16], rax	; src_data, tmp105
	jmp	.L5	;

.L6:
	mov	rdx, qword [rbp-16]	; src_data.0_1, src_data
	lea	rax, [rdx+1]	; tmp106,
	mov	qword [rbp-16], rax	; src_data, tmp106
	mov	rax, qword [rbp-8]	; dest_data.1_2, dest_data
	lea	rcx, [rax+1]	; tmp107,
	mov	qword [rbp-8], rcx	; dest_data, tmp107
	movzx edx, byte [rdx]	; _3, *src_data.0_1
	mov	byte [rax], dl	; *dest_data.1_2, _3

.L5:
	mov	eax, dword [rbp-36]	; size.2_4, size
	lea	edx, [rax-1]	; tmp108,
	mov	dword [rbp-36], edx	; size, tmp108
	test	eax, eax	; size.2_4
	jne	.L6	;,
	mov	rax, qword [rbp-24]	; _8, dest

.L4:
	leave	
	ret	

efi_mem_set:
	push	rbp	;
	mov	rbp, rsp	;,
	sub	rsp, 32	;,
	mov	qword [rbp-24], rdi	; ptr, ptr
	mov	dword [rbp-28], esi	; size, size
	mov	eax, edx	; tmp100, value
	mov	byte [rbp-32], al	; value, tmp101
	cmp	qword [rbp-24], 0	; ptr,
	je	.L12	;,
	mov	rax, qword [rbp-24]	; tmp102, ptr
	mov	qword [rbp-8], rax	; ptr_data, tmp102
	jmp	.L10	;

.L11:
	mov	rax, qword [rbp-8]	; ptr_data.3_1, ptr_data
	lea	rdx, [rax+1]	; tmp103,
	mov	qword [rbp-8], rdx	; ptr_data, tmp103
	movzx	edx, byte [rbp-32]	; tmp104, value
	mov	byte [rax], dl	; *ptr_data.3_1, tmp104

.L10:
	mov	eax, dword [rbp-28]	; size.4_2, size
	lea	edx, [rax-1]	; tmp105,
	mov	dword [rbp-28], edx	; size, tmp105
	test	eax, eax	; size.4_2
	jne	.L11	;,
	jmp	.L7	;

.L12:
	nop	

.L7:
	leave	
	ret	

uefi_realloc:
	push	rbp	;
	mov	rbp, rsp	;,
	sub	rsp, 16	;,
	mov	qword [rbp-8], rdi	; old_ptr, old_ptr
	mov	qword [rbp-16], rsi	; new_size, new_size
	mov	eax, 0	; _1,
	leave	
	ret	

uefi_mem_cmp:
	push	rbp	;
	mov	rbp, rsp	;,
	sub	rsp, 40	;,
	mov	qword [rbp-24], rdi	; a, a
	mov	qword [rbp-32], rsi	; b, b
	mov	qword [rbp-40], rdx	; size, size
	mov	rax, qword [rbp-24]	; tmp105, a
	mov	qword [rbp-8], rax	; a_data, tmp105
	mov	rax, qword [rbp-32]	; tmp106, b
	mov	qword [rbp-16], rax	; b_data, tmp106
	jmp	.L16	;

.L18:
	mov	rax, qword [rbp-8]	; a_data.5_1, a_data
	lea	rdx, [rax+1]	; tmp107,
	mov	qword [rbp-8], rdx	; a_data, tmp107
	movzx	ecx, byte [rax]	; _2, *a_data.5_1
	mov	rax, qword [rbp-16]	; b_data.6_3, b_data
	lea	rdx, [rax+1]	; tmp108,
	mov	qword [rbp-16], rdx	; b_data, tmp108
	movzx	eax, byte [rax]	; _4, *b_data.6_3
	cmp	cl, al	; _2, _4
	je	.L16	;,
	mov	eax, 0	; _9,
	jmp	.L17	;

.L16:
	mov	rax, qword [rbp-40]	; size.7_5, size
	lea	rdx, [rax-1]	; tmp109,
	mov	qword [rbp-40], rdx	; size, tmp109
	test	rax, rax	; size.7_5
	jne	.L18	;,
	mov	eax, 1	; _9,

.L17:
	leave	
	ret	

uefi_rand:
	push	rbp	;
	mov	rbp, rsp	;,
	mov	eax, 0	; _1,
	pop	rbp	;
	ret	

send_data:
	push	rbp	;
	mov	rbp, rsp	;,
	sub	rsp, 32	;,
	mov	ecx, edi	; tmp102, data_type
	mov	eax, esi	; tmp104, error_type
	mov	qword [rbp-32], rdx	; data, data
	mov	edx, ecx	; tmp103, tmp102
	mov	word [rbp-20], dx	; data_type, tmp103
	mov	word [rbp-24], ax	; error_type, tmp105
	movzx	eax, word [rbp-24]	; _1, error_type
	sal	eax, 16	; _1,
	mov	edx, eax	; _2, _1
	movzx	eax, word [rbp-20]	; _3, data_type
	or	eax, edx	; _4, _2
	mov	dword [rbp-4], eax	; type, _4
	mov	edx, dword [rbp-4]	; tmp106, type
	mov	rcx, qword [rbp-32]	; tmp107, data
	mov eax, edx
	out 69h, eax
	mov rax, rcx
	out 69h, eax
	shr rax, 32
	out 69h, eax
	nop	
	leave	
	ret	

panic:
	mov	rax, rdi	; file_name, file_name
	mov	r12, rsi	; line, line
	mov	rbx, rdx	; panic_msg, panic_msg
	mov	rdx, rax	;, file_name.8_1
	mov	esi, 0	;,
	mov	edi, 1	;,
	call	send_data	;
	mov	rax, r12	; line.9_2, line
	mov	rdx, rax	;, line.9_2
	mov	esi, 0	;,
	mov	edi, 0	;,
	call	send_data	;
	mov	rax, rbx	; panic_msg.10_3, panic_msg
	mov	rdx, rax	;, panic_msg.10_3
	mov	esi, 0	;,
	mov	edi, 1	;,
	call	send_data	;
	hlt
	nop	
	ud2	

print_error:
	push	rbp	;
	mov	rbp, rsp	;,
	sub	rsp, 24	;,
	mov	qword [rbp-8], rdi	; file_name, file_name
	mov	qword [rbp-16], rsi	; line, line
	mov	qword [rbp-24], rdx	; err_msg, err_msg
	mov	rax, qword [rbp-8]	; file_name.11_1, file_name
	mov	rdx, rax	;, file_name.11_1
	mov	esi, 1	;,
	mov	edi, 1	;,
	call	send_data	;
	mov	rax, qword [rbp-16]	; line.12_2, line
	mov	rdx, rax	;, line.12_2
	mov	esi, 1	;,
	mov	edi, 0	;,
	call	send_data	;
	mov	rax, qword [rbp-24]	; err_msg.13_3, err_msg
	mov	rdx, rax	;, err_msg.13_3
	mov	esi, 1	;,
	mov	edi, 1	;,
	call	send_data	;
	nop	
	leave	
	ret	

	; .local	open_protocols_info_entries
	; .comm	open_protocols_info_entries,8,8
	; .globl	open_protocols_info_entries_cnt
	; .bss
	; .align 8
	; .type	open_protocols_info_entries_cnt, @object
	; .size	open_protocols_info_entries_cnt, 8
; open_protocols_info_entries_cnt:
	; .zero	8
	; .local	device_handle_magic
	; .comm	device_handle_magic,4,4
	; .local	device_handles
	; .comm	device_handles,8,8
	; .local	device_handles_cnt
	; .comm	device_handles_cnt,4,4
	; .section	.rodata
	; .align 16
	; .type	efi_system_table_header, @object
	; .size	efi_system_table_header, 24
; efi_system_table_header:
; ; signature:
	; .quad	6076298535811760713
; ; revision:
	; .long	131182
; ; header_size:
	; .long	144
; ; crc32:
	; .long	0
; ; reserved:
	; .long	0
; .LC0:
	; .string	"SPDQFCDP"
	; .data
	; .align 8
	; .type	firmware_vendor, @object
	; .size	firmware_vendor, 8
; firmware_vendor:
	; .quad	.LC0
	; .align 32
	; .type	efi_system_table, @object
	; .size	efi_system_table, 120
; efi_system_table:
; ; hdr:
; ; signature:
	; .quad	6076298535811760713
; ; revision:
	; .long	131182
; ; header_size:
	; .long	144
; ; crc32:
	; .long	0
; ; reserved:
	; .long	0
; ; firmware_vendor:
	; .quad	0
; ; firmware_revision:
	; .long	65536
; ; console_in_handle:
	; .zero	4
	; .quad	0
; ; con_in:
	; .quad	0
; ; console_out_handle:
	; .quad	0
; ; con_out:
	; .quad	0
; ; standard_error_handle:
	; .quad	0
; ; std_err:
	; .quad	0
; ; runtime_services:
	; .quad	0
; ; boot_services:
	; .quad	0
; ; number_of_table_entries:
	; .long	0
; ; configuration_table:
	; .zero	4
	; .quad	0
	; .section	.rodata
	; .align 8
; .LC1:
	; .string	"Protocol is NULL or interface_type is not EFI_NATIVE_INTERFACE or handle is NULL\n"
; .LC2:
	; .string	"uefi_protocols.c"
; .LC3:
	; .string	"Invalid Handle\n"
; .LC4:
	; .string	"Duplicate GUID\n"
	; .align 8
; .LC5:
	; .string	"Failed to reallocate the buffer for protocol_infos\n"
	; .align 8
; .LC6:
	; .string	"Failed to allocate the buffer for the new handle\n"

register_protocol_info:
	push	rbp	;
	mov	rbp, rsp	;,
	sub	rsp, 96	;,
	mov	qword [rbp-72], rdi	; handle, handle
	mov	qword [rbp-80], rsi	; protocol, protocol
	mov	dword [rbp-84], edx	; interface_type, interface_type
	mov	qword [rbp-96], rcx	; interface, interface
	cmp	qword [rbp-80], 0	; protocol,
	je	.L27	;,
	cmp	dword [rbp-84], 0	; interface_type,
	jne	.L27	;,
	cmp	qword [rbp-72], 0	; handle,
	jne	.L28	;,

.L27:
	mov	edx, .L27	;,
	mov	esi, 96	;,
	mov	edi, .L28	;,
	call	print_error	;
	mov	eax, 2	; _62,
	jmp	.L29	;

.L28:
.device_handles:
	mov	rax, qword [rbp-72]	; tmp156, handle
	mov	rax, qword [rax]	; _1, *handle_68(D)
	test	rax, rax	; _1
	je	.L30	;,
	mov	byte [rbp-1], 0	; is_valid_handle,
	mov	qword [rbp-16], 0	; real_handle,
	mov	qword [rbp-24], 0	; i,
	jmp	.L31	;

.L34:
	mov	rax, qword [rbp-72]	; tmp157, handle
	mov	rcx, qword [rax]	; _2, *handle_68(D)
	mov	rsi, qword [rip + .device_handles]	; device_handles.14_3, device_handles
	mov	rdx, qword [rbp-24]	; tmp158, i
	mov	rax, rdx	; _4, tmp158
	add	rax, rax	; _4
	add	rax, rdx	; _4, tmp158
	sal	rax, 3	; tmp160,
	add	rax, rsi	; _5, device_handles.14_3
	mov	rax, qword [rax]	; _6, _5->handle
	cmp	rcx, rax	; _2, _6
	je	.L32	;,
	mov	byte [rbp-1], 1	; is_valid_handle,
	mov	rcx, qword [rip + .device_handles] ; device_handles.15_7, device_handles
	mov	rdx, qword [rbp-24]	; tmp161, i
	mov	rax, rdx	; _8, tmp161
	add	rax, rax	; _8
	add	rax, rdx	; _8, tmp161
	sal	rax, 3	; tmp163,
	add	rax, rcx	; tmp164, device_handles.15_7
	mov	qword [rbp-16], rax	; real_handle, tmp164
	jmp	.L33	;

.L32:
	add	qword [rbp-24], 1	; i,

.L31:
	mov	eax, dword [rip + .device_handles]	; device_handles_cnt.16_9, device_handles_cnt
	mov	eax, eax	; _10, device_handles_cnt.16_9
	cmp	qword [rbp-24], rax	; i, _10
	jb	.L34	;,

.LC4:
.LC2:
.LC5:
.LC6:
.L33:
	cmp	byte [rbp-1], 0	; is_valid_handle,
	jne	.L35	;,
	mov	edx, .device_handles	;,
	mov	esi, 113	;,
	mov	edi, .device_handles	;,
	call	print_error	;
	mov	eax, 2	; _62,
	jmp	.L29	;

.L35:
	mov	byte [rbp-25], 0	; is_duplicate_guid,
	mov	qword [rbp-40], 0	; i,
	jmp	.L36	;

.L39:
	mov	rax, qword [rbp-16]	; tmp165, real_handle
	mov	rcx, qword [rax+8]	; _11, real_handle_58->protocol_infos
	mov	rdx, qword [rbp-40]	; tmp166, i
	mov	rax, rdx	; _12, tmp166
	add	rax, rax	; _12
	add	rax, rdx	; _12, tmp166
	sal	rax, 4	; tmp168,
	add	rax, rcx	; _13, _11
	mov	rcx, rax	; _14, _13
	mov	rax, qword [rbp-80]	; tmp169, protocol
	mov	edx, 16	;,
	mov	rsi, rcx	;, _14
	mov	rdi, rax	;, tmp169
	call	uefi_mem_cmp	;
	test	al, al	; _15
	je	.L37	;,
	mov	byte [rbp-25], 1	; is_duplicate_guid,
	jmp	.L38	;

.L37:
	add	qword [rbp-40], 1	; i,

.L36:
	mov	rax, qword [rbp-16]	; tmp170, real_handle
	mov	rax, qword [rax+16]	; _16, real_handle_58->protocol_infos_cnt
	cmp	qword [rbp-40], rax	; i, _16
	jb	.L39	;,

.L38:
	cmp	byte [rbp-25], 0	; is_duplicate_guid,
	je	.L40	;,
	mov	edx, .LC4	;,
	mov	esi, 127	;,
	mov	edi, .LC2	;,
	call	print_error	;
	mov	eax, 2	; _62,
	jmp	.L29	;

.L40:
	mov	rax, qword [rbp-16]	; tmp171, real_handle
	mov	rax, qword [rax+16]	; _17, real_handle_58->protocol_infos_cnt
	lea	rdx, [rax+1]	; _18,
	mov	rax, qword [rbp-16]	; tmp172, real_handle
	mov	qword [rax+16], rdx	; real_handle_58->protocol_infos_cnt, _18
	mov	rax, qword [rbp-16]	; tmp173, real_handle
	mov	rdx, qword [rax+16]	; _19, real_handle_58->protocol_infos_cnt
	mov	rax, rdx	; _20, _19
	add	rax, rax	; _20
	add	rax, rdx	; _20, _19
	sal	rax, 4	; tmp175,
	mov	rdx, rax	; _20, _20
	mov	rax, qword [rbp-16]	; tmp176, real_handle
	mov	rax, qword [rax+8]	; _21, real_handle_58->protocol_infos
	mov	rsi, rdx	;, _20
	mov	rdi, rax	;, _21
	call	uefi_realloc	;
	mov	rdx, qword [rbp-16]	; tmp177, real_handle
	mov	qword [rdx+8], rax	; real_handle_58->protocol_infos, _22
	mov	rax, qword [rbp-16]	; tmp178, real_handle
	mov	rax, qword [rax+8]	; _23, real_handle_58->protocol_infos
	test	rax, rax	; _23
	jne	.L41	;,
	mov	edx, .LC5	;,
	mov	esi, 133	;,
	mov	edi, .LC2	;,
	call	print_error	;
	mov	eax, 1	; _62,
	jmp	.L29	;

.L41:
	mov	rax, qword [rbp-16]	; tmp179, real_handle
	mov	rcx, qword [rax+8]	; _24, real_handle_58->protocol_infos
	mov	rax, qword [rbp-16]	; tmp180, real_handle
	mov	rdx, qword [rax+16]	; _25, real_handle_58->protocol_infos_cnt
	mov	rax, rdx	; _26, _25
	add	rax, rax	; _26
	add	rax, rdx	; _26, _25
	sal	rax, 4	; tmp182,
	sub	rax, 48	; _27,
	add	rax, rcx	; tmp183, _24
	mov	qword [rbp-64], rax	; protocol_info, tmp183
	mov	rax, qword [rbp-64]	; tmp184, protocol_info
	mov	edx, 0	;,
	mov	esi, 48	;,
	mov	rdi, rax	;, tmp184
	call	efi_mem_set	;
	mov	rax, qword [rbp-64]	; _28, protocol_info
	mov	rcx, qword [rbp-80]	; tmp185, protocol
	mov	edx, 16	;,
	mov	rsi, rcx	;, tmp185
	mov	rdi, rax	;, _28
	call	efi_mem_cpy	;
	mov	rax, qword [rbp-64]	; tmp186, protocol_info
	mov	edx, dword [rbp-84]	; tmp187, interface_type
	mov	dword [rax+16], edx	; protocol_info_106->interface_type, tmp187
	mov	rax, qword [rbp-64]	; tmp188, protocol_info
	mov	rdx, qword [rbp-96]	; tmp189, interface
	mov	qword [rax+24], rdx	; protocol_info_106->interface, tmp189
	mov	eax, 0	; _62,
	jmp	.L29	;

.L30:
	mov	eax, dword [rip + .LC2]	; device_handles_cnt.17_29, device_handles_cnt
	add	eax, 1	; _30,
	mov	dword [rip + .LC2], eax	; device_handles_cnt, _30
	mov	eax, dword [rip + .LC2]	; device_handles_cnt.18_31, device_handles_cnt
	mov	edx, eax	; _32, device_handles_cnt.18_31
	mov	rax, rdx	; _33, _32
	add	rax, rax	; _33
	add	rax, rdx	; _33, _32
	sal	rax, 3	; tmp191,
	mov	rdx, rax	; _33, _33
	mov	rax, qword [rip + .LC2]	; .LC2.19_34, .LC2
	mov	rsi, rdx	;, _33
	mov	rdi, rax	;, .LC2.19_34
	call	uefi_realloc	;
	mov	qword [rip + .LC2], rax	; .LC2, _35
	mov	rax, qword [rip + .LC2]	; .LC2.20_36, .LC2
	test	rax, rax	; .LC2.20_36
	jne	.L42	;,
	mov	edx, .LC6	;,
	mov	esi, 152	;,
	mov	edi, .LC2	;,
	call	print_error	;
	mov	eax, 1	; _62,
	jmp	.L29	;

.L42:
	mov	eax, dword [rip + .LC6]	; .LC6.21_37, .LC6
	add	eax, 1	; _38,
	mov	dword [rip + .LC6], eax	; .LC6, _38
	mov	rax, qword [rbp-72]	; tmp192, handle
	mov	edx, 4	;,
	mov	esi, .LC6	;,
	mov	rdi, rax	;, tmp192
	call	efi_mem_cpy	;
	mov	rdx, qword [rip + .LC2]	; .LC2.22_39, .LC2
	mov	eax, dword [rip + .LC2]	; .LC2.23_40, .LC2
	mov	ecx, eax	; _41, .LC2.23_40
	mov	rax, rcx	; _42, _41
	add	rax, rax	; _42
	add	rax, rcx	; _42, _41
	sal	rax, 3	; tmp194,
	sub	rax, 24	; _43,
	add	rax, rdx	; tmp195, .LC2.22_39
	mov	qword [rbp-48], rax	; new_handle, tmp195
	mov	rax, qword [rbp-48]	; tmp196, new_handle
	mov	edx, 0	;,
	mov	esi, 24	;,
	mov	rdi, rax	;, tmp196
	call	efi_mem_set	;
	mov	rax, qword [rbp-48]	; tmp197, new_handle
	mov	rax, qword [rax]	; _44, new_handle_75->handle
	mov	edx, 4	;,
	mov	esi, .LC6	;,
	mov	rdi, rax	;, _44
	call	efi_mem_cpy	;
	mov	rax, qword [rbp-48]	; tmp198, new_handle
	mov	rax, qword [rax+16]	; _45, new_handle_75->protocol_infos_cnt
	lea	rdx, [rax+1]	; _46,
	mov	rax, qword [rbp-48]	; tmp199, new_handle
	mov	qword [rax+16], rdx	; new_handle_75->protocol_infos_cnt, _46
	mov	rax, qword [rbp-48]	; tmp200, new_handle
	mov	rdx, qword [rax+16]	; _47, new_handle_75->protocol_infos_cnt
	mov	rax, rdx	; _48, _47
	add	rax, rax	; _48
	add	rax, rdx	; _48, _47
	sal	rax, 4	; tmp202,
	mov	rdx, rax	; _48, _48
	mov	rax, qword [rbp-48]	; tmp203, new_handle
	mov	rax, qword [rax+8]	; _49, new_handle_75->protocol_infos
	mov	rsi, rdx	;, _48
	mov	rdi, rax	;, _49
	call	uefi_realloc	;
	mov	rdx, qword [rbp-48]	; tmp204, new_handle
	mov	qword [rdx+8], rax	; new_handle_75->protocol_infos, _50
	mov	rax, qword [rbp-48]	; tmp205, new_handle
	mov	rax, qword [rax+8]	; _51, new_handle_75->protocol_infos
	test	rax, rax	; _51
	jne	.L43	;,
	mov	edx, .LC6	;,
	mov	esi, 166	;,
	mov	edi, .LC2	;,
	call	print_error	;
	mov	eax, 1	; _62,
	jmp	.L29	;

.L43:
	mov	rax, qword [rbp-48]	; tmp206, new_handle
	mov	rcx, qword [rax+8]	; _52, new_handle_75->protocol_infos
	mov	rax, qword [rbp-48]	; tmp207, new_handle
	mov	rdx, qword [rax+16]	; _53, new_handle_75->protocol_infos_cnt
	mov	rax, rdx	; _54, _53
	add	rax, rax	; _54
	add	rax, rdx	; _54, _53
	sal	rax, 4	; tmp209,
	sub	rax, 48	; _55,
	add	rax, rcx	; tmp210, _52
	mov	qword [rbp-56], rax	; protocol_info, tmp210
	mov	rax, qword [rbp-56]	; tmp211, protocol_info
	mov	edx, 0	;,
	mov	esi, 48	;,
	mov	rdi, rax	;, tmp211
	call	efi_mem_set	;
	mov	rax, qword [rbp-56]	; _56, protocol_info
	mov	rcx, qword [rbp-80]	; tmp212, protocol
	mov	edx, 16	;,
	mov	rsi, rcx	;, tmp212
	mov	rdi, rax	;, _56
	call	efi_mem_cpy	;
	mov	rax, qword [rbp-56]	; tmp213, protocol_info
	mov	edx, dword [rbp-84]	; tmp214, interface_type
	mov	dword [rax+16], edx	; protocol_info_81->interface_type, tmp214
	mov	rax, qword [rbp-56]	; tmp215, protocol_info
	mov	rdx, qword [rbp-96]	; tmp216, interface
	mov	qword [rax+24], rdx	; protocol_info_81->interface, tmp216
	mov	eax, 0	; _62,

.L29:
	leave	
	ret	

	; .size	register_protocol_info, .-register_protocol_info
	; .section	.rodata
; .LC7:
	; .string	"Fuck you bitch!\n"
	; .align 8
; .LC8:
	; .string	"An error occurred while registering the protocol info.\n"

init_system:
	push	rbp	;
	mov	rbp, rsp	;,
	sub	rsp, 32	;,
	mov	edx, .LC2	;,
	mov	esi, 183	;,
	mov	edi, .LC2	;,
	call	panic	;
	mov	rax, qword [rip + .LC2]	; firmware_vendor.24_1, firmware_vendor
	mov	qword [rip + .LC2 + 24], rax	; efi_system_table.firmware_vendor, firmware_vendor.24_1
	call	uefi_rand	;
	mov	dword [rip + .LC6], eax	; .LC6, _2
	mov	qword [rbp-8], 0	; first_handle,
	mov	dword [rbp-32], 947156929	; protocol.data1,
	mov	word [rbp-28], 27079	; protocol.data2,
	mov	word [rbp-26], 4562	; protocol.data3,
	mov	rax, 4283602510276475278	; tmp107,
	mov	qword [rbp-24], rax	; protocol.data4, tmp107
	lea	rsi, [rbp-32]	; tmp103,
	lea	rax, [rbp-8]	; tmp104,
	mov	ecx, 0	;,
	mov	edx, 0	;,
	mov	rdi, rax	;, tmp104
	call	register_protocol_info	;
	test	eax, eax	; _3
	je	.L45	;,
	mov	edx, .LC4	;,
	mov	esi, 193	;,
	mov	edi, .LC2	;,
	call	panic	;
	mov	eax, -1	; _4,
	jmp	.L47	;

.LC2:
.LC6:
.LC4:
.L45:
	mov	eax, 0	; _4,

.L47:
	leave	
	ret	

