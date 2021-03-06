.late_rodata
glabel D_80B9CD14
    .float 0.001

.text
glabel func_80B9C14C
/* 00FCC 80B9C14C 27BDFFD0 */  addiu   $sp, $sp, 0xFFD0           ## $sp = FFFFFFD0
/* 00FD0 80B9C150 AFBF001C */  sw      $ra, 0x001C($sp)           
/* 00FD4 80B9C154 AFB10018 */  sw      $s1, 0x0018($sp)           
/* 00FD8 80B9C158 AFB00014 */  sw      $s0, 0x0014($sp)           
/* 00FDC 80B9C15C 8CAE1C44 */  lw      $t6, 0x1C44($a1)           ## 00001C44
/* 00FE0 80B9C160 00808025 */  or      $s0, $a0, $zero            ## $s0 = 00000000
/* 00FE4 80B9C164 00A08825 */  or      $s1, $a1, $zero            ## $s1 = 00000000
/* 00FE8 80B9C168 AFAE0028 */  sw      $t6, 0x0028($sp)           
/* 00FEC 80B9C16C 948F0168 */  lhu     $t7, 0x0168($a0)           ## 00000168
/* 00FF0 80B9C170 35F80004 */  ori     $t8, $t7, 0x0004           ## $t8 = 00000004
/* 00FF4 80B9C174 0C00B638 */  jal     Actor_MoveForward
              
/* 00FF8 80B9C178 A4980168 */  sh      $t8, 0x0168($a0)           ## 00000168
/* 00FFC 80B9C17C 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 01000 80B9C180 0C2E6EF2 */  jal     func_80B9BBC8              
/* 01004 80B9C184 02202825 */  or      $a1, $s1, $zero            ## $a1 = 00000000
/* 01008 80B9C188 5040004B */  beql    $v0, $zero, .L80B9C2B8     
/* 0100C 80B9C18C 860F01BC */  lh      $t7, 0x01BC($s0)           ## 000001BC
/* 01010 80B9C190 861901BC */  lh      $t9, 0x01BC($s0)           ## 000001BC
/* 01014 80B9C194 24010032 */  addiu   $at, $zero, 0x0032         ## $at = 00000032
/* 01018 80B9C198 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 0101C 80B9C19C 00194080 */  sll     $t0, $t9,  2               
/* 01020 80B9C1A0 02084821 */  addu    $t1, $s0, $t0              
/* 01024 80B9C1A4 8D250180 */  lw      $a1, 0x0180($t1)           ## 00000180
/* 01028 80B9C1A8 14A10005 */  bne     $a1, $at, .L80B9C1C0       
/* 0102C 80B9C1AC 00000000 */  nop
/* 01030 80B9C1B0 0C2E6FFE */  jal     func_80B9BFF8              
/* 01034 80B9C1B4 02202825 */  or      $a1, $s1, $zero            ## $a1 = 00000000
/* 01038 80B9C1B8 1000005D */  beq     $zero, $zero, .L80B9C330   
/* 0103C 80B9C1BC 8FBF001C */  lw      $ra, 0x001C($sp)           
.L80B9C1C0:
/* 01040 80B9C1C0 0C00FAE1 */  jal     DynaPolyInfo_GetActor
              ## DynaPolyInfo_getActor
