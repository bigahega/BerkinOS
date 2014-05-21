#include "cmos.h"

unsigned char read_cmos(unsigned char address)
{
	unsigned char data;
	outb(CMOS_ADDREG, address);
	data = inb(CMOS_DATAREG);
	return data;
}

void write_cmos(unsigned char address, unsigned int data)
{
	outb(CMOS_ADDREG, address);
	outb(CMOS_DATAREG, NMI_disable_bit << 7 | data);
}
