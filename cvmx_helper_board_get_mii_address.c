/*
Decompiled using ghidra
*/

ulonglong cvmx_helper_board_get_mii_address(ulonglong param_1)

{
  ushort uVar1;
  undefined4 extraout_v0_hi;
  undefined1 *puVar2;
  undefined4 uVar4;
  undefined8 extraout_a2;
  undefined8 extraout_a3;
  undefined8 extraout_t0;
  undefined8 extraout_t1;
  undefined8 extraout_t2;
  undefined8 extraout_t3;
  int iVar6;
  ulonglong uVar5;
  undefined4 auStack32 [2];
  int local_18;
  longlong lVar3;
  
  puVar2 = cvmx_sysinfo_get();
  uVar1 = *(ushort *)(puVar2 + 0x40);
  iVar6 = (int)param_1;
  if (uVar1 < 0x11) {
    if ((uVar1 < 0xf) && (uVar1 != 6)) {
      if (6 < uVar1) {
        if (uVar1 < 0xd) {
          if (8 < uVar1) goto LAB_ffffffff80110c9c;
          if (uVar1 == 8) {
            return 0xffffffffffffffff;
          }
        }
        else {
          if (uVar1 == 0xe) {
LAB_ffffffff80110c9c:
            sofaware_get_octeon_eth_port_desc(param_1,auStack32);
            return (longlong)local_18;
          }
        }
LAB_ffffffff80110ba8:
        puVar2 = cvmx_sysinfo_get();
        printk("cvmx_helper_board_get_mii_address: Unknown board type %d\n",
               (ulonglong)*(ushort *)(puVar2 + 0x40),extraout_a2,extraout_a3,extraout_t0,extraout_t1
               ,extraout_t2,extraout_t3);
        return 0xffffffffffffffff;
      }
      if (uVar1 != 2) {
        if (uVar1 < 3) {
          if (uVar1 == 1) {
            return 0xffffffffffffffff;
          }
        }
        else {
          if (uVar1 == 3) goto LAB_ffffffff80110c9c;
          if (uVar1 == 5) {
            if (param_1 < 4) {
              return param_1;
            }
            if (3 < iVar6 - 0x10U) {
              return 0xffffffffffffffff;
            }
            return (longlong)(iVar6 + -0xc);
          }
        }
        goto LAB_ffffffff80110ba8;
      }
    }
    if ((ulonglong)(longlong)(iVar6 + -0x10) < 4) {
      return (longlong)(iVar6 + -0x10);
    }
  }
  else {
    if (uVar1 == 0x15) {
      if (3 < iVar6 - 0x10U) {
        return 0xffffffffffffffff;
      }
      return (longlong)(iVar6 + -0xf);
    }
    if (uVar1 < 0x16) {
      if (uVar1 == 0x13) {
LAB_ffffffff80110c6c:
        if (3 < param_1) {
          return 0xffffffffffffffff;
        }
        return (longlong)(iVar6 + 2);
      }
      if (uVar1 < 0x14) {
        if (3 < param_1) {
          return 0xffffffffffffffff;
        }
        return (longlong)(iVar6 + 1);
      }
    }
    else {
      if (uVar1 == 0x1e) goto LAB_ffffffff80110c9c;
      if (uVar1 < 0x1f) {
        if (uVar1 - 0x17 < 2) goto LAB_ffffffff80110c6c;
        goto LAB_ffffffff80110ba8;
      }
      if (uVar1 == 0x2713) {
        uVar5 = 4;
      }
      else {
        if (uVar1 != 0x4e2b) goto LAB_ffffffff80110ba8;
        if (param_1 == 0) {
          uVar4 = is_dsl_board();
          lVar3 = CONCAT44(extraout_v0_hi,uVar4);
          special2(lVar3,lVar3,0,0x3a);
          if (lVar3 != 0) {
            return 0xffffffffffffffff;
          }
          return 0xc;
        }
        if (param_1 == 1) {
          return 0xffffffffffffffff;
        }
        uVar5 = 0xd;
      }
      if (param_1 == 2) {
        return uVar5;
      }
    }
  }
  return 0xffffffffffffffff;
}