/* 01044 80B9C1C4 262407C0 */  addiu   $a0, $s1, 0x07C0           ## $a0 = 000007C0
/* 01048 80B9C1C8 10400035 */  beq     $v0, $zero, .L80B9C2A0     
/* 0104C 80B9C1CC 00402025 */  or      $a0, $v0, $zero            ## $a0 = 00000000
/* 01050 80B9C1D0 0C010D2A */  jal     func_800434A8              
/* 01054 80B9C1D4 AFA20024 */  sw      $v0, 0x0024($sp)           
/* 01058 80B9C1D8 0C010D4E */  jal     func_80043538              
/* 0105C 80B9C1DC 8FA40024 */  lw      $a0, 0x0024($sp)           
/* 01060 80B9C1E0 860A016A */  lh      $t2, 0x016A($s0)           ## 0000016A
/* 01064 80B9C1E4 8FA20028 */  lw      $v0, 0x0028($sp)           
/* 01068 80B9C1E8 5D400027 */  bgtzl   $t2, .L80B9C288            
/* 0106C 80B9C1EC 8C4D0680 */  lw      $t5, 0x0680($v0)           ## 00000680
/* 01070 80B9C1F0 C6000150 */  lwc1    $f0, 0x0150($s0)           ## 00000150
/* 01074 80B9C1F4 3C0180BA */  lui     $at, %hi(D_80B9CD14)       ## $at = 80BA0000
/* 01078 80B9C1F8 C424CD14 */  lwc1    $f4, %lo(D_80B9CD14)($at)  
/* 0107C 80B9C1FC 46000005 */  abs.s   $f0, $f0                   
/* 01080 80B9C200 4600203C */  c.lt.s  $f4, $f0                   
/* 01084 80B9C204 00000000 */  nop
/* 01088 80B9C208 4502001F */  bc1fl   .L80B9C288                 
/* 0108C 80B9C20C 8C4D0680 */  lw      $t5, 0x0680($v0)           ## 00000680
/* 01090 80B9C210 0C2E6C95 */  jal     func_80B9B254              
/* 01094 80B9C214 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 01098 80B9C218 10400012 */  beq     $v0, $zero, .L80B9C264     
/* 0109C 80B9C21C 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 010A0 80B9C220 8FA50024 */  lw      $a1, 0x0024($sp)           
/* 010A4 80B9C224 0C2E6D2F */  jal     func_80B9B4BC              
/* 010A8 80B9C228 02203025 */  or      $a2, $s1, $zero            ## $a2 = 00000000
/* 010AC 80B9C22C 1040000D */  beq     $v0, $zero, .L80B9C264     
/* 010B0 80B9C230 02202025 */  or      $a0, $s1, $zero            ## $a0 = 00000000
/* 010B4 80B9C234 86050158 */  lh      $a1, 0x0158($s0)           ## 00000158
/* 010B8 80B9C238 8E060150 */  lw      $a2, 0x0150($s0)           ## 00000150
/* 010BC 80B9C23C 0C2E6F2E */  jal     func_80B9BCB8              
/* 010C0 80B9C240 02003825 */  or      $a3, $s0, $zero            ## $a3 = 00000000
/* 010C4 80B9C244 14400007 */  bne     $v0, $zero, .L80B9C264     
/* 010C8 80B9C248 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 010CC 80B9C24C C6060150 */  lwc1    $f6, 0x0150($s0)           ## 00000150
/* 010D0 80B9C250 02202825 */  or      $a1, $s1, $zero            ## $a1 = 00000000
/* 010D4 80B9C254 0C2E70D0 */  jal     func_80B9C340              
/* 010D8 80B9C258 E606017C */  swc1    $f6, 0x017C($s0)           ## 0000017C
/* 010DC 80B9C25C 10000034 */  beq     $zero, $zero, .L80B9C330   
/* 010E0 80B9C260 8FBF001C */  lw      $ra, 0x001C($sp)           
.L80B9C264:
/* 010E4 80B9C264 8FA20028 */  lw      $v0, 0x0028($sp)           
/* 010E8 80B9C268 2401FFEF */  addiu   $at, $zero, 0xFFEF         ## $at = FFFFFFEF
/* 010EC 80B9C26C 44804000 */  mtc1    $zero, $f8                 ## $f8 = 0.00
/* 010F0 80B9C270 8C4B0680 */  lw      $t3, 0x0680($v0)           ## 00000680
/* 010F4 80B9C274 01616024 */  and     $t4, $t3, $at              
/* 010F8 80B9C278 AC4C0680 */  sw      $t4, 0x0680($v0)           ## 00000680
/* 010FC 80B9C27C 1000002B */  beq     $zero, $zero, .L80B9C32C   
/* 01100 80B9C280 E6080150 */  swc1    $f8, 0x0150($s0)           ## 00000150
/* 01104 80B9C284 8C4D0680 */  lw      $t5, 0x0680($v0)           ## 00000680
.L80B9C288:
/* 01108 80B9C288 2401FFEF */  addiu   $at, $zero, 0xFFEF         ## $at = FFFFFFEF
/* 0110C 80B9C28C 44805000 */  mtc1    $zero, $f10                ## $f10 = 0.00
/* 01110 80B9C290 01A17024 */  and     $t6, $t5, $at              
/* 01114 80B9C294 AC4E0680 */  sw      $t6, 0x0680($v0)           ## 00000680
/* 01118 80B9C298 10000024 */  beq     $zero, $zero, .L80B9C32C   
/* 0111C 80B9C29C E60A0150 */  swc1    $f10, 0x0150($s0)          ## 00000150
.L80B9C2A0:
/* 01120 80B9C2A0 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 01124 80B9C2A4 0C2E6FFE */  jal     func_80B9BFF8              
/* 01128 80B9C2A8 02202825 */  or      $a1, $s1, $zero            ## $a1 = 00000000
/* 0112C 80B9C2AC 10000020 */  beq     $zero, $zero, .L80B9C330   
/* 01130 80B9C2B0 8FBF001C */  lw      $ra, 0x001C($sp)           
/* 01134 80B9C2B4 860F01BC */  lh      $t7, 0x01BC($s0)           ## 000001BC
.L80B9C2B8:
/* 01138 80B9C2B8 24010032 */  addiu   $at, $zero, 0x0032         ## $at = 00000032
/* 0113C 80B9C2BC 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 01140 80B9C2C0 000FC080 */  sll     $t8, $t7,  2               
/* 01144 80B9C2C4 0218C821 */  addu    $t9, $s0, $t8              
/* 01148 80B9C2C8 8F250180 */  lw      $a1, 0x0180($t9)           ## 00000180
/* 0114C 80B9C2CC 14A10005 */  bne     $a1, $at, .L80B9C2E4       
/* 01150 80B9C2D0 00000000 */  nop
/* 01154 80B9C2D4 0C2E7161 */  jal     func_80B9C584              
/* 01158 80B9C2D8 02202825 */  or      $a1, $s1, $zero            ## $a1 = 00000000
/* 0115C 80B9C2DC 10000014 */  beq     $zero, $zero, .L80B9C330   
/* 01160 80B9C2E0 8FBF001C */  lw      $ra, 0x001C($sp)           
.L80B9C2E4:
/* 01164 80B9C2E4 0C00FAE1 */  jal     DynaPolyInfo_GetActor
              ## DynaPolyInfo_getActor
