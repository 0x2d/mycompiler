  .comm      v0, 12, 4
  .global    v1
  .section   .sdata
  .align     2
  .type      v1, @object
  .size      v1, 4
v1:
  .word      0
  .comm      v2, 40000, 4
  .text
  .align     2
  .global    set
  .type      set, @function
set:
  addi   sp, sp, -432
  sw     ra, 428(sp)
  sw     a0, 0(sp)
  sw     a1, 4(sp)
  sw     a2, 8(sp)
  li     t1, 30
  sw     t1, 12(sp)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 0(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 4(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 8(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 12(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 16(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 20(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 24(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 28(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 32(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 36(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 40(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 44(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 48(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 52(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 56(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 60(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 64(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 68(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 72(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 76(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 80(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 84(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 88(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 92(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 96(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 100(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 104(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 108(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 112(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 116(t0)
  li     t1, 0
  addi   t0, sp, 16
  sw     t1, 120(t0)
  li     t1, 0
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 148(sp)
  addi   t1, sp, 16
  lw     t2, 148(sp)
  add    t0, t1, t2
  sw     t0, 148(sp)
  li     t1, 1
  lw     t0, 148(sp)
  sw     t1, 0(t0)
  li     t1, 1
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 152(sp)
  addi   t1, sp, 16
  lw     t2, 152(sp)
  add    t0, t1, t2
  sw     t0, 152(sp)
  li     t1, 0
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 156(sp)
  addi   t1, sp, 16
  lw     t2, 156(sp)
  add    t0, t1, t2
  sw     t0, 156(sp)
  lw     t1, 156(sp)
  lw     t0, 0(t1)
  sw     t0, 156(sp)
  lw     t1, 156(sp)
  li     s0, 2
  mul    t0, t1, s0
  sw     t0, 160(sp)
  lw     t1, 160(sp)
  lw     t0, 152(sp)
  sw     t1, 0(t0)
  li     t1, 2
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 164(sp)
  addi   t1, sp, 16
  lw     t2, 164(sp)
  add    t0, t1, t2
  sw     t0, 164(sp)
  li     t1, 1
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 168(sp)
  addi   t1, sp, 16
  lw     t2, 168(sp)
  add    t0, t1, t2
  sw     t0, 168(sp)
  lw     t1, 168(sp)
  lw     t0, 0(t1)
  sw     t0, 168(sp)
  lw     t1, 168(sp)
  li     s0, 2
  mul    t0, t1, s0
  sw     t0, 172(sp)
  lw     t1, 172(sp)
  lw     t0, 164(sp)
  sw     t1, 0(t0)
  li     t1, 3
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 176(sp)
  addi   t1, sp, 16
  lw     t2, 176(sp)
  add    t0, t1, t2
  sw     t0, 176(sp)
  li     t1, 2
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 180(sp)
  addi   t1, sp, 16
  lw     t2, 180(sp)
  add    t0, t1, t2
  sw     t0, 180(sp)
  lw     t1, 180(sp)
  lw     t0, 0(t1)
  sw     t0, 180(sp)
  lw     t1, 180(sp)
  li     s0, 2
  mul    t0, t1, s0
  sw     t0, 184(sp)
  lw     t1, 184(sp)
  lw     t0, 176(sp)
  sw     t1, 0(t0)
  li     t1, 4
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 188(sp)
  addi   t1, sp, 16
  lw     t2, 188(sp)
  add    t0, t1, t2
  sw     t0, 188(sp)
  li     t1, 3
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 192(sp)
  addi   t1, sp, 16
  lw     t2, 192(sp)
  add    t0, t1, t2
  sw     t0, 192(sp)
  lw     t1, 192(sp)
  lw     t0, 0(t1)
  sw     t0, 192(sp)
  lw     t1, 192(sp)
  li     s0, 2
  mul    t0, t1, s0
  sw     t0, 196(sp)
  lw     t1, 196(sp)
  lw     t0, 188(sp)
  sw     t1, 0(t0)
  li     t1, 5
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 200(sp)
  addi   t1, sp, 16
  lw     t2, 200(sp)
  add    t0, t1, t2
  sw     t0, 200(sp)
  li     t1, 4
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 204(sp)
  addi   t1, sp, 16
  lw     t2, 204(sp)
  add    t0, t1, t2
  sw     t0, 204(sp)
  lw     t1, 204(sp)
  lw     t0, 0(t1)
  sw     t0, 204(sp)
  lw     t1, 204(sp)
  li     s0, 2
  mul    t0, t1, s0
  sw     t0, 208(sp)
  lw     t1, 208(sp)
  lw     t0, 200(sp)
  sw     t1, 0(t0)
  li     t1, 6
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 212(sp)
  addi   t1, sp, 16
  lw     t2, 212(sp)
  add    t0, t1, t2
  sw     t0, 212(sp)
  li     t1, 5
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 216(sp)
  addi   t1, sp, 16
  lw     t2, 216(sp)
  add    t0, t1, t2
  sw     t0, 216(sp)
  lw     t1, 216(sp)
  lw     t0, 0(t1)
  sw     t0, 216(sp)
  lw     t1, 216(sp)
  li     s0, 2
  mul    t0, t1, s0
  sw     t0, 220(sp)
  lw     t1, 220(sp)
  lw     t0, 212(sp)
  sw     t1, 0(t0)
  li     t1, 7
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 224(sp)
  addi   t1, sp, 16
  lw     t2, 224(sp)
  add    t0, t1, t2
  sw     t0, 224(sp)
  li     t1, 6
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 228(sp)
  addi   t1, sp, 16
  lw     t2, 228(sp)
  add    t0, t1, t2
  sw     t0, 228(sp)
  lw     t1, 228(sp)
  lw     t0, 0(t1)
  sw     t0, 228(sp)
  lw     t1, 228(sp)
  li     s0, 2
  mul    t0, t1, s0
  sw     t0, 232(sp)
  lw     t1, 232(sp)
  lw     t0, 224(sp)
  sw     t1, 0(t0)
  li     t1, 8
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 236(sp)
  addi   t1, sp, 16
  lw     t2, 236(sp)
  add    t0, t1, t2
  sw     t0, 236(sp)
  li     t1, 7
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 240(sp)
  addi   t1, sp, 16
  lw     t2, 240(sp)
  add    t0, t1, t2
  sw     t0, 240(sp)
  lw     t1, 240(sp)
  lw     t0, 0(t1)
  sw     t0, 240(sp)
  lw     t1, 240(sp)
  li     s0, 2
  mul    t0, t1, s0
  sw     t0, 244(sp)
  lw     t1, 244(sp)
  lw     t0, 236(sp)
  sw     t1, 0(t0)
  li     t1, 9
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 248(sp)
  addi   t1, sp, 16
  lw     t2, 248(sp)
  add    t0, t1, t2
  sw     t0, 248(sp)
  li     t1, 8
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 252(sp)
  addi   t1, sp, 16
  lw     t2, 252(sp)
  add    t0, t1, t2
  sw     t0, 252(sp)
  lw     t1, 252(sp)
  lw     t0, 0(t1)
  sw     t0, 252(sp)
  lw     t1, 252(sp)
  li     s0, 2
  mul    t0, t1, s0
  sw     t0, 256(sp)
  lw     t1, 256(sp)
  lw     t0, 248(sp)
  sw     t1, 0(t0)
  li     t1, 10
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 260(sp)
  addi   t1, sp, 16
  lw     t2, 260(sp)
  add    t0, t1, t2
  sw     t0, 260(sp)
  li     t1, 9
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 264(sp)
  addi   t1, sp, 16
  lw     t2, 264(sp)
  add    t0, t1, t2
  sw     t0, 264(sp)
  lw     t1, 264(sp)
  lw     t0, 0(t1)
  sw     t0, 264(sp)
  lw     t1, 264(sp)
  li     s0, 2
  mul    t0, t1, s0
  sw     t0, 268(sp)
  lw     t1, 268(sp)
  lw     t0, 260(sp)
  sw     t1, 0(t0)
  li     t1, 10
  sw     t1, 140(sp)
.l0:
  lw     t1, 140(sp)
  lw     t2, 12(sp)
  slt    t0, t1, t2
  sw     t0, 272(sp)
  lw     t0, 272(sp)
  li     t1, 0
  beq    t0, t1, .l2
.l1:
  lw     t1, 140(sp)
  li     s0, 1
  add    t0, t1, s0
  sw     t0, 276(sp)
  lw     t1, 276(sp)
  sw     t1, 140(sp)
  lw     t1, 140(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 280(sp)
  addi   t1, sp, 16
  lw     t2, 280(sp)
  add    t0, t1, t2
  sw     t0, 280(sp)
  lw     t1, 140(sp)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 288(sp)
  lw     t1, 288(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 284(sp)
  addi   t1, sp, 16
  lw     t2, 284(sp)
  add    t0, t1, t2
  sw     t0, 284(sp)
  lw     t1, 284(sp)
  lw     t0, 0(t1)
  sw     t0, 284(sp)
  lw     t1, 284(sp)
  li     s0, 2
  mul    t0, t1, s0
  sw     t0, 292(sp)
  lw     t1, 292(sp)
  lw     t0, 280(sp)
  sw     t1, 0(t0)
  j      .l0
.l2:
  li     t1, 0
  sw     t1, 144(sp)
  lw     t1, 4(sp)
  lw     t2, 12(sp)
  div    t0, t1, t2
  sw     t0, 296(sp)
  lw     t1, 296(sp)
  li     s0, 10000
  slt    t0, t1, s0
  seqz   t0, t0
  sw     t0, 300(sp)
  lw     t0, 300(sp)
  li     t1, 0
  beq    t0, t1, .l4
.l3:
  li     a0, 0
  lw     ra, 428(sp)
  addi   sp, sp, 432
  ret
.l4:
  lw     t1, 4(sp)
  lw     t2, 12(sp)
  div    t0, t1, t2
  sw     t0, 308(sp)
  lw     t1, 308(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 304(sp)
  lw     t1, 0(sp)
  lw     t2, 304(sp)
  add    t0, t1, t2
  sw     t0, 304(sp)
  lw     t1, 304(sp)
  lw     t0, 0(t1)
  sw     t0, 304(sp)
  lw     t1, 4(sp)
  lw     t2, 12(sp)
  rem    t0, t1, t2
  sw     t0, 320(sp)
  lw     t1, 320(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 316(sp)
  addi   t1, sp, 16
  lw     t2, 316(sp)
  add    t0, t1, t2
  sw     t0, 316(sp)
  lw     t1, 316(sp)
  lw     t0, 0(t1)
  sw     t0, 316(sp)
  lw     t1, 304(sp)
  lw     t2, 316(sp)
  div    t0, t1, t2
  sw     t0, 312(sp)
  lw     t1, 312(sp)
  li     s0, 2
  rem    t0, t1, s0
  sw     t0, 312(sp)
  lw     t1, 312(sp)
  lw     t2, 8(sp)
  xor    t0, t1, t2
  snez   t0, t0
  sw     t0, 324(sp)
  lw     t0, 324(sp)
  li     t1, 0
  beq    t0, t1, .l6
.l5:
  lw     t1, 4(sp)
  lw     t2, 12(sp)
  div    t0, t1, t2
  sw     t0, 332(sp)
  lw     t1, 332(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 328(sp)
  lw     t1, 0(sp)
  lw     t2, 328(sp)
  add    t0, t1, t2
  sw     t0, 328(sp)
  lw     t1, 328(sp)
  lw     t0, 0(t1)
  sw     t0, 328(sp)
  lw     t1, 4(sp)
  lw     t2, 12(sp)
  rem    t0, t1, t2
  sw     t0, 344(sp)
  lw     t1, 344(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 340(sp)
  addi   t1, sp, 16
  lw     t2, 340(sp)
  add    t0, t1, t2
  sw     t0, 340(sp)
  lw     t1, 340(sp)
  lw     t0, 0(t1)
  sw     t0, 340(sp)
  lw     t1, 328(sp)
  lw     t2, 340(sp)
  div    t0, t1, t2
  sw     t0, 336(sp)
  lw     t1, 336(sp)
  li     s0, 2
  rem    t0, t1, s0
  sw     t0, 336(sp)
  lw     t1, 336(sp)
  li     s0, 0
  xor    t0, t1, s0
  seqz   t0, t0
  sw     t0, 348(sp)
  lw     t0, 348(sp)
  li     t1, 0
  beq    t0, t1, .l8
.l7:
  lw     t1, 8(sp)
  li     s0, 1
  xor    t0, t1, s0
  seqz   t0, t0
  sw     t0, 352(sp)
  lw     t0, 352(sp)
  li     t1, 0
  beq    t0, t1, .l10
.l9:
  lw     t1, 4(sp)
  lw     t2, 12(sp)
  rem    t0, t1, t2
  sw     t0, 360(sp)
  lw     t1, 360(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 356(sp)
  addi   t1, sp, 16
  lw     t2, 356(sp)
  add    t0, t1, t2
  sw     t0, 356(sp)
  lw     t1, 356(sp)
  lw     t0, 0(t1)
  sw     t0, 356(sp)
  lw     t1, 356(sp)
  sw     t1, 144(sp)
.l10:
.l8:
  lw     t1, 4(sp)
  lw     t2, 12(sp)
  div    t0, t1, t2
  sw     t0, 368(sp)
  lw     t1, 368(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 364(sp)
  lw     t1, 0(sp)
  lw     t2, 364(sp)
  add    t0, t1, t2
  sw     t0, 364(sp)
  lw     t1, 364(sp)
  lw     t0, 0(t1)
  sw     t0, 364(sp)
  lw     t1, 4(sp)
  lw     t2, 12(sp)
  rem    t0, t1, t2
  sw     t0, 380(sp)
  lw     t1, 380(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 376(sp)
  addi   t1, sp, 16
  lw     t2, 376(sp)
  add    t0, t1, t2
  sw     t0, 376(sp)
  lw     t1, 376(sp)
  lw     t0, 0(t1)
  sw     t0, 376(sp)
  lw     t1, 364(sp)
  lw     t2, 376(sp)
  div    t0, t1, t2
  sw     t0, 372(sp)
  lw     t1, 372(sp)
  li     s0, 2
  rem    t0, t1, s0
  sw     t0, 372(sp)
  lw     t1, 372(sp)
  li     s0, 1
  xor    t0, t1, s0
  seqz   t0, t0
  sw     t0, 384(sp)
  lw     t0, 384(sp)
  li     t1, 0
  beq    t0, t1, .l12
.l11:
  lw     t1, 8(sp)
  li     s0, 0
  xor    t0, t1, s0
  seqz   t0, t0
  sw     t0, 388(sp)
  lw     t0, 388(sp)
  li     t1, 0
  beq    t0, t1, .l14
.l13:
  lw     t1, 4(sp)
  lw     t2, 12(sp)
  rem    t0, t1, t2
  sw     t0, 400(sp)
  lw     t1, 400(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 396(sp)
  addi   t1, sp, 16
  lw     t2, 396(sp)
  add    t0, t1, t2
  sw     t0, 396(sp)
  lw     t1, 396(sp)
  lw     t0, 0(t1)
  sw     t0, 396(sp)
  lw     t1, 144(sp)
  lw     t2, 396(sp)
  sub    t0, t1, t2
  sw     t0, 392(sp)
  lw     t1, 392(sp)
  sw     t1, 144(sp)
.l14:
.l12:
.l6:
  lw     t1, 4(sp)
  lw     t2, 12(sp)
  div    t0, t1, t2
  sw     t0, 408(sp)
  lw     t1, 408(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 404(sp)
  lw     t1, 0(sp)
  lw     t2, 404(sp)
  add    t0, t1, t2
  sw     t0, 404(sp)
  lw     t1, 4(sp)
  lw     t2, 12(sp)
  div    t0, t1, t2
  sw     t0, 416(sp)
  lw     t1, 416(sp)
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 412(sp)
  lw     t1, 0(sp)
  lw     t2, 412(sp)
  add    t0, t1, t2
  sw     t0, 412(sp)
  lw     t1, 412(sp)
  lw     t0, 0(t1)
  sw     t0, 412(sp)
  lw     t1, 412(sp)
  lw     t2, 144(sp)
  add    t0, t1, t2
  sw     t0, 420(sp)
  lw     t1, 420(sp)
  lw     t0, 404(sp)
  sw     t1, 0(t0)
  li     a0, 0
  lw     ra, 428(sp)
  addi   sp, sp, 432
  ret
  li     a0, 0
  lw     ra, 428(sp)
  addi   sp, sp, 432
  ret
  .size      set, .-set
  .text
  .align     2
  .global    rand
  .type      rand, @function
rand:
  addi   sp, sp, -48
  sw     ra, 44(sp)
  li     t1, 0
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 4(sp)
  la     t1, v0
  lw     t2, 4(sp)
  add    t0, t1, t2
  sw     t0, 4(sp)
  lw     t1, 4(sp)
  lw     t0, 0(t1)
  sw     t0, 4(sp)
  lui    t1, %hi(v1)
  lw     t1, %lo(v1)(t1)
  lw     t2, 4(sp)
  mul    t0, t1, t2
  sw     t0, 0(sp)
  li     t1, 1
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
  lw     t1, 0(sp)
  lw     t2, 12(sp)
  add    t0, t1, t2
  sw     t0, 8(sp)
  lw     t1, 8(sp)
  la     t0, v1
  sw     t1, 0(t0)
  li     t1, 2
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 20(sp)
  la     t1, v0
  lw     t2, 20(sp)
  add    t0, t1, t2
  sw     t0, 20(sp)
  lw     t1, 20(sp)
  lw     t0, 0(t1)
  sw     t0, 20(sp)
  lui    t1, %hi(v1)
  lw     t1, %lo(v1)(t1)
  lw     t2, 20(sp)
  rem    t0, t1, t2
  sw     t0, 16(sp)
  lw     t1, 16(sp)
  la     t0, v1
  sw     t1, 0(t0)
  lui    t1, %hi(v1)
  lw     t1, %lo(v1)(t1)
  li     s0, 0
  slt    t0, t1, s0
  sw     t0, 24(sp)
  lw     t0, 24(sp)
  li     t1, 0
  beq    t0, t1, .l16
.l15:
  li     t1, 2
  li     s0, 4
  mul    t0, t1, s0
  sw     t0, 28(sp)
  la     t1, v0
  lw     t2, 28(sp)
  add    t0, t1, t2
  sw     t0, 28(sp)
  lw     t1, 28(sp)
  lw     t0, 0(t1)
  sw     t0, 28(sp)
  lw     t1, 28(sp)
  lui    t2, %hi(v1)
  lw     t2, %lo(v1)(t2)
  add    t0, t1, t2
  sw     t0, 32(sp)
  lw     t1, 32(sp)
  la     t0, v1
  sw     t1, 0(t0)
.l16:
  lui    a0, %hi(v1)
  lw     a0, %lo(v1)(a0)
  lw     ra, 44(sp)
  addi   sp, sp, 48
  ret
  li     a0, 0
  lw     ra, 44(sp)
  addi   sp, sp, 48
  ret
  .size      rand, .-rand
  .text
  .align     2
  .global    main
  .type      main, @function
main:
  addi   sp, sp, -64
  sw     ra, 60(sp)
  la     t0, v0
  li     t1, 19971231
  sw     t1, 0(t0)
  li     t1, 19981013
  sw     t1, 4(t0)
  li     t1, 1000000007
  sw     t1, 8(t0)
  call   getint
  sw     a0, 12(sp)
  lw     t1, 12(sp)
  sw     t1, 0(sp)
  call   getint
  sw     a0, 16(sp)
  lw     t1, 16(sp)
  la     t0, v1
  sw     t1, 0(t0)
  li     a0, 56
  call   _sysy_starttime
.l17:
  lw     t1, 0(sp)
  li     s0, 0
  sgt    t0, t1, s0
  sw     t0, 24(sp)
  lw     t0, 24(sp)
  li     t1, 0
  beq    t0, t1, .l19
.l18:
  lw     t1, 0(sp)
  li     s0, 1
  sub    t0, t1, s0
  sw     t0, 28(sp)
  lw     t1, 28(sp)
  sw     t1, 0(sp)
  call   rand
  sw     a0, 32(sp)
  lw     t1, 32(sp)
  li     s0, 300000
  rem    t0, t1, s0
  sw     t0, 36(sp)
  lw     t1, 36(sp)
  sw     t1, 4(sp)
  call   rand
  sw     a0, 40(sp)
  lw     t1, 40(sp)
  li     s0, 2
  rem    t0, t1, s0
  sw     t0, 44(sp)
  lw     t1, 44(sp)
  sw     t1, 8(sp)
  la     a0, v2
  lw     a1, 4(sp)
  lw     a2, 8(sp)
  call   set
  sw     a0, 48(sp)
  j      .l17
.l19:
  li     a0, 64
  call   _sysy_stoptime
  li     a0, 10000
  la     a1, v2
  call   putarray
  li     a0, 0
  lw     ra, 60(sp)
  addi   sp, sp, 64
  ret
  li     a0, 0
  lw     ra, 60(sp)
  addi   sp, sp, 64
  ret
  .size      main, .-main
