#include <unistd.h>
#include <stdarg.h>
#include "main.h"

int write_char(char c) {
    return (write(1, &c, 1));
}

int write_str(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return (write(1, str, len));
}

int write_int(int num)
{
    char buffer[20];
    int len = 0;
    int i = 0;
    int start, end;
    if (num < 0)
    {
        write_char('-');
        num = -num;
        len++;
    }
    else if (num == 0)
    {
        write_char('0');
        return 1;
    }

    while (num > 0)
    {
        buffer[i] = '0' + num % 10;
        num /= 10;
        i++;
        len++;
    }
    start = 0;
    end = i - 1; 
    while (start < end)
    {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }

    buffer[i] = '\0';

    return (write(1, buffer, len));
}

int _printf(const char *format, ...) {
    int chars_written = 0;
    int i = 0;
    va_list args;
    va_start(args, format);

    while (format[i] != '\0') {
        if (format[i] == '%') {
            i++;
            switch (format[i]) {
                case 'c':
                    chars_written += write_char(va_arg(args, int));
                    break;
                case 's':
                    chars_written += write_str(va_arg(args, char *));
                    break;
                case '%':
                    chars_written += write_char('%');
                    break;
                case 'i':
                case 'd':
                    chars_written += write_int(va_arg(args, int));
                    break;
                default:
                    write(1, "Invalid format specifier", 23);
                    chars_written += 23;
                    break;
            }
        } else {
            chars_written += write_char(format[i]);
        }
        i++;
    }

    va_end(args);
    return chars_written;
}


