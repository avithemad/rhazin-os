#ifndef MULTIBOOT_H
#define MULTIBOOT_H
#include<stdint.h>
typedef unsigned char           multiboot_uint8_t;
typedef unsigned short          multiboot_uint16_t;
typedef unsigned int            multiboot_uint32_t;
typedef unsigned long long      multiboot_uint64_t;

#define MULTIBOOT_HEADER_MAGIC 0x1BADB002
#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

/* The symbol table for a.out. */
struct multiboot_aout_symbol_table
{
  multiboot_uint32_t tabsize;
  multiboot_uint32_t strsize;
  multiboot_uint32_t addr;
  multiboot_uint32_t reserved;
};
typedef struct multiboot_aout_symbol_table multiboot_aout_symbol_table_t;

/* The section header table for ELF. */
struct multiboot_elf_section_header_table
{
  multiboot_uint32_t num;
  multiboot_uint32_t size;
  multiboot_uint32_t addr;
  multiboot_uint32_t shndx;
};
typedef struct multiboot_elf_section_header_table multiboot_elf_section_header_table_t;

struct multiboot_info
{
  /* Multiboot info version number */
  multiboot_uint32_t flags;

  /* Available memory from BIOS */
  multiboot_uint32_t mem_lower;
  multiboot_uint32_t mem_upper;

  /* "root" partition */
  multiboot_uint32_t boot_device;

  /* Kernel command line */
  multiboot_uint32_t cmdline;

  /* Boot-Module list */
  multiboot_uint32_t mods_count;
  multiboot_uint32_t mods_addr;

  union
  {
    multiboot_aout_symbol_table_t aout_sym;
    multiboot_elf_section_header_table_t elf_sec;
  } u;

  /* Memory Mapping buffer */
  multiboot_uint32_t mmap_length;
  multiboot_uint32_t mmap_addr;

  /* Drive Info buffer */
  multiboot_uint32_t drives_length;
  multiboot_uint32_t drives_addr;

  /* ROM configuration table */
  multiboot_uint32_t config_table;

  /* Boot Loader Name */
  multiboot_uint32_t boot_loader_name;

  /* APM table */
  multiboot_uint32_t apm_table;

  /* Video */
  multiboot_uint32_t vbe_control_info;
  multiboot_uint32_t vbe_mode_info;
  multiboot_uint16_t vbe_mode;
  multiboot_uint16_t vbe_interface_seg;
  multiboot_uint16_t vbe_interface_off;
  multiboot_uint16_t vbe_interface_len;

  multiboot_uint64_t framebuffer_addr;
  multiboot_uint32_t framebuffer_pitch;
  multiboot_uint32_t framebuffer_width;
  multiboot_uint32_t framebuffer_height;
  multiboot_uint8_t framebuffer_bpp;
#define MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED 0
#define MULTIBOOT_FRAMEBUFFER_TYPE_RGB     1
#define MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT     2
  multiboot_uint8_t framebuffer_type;
  union
  {
    struct
    {
      multiboot_uint32_t framebuffer_palette_addr;
      multiboot_uint16_t framebuffer_palette_num_colors;
    };
    struct
    {
      multiboot_uint8_t framebuffer_red_field_position;
      multiboot_uint8_t framebuffer_red_mask_size;
      multiboot_uint8_t framebuffer_green_field_position;
      multiboot_uint8_t framebuffer_green_mask_size;
      multiboot_uint8_t framebuffer_blue_field_position;
      multiboot_uint8_t framebuffer_blue_mask_size;
    };
  };
};
struct multiboot_mmap_entry
{
  multiboot_uint32_t size;
  multiboot_uint32_t addr_low;
  multiboot_uint32_t addr_high;
  multiboot_uint32_t len_low;
  multiboot_uint32_t len_high;
#define MULTIBOOT_MEMORY_AVAILABLE              1
#define MULTIBOOT_MEMORY_RESERVED               2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE       3
#define MULTIBOOT_MEMORY_NVS                    4
#define MULTIBOOT_MEMORY_BADRAM                 5
  multiboot_uint32_t type;
} __attribute__((packed));
typedef struct multiboot_mmap_entry multiboot_memory_map_t;

#endif