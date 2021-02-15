undefined8 __cvmx_helper_rgmii_enable(ulonglong param_1)

{
  undefined4 uVar1;
  uint uVar2;
  undefined8 in_zero;
  undefined8 in_at;
  undefined4 extraout_v0_hi;
  undefined4 extraout_v0_hi_00;
  int iVar6;
  undefined1 *puVar4;
  undefined1 *puVar5;
  longlong lVar7;
  ulonglong uVar8;
  undefined8 extraout_a1;
  longlong lVar9;
  undefined8 extraout_a2;
  longlong lVar10;
  undefined8 extraout_a3;
  ulonglong uVar11;
  undefined8 extraout_t0;
  undefined8 *extraout_t1;
  undefined8 *puVar12;
  undefined8 *extraout_t1_00;
  undefined8 extraout_t1_01;
  undefined8 extraout_t2;
  undefined8 extraout_t2_00;
  undefined8 uVar13;
  undefined8 extraout_t2_01;
  undefined8 extraout_t2_02;
  undefined8 extraout_t3;
  undefined8 extraout_t3_00;
  undefined8 uVar14;
  undefined8 extraout_t3_01;
  undefined8 extraout_t3_02;
  ulonglong uVar15;
  ulonglong uVar16;
  ulonglong uVar17;
  ulonglong uVar3;
  
  iVar6 = cvmx_helper_ports_on_interface(param_1);
  uVar3 = CONCAT44(extraout_v0_hi,iVar6);
  puVar4 = cvmx_sysinfo_get();
  uVar11 = param_1 & 1;
  lVar10 = uVar11 * 0x8000000;
  lVar7 = *(longlong *)(lVar10 + -0x7ffee7fff7fff808);
  setCopReg(2,in_at,*(undefined4 *)(lVar7 + 0x8b));
  if ((((longlong)(int)PRId ^ 0x10d0000U) >> 8 & 0xffff) == 0) {
    uVar1 = getCopReg(2,0);
    *(undefined4 *)(lVar7 + 0x83) = uVar1;
  }
  else {
    if ((((longlong)(int)PRId ^ 0x10d0300U) << 0x28) >> 0x30 == 0) {
      setCopReg(2,in_zero,*(undefined4 *)(lVar7 + -0x92));
      return 0xffffffffffffffff;
    }
  }
  uVar8 = (longlong)(int)~(uint)(-1 << (longlong)iVar6) & 0xf;
  *(ulonglong *)(&DAT_80011800b0000008 + lVar10) = uVar8;
  *(ulonglong *)(&DAT_80011800b0000000 + lVar10) = uVar8;
  if ((longlong)uVar3 < 1) {
    __cvmx_helper_setup_gmx(param_1,uVar3);
  }
  else {
    uVar8 = SEXT48((int)PRId);
    uVar2 = PRId ^ 0xd0000;
    uVar17 = ((longlong)(iVar6 + -1) & 0xffffffffU) + 1;
    lVar7 = uVar11 * 0x10000;
    uVar16 = 0;
    puVar12 = extraout_t1;
    uVar13 = extraout_t2;
    uVar14 = extraout_t3;
    do {
      while( true ) {
        uVar15 = uVar16 & 3;
        lVar10 = (uVar15 + lVar7) * 0x800;
        if ((uVar2 & 0xffff0f) == 0) {
          __cvmx_helper_errata_asx_pass1
                    (param_1,(longlong)(int)uVar16,(longlong)*(int *)(puVar4 + 0x38),
                     &DAT_80011800000000f8,lVar10,puVar12,uVar13,uVar14);
          lVar10 = (uVar15 + lVar7) * 0x800;
          uVar13 = extraout_t2_00;
          uVar14 = extraout_t3_00;
        }
        else {
          *(ulonglong *)(lVar10 + -0x7ffee7fff7ffffe8) =
               *(ulonglong *)(lVar10 + -0x7ffee7fff7ffffe8) & 0x800000000000003f | 0x40;
        }
        lVar9 = (uVar15 + uVar11 * 0x1000000) * 8;
        puVar12 = (undefined8 *)(&DAT_80011800b0000048 + lVar9);
        *(undefined8 *)(lVar10 + -0x7ffee7fff7fffdc8) = 20000;
        *(undefined8 *)(lVar10 + -0x7ffee7fff7fffdb8) = 19000;
        if (((uVar8 ^ 0x10d0600) << 0x28) >> 0x30 == 0) break;
        *puVar12 = 0x18;
        uVar16 = uVar16 + 1;
        *(undefined8 *)(&DAT_80011800b0000020 + lVar9) = 0x18;
        if (uVar16 == uVar17) goto LAB_ffffffff80113638;
      }
      puVar5 = cvmx_sysinfo_get();
      lVar10 = (uVar15 + uVar11 * 0x1000000) * 8;
      if (*(short *)(puVar5 + 0x40) != 0x4e2b) {
        *(undefined8 *)(&DAT_80011800b0000048 + lVar10) = 0x10;
        *(undefined8 *)(&DAT_80011800b0000020 + lVar10) = 0x10;
      }
      uVar16 = uVar16 + 1;
      puVar12 = extraout_t1_00;
      uVar13 = extraout_t2_01;
      uVar14 = extraout_t3_01;
    } while (uVar16 != uVar17);
LAB_ffffffff80113638:
    __cvmx_helper_setup_gmx(param_1,uVar3);
    lVar10 = 0;
    uVar11 = 0;
    do {
      iVar6 = cvmx_helper_get_ipd_port(param_1,(int)lVar10);
      lVar10 = (longlong)((int)lVar10 + 1);
      cvmx_helper_link_autoconf
                (CONCAT44(extraout_v0_hi_00,iVar6),extraout_a1,extraout_a2,extraout_a3,extraout_t0,
                 extraout_t1_01,extraout_t2_02,extraout_t3_02);
      uVar8 = uVar11 & 3;
      uVar11 = uVar11 + 1;
      *(ulonglong *)(&DAT_8001180008000010 + (uVar8 + lVar7) * 0x800) =
           *(ulonglong *)(&DAT_8001180008000010 + (uVar8 + lVar7) * 0x800) & 0xfe00000000000000 | 1;
    } while (lVar10 < (longlong)uVar3);
  }
  return 0;
}
