glabel func_80B58AAC
/* 056FC 80B58AAC 27BDFFE8 */  addiu   $sp, $sp, 0xFFE8           ## $sp = FFFFFFE8
/* 05700 80B58AB0 AFBF0014 */  sw      $ra, 0x0014($sp)           
/* 05704 80B58AB4 3C013F80 */  lui     $at, 0x3F80                ## $at = 3F800000
/* 05708 80B58AB8 44813000 */  mtc1    $at, $f6                   ## $f6 = 1.00
/* 0570C 80B58ABC C48402EC */  lwc1    $f4, 0x02EC($a0)           ## 000002EC
/* 05710 80B58AC0 3C028016 */  lui     $v0, %hi(gGameInfo)
/* 05714 80B58AC4 3C0141C0 */  lui     $at, 0x41C0                ## $at = 41C00000
/* 05718 80B58AC8 46062200 */  add.s   $f8, $f4, $f6              
/* 0571C 80B58ACC 44812000 */  mtc1    $at, $f4                   ## $f4 = 24.00
/* 05720 80B58AD0 E48802EC */  swc1    $f8, 0x02EC($a0)           ## 000002EC
/* 05724 80B58AD4 8C42FA90 */  lw      $v0, %lo(gGameInfo)($v0)
/* 05728 80B58AD8 C48A02EC */  lwc1    $f10, 0x02EC($a0)          ## 000002EC
/* 0572C 80B58ADC 844E1462 */  lh      $t6, 0x1462($v0)           ## 80161462
/* 05730 80B58AE0 448E8000 */  mtc1    $t6, $f16                  ## $f16 = 0.00
/* 05734 80B58AE4 00000000 */  nop
/* 05738 80B58AE8 468084A0 */  cvt.s.w $f18, $f16                 
/* 0573C 80B58AEC 46049180 */  add.s   $f6, $f18, $f4             
/* 05740 80B58AF0 460A303E */  c.le.s  $f6, $f10                  
/* 05744 80B58AF4 00000000 */  nop
/* 05748 80B58AF8 4502000D */  bc1fl   .L80B58B30                 
/* 0574C 80B58AFC 84581464 */  lh      $t8, 0x1464($v0)           ## 80161464
/* 05750 80B58B00 8C8F036C */  lw      $t7, 0x036C($a0)           ## 0000036C
/* 05754 80B58B04 55E0000A */  bnel    $t7, $zero, .L80B58B30     
/* 05758 80B58B08 84581464 */  lh      $t8, 0x1464($v0)           ## 80161464
/* 0575C 80B58B0C AFA40018 */  sw      $a0, 0x0018($sp)           
/* 05760 80B58B10 0C2D5DD5 */  jal     func_80B57754              
/* 05764 80B58B14 AFA5001C */  sw      $a1, 0x001C($sp)           
/* 05768 80B58B18 8FA40018 */  lw      $a0, 0x0018($sp)           
/* 0576C 80B58B1C 0C2D6213 */  jal     func_80B5884C              
/* 05770 80B58B20 8FA5001C */  lw      $a1, 0x001C($sp)           
/* 05774 80B58B24 10000035 */  beq     $zero, $zero, .L80B58BFC   
/* 05778 80B58B28 8FBF0014 */  lw      $ra, 0x0014($sp)           
/* 0577C 80B58B2C 84581464 */  lh      $t8, 0x1464($v0)           ## 00001464
.L80B58B30:
/* 05780 80B58B30 3C014248 */  lui     $at, 0x4248                ## $at = 42480000
/* 05784 80B58B34 44819000 */  mtc1    $at, $f18                  ## $f18 = 50.00
/* 05788 80B58B38 44984000 */  mtc1    $t8, $f8                   ## $f8 = 0.00
/* 0578C 80B58B3C C48002EC */  lwc1    $f0, 0x02EC($a0)           ## 000002EC
/* 05790 80B58B40 46804420 */  cvt.s.w $f16, $f8                  
/* 05794 80B58B44 46128100 */  add.s   $f4, $f16, $f18            
/* 05798 80B58B48 4600203E */  c.le.s  $f4, $f0                   
/* 0579C 80B58B4C 00000000 */  nop
/* 057A0 80B58B50 4502000B */  bc1fl   .L80B58B80                 
/* 057A4 80B58B54 84491466 */  lh      $t1, 0x1466($v0)           ## 00001466
/* 057A8 80B58B58 8C990370 */  lw      $t9, 0x0370($a0)           ## 00000370
/* 057AC 80B58B5C 57200008 */  bnel    $t9, $zero, .L80B58B80     
/* 057B0 80B58B60 84491466 */  lh      $t1, 0x1466($v0)           ## 00001466
/* 057B4 80B58B64 0C2D5BAE */  jal     func_80B56EB8              
/* 057B8 80B58B68 AFA40018 */  sw      $a0, 0x0018($sp)           
/* 057BC 80B58B6C 8FA40018 */  lw      $a0, 0x0018($sp)           
/* 057C0 80B58B70 24080001 */  addiu   $t0, $zero, 0x0001         ## $t0 = 00000001
/* 057C4 80B58B74 10000020 */  beq     $zero, $zero, .L80B58BF8   
/* 057C8 80B58B78 AC880370 */  sw      $t0, 0x0370($a0)           ## 00000370
/* 057CC 80B58B7C 84491466 */  lh      $t1, 0x1466($v0)           ## 00001466
.L80B58B80:
/* 057D0 80B58B80 3C014260 */  lui     $at, 0x4260                ## $at = 42600000
/* 057D4 80B58B84 44814000 */  mtc1    $at, $f8                   ## $f8 = 56.00
/* 057D8 80B58B88 44895000 */  mtc1    $t1, $f10                  ## $f10 = 0.00
/* 057DC 80B58B8C 00000000 */  nop
/* 057E0 80B58B90 468051A0 */  cvt.s.w $f6, $f10                  
/* 057E4 80B58B94 46083400 */  add.s   $f16, $f6, $f8             
/* 057E8 80B58B98 4600803E */  c.le.s  $f16, $f0                  
/* 057EC 80B58B9C 00000000 */  nop
/* 057F0 80B58BA0 45020009 */  bc1fl   .L80B58BC8                 
/* 057F4 80B58BA4 844B1468 */  lh      $t3, 0x1468($v0)           ## 00001468
/* 057F8 80B58BA8 8C8A0374 */  lw      $t2, 0x0374($a0)           ## 00000374
/* 057FC 80B58BAC 55400006 */  bnel    $t2, $zero, .L80B58BC8     
/* 05800 80B58BB0 844B1468 */  lh      $t3, 0x1468($v0)           ## 00001468
/* 05804 80B58BB4 0C2D6226 */  jal     func_80B58898              
/* 05808 80B58BB8 00000000 */  nop
/* 0580C 80B58BBC 1000000F */  beq     $zero, $zero, .L80B58BFC   
/* 05810 80B58BC0 8FBF0014 */  lw      $ra, 0x0014($sp)           
/* 05814 80B58BC4 844B1468 */  lh      $t3, 0x1468($v0)           ## 00001468
.L80B58BC8:
/* 05818 80B58BC8 3C0142A4 */  lui     $at, 0x42A4                ## $at = 42A40000
/* 0581C 80B58BCC 44815000 */  mtc1    $at, $f10                  ## $f10 = 82.00
/* 05820 80B58BD0 448B9000 */  mtc1    $t3, $f18                  ## $f18 = 0.00
/* 05824 80B58BD4 00000000 */  nop
/* 05828 80B58BD8 46809120 */  cvt.s.w $f4, $f18                  
/* 0582C 80B58BDC 460A2180 */  add.s   $f6, $f4, $f10             
/* 05830 80B58BE0 4600303E */  c.le.s  $f6, $f0                   
/* 05834 80B58BE4 00000000 */  nop
/* 05838 80B58BE8 45020004 */  bc1fl   .L80B58BFC                 
/* 0583C 80B58BEC 8FBF0014 */  lw      $ra, 0x0014($sp)           
/* 05840 80B58BF0 0C2D623A */  jal     func_80B588E8              
/* 05844 80B58BF4 00000000 */  nop
.L80B58BF8:
/* 05848 80B58BF8 8FBF0014 */  lw      $ra, 0x0014($sp)           
.L80B58BFC:
/* 0584C 80B58BFC 27BD0018 */  addiu   $sp, $sp, 0x0018           ## $sp = 00000000
/* 05850 80B58C00 03E00008 */  jr      $ra                        
/* 05854 80B58C04 00000000 */  nop
