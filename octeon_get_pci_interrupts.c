char * octeon_get_pci_interrupts(void)

{
  ushort uVar1;
  
  uVar1 = *(ushort *)(octeon_bootinfo + 0x50);
  if (0xc < uVar1) {
    if (uVar1 == 0x14) {
      return "AABCD";
    }
    if (uVar1 != 0x4e2b) {
      return "";
    }
    return "ABA";
  }
  if (uVar1 < 0xb) {
    if (uVar1 == 5) {
      return "AAAAADABAAAAAAAAAAAAAAAAAAAAAAAA";
    }
    if (uVar1 != 9) {
      return "";
    }
  }
  return "AAABAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
}
