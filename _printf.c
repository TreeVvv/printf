#include <stdio.h>
#include <stdarg.h>

int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int count = 0;  // Initialize character count to zero

    while (*format != '\0') {
        if (*format == '%') {
            format++;  // Move past '%'

            if (*format == '\0') {
                break;  // Reached the end of the format string
            }

            if (*format == 'c') {
                int c = va_arg(args, int);
                putchar(c);
                count++;
            } else if (*format == 's') {
                const char *s = va_arg(args, const char *);
                if (s == NULL) {
                    s = "(null)";
                }
                while (*s != '\0') {
                    putchar(*s);
                    s++;
                    count++;
                }
            } else if (*format == 'd' || *format == 'i') {
                int num = va_arg(args, int);
                printf("%d", num);
                count++;
            } else if (*format == '%') {
                putchar('%');
                count++;
            } else {
                // Unsupported format specifier, just print it as is
                putchar('%');
                putchar(*format);
                count += 2;
            }
        } else {
            putchar(*format);
            count++;
        }
        format++;
    }

    va_end(args);
    return count;
}

int main() {
    int n = _printf("Hello, %s! The answer is %d.\n", "world", 42);
    printf("Character count: %d\n", n);
    return 0;
}
