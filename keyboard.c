#include "isr.h"
#include "monitor.h"
#include "main.h"

unsigned char kbdus[128] =
{
    0,  '"', '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '*', '-', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', 'g', 'u', '\n',		/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 's',	/* 39 */
 'i', '`',   0,		/* Left shift */
 ',', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', 'o', 'c', '.',   0,					/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

static unsigned char command[255];
static u8int i = 0;

void print_linehead() {
	monitor_write("[BerkinOS]$ ");
}

void reset_command() {
	i = 0;
	while(i < 255)
		command[i++] = '\0';
	i = 0;
	print_linehead();
}

void run(char* com) {
	if(strstr(com, "version") != 0) {
		monitor_write("BerkinOS version 1.0\r\n");
		reset_command();
	}
	else if(strstr(com, "showtimer") != 0) {
		showtimer();
		reset_command();
	}
	else if(strstr(com, "hidetimer") != 0) {
		hidetimer();
		reset_command();
	}
	else if(strstr(com, "reboot") != 0) {
		u8int good = 0x02;
		while(good & 0x02)
			good = inb(0x64);
		outb(0x64, 0xFE);
		asm volatile ("hlt");
	}
	else if(strstr(com, "chgtimer") != 0) {
		u32int h = (com[9] - '0') * 10;
		h += com[10] - '0';
		//monitor_write_dec(h);
		u32int m = (com[12] - '0') * 10;
		m += com[13] - '0';
		//monitor_write_dec(m);
		u32int s = (com[15] - '0') * 10;
		s += com[16] - '0';
		//monitor_write_dec(s);
		changetime(h, m, s);
		reset_command();
	}
	else if(strstr(com, "updatetimer") != 0) {
		updatetimer();
		reset_command();
	}
	else {
		monitor_write("Command '");
		monitor_write(com);
		monitor_write("' not found.\r\n");
		reset_command();
	}
}

static void keyboard_handler(registers_t regs)
{
	unsigned char scancode;
	scancode = inb(0x60);
	if(scancode & 0x80) {
	}
	else {
		monitor_put(kbdus[scancode]);
		if(kbdus[scancode] == '\n') {
			run(command);
		}
		else
			command[i++] = kbdus[scancode];
	}
}

void install_keyboard()
{
	register_interrupt_handler(IRQ1, &keyboard_handler);
	reset_command();
}