/* 01168 80B9C2E8 262407C0 */  addiu   $a0, $s1, 0x07C0           ## $a0 = 000007C0
/* 0116C 80B9C2EC 1040000C */  beq     $v0, $zero, .L80B9C320     
/* 01170 80B9C2F0 00402025 */  or      $a0, $v0, $zero            ## $a0 = 00000000
/* 01174 80B9C2F4 8C48015C */  lw      $t0, 0x015C($v0)           ## 0000015C
/* 01178 80B9C2F8 31090001 */  andi    $t1, $t0, 0x0001           ## $t1 = 00000000
/* 0117C 80B9C2FC 51200009 */  beql    $t1, $zero, .L80B9C324     
/* 01180 80B9C300 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 01184 80B9C304 0C010D2A */  jal     func_800434A8              
/* 01188 80B9C308 AFA20024 */  sw      $v0, 0x0024($sp)           
/* 0118C 80B9C30C 0C010D4E */  jal     func_80043538              
/* 01190 80B9C310 8FA40024 */  lw      $a0, 0x0024($sp)           
/* 01194 80B9C314 C6100080 */  lwc1    $f16, 0x0080($s0)          ## 00000080
/* 01198 80B9C318 10000004 */  beq     $zero, $zero, .L80B9C32C   
/* 0119C 80B9C31C E6100028 */  swc1    $f16, 0x0028($s0)          ## 00000028
.L80B9C320:
/* 011A0 80B9C320 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
.L80B9C324:
/* 011A4 80B9C324 0C2E7161 */  jal     func_80B9C584              
/* 011A8 80B9C328 02202825 */  or      $a1, $s1, $zero            ## $a1 = 00000000
.L80B9C32C:
/* 011AC 80B9C32C 8FBF001C */  lw      $ra, 0x001C($sp)           
.L80B9C330:
/* 011B0 80B9C330 8FB00014 */  lw      $s0, 0x0014($sp)           
/* 011B4 80B9C334 8FB10018 */  lw      $s1, 0x0018($sp)           
/* 011B8 80B9C338 03E00008 */  jr      $ra                        
/* 011BC 80B9C33C 27BD0030 */  addiu   $sp, $sp, 0x0030           ## $sp = 00000000
