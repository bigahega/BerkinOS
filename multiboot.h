/* multiboot.h - the header for Multiboot */
/* Copyright (C) 1999, 2001  Free Software Foundation, Inc.
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#ifndef __MULTIBOOT_H__
#define __MULTIBOOT_H__


/*
 * Multiboot header structure.
 */
#define MULTIBOOT_HEADER_MAGIC         0x1BADB002
#define MULTIBOOT_HEADER_MODS_ALIGNED  0x00000001
#define MULTIBOOT_HEADER_WANT_MEMORY   0x00000002
#define MULTIBOOT_HEADER_HAS_VBE       0x00000004
#define MULTIBOOT_HEADER_HAS_ADDR      0x00010000

/* The magic number passed by a Multiboot-compliant boot loader. */
#define MULTIBOOT_BOOTLOADER_MAGIC     0x2BADB002

#define MBI_MEMLIMITS  (1<<0)
#define MBI_DRIVES     (1<<1)
#define MBI_CMDLINE    (1<<2)
#define MBI_MODULES    (1<<3)
#define MBI_AOUT_SYMS  (1<<4)
#define MBI_ELF_SYMS   (1<<5)
#define MBI_MEMMAP     (1<<6)
#define MBI_LOADERNAME (1<<9)

#ifndef __ASSEMBLY__

/* The symbol table for a.out.  */
typedef struct {
    u32int tabsize;
    u32int strsize;
    u32int addr;
    u32int reserved;
} aout_symbol_table_t;

/* The section header table for ELF.  */
typedef struct {
    u32int num;
    u32int size;
    u32int addr;
    u32int shndx;
} elf_section_header_table_t;

/* The Multiboot information.  */
typedef struct {
    u32int flags;

    /* Valid if flags sets MBI_MEMLIMITS */
    u32int mem_lower;
    u32int mem_upper;

    /* Valid if flags sets MBI_DRIVES */
    u32int boot_device;

    /* Valid if flags sets MBI_CMDLINE */
    u32int cmdline;

    /* Valid if flags sets MBI_MODULES */
    u32int mods_count;
    u32int mods_addr;

    /* Valid if flags sets ... */
    union {
        aout_symbol_table_t aout_sym;        /* ... MBI_AOUT_SYMS */
        elf_section_header_table_t elf_sec;  /* ... MBI_ELF_SYMS */
    } u;

    /* Valid if flags sets MBI_MEMMAP */
    u32int mmap_length;
    u32int mmap_addr;
} multiboot_info_t;

/* The module structure.  */
typedef struct {
    u32int mod_start;
    u32int mod_end;
    u32int string;
    u32int reserved;
} module_t;

/* The memory map. Be careful that the offset 0 is base_addr_low
   but no size.  */
typedef struct {
    u32int size;
    u32int base_addr_low;
    u32int base_addr_high;
    u32int length_low;
    u32int length_high;
    u32int type;
} memory_map_t;


#endif /* __ASSEMBLY__ */

#endif /* __MULTIBOOT_H__ */
