
#include "stdio.h"

const char* OK = " OK ";
const char* FAILURE = "FATAL";
const char* WARNING = "WARN";
const char* TEST = "INFO";
const char* ERROR = "ERROR";
uint8 fc;
uint8 g_bg = CYAN;
uint8 g_fg = WHITE;

uint16* vga_buffer;

uint32 vga_index;

static int cursor_x = 0;
static int cursor_y = 0;

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
  next_line_index = 0;
}

void disable_cursor()
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void enable_cursor(uint8 cursor_start, uint8 cursor_end)
{
    outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void update_cursor(int x, int y)
{
    uint16 pos = y * 80 + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8) ((pos >> 8) & 0xFF));
}

void init_term(uint8 fore_color, uint8 back_color)
{
    vga_buffer = (uint16*)VGA_ADDRESS;
    clear_vga_buffer(&vga_buffer, fore_color, back_color);

    enable_cursor(0, 28);
    update_cursor(cursor_x, cursor_y);
}

void scroll(uint8 fore_color)
{
    clear_vga_buffer(&vga_buffer, fore_color, g_bg);
    vga_index = 0;
    next_line_index = 1;
}

void newline()
{
    if(next_line_index >= 24)
    {
        scroll(WHITE);
    }

    vga_index = 80*next_line_index;
    next_line_index++;
    cursor_y++;
}

void printchar(char ch, uint8 fore_color, uint8 back_color)
{
    switch(ch)
    {
      case '\n':
        newline();
        break;

      case '\t':
        newline();
        newline();
        break;

      default:
        vga_buffer[vga_index] = vga_entry(ch, fore_color, back_color);
        vga_index++;
        break;
    }

    cursor_x++;
    update_cursor(cursor_x, cursor_y - 2);
}

void printf(const char* str)
{
    uint32 index = 0;

    while(str[index])
    {
        printchar(str[index], g_fg, g_bg);
        index++;

        if(index >= 30)
            cursor_y++;
            cursor_x = 0;

        cursor_x = index - 1;
    }
}

void log(const char* type, const char* message)
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

    g_fg = fc;

    printf("[");
    printf(type);
    printf("] ");

    g_fg = WHITE;

    printf(message);
}

void outb(uint16 port, uint8 value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a"(value));
}


uint8 inb(uint16 port)
{
   uint8 ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

uint16 inw(uint16 port)
{
   uint16 ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

void memcpy(uint8 *dest, const uint8 *src, uint32 len)
{
    const uint8 *sp = (const uint8 *)src;
    uint8 *dp = (uint8 *)dest;
    for(; len != 0; len--) *dp++ = *sp++;
}

// Write len copies of val into dest.
void memset(uint8 *dest, uint8 val, uint32 len)
{
    uint8 *temp = (uint8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

int strcmp(const char* str1, const char* str2) {
    while (*str1 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *(uint8*)str1 - *(uint8*)str2;
}

void uint32_to_string(uint32 num, char* str, BOOL is_signed) {
    uint32 temp = num;
    int i = 0;

    if (num == 0) {
        str[i++] = '0';
    } else {
        if (is_signed && num & 0x80000000) {
            str[i++] = '-';  // Handle signed numbers
            temp = ~num + 1; // Two's complement for negative numbers
        }

        while (temp != 0) {
            str[i++] = '0' + (temp % 10);
            temp /= 10;
        }
    }

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string
    int len = i;
    for (int j = 0; j < len / 2; j++) {
        char temp = str[j];
        str[j] = str[len - j - 1];
        str[len - j - 1] = temp;
    }
}

void print_uint32(uint32 num, BOOL is_signed) {
    char str[11]; // Enough to hold "-2147483648\0"
    uint32_to_string(num, str, is_signed);
    printf(str);
}

void io_wait()
{
    outb(UNUSED_PORT, 0);
}

void resetfg()
{
    g_fg = WHITE;
}