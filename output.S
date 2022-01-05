  .comm      v0, 200, 4
  .global    v1
  .section   .sdata
  .align     2
  .type      v1, @object
  .size      v1, 4
v1:
  .word      0
  .global    v2
  .section   .sdata
  .align     2
  .type      v2, @object
  .size      v2, 4
v2:
  .word      0
  .comm      v3, 200, 4
  .comm      v4, 200, 4
  .comm      v5, 400, 4
  .text
  .align     2
  .global    printans
  .type      printans, @function
printans:
  addi   sp, sp, -48
  sw     ra, 44(sp)
  lui    t1, %hi(v1)
  lw     t1, %lo(v1)(t1)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 4(sp)
  lw     t1, 4(sp)
  la     t0, v1
  sw     t1, 0(t0)
  li     t1, 1
  sw     t1, 0(sp)
.l0:
  lw     t1, 0(sp)
  lui    t2, %hi(v2)
  lw     t2, %lo(v2)(t2)
  sgt    t0, t1, t2
  seqz   t0, t0
  sw     t0, 8(sp)
  lw     t0, 8(sp)
  li     t1, 0
  beq    t0, t1, .l2
.l1:
  lw     t1, 0(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 12(sp)
  la     t1, v0
  lw     t2, 12(sp)
  add    t0, t1, t2
  sw     t0, 12(sp)
  lw     t1, 12(sp)
  lw     t0, 0(t1)
  sw     t0, 12(sp)
  lw     a0, 12(sp)
  call   putint
  lw     t1, 0(sp)
  lui    t2, %hi(v2)
  lw     t2, %lo(v2)(t2)
  xor    t0, t1, t2
  seqz   t0, t0
  sw     t0, 20(sp)
  lw     t0, 20(sp)
  li     t1, 0
  beq    t0, t1, .l4
.l3:
  li     a0, 10
  call   putch
  lw     ra, 44(sp)
  addi   sp, sp, 48
  ret
  j      .l5
.l4:
  li     a0, 32
  call   putch
.l5:
  lw     t1, 0(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 32(sp)
  lw     t1, 32(sp)
  sw     t1, 0(sp)
  j      .l0
.l2:
  lw     ra, 44(sp)
  addi   sp, sp, 48
  ret
  .size      printans, .-printans
  .text
  .align     2
  .global    f
  .type      f, @function
f:
  addi   sp, sp, -112
  sw     ra, 108(sp)
  sw     a0, 0(sp)
  li     t1, 1
  sw     t1, 4(sp)
.l6:
  lw     t1, 4(sp)
  lui    t2, %hi(v2)
  lw     t2, %lo(v2)(t2)
  sgt    t0, t1, t2
  seqz   t0, t0
  sw     t0, 8(sp)
  lw     t0, 8(sp)
  li     t1, 0
  beq    t0, t1, .l8
.l7:
  lw     t1, 4(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 12(sp)
  la     t1, v3
  lw     t2, 12(sp)
  add    t0, t1, t2
  sw     t0, 12(sp)
  lw     t1, 12(sp)
  lw     t0, 0(t1)
  sw     t0, 12(sp)
  lw     t1, 12(sp)
  li     s0, 1
  xor    t0, t1, s0
  snez   t0, t0
  sw     t0, 16(sp)
  lw     t0, 16(sp)
  li     t1, 0
  beq    t0, t1, .l10
  lw     t1, 0(sp)
  lw     t2, 4(sp)
  add    t0, t1, t2
  sw     t0, 24(sp)
  lw     t1, 24(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 20(sp)
  la     t1, v4
  lw     t2, 20(sp)
  add    t0, t1, t2
  sw     t0, 20(sp)
  lw     t1, 20(sp)
  lw     t0, 0(t1)
  sw     t0, 20(sp)
  lw     t1, 20(sp)
  li     s0, 0
  xor    t0, t1, s0
  seqz   t0, t0
  sw     t0, 28(sp)
  lw     t0, 28(sp)
  li     t1, 0
  beq    t0, t1, .l10
  lui    t1, %hi(v2)
  lw     t1, %lo(v2)(t1)
  lw     t2, 0(sp)
  add    t0, t1, t2
  sw     t0, 40(sp)
  lw     t1, 40(sp)
  lw     t2, 4(sp)
  sub    t0, t1, t2
  sw     t0, 40(sp)
  lw     t1, 40(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 36(sp)
  la     t1, v5
  lw     t2, 36(sp)
  add    t0, t1, t2
  sw     t0, 36(sp)
  lw     t1, 36(sp)
  lw     t0, 0(t1)
  sw     t0, 36(sp)
  lw     t1, 36(sp)
  seqz   t0, t1
  sw     t0, 32(sp)
  lw     t0, 32(sp)
  li     t1, 0
  beq    t0, t1, .l10
.l9:
  lw     t1, 0(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 44(sp)
  la     t1, v0
  lw     t2, 44(sp)
  add    t0, t1, t2
  sw     t0, 44(sp)
  lw     t1, 4(sp)
  lw     t0, 44(sp)
  sw     t1, 0(t0)
  lw     t1, 0(sp)
  lui    t2, %hi(v2)
  lw     t2, %lo(v2)(t2)
  xor    t0, t1, t2
  seqz   t0, t0
  sw     t0, 48(sp)
  lw     t0, 48(sp)
  li     t1, 0
  beq    t0, t1, .l12
.l11:
  call   printans
.l12:
  lw     t1, 4(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 56(sp)
  la     t1, v3
  lw     t2, 56(sp)
  add    t0, t1, t2
  sw     t0, 56(sp)
  li     t1, 1
  lw     t0, 56(sp)
  sw     t1, 0(t0)
  lw     t1, 0(sp)
  lw     t2, 4(sp)
  add    t0, t1, t2
  sw     t0, 64(sp)
  lw     t1, 64(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 60(sp)
  la     t1, v4
  lw     t2, 60(sp)
  add    t0, t1, t2
  sw     t0, 60(sp)
  li     t1, 1
  lw     t0, 60(sp)
  sw     t1, 0(t0)
  lui    t1, %hi(v2)
  lw     t1, %lo(v2)(t1)
  lw     t2, 0(sp)
  add    t0, t1, t2
  sw     t0, 72(sp)
  lw     t1, 72(sp)
  lw     t2, 4(sp)
  sub    t0, t1, t2
  sw     t0, 72(sp)
  lw     t1, 72(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 68(sp)
  la     t1, v5
  lw     t2, 68(sp)
  add    t0, t1, t2
  sw     t0, 68(sp)
  li     t1, 1
  lw     t0, 68(sp)
  sw     t1, 0(t0)
  lw     t1, 0(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 76(sp)
  lw     a0, 76(sp)
  call   f
  lw     t1, 4(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 84(sp)
  la     t1, v3
  lw     t2, 84(sp)
  add    t0, t1, t2
  sw     t0, 84(sp)
  li     t1, 0
  lw     t0, 84(sp)
  sw     t1, 0(t0)
  lw     t1, 0(sp)
  lw     t2, 4(sp)
  add    t0, t1, t2
  sw     t0, 92(sp)
  lw     t1, 92(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 88(sp)
  la     t1, v4
  lw     t2, 88(sp)
  add    t0, t1, t2
  sw     t0, 88(sp)
  li     t1, 0
  lw     t0, 88(sp)
  sw     t1, 0(t0)
  lui    t1, %hi(v2)
  lw     t1, %lo(v2)(t1)
  lw     t2, 0(sp)
  add    t0, t1, t2
  sw     t0, 100(sp)
  lw     t1, 100(sp)
  lw     t2, 4(sp)
  sub    t0, t1, t2
  sw     t0, 100(sp)
  lw     t1, 100(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 96(sp)
  la     t1, v5
  lw     t2, 96(sp)
  add    t0, t1, t2
  sw     t0, 96(sp)
  li     t1, 0
  lw     t0, 96(sp)
  sw     t1, 0(t0)
.l10:
  lw     t1, 4(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 104(sp)
  lw     t1, 104(sp)
  sw     t1, 4(sp)
  j      .l6
.l8:
  lw     ra, 108(sp)
  addi   sp, sp, 112
  ret
  .size      f, .-f
  .text
  .align     2
  .global    main
  .type      main, @function
main:
  addi   sp, sp, -32
  sw     ra, 28(sp)
  call   getint
  sw     a0, 4(sp)
  lw     t1, 4(sp)
  sw     t1, 0(sp)
.l13:
  lw     t1, 0(sp)
  li     s0, 0
  sgt    t0, t1, s0
  sw     t0, 8(sp)
  lw     t0, 8(sp)
  li     t1, 0
  beq    t0, t1, .l15
.l14:
  call   getint
  sw     a0, 12(sp)
  lw     t1, 12(sp)
  la     t0, v2
  sw     t1, 0(t0)
  li     a0, 1
  call   f
  lw     t1, 0(sp)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 20(sp)
  lw     t1, 20(sp)
  sw     t1, 0(sp)
  j      .l13
.l15:
  lui    a0, %hi(v1)
  lw     a0, %lo(v1)(a0)
  lw     ra, 28(sp)
  addi   sp, sp, 32
  ret
  li     a0, 0
  lw     ra, 28(sp)
  addi   sp, sp, 32
  ret
  .size      main, .-main
