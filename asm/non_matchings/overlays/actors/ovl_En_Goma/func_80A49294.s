glabel func_80A49294
/* 003D4 80A49294 27BDFFD0 */  addiu   $sp, $sp, 0xFFD0           ## $sp = FFFFFFD0
/* 003D8 80A49298 AFB00028 */  sw      $s0, 0x0028($sp)
/* 003DC 80A4929C 00808025 */  or      $s0, $a0, $zero            ## $s0 = 00000000
/* 003E0 80A492A0 AFBF002C */  sw      $ra, 0x002C($sp)
/* 003E4 80A492A4 3C040600 */  lui     $a0, %hi(D_06003D78)                ## $a0 = 06000000
/* 003E8 80A492A8 0C028800 */  jal     SkelAnime_GetFrameCount

/* 003EC 80A492AC 24843D78 */  addiu   $a0, $a0, %lo(D_06003D78)           ## $a0 = 06003D78
/* 003F0 80A492B0 44822000 */  mtc1    $v0, $f4                   ## $f4 = 0.00
/* 003F4 80A492B4 3C01C000 */  lui     $at, 0xC000                ## $at = C0000000
/* 003F8 80A492B8 44814000 */  mtc1    $at, $f8                   ## $f8 = -2.00
/* 003FC 80A492BC 468021A0 */  cvt.s.w $f6, $f4
/* 00400 80A492C0 3C050600 */  lui     $a1, %hi(D_06003D78)                ## $a1 = 06000000
/* 00404 80A492C4 24A53D78 */  addiu   $a1, $a1, %lo(D_06003D78)           ## $a1 = 06003D78
/* 00408 80A492C8 2604014C */  addiu   $a0, $s0, 0x014C           ## $a0 = 0000014C
/* 0040C 80A492CC 3C064000 */  lui     $a2, 0x4000                ## $a2 = 40000000
/* 00410 80A492D0 24070000 */  addiu   $a3, $zero, 0x0000         ## $a3 = 00000000
/* 00414 80A492D4 E7A60010 */  swc1    $f6, 0x0010($sp)
/* 00418 80A492D8 AFA00014 */  sw      $zero, 0x0014($sp)
/* 0041C 80A492DC 0C029468 */  jal     SkelAnime_ChangeAnim

/* 00420 80A492E0 E7A80018 */  swc1    $f8, 0x0018($sp)
/* 00424 80A492E4 8618001C */  lh      $t8, 0x001C($s0)           ## 0000001C
/* 00428 80A492E8 3C0E80A5 */  lui     $t6, %hi(func_80A49338)    ## $t6 = 80A50000
/* 0042C 80A492EC 25CE9338 */  addiu   $t6, $t6, %lo(func_80A49338) ## $t6 = 80A49338
/* 00430 80A492F0 240F0014 */  addiu   $t7, $zero, 0x0014         ## $t7 = 00000014
/* 00434 80A492F4 2B010006 */  slti    $at, $t8, 0x0006
/* 00438 80A492F8 AE0E02B0 */  sw      $t6, 0x02B0($s0)           ## 000002B0
/* 0043C 80A492FC 10200006 */  beq     $at, $zero, .L80A49318
/* 00440 80A49300 A60F02CC */  sh      $t7, 0x02CC($s0)           ## 000002CC
/* 00444 80A49304 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 00448 80A49308 0C00BE0A */  jal     Audio_PlayActorSound2

/* 0044C 80A4930C 24053819 */  addiu   $a1, $zero, 0x3819         ## $a1 = 00003819
/* 00450 80A49310 10000005 */  beq     $zero, $zero, .L80A49328
/* 00454 80A49314 8FBF002C */  lw      $ra, 0x002C($sp)
.L80A49318:
/* 00458 80A49318 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 0045C 80A4931C 0C00BE0A */  jal     Audio_PlayActorSound2

/* 00460 80A49320 2405395F */  addiu   $a1, $zero, 0x395F         ## $a1 = 0000395F
/* 00464 80A49324 8FBF002C */  lw      $ra, 0x002C($sp)
.L80A49328:
/* 00468 80A49328 8FB00028 */  lw      $s0, 0x0028($sp)
/* 0046C 80A4932C 27BD0030 */  addiu   $sp, $sp, 0x0030           ## $sp = 00000000
/* 00470 80A49330 03E00008 */  jr      $ra
/* 00474 80A49334 00000000 */  nop
