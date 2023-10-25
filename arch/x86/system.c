
#include "system.h"

const char* OK = "OK";
const char* FAILURE = "FAILURE";
const char* WARNING = "WARN";
const char* TEST = "INFO";
const char* ERROR = "ERROR";
uint8 fc;
uint8 g_bg = MAGENTA;

uint16* vga_buffer;

uint32 vga_index;

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

void init_term(uint8 fore_color, uint8 back_color)
{
  vga_buffer = (uint16*)VGA_ADDRESS;
  clear_vga_buffer(&vga_buffer, fore_color, back_color);
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

}

void printchar(char ch, uint8 fore_color, uint8 back_color)
{
    switch(ch)
    {
      case '\n':
        newline();
        break;

      default:
        vga_buffer[vga_index] = vga_entry(ch, fore_color, back_color);
        vga_index++;
        break;
    }
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

    printstring("[", WHITE, g_bg);
    printstring(type, fc, g_bg);
    printstring("] ", WHITE, g_bg);
    printstring(message, WHITE, g_bg);
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

void panic(const char* errorcode)
{
        g_bg = RED;

        init_term(WHITE, g_bg);

        messages(FAILURE, "UNRESOLVED PANIC ");
        printstring(errorcode, WHITE, g_bg);
        vga_index = 80*1;
        const char* message;

        if(strcmp(errorcode, "0x0001") == 0)
        {
            message = "TEST ERRORCODE, THERES NOTHING TO WORRY ABOUT. (RESTART YOUR SYSTEM)";
        }

        else
        {
            message = "UNKNOWN ERRORCODE, PLEASE RESTART YOUR SYSTEM.";
        }

        messages(TEST, message);

        asm volatile ("cli");
        asm volatile ("hlt");
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

void print_uint32(uint32 num, uint8 fore_color, uint8 back_color, BOOL is_signed) {
    char str[11]; // Enough to hold "-2147483648\0"
    uint32_to_string(num, str, is_signed);
    printstring(str, fore_color, back_color);
}
