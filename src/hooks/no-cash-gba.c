#include "global.h"
#include "common-chax.h"
#include <stdarg.h>

#define NOCASHGBAPRINTADDR 0x4FFFA18

static char *AppendUnsigned(char *dst, char *end, unsigned int value, unsigned int base, int uppercase)
{
	char tmp[16];
	unsigned int len = 0;

	do {
		unsigned int digit = value % base;
		tmp[len++] = (char)(digit < 10 ? '0' + digit : (uppercase ? 'A' : 'a') + (digit - 10));
		value /= base;
	} while (value != 0 && len < sizeof(tmp));

	while (len > 0 && dst < end) {
		*dst++ = tmp[--len];
	}

	return dst;
}

static char *AppendSigned(char *dst, char *end, int value)
{
	unsigned int magnitude;

	if (value < 0) {
		if (dst < end)
			*dst++ = '-';
		magnitude = (unsigned int)(-(value + 1)) + 1;
		return AppendUnsigned(dst, end, magnitude, 10, 0);
	}

	return AppendUnsigned(dst, end, (unsigned int)value, 10, 0);
}

void NoCashGBAPrint(const char *pBuf)
{
	*(volatile u32 *)NOCASHGBAPRINTADDR = (u32)pBuf;
}

void NoCashGBAPrintf(const char *pBuf, ...)
{
	char bufPrint[0x100];
	char *out = bufPrint;
	char *end = bufPrint + sizeof(bufPrint) - 1;
	const char *fmt = pBuf;
	va_list vArgv;

	va_start(vArgv, pBuf);
	while (*fmt != '\0' && out < end) {
		if (*fmt != '%') {
			*out++ = *fmt++;
			continue;
		}

		fmt++;
		if (*fmt == '\0')
			break;

		switch (*fmt) {
		case '%':
			*out++ = '%';
			break;
		case 'd':
		case 'i':
			out = AppendSigned(out, end, va_arg(vArgv, int));
			break;
		case 'u':
			out = AppendUnsigned(out, end, va_arg(vArgv, unsigned int), 10, 0);
			break;
		case 'x':
			out = AppendUnsigned(out, end, va_arg(vArgv, unsigned int), 16, 0);
			break;
		case 'X':
			out = AppendUnsigned(out, end, va_arg(vArgv, unsigned int), 16, 1);
			break;
		case 'c':
			*out++ = (char)va_arg(vArgv, int);
			break;
		case 's':
		{
			const char *str = va_arg(vArgv, const char *);

			if (str != NULL) {
				while (*str != '\0' && out < end)
					*out++ = *str++;
			}
			break;
		}
		default:
			*out++ = '%';
			if (out < end)
				*out++ = *fmt;
			break;
		}

		fmt++;
	}
	*out = '\0';
	va_end(vArgv);
	NoCashGBAPrint(bufPrint);
}
