#ifndef KERNEL_H
#define KERNEL_H

#include "types.h"

#define NULL 0

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

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

uint16* vga_buffer;

uint32 vga_index;
static uint32 next_line_index = 1;

uint8 g_bg = MAGENTA;

uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color)
{
  uint16 ax = 0;
  uint8 ah = 0, al = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color)
{
  uint32 i;
  for(i = 0; i < BUFSIZE; i++){
    (*buffer)[i] = vga_entry(NULL, fore_color, back_color);
  }

  vga_index = 0;
}

void init_term(uint8 fore_color, uint8 back_color)
{
  vga_buffer = (uint16*)VGA_ADDRESS;
  clear_vga_buffer(&vga_buffer, fore_color, back_color);
}

void printchar(char ch, uint8 fore_color, uint8 back_color)
{
    vga_buffer[vga_index] = vga_entry(ch, fore_color, back_color);
    vga_index++;
}

void printstring(const char* str, uint8 fore_color, uint8 back_color)
{
    uint32 index = 0;

    while(str[index])
    {
        printchar(str[index], fore_color, back_color);
        index++;
    }
}

void scroll(uint8 fore_color)
{
    clear_vga_buffer(&vga_buffer, fore_color, g_bg);
    vga_index = 0;
    next_line_index = 0;
}

void newline()
{
    if(next_line_index >= 24)
    {
        scroll(WHITE);
    }

    vga_index = 80*next_line_index;
    next_line_index++;

}

const char* OK = "OK";
const char* FAILURE = "FAILURE";
const char* WARNING = "WARN";
const char* TEST = "INFO";
const char* ERROR = "ERROR";
uint8 fc;

void messages(const char* type, const char* message)
{
    if(type == OK)
    {
        fc = BRIGHT_GREEN;
    }

    if(type == FAILURE)
    {
        fc = BRIGHT_RED;
    }

    if(type == WARNING)
    {
        fc = YELLOW;
    }

    if(type == ERROR)
    {
        fc = BRIGHT_RED;
    }

    if(type == TEST)
    {
        fc = BLUE;
    }

    printstring("[ ", WHITE, g_bg);
    printstring(type, fc, g_bg);
    printstring(" ] ", WHITE, g_bg);
    printstring(message, WHITE, g_bg);
}

#endif
