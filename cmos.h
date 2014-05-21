#include "common.h"

#define CMOS_ADDREG 0x70
#define CMOS_DATAREG 0x71
#define NMI_disable_bit 0x80

#define BCD2BIN(bcd) ((((bcd) & 15) + ((bcd) >> 4) * 10))

unsigned char read_cmos(unsigned char address);
void write_cmos(unsigned char address, unsigned int data);
