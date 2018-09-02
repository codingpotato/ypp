/* Context: */
/* 0x0,      0x4,       0x8; 0x10; 0x18; 0x20; 0x28; 0x30; 0x38; 0x40 */
/* fc_mxcsr, fc_x87_cw; r12; r13;  r14;  r15;  rbx;  rbp;  rsp;  rip  */

.globl _make_ctx
_make_ctx:
  /* shift address of stack_ptr to lower 16 byte boundary */
  andq $-16, %rsi

  /* store abs address of label finish in stack */
  leaq finish(%rip), %rax
  subq $8, %rsi
  movq %rax, (%rsi)
  
  /* store rsp */
  movq %rsi, 0x38(%rdi)

  /* save MMX control- and status-word */
  stmxcsr (%rdi)
  /* save x87 control-word */
  fnstcw 0x4(%rdi)

  /* store context function for rip */
  movq %rdx, 0x40(%rdi)

  ret

.globl _jump_ctx
_jump_ctx:
  /* save MMX control- and status-word */
  stmxcsr (%rdi)
  /* save x87 control-word */ 
  fnstcw 0x4(%rdi)

  movq %r12, 0x8(%rdi)  /* save R12 */
  movq %r13, 0x10(%rdi)  /* save R13 */
  movq %r14, 0x18(%rdi)  /* save R14 */
  movq %r15, 0x20(%rdi)  /* save R15 */
  movq %rbx, 0x28(%rdi)  /* save RBX */
  movq %rbp, 0x30(%rdi)  /* save RBP */

  pop 0x40(%rdi) /* save RIP */
  movq %rsp, 0x38(%rdi)  /* save RSP */

  /* restore MMX control- and status-word */
  ldmxcsr (%rsi)
  /* restore x87 control-word */ 
  fldcw 0x4(%rsi)

  movq 0x8(%rsi), %r12  /* restore R12 */
  movq 0x10(%rsi), %r13  /* restore R13 */
  movq 0x18(%rsi), %r14  /* restore R14 */
  movq 0x20(%rsi), %r15  /* restore R15 */
  movq 0x28(%rsi), %rbx  /* restore RBX */
  movq 0x30(%rsi), %rbp  /* restore RBP */
  movq 0x38(%rsi), %rsp /* restore RSP */

  movq %rdx, %rdi

  jmp *0x40(%rsi)

finish:
  xorq %rdi, %rdi
  call __exit
  hlt
