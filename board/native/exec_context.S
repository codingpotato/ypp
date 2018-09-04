
/****************************************************************************************
 *                                                                                      *
 *  ----------------------------------------------------------------------------------  *
 *  |    0    |    1    |    2    |    3    |    4     |    5    |    6    |    7    |  *
 *  ----------------------------------------------------------------------------------  *
 *  |   0x0   |   0x4   |   0x8   |   0xc   |   0x10   |   0x14  |   0x18  |   0x1c  |  *
 *  ----------------------------------------------------------------------------------  *
 *  | fc_mxcsr|fc_x87_cw|        R12        |         R13        |        R14        |  *
 *  ----------------------------------------------------------------------------------  *
 *  ----------------------------------------------------------------------------------  *
 *  |    8    |    9    |   10    |   11    |    12    |    13   |    14   |    15   |  *
 *  ----------------------------------------------------------------------------------  *
 *  |   0x20  |   0x24  |   0x28  |  0x2c   |   0x30   |   0x34  |   0x38  |   0x3c  |  *
 *  ----------------------------------------------------------------------------------  *
 *  |        R15        |        RBX        |         RBP        |        RSP        |  *
 *  ----------------------------------------------------------------------------------  *
 *  ---------------------                                                               *
 *  |    16   |    17   |                                                               *
 *  ---------------------                                                               *
 *  |   0x40  |   0x44  |                                                               *
 *  ---------------------                                                               *
 *  |        RIP        |                                                               *
 *  ---------------------                                                               *
 *                                                                                      *
 ****************************************************************************************/

.text
.globl _make_ctx
.align 8
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

  /* store context function target */
  movq %rcx, 0x28(%rdi)

  /* store context function for rip */
  movq %rdx, 0x40(%rdi)

  ret

.globl _jump_ctx
.align 8
_jump_ctx:
  /* save MMX control- and status-word */
  stmxcsr (%rsi)
  /* save x87 control-word */ 
  fnstcw 0x4(%rsi)

  movq %r12, 0x8(%rsi)  /* save R12 */
  movq %r13, 0x10(%rsi)  /* save R13 */
  movq %r14, 0x18(%rsi)  /* save R14 */
  movq %r15, 0x20(%rsi)  /* save R15 */
  movq %rbx, 0x28(%rsi)  /* save RBX */
  movq %rbp, 0x30(%rsi)  /* save RBP */

  pop 0x40(%rsi) /* save RIP */
  movq %rsp, 0x38(%rsi)  /* save RSP */

.globl _set_ctx
.align 8
_set_ctx:
  /* restore MMX control- and status-word */
  ldmxcsr (%rdi)
  /* restore x87 control-word */ 
  fldcw 0x4(%rdi)

  movq 0x8(%rdi), %r12  /* restore R12 */
  movq 0x10(%rdi), %r13  /* restore R13 */
  movq 0x18(%rdi), %r14  /* restore R14 */
  movq 0x20(%rdi), %r15  /* restore R15 */
  movq 0x28(%rdi), %rbx  /* restore RBX */
  movq 0x30(%rdi), %rbp  /* restore RBP */
  movq 0x38(%rdi), %rsp /* restore RSP */

  movq 0x40(%rdi), %rax

  movq %rbx, %rdi

  jmp *%rax

finish:
  xorq %rdi, %rdi
  call __exit
  hlt
