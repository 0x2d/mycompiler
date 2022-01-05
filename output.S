  .global    v0
  .section   .sdata
  .align     2
  .type      v0, @object
  .size      v0, 4
v0:
  .word      0
  .text
  .align     2
  .global    bubblesort
  .type      bubblesort, @function
bubblesort:
  addi   sp, sp, -96
  sw     ra, 92(sp)
  sw     a0, 0(sp)
  li     t1, 0
  sw     t1, 4(sp)
.l0:
  lui    t1, %hi(v0)
  lw     t1, %lo(v0)(t1)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 20(sp)
  lw     t1, 4(sp)
  lw     t2, 20(sp)
  slt    t0, t1, t2
  sw     t0, 16(sp)
  lw     t0, 16(sp)
  li     t1, 0
  beq    t0, t1, .l2
.l1:
  li     t1, 0
  sw     t1, 8(sp)
.l3:
  lui    t1, %hi(v0)
  lw     t1, %lo(v0)(t1)
  lw     t2, 4(sp)
  sub    t0, t1, t2
  sw     t0, 28(sp)
  lw     t1, 28(sp)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 28(sp)
  lw     t1, 8(sp)
  lw     t2, 28(sp)
  slt    t0, t1, t2
  sw     t0, 24(sp)
  lw     t0, 24(sp)
  li     t1, 0
  beq    t0, t1, .l5
