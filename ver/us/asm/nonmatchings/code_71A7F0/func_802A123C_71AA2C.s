.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel func_802A123C_71AA2C
/* 71AA2C 802A123C 27BDFFE8 */  addiu     $sp, $sp, -0x18
/* 71AA30 802A1240 0080102D */  daddu     $v0, $a0, $zero
/* 71AA34 802A1244 AFB00010 */  sw        $s0, 0x10($sp)
/* 71AA38 802A1248 3C10800E */  lui       $s0, %hi(gBattleStatus+0xD8)
/* 71AA3C 802A124C 8E10C148 */  lw        $s0, %lo(gBattleStatus+0xD8)($s0)
/* 71AA40 802A1250 2405000B */  addiu     $a1, $zero, 0xb
/* 71AA44 802A1254 AFBF0014 */  sw        $ra, 0x14($sp)
/* 71AA48 802A1258 8C460084 */  lw        $a2, 0x84($v0)
/* 71AA4C 802A125C 0C0997D0 */  jal       inflict_status
/* 71AA50 802A1260 0200202D */   daddu    $a0, $s0, $zero
/* 71AA54 802A1264 A200021C */  sb        $zero, 0x21c($s0)
/* 71AA58 802A1268 8FBF0014 */  lw        $ra, 0x14($sp)
/* 71AA5C 802A126C 8FB00010 */  lw        $s0, 0x10($sp)
/* 71AA60 802A1270 24020002 */  addiu     $v0, $zero, 2
/* 71AA64 802A1274 03E00008 */  jr        $ra
/* 71AA68 802A1278 27BD0018 */   addiu    $sp, $sp, 0x18
/* 71AA6C 802A127C 00000000 */  nop
