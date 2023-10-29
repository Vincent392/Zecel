#ifndef KERNEL_H
#define KERNEL_H

#include "types.h"

#define NULL 0
#define ASMCALL __attribute__((cdecl))
#define UNUSED_PORT 0x80

enum vga_color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE,
};

typedef enum {
    FALSE,
    TRUE
} BOOL;

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

static uint32 next_line_index = 1;

extern const char* OK;
extern const char* FAILURE;
extern const char* WARNING;
extern const char* TEST;
extern const char* ERROR;
extern uint8 fc;
extern uint8 g_bg;
extern uint8 g_fg;

uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color);

void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color);

void init_term(uint8 fore_color, uint8 back_color);

void scroll(uint8 fore_color);

void newline();

void printchar(char ch, uint8 fore_color, uint8 back_color);

void printf(const char* str);

void messages(const char* type, const char* message);

void outb(uint16 port, uint8 value);


uint8 inb(uint16 port);

uint16 inw(uint16 port);

void io_wait();

void memcpy(uint8 *dest, const uint8 *src, uint32 len);

// Write len copies of val into dest.
void memset(uint8 *dest, uint8 val, uint32 len);

int strcmp(const char* str1, const char* str2);

void print_uint32(uint32 num, BOOL is_signed);

#endif
