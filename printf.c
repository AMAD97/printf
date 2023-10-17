#include <stdarg.h>
#include <unistd.h>

int write_char(char c)
{
	return (write(1, &c, 1));
}

int write_str(const char *str)
{
	int len = 0;

	while (str[len] != '\0')
	{
		len++;
	}

	return (write(1, str, len));
}

int write_int(int num)
{
	char buffer[20];

	int len = 0;

	if (num < 0)
	{
		write_char('-');
		num = -num;
		len++;
	}

	int temp = num;

	while (temp > 0)
	{
		temp /= 10;
		len++;
	}

	for (int i = len - 1; i >= 0; i--)
	{
		buffer[i] = '0' + num % 10;
		num /= 10;
	}

	return (write(1, buffer, len));
}

int _printf(const char *format, ...)
{
	va_list args;

	va_start(args, format);

	int chars_written = 0;

	int i = 0;

	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			switch (format[i])
			{
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
			}
		}
		else
		{
			chars_written += write_char(format[i]);
		}

		i++;
	}

	va_end(args);
	return (chars_written);
}
