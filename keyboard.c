#include "isr.h"
#include "monitor.h"
#include "main.h"
#include "keyboard.h"

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

unsigned char upper_kbdus[128] =
{
0,27,'!','@','#','$','%','^','&','&', /* 9 */
'(',')','_','+','\b',/* Backspace */
'\t', /* Tab */
'Q','W','E','R',/* 19 */
'T','Y','U','I','O','P','{','}','\n',/* Enter key */
0,/* 29 - Control */
'A','S','D','F','G','H','J','K','L',':',/* 39 */
'\"','~',90,/* Left shift */
'|','Z','X','C','V','B','N',/* 49 */
'M','<','>','?',91,/* Right shift */
'*',
0, /* Alt */
' ', /* Space bar */
0, /* Caps lock */
0, /* 59 - F1 key ... > */
0, 0, 0, 0, 0, 0, 0, 0,
0, /* < ... F10 */
0, /* 69 - Num lock*/
0, /* Scroll Lock */
0, /* Home key */
0, /* Up Arrow */
0, /* Page Up */
'-',
0, /* Left Arrow */
0,
0, /* Right Arrow */
'+',
0, /* 79 - End key*/
0, /* Down Arrow */
0, /* Page Down */
0, /* Insert Key */
0, /* Delete Key */
0, 0, 0,
0, /* F11 Key */
0, /* F12 Key */
0, /* All other keys are undefined */
};

static unsigned char command[255];
static u8int i = 0;

void print_linehead() {
	set_forecolor(11);
	monitor_write("[BerkinOS]$ ");
	set_forecolor(15);
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
		monitor_write("BerkinOS version 1.1\r\n");
		reset_command();
	}
	else if(strstr(com, "showtime") != 0) {
		showtimer();
		reset_command();
	}
	else if(strstr(com, "hidetime") != 0) {
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
	else if(strstr(com, "settime") != 0) {
		if(com[7] != ' ' || com[10] != ' ' || com[13] != ' ') {
		    monitor_write("Usage: settime hh mm ss\r\n");
		    reset_command();
		    return;
		}
		u32int h = (com[8] - '0') * 10;
		h += com[9] - '0';
		//monitor_write_dec(h);
		u32int m = (com[11] - '0') * 10;
		m += com[12] - '0';
		//monitor_write_dec(m);
		u32int s = (com[14] - '0') * 10;
		s += com[15] - '0';
		//monitor_write_dec(s);
		changetime(h, m, s);
		monitor_write("Time has been set to ");
		monitor_write_dec(h);
		monitor_write(":");
		monitor_write_dec(m);
		monitor_write(":");
		monitor_write_dec(s);
		monitor_write("\r\n");
		reset_command();
	}
	else if(strstr(com, "fixtime") != 0) {
		updatetimer();
		reset_command();
	}
	else if(strstr(com, "help") != 0) {
		monitor_write("Available commands: help, version, showtime, hidetime, settime, fixtime, reboot\r\n");
		reset_command();
	}
	else {
		monitor_write("Command '");
		monitor_write(com);
		monitor_write("' not found. Type \"help\" for a list of available commands.\r\n");
		reset_command();
	}
}

u8int is_shift = 0;

static void keyboard_handler(registers_t regs)
{
	unsigned char scancode;
	scancode = inb(0x60);
	
	if(((scancode&0x7f) == 0x2a) || ((scancode&0x7f) == 0x36)) {
	  if((scancode & 0x80) == 0)
	    is_shift = 1;
	  else
	    is_shift = 0;
	    return;
	}
	
	if((scancode & 0x80) == 0) {
	  if(is_shift != 0) {
	    monitor_put(upper_kbdus[scancode]);
	    makecommand(upper_kbdus[scancode]);
	  }
	  else {
	    monitor_put(kbdus[scancode]);
	    makecommand(kbdus[scancode]);
	  }
	}
}

void makecommand(unsigned char key) {
  switch(key) {
    case '\b':
      command[--i] = '\0';
      break;
    case '\n':
      run(command);
      break;
    default:
      command[i++] = key;
  }
}

void install_keyboard()
{
	register_interrupt_handler(IRQ1, &keyboard_handler);
	reset_command();
}