.l4:
  lw     t1, 8(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 32(sp)
  lw     t1, 0(sp)
  lw     t2, 32(sp)
  add    t0, t1, t2
  sw     t0, 32(sp)
  lw     t1, 32(sp)
  lw     t0, 0(t1)
  sw     t0, 32(sp)
  lw     t1, 8(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 44(sp)
  lw     t1, 44(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 40(sp)
  lw     t1, 0(sp)
  lw     t2, 40(sp)
  add    t0, t1, t2
  sw     t0, 40(sp)
  lw     t1, 40(sp)
  lw     t0, 0(t1)
  sw     t0, 40(sp)
  lw     t1, 32(sp)
  lw     t2, 40(sp)
  sgt    t0, t1, t2
  sw     t0, 36(sp)
  lw     t0, 36(sp)
  li     t1, 0
  beq    t0, t1, .l7
.l6:
  lw     t1, 8(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 52(sp)
  lw     t1, 52(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 48(sp)
  lw     t1, 0(sp)
  lw     t2, 48(sp)
  add    t0, t1, t2
  sw     t0, 48(sp)
  lw     t1, 48(sp)
  lw     t0, 0(t1)
  sw     t0, 48(sp)
  lw     t1, 48(sp)
  sw     t1, 12(sp)
  lw     t1, 8(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 60(sp)
  lw     t1, 60(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 56(sp)
  lw     t1, 0(sp)
  lw     t2, 56(sp)
  add    t0, t1, t2
  sw     t0, 56(sp)
  lw     t1, 8(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 64(sp)
  lw     t1, 0(sp)
  lw     t2, 64(sp)
  add    t0, t1, t2
  sw     t0, 64(sp)
  lw     t1, 64(sp)
  lw     t0, 0(t1)
  sw     t0, 64(sp)
  lw     t1, 64(sp)
  lw     t0, 56(sp)
  sw     t1, 0(t0)
  lw     t1, 8(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 68(sp)
  lw     t1, 0(sp)
  lw     t2, 68(sp)
  add    t0, t1, t2
  sw     t0, 68(sp)
  lw     t1, 12(sp)
  lw     t0, 68(sp)
  sw     t1, 0(t0)
.l7:
  lw     t1, 8(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 72(sp)
  lw     t1, 72(sp)
  sw     t1, 8(sp)
  j      .l3
.l5:
  lw     t1, 4(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 76(sp)
  lw     t1, 76(sp)
  sw     t1, 4(sp)
  j      .l0
.l2:
  li     a0, 0
  lw     ra, 92(sp)
  addi   sp, sp, 96
  ret
  li     a0, 0
  lw     ra, 92(sp)
  addi   sp, sp, 96
  ret
  .size      bubblesort, .-bubblesort
  .text
  .align     2
  .global    insertsort
  .type      insertsort, @function
insertsort:
  addi   sp, sp, -80
  sw     ra, 76(sp)
  sw     a0, 0(sp)
  li     t1, 1
  sw     t1, 4(sp)
.l8:
  lw     t1, 4(sp)
  lui    t2, %hi(v0)
  lw     t2, %lo(v0)(t2)
  slt    t0, t1, t2
  sw     t0, 16(sp)
  lw     t0, 16(sp)
  li     t1, 0
  beq    t0, t1, .l10
.l9:
  lw     t1, 4(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 20(sp)
  lw     t1, 0(sp)
  lw     t2, 20(sp)
  add    t0, t1, t2
  sw     t0, 20(sp)
  lw     t1, 20(sp)
  lw     t0, 0(t1)
  sw     t0, 20(sp)
  lw     t1, 20(sp)
  sw     t1, 8(sp)
  lw     t1, 4(sp)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 24(sp)
  lw     t1, 24(sp)
  sw     t1, 12(sp)
.l11:
  li     t1, 1
  neg    t0, t1
  sw     t0, 32(sp)
  lw     t1, 12(sp)
  lw     t2, 32(sp)
  sgt    t0, t1, t2
  sw     t0, 28(sp)
  lw     t0, 28(sp)
  li     t1, 0
  beq    t0, t1, .l13
  lw     t1, 12(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 40(sp)
  lw     t1, 0(sp)
  lw     t2, 40(sp)
  add    t0, t1, t2
  sw     t0, 40(sp)
  lw     t1, 40(sp)
  lw     t0, 0(t1)
  sw     t0, 40(sp)
  lw     t1, 8(sp)
  lw     t2, 40(sp)
  slt    t0, t1, t2
  sw     t0, 36(sp)
  lw     t0, 36(sp)
  li     t1, 0
  beq    t0, t1, .l13
.l12:
  lw     t1, 12(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 48(sp)
  lw     t1, 48(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 44(sp)
  lw     t1, 0(sp)
  lw     t2, 44(sp)
  add    t0, t1, t2
  sw     t0, 44(sp)
  lw     t1, 12(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 52(sp)
  lw     t1, 0(sp)
  lw     t2, 52(sp)
  add    t0, t1, t2
  sw     t0, 52(sp)
  lw     t1, 52(sp)
  lw     t0, 0(t1)
  sw     t0, 52(sp)
  lw     t1, 52(sp)
  lw     t0, 44(sp)
  sw     t1, 0(t0)
  lw     t1, 12(sp)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 56(sp)
  lw     t1, 56(sp)
  sw     t1, 12(sp)
  j      .l11
.l13:
  lw     t1, 12(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 64(sp)
  lw     t1, 64(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 60(sp)
  lw     t1, 0(sp)
  lw     t2, 60(sp)
  add    t0, t1, t2
  sw     t0, 60(sp)
  lw     t1, 8(sp)
  lw     t0, 60(sp)
  sw     t1, 0(t0)
  lw     t1, 4(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 68(sp)
  lw     t1, 68(sp)
  sw     t1, 4(sp)
  j      .l8
.l10:
  li     a0, 0
  lw     ra, 76(sp)
  addi   sp, sp, 80
  ret
  li     a0, 0
  lw     ra, 76(sp)
  addi   sp, sp, 80
  ret
  .size      insertsort, .-insertsort
  .text
  .align     2
  .global    QuickSort
  .type      QuickSort, @function
QuickSort:
  addi   sp, sp, -144
  sw     ra, 140(sp)
  sw     a0, 0(sp)
  sw     a1, 4(sp)
  sw     a2, 8(sp)
  lw     t1, 4(sp)
  lw     t2, 8(sp)
  slt    t0, t1, t2
  sw     t0, 28(sp)
  lw     t0, 28(sp)
  li     t1, 0
  beq    t0, t1, .l15
.l14:
  lw     t1, 4(sp)
  sw     t1, 12(sp)
  lw     t1, 8(sp)
  sw     t1, 16(sp)
  lw     t1, 4(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 32(sp)
  lw     t1, 0(sp)
  lw     t2, 32(sp)
  add    t0, t1, t2
  sw     t0, 32(sp)
  lw     t1, 32(sp)
  lw     t0, 0(t1)
  sw     t0, 32(sp)
  lw     t1, 32(sp)
  sw     t1, 20(sp)
.l16:
  lw     t1, 12(sp)
  lw     t2, 16(sp)
  slt    t0, t1, t2
  sw     t0, 36(sp)
  lw     t0, 36(sp)
  li     t1, 0
  beq    t0, t1, .l18
.l17:
.l19:
  lw     t1, 12(sp)
  lw     t2, 16(sp)
  slt    t0, t1, t2
  sw     t0, 40(sp)
  lw     t0, 40(sp)
  li     t1, 0
  beq    t0, t1, .l21
  lw     t1, 16(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 44(sp)
  lw     t1, 0(sp)
  lw     t2, 44(sp)
  add    t0, t1, t2
  sw     t0, 44(sp)
  lw     t1, 44(sp)
  lw     t0, 0(t1)
  sw     t0, 44(sp)
  lw     t1, 20(sp)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 52(sp)
  lw     t1, 44(sp)
  lw     t2, 52(sp)
  sgt    t0, t1, t2
  sw     t0, 48(sp)
  lw     t0, 48(sp)
  li     t1, 0
  beq    t0, t1, .l21
.l20:
  lw     t1, 16(sp)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 56(sp)
  lw     t1, 56(sp)
  sw     t1, 16(sp)
  j      .l19
.l21:
  lw     t1, 12(sp)
  lw     t2, 16(sp)
  slt    t0, t1, t2
  sw     t0, 60(sp)
  lw     t0, 60(sp)
  li     t1, 0
  beq    t0, t1, .l23
.l22:
  lw     t1, 12(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 64(sp)
  lw     t1, 0(sp)
  lw     t2, 64(sp)
  add    t0, t1, t2
  sw     t0, 64(sp)
  lw     t1, 16(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 68(sp)
  lw     t1, 0(sp)
  lw     t2, 68(sp)
  add    t0, t1, t2
  sw     t0, 68(sp)
  lw     t1, 68(sp)
  lw     t0, 0(t1)
  sw     t0, 68(sp)
  lw     t1, 68(sp)
  lw     t0, 64(sp)
  sw     t1, 0(t0)
  lw     t1, 12(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 72(sp)
  lw     t1, 72(sp)
  sw     t1, 12(sp)
.l23:
.l24:
  lw     t1, 12(sp)
  lw     t2, 16(sp)
  slt    t0, t1, t2
  sw     t0, 76(sp)
  lw     t0, 76(sp)
  li     t1, 0
  beq    t0, t1, .l26
  lw     t1, 12(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 80(sp)
  lw     t1, 0(sp)
  lw     t2, 80(sp)
  add    t0, t1, t2
  sw     t0, 80(sp)
  lw     t1, 80(sp)
  lw     t0, 0(t1)
  sw     t0, 80(sp)
  lw     t1, 80(sp)
  lw     t2, 20(sp)
  slt    t0, t1, t2
  sw     t0, 84(sp)
  lw     t0, 84(sp)
  li     t1, 0
  beq    t0, t1, .l26
.l25:
  lw     t1, 12(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 88(sp)
  lw     t1, 88(sp)
  sw     t1, 12(sp)
  j      .l24
.l26:
  lw     t1, 12(sp)
  lw     t2, 16(sp)
  slt    t0, t1, t2
  sw     t0, 92(sp)
  lw     t0, 92(sp)
  li     t1, 0
  beq    t0, t1, .l28
.l27:
  lw     t1, 16(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 96(sp)
  lw     t1, 0(sp)
  lw     t2, 96(sp)
  add    t0, t1, t2
  sw     t0, 96(sp)
  lw     t1, 12(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 100(sp)
  lw     t1, 0(sp)
  lw     t2, 100(sp)
  add    t0, t1, t2
  sw     t0, 100(sp)
  lw     t1, 100(sp)
  lw     t0, 0(t1)
  sw     t0, 100(sp)
  lw     t1, 100(sp)
  lw     t0, 96(sp)
  sw     t1, 0(t0)
  lw     t1, 16(sp)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 104(sp)
  lw     t1, 104(sp)
  sw     t1, 16(sp)
.l28:
  j      .l16
.l18:
  lw     t1, 12(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 108(sp)
  lw     t1, 0(sp)
  lw     t2, 108(sp)
  add    t0, t1, t2
  sw     t0, 108(sp)
  lw     t1, 20(sp)
  lw     t0, 108(sp)
  sw     t1, 0(t0)
  lw     t1, 12(sp)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 112(sp)
  lw     t1, 112(sp)
  sw     t1, 24(sp)
  lw     a0, 0(sp)
  lw     a1, 4(sp)
  lw     a2, 24(sp)
  call   QuickSort
  sw     a0, 116(sp)
  lw     t1, 116(sp)
  sw     t1, 24(sp)
  lw     t1, 12(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 120(sp)
  lw     t1, 120(sp)
  sw     t1, 24(sp)
  lw     a0, 0(sp)
  lw     a1, 24(sp)
  lw     a2, 8(sp)
  call   QuickSort
  sw     a0, 124(sp)
  lw     t1, 124(sp)
  sw     t1, 24(sp)
.l15:
  li     a0, 0
  lw     ra, 140(sp)
  addi   sp, sp, 144
  ret
  li     a0, 0
  lw     ra, 140(sp)
  addi   sp, sp, 144
  ret
  .size      QuickSort, .-QuickSort
  .text
  .align     2
  .global    getMid
  .type      getMid, @function
getMid:
  addi   sp, sp, -64
  sw     ra, 60(sp)
  sw     a0, 0(sp)
  lui    t1, %hi(v0)
  lw     t1, %lo(v0)(t1)
  li     s0, 2
  rem    t0, t1, s0
  sw     t0, 8(sp)
  lw     t1, 8(sp)
  li     s0, 0
  xor    t0, t1, s0
  seqz   t0, t0
  sw     t0, 12(sp)
  lw     t0, 12(sp)
  li     t1, 0
  beq    t0, t1, .l30
.l29:
  lui    t1, %hi(v0)
  lw     t1, %lo(v0)(t1)
  li     s0, 2
  div    t0, t1, s0
  sw     t0, 16(sp)
  lw     t1, 16(sp)
  sw     t1, 4(sp)
  lw     t1, 4(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 20(sp)
  lw     t1, 0(sp)
  lw     t2, 20(sp)
  add    t0, t1, t2
  sw     t0, 20(sp)
  lw     t1, 20(sp)
  lw     t0, 0(t1)
  sw     t0, 20(sp)
  lw     t1, 4(sp)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 32(sp)
  lw     t1, 32(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 28(sp)
  lw     t1, 0(sp)
  lw     t2, 28(sp)
  add    t0, t1, t2
  sw     t0, 28(sp)
  lw     t1, 28(sp)
  lw     t0, 0(t1)
  sw     t0, 28(sp)
  lw     t1, 20(sp)
  lw     t2, 28(sp)
  add    t0, t1, t2
  sw     t0, 24(sp)
  lw     t1, 24(sp)
  li     s0, 2
  div    t0, t1, s0
  sw     t0, 36(sp)
  lw     a0, 36(sp)
  lw     ra, 60(sp)
  addi   sp, sp, 64
  ret
  j      .l31
.l30:
  lui    t1, %hi(v0)
  lw     t1, %lo(v0)(t1)
  li     s0, 2
  div    t0, t1, s0
  sw     t0, 40(sp)
  lw     t1, 40(sp)
  sw     t1, 4(sp)
  lw     t1, 4(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 44(sp)
  lw     t1, 0(sp)
  lw     t2, 44(sp)
  add    t0, t1, t2
  sw     t0, 44(sp)
  lw     t1, 44(sp)
  lw     t0, 0(t1)
  sw     t0, 44(sp)
  lw     a0, 44(sp)
  lw     ra, 60(sp)
  addi   sp, sp, 64
  ret
.l31:
  li     a0, 0
  lw     ra, 60(sp)
  addi   sp, sp, 64
  ret
  .size      getMid, .-getMid
  .text
  .align     2
  .global    getMost
  .type      getMost, @function
getMost:
  li     s0, 4080
  sub    sp, sp, s0
  add    s0, s0, sp
  sw     ra, -4(s0)
  sw     a0, 0(sp)
  li     t1, 0
  li     s0, 4004
  add    s0, sp, s0
  sw     t1, (s0)
.l32:
  li     s0, 4004
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 1000
  slt    t0, t1, s0
  li     s0, 4020
  add    s0, sp, s0
  sw     t0, (s0)
  li     s0, 4020
  add    s0, sp, s0
  lw     t0, (s0)
  li     t1, 0
  beq    t0, t1, .l34
.l33:
  li     s0, 4004
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 4
  mul    t0, t1, s0
  li     s0, 4024
  add    s0, sp, s0
  sw     t0, (s0)
  addi   t1, sp, 4
  li     s0, 4024
  add    s0, sp, s0
  lw     t2, (s0)
  add    t0, t1, t2
  li     s0, 4024
  add    s0, sp, s0
  sw     t0, (s0)
  li     t1, 0
  li     s0, 4024
  add    s0, sp, s0
  lw     t0, (s0)
  sw     t1, 0(t0)
  li     s0, 4004
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 1
  add    t0, t1, s0
  li     s0, 4028
  add    s0, sp, s0
  sw     t0, (s0)
  li     s0, 4028
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 4004
  add    s0, sp, s0
  sw     t1, (s0)
  j      .l32
.l34:
  li     t1, 0
  li     s0, 4004
  add    s0, sp, s0
  sw     t1, (s0)
  li     t1, 0
  li     s0, 4008
  add    s0, sp, s0
  sw     t1, (s0)
.l35:
  li     s0, 4004
  add    s0, sp, s0
  lw     t1, (s0)
  lui    t2, %hi(v0)
  lw     t2, %lo(v0)(t2)
  slt    t0, t1, t2
  li     s0, 4032
  add    s0, sp, s0
  sw     t0, (s0)
  li     s0, 4032
  add    s0, sp, s0
  lw     t0, (s0)
  li     t1, 0
  beq    t0, t1, .l37
.l36:
  li     s0, 4004
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 4
  mul    t0, t1, s0
  li     s0, 4036
  add    s0, sp, s0
  sw     t0, (s0)
  lw     t1, 0(sp)
  li     s0, 4036
  add    s0, sp, s0
  lw     t2, (s0)
  add    t0, t1, t2
  li     s0, 4036
  add    s0, sp, s0
  sw     t0, (s0)
  li     s0, 4036
  add    s0, sp, s0
  lw     t1, (s0)
  lw     t0, 0(t1)
  li     s0, 4036
  add    s0, sp, s0
  sw     t0, (s0)
  li     s0, 4036
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 4016
  add    s0, sp, s0
  sw     t1, (s0)
  li     s0, 4016
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 4
  mul    t0, t1, s0
  li     s0, 4040
  add    s0, sp, s0
  sw     t0, (s0)
  addi   t1, sp, 4
  li     s0, 4040
  add    s0, sp, s0
  lw     t2, (s0)
  add    t0, t1, t2
  li     s0, 4040
  add    s0, sp, s0
  sw     t0, (s0)
  li     s0, 4016
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 4
  mul    t0, t1, s0
  li     s0, 4044
  add    s0, sp, s0
  sw     t0, (s0)
  addi   t1, sp, 4
  li     s0, 4044
  add    s0, sp, s0
  lw     t2, (s0)
  add    t0, t1, t2
  li     s0, 4044
  add    s0, sp, s0
  sw     t0, (s0)
  li     s0, 4044
  add    s0, sp, s0
  lw     t1, (s0)
  lw     t0, 0(t1)
  li     s0, 4044
  add    s0, sp, s0
  sw     t0, (s0)
  li     s0, 4044
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 1
  add    t0, t1, s0
  li     s0, 4048
  add    s0, sp, s0
  sw     t0, (s0)
  li     s0, 4048
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 4040
  add    s0, sp, s0
  lw     t0, (s0)
  sw     t1, 0(t0)
  li     s0, 4016
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 4
  mul    t0, t1, s0
  li     s0, 4052
  add    s0, sp, s0
  sw     t0, (s0)
  addi   t1, sp, 4
  li     s0, 4052
  add    s0, sp, s0
  lw     t2, (s0)
  add    t0, t1, t2
  li     s0, 4052
  add    s0, sp, s0
  sw     t0, (s0)
  li     s0, 4052
  add    s0, sp, s0
  lw     t1, (s0)
  lw     t0, 0(t1)
  li     s0, 4052
  add    s0, sp, s0
  sw     t0, (s0)
  li     s0, 4052
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 4008
  add    s0, sp, s0
  lw     t2, (s0)
  sgt    t0, t1, t2
  li     s0, 4056
  add    s0, sp, s0
  sw     t0, (s0)
  li     s0, 4056
  add    s0, sp, s0
  lw     t0, (s0)
  li     t1, 0
  beq    t0, t1, .l39
.l38:
  li     s0, 4016
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 4
  mul    t0, t1, s0
  li     s0, 4060
  add    s0, sp, s0
  sw     t0, (s0)
  addi   t1, sp, 4
  li     s0, 4060
  add    s0, sp, s0
  lw     t2, (s0)
  add    t0, t1, t2
  li     s0, 4060
  add    s0, sp, s0
  sw     t0, (s0)
  li     s0, 4060
  add    s0, sp, s0
  lw     t1, (s0)
  lw     t0, 0(t1)
  li     s0, 4060
  add    s0, sp, s0
  sw     t0, (s0)
  li     s0, 4060
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 4008
  add    s0, sp, s0
  sw     t1, (s0)
  li     s0, 4016
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 4012
  add    s0, sp, s0
  sw     t1, (s0)
.l39:
  li     s0, 4004
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 1
  add    t0, t1, s0
  li     s0, 4064
  add    s0, sp, s0
  sw     t0, (s0)
  li     s0, 4064
  add    s0, sp, s0
  lw     t1, (s0)
  li     s0, 4004
  add    s0, sp, s0
  sw     t1, (s0)
  j      .l35
.l37:
  li     s0, 4012
  add    s0, sp, s0
  lw     a0, (s0)
  li     s0, 4080
  add    s0, s0, sp
  lw     ra, -4(s0)
  li     s0, 4080
  add    sp, sp, s0
  ret
  li     a0, 0
  li     s0, 4080
  add    s0, s0, sp
  lw     ra, -4(s0)
  li     s0, 4080
  add    sp, sp, s0
  ret
  .size      getMost, .-getMost
  .text
  .align     2
  .global    revert
  .type      revert, @function
revert:
  addi   sp, sp, -48
  sw     ra, 44(sp)
  sw     a0, 0(sp)
  li     t1, 0
  sw     t1, 8(sp)
  li     t1, 0
  sw     t1, 12(sp)
.l40:
  lw     t1, 8(sp)
  lw     t2, 12(sp)
  slt    t0, t1, t2
  sw     t0, 16(sp)
  lw     t0, 16(sp)
  li     t1, 0
  beq    t0, t1, .l42
.l41:
  lw     t1, 8(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 20(sp)
  lw     t1, 0(sp)
  lw     t2, 20(sp)
  add    t0, t1, t2
  sw     t0, 20(sp)
  lw     t1, 20(sp)
  lw     t0, 0(t1)
  sw     t0, 20(sp)
  lw     t1, 20(sp)
  sw     t1, 4(sp)
  lw     t1, 8(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 24(sp)
  lw     t1, 0(sp)
  lw     t2, 24(sp)
  add    t0, t1, t2
  sw     t0, 24(sp)
  lw     t1, 12(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 28(sp)
  lw     t1, 0(sp)
  lw     t2, 28(sp)
  add    t0, t1, t2
  sw     t0, 28(sp)
  lw     t1, 28(sp)
  lw     t0, 0(t1)
  sw     t0, 28(sp)
  lw     t1, 28(sp)
  lw     t0, 24(sp)
  sw     t1, 0(t0)
  lw     t1, 12(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 32(sp)
  lw     t1, 0(sp)
  lw     t2, 32(sp)
  add    t0, t1, t2
  sw     t0, 32(sp)
  lw     t1, 4(sp)
  lw     t0, 32(sp)
  sw     t1, 0(t0)
  lw     t1, 8(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 36(sp)
  lw     t1, 36(sp)
  sw     t1, 8(sp)
  lw     t1, 12(sp)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 40(sp)
  lw     t1, 40(sp)
  sw     t1, 12(sp)
  j      .l40
.l42:
  li     a0, 0
  lw     ra, 44(sp)
  addi   sp, sp, 48
  ret
  li     a0, 0
  lw     ra, 44(sp)
  addi   sp, sp, 48
  ret
  .size      revert, .-revert
  .text
  .align     2
  .global    arrCopy
  .type      arrCopy, @function
arrCopy:
  addi   sp, sp, -32
  sw     ra, 28(sp)
  sw     a0, 0(sp)
  sw     a1, 4(sp)
  li     t1, 0
  sw     t1, 8(sp)
.l43:
  lw     t1, 8(sp)
  lui    t2, %hi(v0)
  lw     t2, %lo(v0)(t2)
  slt    t0, t1, t2
  sw     t0, 12(sp)
  lw     t0, 12(sp)
  li     t1, 0
  beq    t0, t1, .l45
.l44:
  lw     t1, 8(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 16(sp)
  lw     t1, 4(sp)
  lw     t2, 16(sp)
  add    t0, t1, t2
  sw     t0, 16(sp)
  lw     t1, 8(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 20(sp)
  lw     t1, 0(sp)
  lw     t2, 20(sp)
  add    t0, t1, t2
  sw     t0, 20(sp)
  lw     t1, 20(sp)
  lw     t0, 0(t1)
  sw     t0, 20(sp)
  lw     t1, 20(sp)
  lw     t0, 16(sp)
  sw     t1, 0(t0)
  lw     t1, 8(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 24(sp)
  lw     t1, 24(sp)
  sw     t1, 8(sp)
  j      .l43
.l45:
  li     a0, 0
  lw     ra, 28(sp)
  addi   sp, sp, 32
  ret
  li     a0, 0
  lw     ra, 28(sp)
  addi   sp, sp, 32
  ret
  .size      arrCopy, .-arrCopy
  .text
  .align     2
  .global    calSum
  .type      calSum, @function
calSum:
  addi   sp, sp, -64
  sw     ra, 60(sp)
  sw     a0, 0(sp)
  sw     a1, 4(sp)
  li     t1, 0
  sw     t1, 8(sp)
  li     t1, 0
  sw     t1, 12(sp)
.l46:
  lw     t1, 12(sp)
  lui    t2, %hi(v0)
  lw     t2, %lo(v0)(t2)
  slt    t0, t1, t2
  sw     t0, 16(sp)
  lw     t0, 16(sp)
  li     t1, 0
  beq    t0, t1, .l48
.l47:
  lw     t1, 12(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 24(sp)
  lw     t1, 0(sp)
  lw     t2, 24(sp)
  add    t0, t1, t2
  sw     t0, 24(sp)
  lw     t1, 24(sp)
  lw     t0, 0(t1)
  sw     t0, 24(sp)
  lw     t1, 8(sp)
  lw     t2, 24(sp)
  add    t0, t1, t2
  sw     t0, 20(sp)
  lw     t1, 20(sp)
  sw     t1, 8(sp)
  lw     t1, 12(sp)
  lw     t2, 4(sp)
  rem    t0, t1, t2
  sw     t0, 28(sp)
  lw     t1, 4(sp)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 36(sp)
  lw     t1, 28(sp)
  lw     t2, 36(sp)
  xor    t0, t1, t2
  snez   t0, t0
  sw     t0, 32(sp)
  lw     t0, 32(sp)
  li     t1, 0
  beq    t0, t1, .l50
.l49:
  lw     t1, 12(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 40(sp)
  lw     t1, 0(sp)
  lw     t2, 40(sp)
  add    t0, t1, t2
  sw     t0, 40(sp)
  li     t1, 0
  lw     t0, 40(sp)
  sw     t1, 0(t0)
  j      .l51
.l50:
  lw     t1, 12(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 44(sp)
  lw     t1, 0(sp)
  lw     t2, 44(sp)
  add    t0, t1, t2
  sw     t0, 44(sp)
  lw     t1, 8(sp)
  lw     t0, 44(sp)
  sw     t1, 0(t0)
  li     t1, 0
  sw     t1, 8(sp)
.l51:
  lw     t1, 12(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 48(sp)
  lw     t1, 48(sp)
  sw     t1, 12(sp)
  j      .l46
.l48:
  li     a0, 0
  lw     ra, 60(sp)
  addi   sp, sp, 64
  ret
  li     a0, 0
  lw     ra, 60(sp)
  addi   sp, sp, 64
  ret
  .size      calSum, .-calSum
  .text
  .align     2
  .global    avgPooling
  .type      avgPooling, @function
avgPooling:
  addi   sp, sp, -112
  sw     ra, 108(sp)
  sw     a0, 0(sp)
  sw     a1, 4(sp)
  li     t1, 0
  sw     t1, 12(sp)
  li     t1, 0
  sw     t1, 8(sp)
.l52:
  lw     t1, 12(sp)
  lui    t2, %hi(v0)
  lw     t2, %lo(v0)(t2)
  slt    t0, t1, t2
  sw     t0, 20(sp)
  lw     t0, 20(sp)
  li     t1, 0
  beq    t0, t1, .l54
.l53:
  lw     t1, 4(sp)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 28(sp)
  lw     t1, 12(sp)
  lw     t2, 28(sp)
  slt    t0, t1, t2
  sw     t0, 24(sp)
  lw     t0, 24(sp)
  li     t1, 0
  beq    t0, t1, .l56
.l55:
  lw     t1, 12(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 36(sp)
  lw     t1, 0(sp)
  lw     t2, 36(sp)
  add    t0, t1, t2
  sw     t0, 36(sp)
  lw     t1, 36(sp)
  lw     t0, 0(t1)
  sw     t0, 36(sp)
  lw     t1, 8(sp)
  lw     t2, 36(sp)
  add    t0, t1, t2
  sw     t0, 32(sp)
  lw     t1, 32(sp)
  sw     t1, 8(sp)
  j      .l57
.l56:
  lw     t1, 4(sp)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 44(sp)
  lw     t1, 12(sp)
  lw     t2, 44(sp)
  xor    t0, t1, t2
  seqz   t0, t0
  sw     t0, 40(sp)
  lw     t0, 40(sp)
  li     t1, 0
  beq    t0, t1, .l59
.l58:
  li     t1, 0
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 48(sp)
  lw     t1, 0(sp)
  lw     t2, 48(sp)
  add    t0, t1, t2
  sw     t0, 48(sp)
  lw     t1, 48(sp)
  lw     t0, 0(t1)
  sw     t0, 48(sp)
  lw     t1, 48(sp)
  sw     t1, 16(sp)
  li     t1, 0
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 52(sp)
  lw     t1, 0(sp)
  lw     t2, 52(sp)
  add    t0, t1, t2
  sw     t0, 52(sp)
  lw     t1, 8(sp)
  lw     t2, 4(sp)
  div    t0, t1, t2
  sw     t0, 56(sp)
  lw     t1, 56(sp)
  lw     t0, 52(sp)
  sw     t1, 0(t0)
  j      .l60
.l59:
  lw     t1, 12(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 64(sp)
  lw     t1, 0(sp)
  lw     t2, 64(sp)
  add    t0, t1, t2
  sw     t0, 64(sp)
  lw     t1, 64(sp)
  lw     t0, 0(t1)
  sw     t0, 64(sp)
  lw     t1, 8(sp)
  lw     t2, 64(sp)
  add    t0, t1, t2
  sw     t0, 60(sp)
  lw     t1, 60(sp)
  lw     t2, 16(sp)
  sub    t0, t1, t2
  sw     t0, 60(sp)
  lw     t1, 60(sp)
  sw     t1, 8(sp)
  lw     t1, 12(sp)
  lw     t2, 4(sp)
  sub    t0, t1, t2
  sw     t0, 72(sp)
  lw     t1, 72(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 72(sp)
  lw     t1, 72(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 68(sp)
  lw     t1, 0(sp)
  lw     t2, 68(sp)
  add    t0, t1, t2
  sw     t0, 68(sp)
  lw     t1, 68(sp)
  lw     t0, 0(t1)
  sw     t0, 68(sp)
  lw     t1, 68(sp)
  sw     t1, 16(sp)
  lw     t1, 12(sp)
  lw     t2, 4(sp)
  sub    t0, t1, t2
  sw     t0, 80(sp)
  lw     t1, 80(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 80(sp)
  lw     t1, 80(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 76(sp)
  lw     t1, 0(sp)
  lw     t2, 76(sp)
  add    t0, t1, t2
  sw     t0, 76(sp)
  lw     t1, 8(sp)
  lw     t2, 4(sp)
  div    t0, t1, t2
  sw     t0, 84(sp)
  lw     t1, 84(sp)
  lw     t0, 76(sp)
  sw     t1, 0(t0)
.l60:
.l57:
  lw     t1, 12(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 88(sp)
  lw     t1, 88(sp)
  sw     t1, 12(sp)
  j      .l52
.l54:
  lui    t1, %hi(v0)
  lw     t1, %lo(v0)(t1)
  lw     t2, 4(sp)
  sub    t0, t1, t2
  sw     t0, 92(sp)
  lw     t1, 92(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 92(sp)
  lw     t1, 92(sp)
  sw     t1, 12(sp)
.l61:
  lw     t1, 12(sp)
  lui    t2, %hi(v0)
  lw     t2, %lo(v0)(t2)
  slt    t0, t1, t2
  sw     t0, 96(sp)
  lw     t0, 96(sp)
  li     t1, 0
  beq    t0, t1, .l63
.l62:
  lw     t1, 12(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 100(sp)
  lw     t1, 0(sp)
  lw     t2, 100(sp)
  add    t0, t1, t2
  sw     t0, 100(sp)
  li     t1, 0
  lw     t0, 100(sp)
  sw     t1, 0(t0)
  lw     t1, 12(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 104(sp)
  lw     t1, 104(sp)
  sw     t1, 12(sp)
  j      .l61
.l63:
  li     a0, 0
  lw     ra, 108(sp)
  addi   sp, sp, 112
  ret
  li     a0, 0
  lw     ra, 108(sp)
  addi   sp, sp, 112
  ret
  .size      avgPooling, .-avgPooling
  .text
  .align     2
  .global    main
  .type      main, @function
main:
  addi   sp, sp, -576
  sw     ra, 572(sp)
  li     t1, 32
  la     t0, v0
  sw     t1, 0(t0)
  li     t1, 0
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 264(sp)
  addi   t1, sp, 0
  lw     t2, 264(sp)
  add    t0, t1, t2
  sw     t0, 264(sp)
  li     t1, 7
  lw     t0, 264(sp)
  sw     t1, 0(t0)
  li     t1, 1
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 268(sp)
  addi   t1, sp, 0
  lw     t2, 268(sp)
  add    t0, t1, t2
  sw     t0, 268(sp)
  li     t1, 23
  lw     t0, 268(sp)
  sw     t1, 0(t0)
  li     t1, 2
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 272(sp)
  addi   t1, sp, 0
  lw     t2, 272(sp)
  add    t0, t1, t2
  sw     t0, 272(sp)
  li     t1, 89
  lw     t0, 272(sp)
  sw     t1, 0(t0)
  li     t1, 3
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 276(sp)
  addi   t1, sp, 0
  lw     t2, 276(sp)
  add    t0, t1, t2
  sw     t0, 276(sp)
  li     t1, 26
  lw     t0, 276(sp)
  sw     t1, 0(t0)
  li     t1, 4
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 280(sp)
  addi   t1, sp, 0
  lw     t2, 280(sp)
  add    t0, t1, t2
  sw     t0, 280(sp)
  li     t1, 282
  lw     t0, 280(sp)
  sw     t1, 0(t0)
  li     t1, 5
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 284(sp)
  addi   t1, sp, 0
  lw     t2, 284(sp)
  add    t0, t1, t2
  sw     t0, 284(sp)
  li     t1, 254
  lw     t0, 284(sp)
  sw     t1, 0(t0)
  li     t1, 6
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 288(sp)
  addi   t1, sp, 0
  lw     t2, 288(sp)
  add    t0, t1, t2
  sw     t0, 288(sp)
  li     t1, 27
  lw     t0, 288(sp)
  sw     t1, 0(t0)
  li     t1, 7
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 292(sp)
  addi   t1, sp, 0
  lw     t2, 292(sp)
  add    t0, t1, t2
  sw     t0, 292(sp)
  li     t1, 5
  lw     t0, 292(sp)
  sw     t1, 0(t0)
  li     t1, 8
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 296(sp)
  addi   t1, sp, 0
  lw     t2, 296(sp)
  add    t0, t1, t2
  sw     t0, 296(sp)
  li     t1, 83
  lw     t0, 296(sp)
  sw     t1, 0(t0)
  li     t1, 9
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 300(sp)
  addi   t1, sp, 0
  lw     t2, 300(sp)
  add    t0, t1, t2
  sw     t0, 300(sp)
  li     t1, 273
  lw     t0, 300(sp)
  sw     t1, 0(t0)
  li     t1, 10
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 304(sp)
  addi   t1, sp, 0
  lw     t2, 304(sp)
  add    t0, t1, t2
  sw     t0, 304(sp)
  li     t1, 574
  lw     t0, 304(sp)
  sw     t1, 0(t0)
  li     t1, 11
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 308(sp)
  addi   t1, sp, 0
  lw     t2, 308(sp)
  add    t0, t1, t2
  sw     t0, 308(sp)
  li     t1, 905
  lw     t0, 308(sp)
  sw     t1, 0(t0)
  li     t1, 12
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 312(sp)
  addi   t1, sp, 0
  lw     t2, 312(sp)
  add    t0, t1, t2
  sw     t0, 312(sp)
  li     t1, 354
  lw     t0, 312(sp)
  sw     t1, 0(t0)
  li     t1, 13
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 316(sp)
  addi   t1, sp, 0
  lw     t2, 316(sp)
  add    t0, t1, t2
  sw     t0, 316(sp)
  li     t1, 657
  lw     t0, 316(sp)
  sw     t1, 0(t0)
  li     t1, 14
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 320(sp)
  addi   t1, sp, 0
  lw     t2, 320(sp)
  add    t0, t1, t2
  sw     t0, 320(sp)
  li     t1, 935
  lw     t0, 320(sp)
  sw     t1, 0(t0)
  li     t1, 15
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 324(sp)
  addi   t1, sp, 0
  lw     t2, 324(sp)
  add    t0, t1, t2
  sw     t0, 324(sp)
  li     t1, 264
  lw     t0, 324(sp)
  sw     t1, 0(t0)
  li     t1, 16
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 328(sp)
  addi   t1, sp, 0
  lw     t2, 328(sp)
  add    t0, t1, t2
  sw     t0, 328(sp)
  li     t1, 639
  lw     t0, 328(sp)
  sw     t1, 0(t0)
  li     t1, 17
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 332(sp)
  addi   t1, sp, 0
  lw     t2, 332(sp)
  add    t0, t1, t2
  sw     t0, 332(sp)
  li     t1, 459
  lw     t0, 332(sp)
  sw     t1, 0(t0)
  li     t1, 18
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 336(sp)
  addi   t1, sp, 0
  lw     t2, 336(sp)
  add    t0, t1, t2
  sw     t0, 336(sp)
  li     t1, 29
  lw     t0, 336(sp)
  sw     t1, 0(t0)
  li     t1, 19
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 340(sp)
  addi   t1, sp, 0
  lw     t2, 340(sp)
  add    t0, t1, t2
  sw     t0, 340(sp)
  li     t1, 68
  lw     t0, 340(sp)
  sw     t1, 0(t0)
  li     t1, 20
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 344(sp)
  addi   t1, sp, 0
  lw     t2, 344(sp)
  add    t0, t1, t2
  sw     t0, 344(sp)
  li     t1, 929
  lw     t0, 344(sp)
  sw     t1, 0(t0)
  li     t1, 21
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 348(sp)
  addi   t1, sp, 0
  lw     t2, 348(sp)
  add    t0, t1, t2
  sw     t0, 348(sp)
  li     t1, 756
  lw     t0, 348(sp)
  sw     t1, 0(t0)
  li     t1, 22
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 352(sp)
  addi   t1, sp, 0
  lw     t2, 352(sp)
  add    t0, t1, t2
  sw     t0, 352(sp)
  li     t1, 452
  lw     t0, 352(sp)
  sw     t1, 0(t0)
  li     t1, 23
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 356(sp)
  addi   t1, sp, 0
  lw     t2, 356(sp)
  add    t0, t1, t2
  sw     t0, 356(sp)
  li     t1, 279
  lw     t0, 356(sp)
  sw     t1, 0(t0)
  li     t1, 24
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 360(sp)
  addi   t1, sp, 0
  lw     t2, 360(sp)
  add    t0, t1, t2
  sw     t0, 360(sp)
  li     t1, 58
  lw     t0, 360(sp)
  sw     t1, 0(t0)
  li     t1, 25
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 364(sp)
  addi   t1, sp, 0
  lw     t2, 364(sp)
  add    t0, t1, t2
  sw     t0, 364(sp)
  li     t1, 87
  lw     t0, 364(sp)
  sw     t1, 0(t0)
  li     t1, 26
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 368(sp)
  addi   t1, sp, 0
  lw     t2, 368(sp)
  add    t0, t1, t2
  sw     t0, 368(sp)
  li     t1, 96
  lw     t0, 368(sp)
  sw     t1, 0(t0)
  li     t1, 27
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 372(sp)
  addi   t1, sp, 0
  lw     t2, 372(sp)
  add    t0, t1, t2
  sw     t0, 372(sp)
  li     t1, 36
  lw     t0, 372(sp)
  sw     t1, 0(t0)
  li     t1, 28
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 376(sp)
  addi   t1, sp, 0
  lw     t2, 376(sp)
  add    t0, t1, t2
  sw     t0, 376(sp)
  li     t1, 39
  lw     t0, 376(sp)
  sw     t1, 0(t0)
  li     t1, 29
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 380(sp)
  addi   t1, sp, 0
  lw     t2, 380(sp)
  add    t0, t1, t2
  sw     t0, 380(sp)
  li     t1, 28
  lw     t0, 380(sp)
  sw     t1, 0(t0)
  li     t1, 30
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 384(sp)
  addi   t1, sp, 0
  lw     t2, 384(sp)
  add    t0, t1, t2
  sw     t0, 384(sp)
  li     t1, 1
  lw     t0, 384(sp)
  sw     t1, 0(t0)
  li     t1, 31
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 388(sp)
  addi   t1, sp, 0
  lw     t2, 388(sp)
  add    t0, t1, t2
  sw     t0, 388(sp)
  li     t1, 290
  lw     t0, 388(sp)
  sw     t1, 0(t0)
  addi   a0, sp, 0
  addi   a1, sp, 128
  call   arrCopy
  sw     a0, 392(sp)
  lw     t1, 392(sp)
  sw     t1, 256(sp)
  addi   a0, sp, 128
  call   revert
  sw     a0, 396(sp)
  lw     t1, 396(sp)
  sw     t1, 256(sp)
  li     t1, 0
  sw     t1, 260(sp)
.l64:
  lw     t1, 260(sp)
  li     s0, 32
  slt    t0, t1, s0
  sw     t0, 400(sp)
  lw     t0, 400(sp)
  li     t1, 0
  beq    t0, t1, .l66
.l65:
  lw     t1, 260(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 404(sp)
  addi   t1, sp, 128
  lw     t2, 404(sp)
  add    t0, t1, t2
  sw     t0, 404(sp)
  lw     t1, 404(sp)
  lw     t0, 0(t1)
  sw     t0, 404(sp)
  lw     t1, 404(sp)
  sw     t1, 256(sp)
  lw     a0, 256(sp)
  call   putint
  lw     t1, 260(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 412(sp)
  lw     t1, 412(sp)
  sw     t1, 260(sp)
  j      .l64
.l66:
  addi   a0, sp, 128
  call   bubblesort
  sw     a0, 416(sp)
  lw     t1, 416(sp)
  sw     t1, 256(sp)
  li     t1, 0
  sw     t1, 260(sp)
.l67:
  lw     t1, 260(sp)
  li     s0, 32
  slt    t0, t1, s0
  sw     t0, 420(sp)
  lw     t0, 420(sp)
  li     t1, 0
  beq    t0, t1, .l69
.l68:
  lw     t1, 260(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 424(sp)
  addi   t1, sp, 128
  lw     t2, 424(sp)
  add    t0, t1, t2
  sw     t0, 424(sp)
  lw     t1, 424(sp)
  lw     t0, 0(t1)
  sw     t0, 424(sp)
  lw     t1, 424(sp)
  sw     t1, 256(sp)
  lw     a0, 256(sp)
  call   putint
  lw     t1, 260(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 432(sp)
  lw     t1, 432(sp)
  sw     t1, 260(sp)
  j      .l67
.l69:
  addi   a0, sp, 128
  call   getMid
  sw     a0, 436(sp)
  lw     t1, 436(sp)
  sw     t1, 256(sp)
  lw     a0, 256(sp)
  call   putint
  addi   a0, sp, 128
  call   getMost
  sw     a0, 444(sp)
  lw     t1, 444(sp)
  sw     t1, 256(sp)
  lw     a0, 256(sp)
  call   putint
  addi   a0, sp, 0
  addi   a1, sp, 128
  call   arrCopy
  sw     a0, 452(sp)
  lw     t1, 452(sp)
  sw     t1, 256(sp)
  addi   a0, sp, 128
  call   bubblesort
  sw     a0, 456(sp)
  lw     t1, 456(sp)
  sw     t1, 256(sp)
  li     t1, 0
  sw     t1, 260(sp)
.l70:
  lw     t1, 260(sp)
  li     s0, 32
  slt    t0, t1, s0
  sw     t0, 460(sp)
  lw     t0, 460(sp)
  li     t1, 0
  beq    t0, t1, .l72
.l71:
  lw     t1, 260(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 464(sp)
  addi   t1, sp, 128
  lw     t2, 464(sp)
  add    t0, t1, t2
  sw     t0, 464(sp)
  lw     t1, 464(sp)
  lw     t0, 0(t1)
  sw     t0, 464(sp)
  lw     t1, 464(sp)
  sw     t1, 256(sp)
  lw     a0, 256(sp)
  call   putint
  lw     t1, 260(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 472(sp)
  lw     t1, 472(sp)
  sw     t1, 260(sp)
  j      .l70
.l72:
  addi   a0, sp, 0
  addi   a1, sp, 128
  call   arrCopy
  sw     a0, 476(sp)
  lw     t1, 476(sp)
  sw     t1, 256(sp)
  addi   a0, sp, 128
  call   insertsort
  sw     a0, 480(sp)
  lw     t1, 480(sp)
  sw     t1, 256(sp)
  li     t1, 0
  sw     t1, 260(sp)
.l73:
  lw     t1, 260(sp)
  li     s0, 32
  slt    t0, t1, s0
  sw     t0, 484(sp)
  lw     t0, 484(sp)
  li     t1, 0
  beq    t0, t1, .l75
.l74:
  lw     t1, 260(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 488(sp)
  addi   t1, sp, 128
  lw     t2, 488(sp)
  add    t0, t1, t2
  sw     t0, 488(sp)
  lw     t1, 488(sp)
  lw     t0, 0(t1)
  sw     t0, 488(sp)
  lw     t1, 488(sp)
  sw     t1, 256(sp)
  lw     a0, 256(sp)
  call   putint
  lw     t1, 260(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 496(sp)
  lw     t1, 496(sp)
  sw     t1, 260(sp)
  j      .l73
.l75:
  addi   a0, sp, 0
  addi   a1, sp, 128
  call   arrCopy
  sw     a0, 500(sp)
  lw     t1, 500(sp)
  sw     t1, 256(sp)
  li     t1, 0
  sw     t1, 260(sp)
  li     t1, 31
  sw     t1, 256(sp)
  addi   a0, sp, 128
  lw     a1, 260(sp)
  lw     a2, 256(sp)
  call   QuickSort
  sw     a0, 504(sp)
  lw     t1, 504(sp)
  sw     t1, 256(sp)
.l76:
  lw     t1, 260(sp)
  li     s0, 32
  slt    t0, t1, s0
  sw     t0, 508(sp)
  lw     t0, 508(sp)
  li     t1, 0
  beq    t0, t1, .l78
.l77:
  lw     t1, 260(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 512(sp)
  addi   t1, sp, 128
  lw     t2, 512(sp)
  add    t0, t1, t2
  sw     t0, 512(sp)
  lw     t1, 512(sp)
  lw     t0, 0(t1)
  sw     t0, 512(sp)
  lw     t1, 512(sp)
  sw     t1, 256(sp)
  lw     a0, 256(sp)
  call   putint
  lw     t1, 260(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 520(sp)
  lw     t1, 520(sp)
  sw     t1, 260(sp)
  j      .l76
.l78:
  addi   a0, sp, 0
  addi   a1, sp, 128
  call   arrCopy
  sw     a0, 524(sp)
  lw     t1, 524(sp)
  sw     t1, 256(sp)
  addi   a0, sp, 128
  li     a1, 4
  call   calSum
  sw     a0, 528(sp)
  lw     t1, 528(sp)
  sw     t1, 256(sp)
  li     t1, 0
  sw     t1, 260(sp)
.l79:
  lw     t1, 260(sp)
  li     s0, 32
  slt    t0, t1, s0
  sw     t0, 532(sp)
  lw     t0, 532(sp)
  li     t1, 0
  beq    t0, t1, .l81
.l80:
  lw     t1, 260(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 536(sp)
  addi   t1, sp, 128
  lw     t2, 536(sp)
  add    t0, t1, t2
  sw     t0, 536(sp)
  lw     t1, 536(sp)
  lw     t0, 0(t1)
  sw     t0, 536(sp)
  lw     t1, 536(sp)
  sw     t1, 256(sp)
  lw     a0, 256(sp)
  call   putint
  lw     t1, 260(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 544(sp)
  lw     t1, 544(sp)
  sw     t1, 260(sp)
  j      .l79
.l81:
  addi   a0, sp, 0
  addi   a1, sp, 128
  call   arrCopy
  sw     a0, 548(sp)
  lw     t1, 548(sp)
  sw     t1, 256(sp)
  addi   a0, sp, 128
  li     a1, 3
  call   avgPooling
  sw     a0, 552(sp)
  lw     t1, 552(sp)
  sw     t1, 256(sp)
  li     t1, 0
  sw     t1, 260(sp)
.l82:
  lw     t1, 260(sp)
  li     s0, 32
  slt    t0, t1, s0
  sw     t0, 556(sp)
  lw     t0, 556(sp)
  li     t1, 0
  beq    t0, t1, .l84
.l83:
  lw     t1, 260(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 560(sp)
  addi   t1, sp, 128
  lw     t2, 560(sp)
  add    t0, t1, t2
  sw     t0, 560(sp)
  lw     t1, 560(sp)
  lw     t0, 0(t1)
  sw     t0, 560(sp)
  lw     t1, 560(sp)
  sw     t1, 256(sp)
  lw     a0, 256(sp)
  call   putint
  lw     t1, 260(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 568(sp)
  lw     t1, 568(sp)
  sw     t1, 260(sp)
  j      .l82
.l84:
  li     a0, 0
  lw     ra, 572(sp)
  addi   sp, sp, 576
  ret
  li     a0, 0
  lw     ra, 572(sp)
  addi   sp, sp, 576
  ret
  .size      main, .-main
