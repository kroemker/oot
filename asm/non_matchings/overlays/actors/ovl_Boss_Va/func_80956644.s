glabel func_80956644
/* 07384 80956644 27BDFFD8 */  addiu   $sp, $sp, 0xFFD8           ## $sp = FFFFFFD8
/* 07388 80956648 AFA40028 */  sw      $a0, 0x0028($sp)
/* 0738C 8095664C AFBF0024 */  sw      $ra, 0x0024($sp)
/* 07390 80956650 3C040602 */  lui     $a0, %hi(D_06018B90)                ## $a0 = 06020000
/* 07394 80956654 AFA5002C */  sw      $a1, 0x002C($sp)
/* 07398 80956658 0C028800 */  jal     SkelAnime_GetFrameCount

/* 0739C 8095665C 24848B90 */  addiu   $a0, $a0, %lo(D_06018B90)           ## $a0 = 06018B90
/* 073A0 80956660 44822000 */  mtc1    $v0, $f4                   ## $f4 = 0.00
/* 073A4 80956664 44800000 */  mtc1    $zero, $f0                 ## $f0 = 0.00
/* 073A8 80956668 3C01C0C0 */  lui     $at, 0xC0C0                ## $at = C0C00000
/* 073AC 8095666C 468021A0 */  cvt.s.w $f6, $f4
/* 073B0 80956670 44814000 */  mtc1    $at, $f8                   ## $f8 = -6.00
/* 073B4 80956674 8FA40028 */  lw      $a0, 0x0028($sp)
/* 073B8 80956678 3C050602 */  lui     $a1, %hi(D_06018B90)                ## $a1 = 06020000
/* 073BC 8095667C 240E0003 */  addiu   $t6, $zero, 0x0003         ## $t6 = 00000003
/* 073C0 80956680 44060000 */  mfc1    $a2, $f0
/* 073C4 80956684 44070000 */  mfc1    $a3, $f0
/* 073C8 80956688 AFAE0014 */  sw      $t6, 0x0014($sp)
/* 073CC 8095668C 24A58B90 */  addiu   $a1, $a1, %lo(D_06018B90)           ## $a1 = 06018B90
/* 073D0 80956690 E7A60010 */  swc1    $f6, 0x0010($sp)
/* 073D4 80956694 2484014C */  addiu   $a0, $a0, 0x014C           ## $a0 = 0000014C
/* 073D8 80956698 0C029468 */  jal     SkelAnime_ChangeAnim

/* 073DC 8095669C E7A80018 */  swc1    $f8, 0x0018($sp)
/* 073E0 809566A0 8FA40028 */  lw      $a0, 0x0028($sp)
/* 073E4 809566A4 3C058095 */  lui     $a1, %hi(func_809566C4)    ## $a1 = 80950000
/* 073E8 809566A8 24A566C4 */  addiu   $a1, $a1, %lo(func_809566C4) ## $a1 = 809566C4
/* 073EC 809566AC 0C253CB0 */  jal     func_8094F2C0
/* 073F0 809566B0 A0800195 */  sb      $zero, 0x0195($a0)         ## 00000195
/* 073F4 809566B4 8FBF0024 */  lw      $ra, 0x0024($sp)
/* 073F8 809566B8 27BD0028 */  addiu   $sp, $sp, 0x0028           ## $sp = 00000000
/* 073FC 809566BC 03E00008 */  jr      $ra
/* 07400 809566C0 00000000 */  nop
