.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel guFrustum
/* 3D460 80062060 27BDFF70 */  addiu     $sp, $sp, -0x90
/* 3D464 80062064 F7B80070 */  sdc1      $f24, 0x70($sp)
/* 3D468 80062068 C7B800A0 */  lwc1      $f24, 0xa0($sp)
/* 3D46C 8006206C F7B60068 */  sdc1      $f22, 0x68($sp)
/* 3D470 80062070 C7B600A4 */  lwc1      $f22, 0xa4($sp)
/* 3D474 80062074 F7B40060 */  sdc1      $f20, 0x60($sp)
/* 3D478 80062078 C7B400A8 */  lwc1      $f20, 0xa8($sp)
/* 3D47C 8006207C AFB10054 */  sw        $s1, 0x54($sp)
/* 3D480 80062080 8FB100AC */  lw        $s1, 0xac($sp)
/* 3D484 80062084 F7BC0080 */  sdc1      $f28, 0x80($sp)
/* 3D488 80062088 4485E000 */  mtc1      $a1, $f28
/* 3D48C 8006208C F7BA0078 */  sdc1      $f26, 0x78($sp)
/* 3D490 80062090 4486D000 */  mtc1      $a2, $f26
/* 3D494 80062094 AFB20058 */  sw        $s2, 0x58($sp)
/* 3D498 80062098 00809021 */  addu      $s2, $a0, $zero
/* 3D49C 8006209C AFB00050 */  sw        $s0, 0x50($sp)
/* 3D4A0 800620A0 27B00010 */  addiu     $s0, $sp, 0x10
/* 3D4A4 800620A4 F7BE0088 */  sdc1      $f30, 0x88($sp)
/* 3D4A8 800620A8 4487F000 */  mtc1      $a3, $f30
/* 3D4AC 800620AC AFBF005C */  sw        $ra, 0x5c($sp)
/* 3D4B0 800620B0 0C019D28 */  jal       guMtxIdentF
/* 3D4B4 800620B4 02002021 */   addu     $a0, $s0, $zero
/* 3D4B8 800620B8 461CD001 */  sub.s     $f0, $f26, $f28
/* 3D4BC 800620BC 461CD680 */  add.s     $f26, $f26, $f28
/* 3D4C0 800620C0 4600D683 */  div.s     $f26, $f26, $f0
/* 3D4C4 800620C4 4616B180 */  add.s     $f6, $f22, $f22
/* 3D4C8 800620C8 46003203 */  div.s     $f8, $f6, $f0
/* 3D4CC 800620CC 461EC081 */  sub.s     $f2, $f24, $f30
/* 3D4D0 800620D0 46023183 */  div.s     $f6, $f6, $f2
/* 3D4D4 800620D4 461EC600 */  add.s     $f24, $f24, $f30
/* 3D4D8 800620D8 4602C603 */  div.s     $f24, $f24, $f2
/* 3D4DC 800620DC 4616A101 */  sub.s     $f4, $f20, $f22
/* 3D4E0 800620E0 4616A080 */  add.s     $f2, $f20, $f22
/* 3D4E4 800620E4 46001087 */  neg.s     $f2, $f2
/* 3D4E8 800620E8 46041083 */  div.s     $f2, $f2, $f4
/* 3D4EC 800620EC 3C01C000 */  lui       $at, 0xc000
/* 3D4F0 800620F0 44810000 */  mtc1      $at, $f0
/* 3D4F4 800620F4 00000000 */  nop
/* 3D4F8 800620F8 4600A502 */  mul.s     $f20, $f20, $f0
/* 3D4FC 800620FC 00000000 */  nop
/* 3D500 80062100 4616A502 */  mul.s     $f20, $f20, $f22
/* 3D504 80062104 4604A503 */  div.s     $f20, $f20, $f4
/* 3D508 80062108 3C01BF80 */  lui       $at, 0xbf80
/* 3D50C 8006210C 44810000 */  mtc1      $at, $f0
/* 3D510 80062110 00002821 */  addu      $a1, $zero, $zero
/* 3D514 80062114 AFA0004C */  sw        $zero, 0x4c($sp)
/* 3D518 80062118 E7A0003C */  swc1      $f0, 0x3c($sp)
/* 3D51C 8006211C E7BA0030 */  swc1      $f26, 0x30($sp)
/* 3D520 80062120 E7A80010 */  swc1      $f8, 0x10($sp)
/* 3D524 80062124 E7A60024 */  swc1      $f6, 0x24($sp)
/* 3D528 80062128 E7B80034 */  swc1      $f24, 0x34($sp)
/* 3D52C 8006212C E7A20038 */  swc1      $f2, 0x38($sp)
/* 3D530 80062130 E7B40048 */  swc1      $f20, 0x48($sp)
.L80062134:
/* 3D534 80062134 00002021 */  addu      $a0, $zero, $zero
/* 3D538 80062138 02001821 */  addu      $v1, $s0, $zero
.L8006213C:
/* 3D53C 8006213C C4600000 */  lwc1      $f0, ($v1)
/* 3D540 80062140 44915000 */  mtc1      $s1, $f10
/* 3D544 80062144 00000000 */  nop
/* 3D548 80062148 460A0002 */  mul.s     $f0, $f0, $f10
/* 3D54C 8006214C 24840001 */  addiu     $a0, $a0, 1
/* 3D550 80062150 28820004 */  slti      $v0, $a0, 4
/* 3D554 80062154 E4600000 */  swc1      $f0, ($v1)
/* 3D558 80062158 1440FFF8 */  bnez      $v0, .L8006213C
/* 3D55C 8006215C 24630004 */   addiu    $v1, $v1, 4
/* 3D560 80062160 24A50001 */  addiu     $a1, $a1, 1
/* 3D564 80062164 28A20004 */  slti      $v0, $a1, 4
/* 3D568 80062168 1440FFF2 */  bnez      $v0, .L80062134
/* 3D56C 8006216C 26100010 */   addiu    $s0, $s0, 0x10
/* 3D570 80062170 27A40010 */  addiu     $a0, $sp, 0x10
/* 3D574 80062174 0C019D40 */  jal       guMtxF2L
/* 3D578 80062178 02402821 */   addu     $a1, $s2, $zero
/* 3D57C 8006217C 8FBF005C */  lw        $ra, 0x5c($sp)
/* 3D580 80062180 8FB20058 */  lw        $s2, 0x58($sp)
/* 3D584 80062184 8FB10054 */  lw        $s1, 0x54($sp)
/* 3D588 80062188 8FB00050 */  lw        $s0, 0x50($sp)
/* 3D58C 8006218C D7BE0088 */  ldc1      $f30, 0x88($sp)
/* 3D590 80062190 D7BC0080 */  ldc1      $f28, 0x80($sp)
/* 3D594 80062194 D7BA0078 */  ldc1      $f26, 0x78($sp)
/* 3D598 80062198 D7B80070 */  ldc1      $f24, 0x70($sp)
/* 3D59C 8006219C D7B60068 */  ldc1      $f22, 0x68($sp)
/* 3D5A0 800621A0 D7B40060 */  ldc1      $f20, 0x60($sp)
/* 3D5A4 800621A4 03E00008 */  jr        $ra
/* 3D5A8 800621A8 27BD0090 */   addiu    $sp, $sp, 0x90
/* 3D5AC 800621AC 00000000 */  nop
