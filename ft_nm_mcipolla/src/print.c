#include <ft_nm.h>

static inline void print_s(const char *s, int fd)
{
    write(fd, s, ft_strlen(s));
}

static inline void print_d(long int x, int fd)
{
    char *s = ft_itoa(x, 10);
    write(fd, s, ft_strlen(s));
}

static inline void print_x(unsigned int x, int fd)
{
    char *s = ft_itoa(x, 16);
    write(fd, s, ft_strlen(s));
}

static inline void print_c(char c, int fd)
{
    write(fd, &c, 1);
}

int ft_fprintf(int fd, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int is_zero = 0;
    int length = 0;

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 's': print_s(va_arg(args, const char *), fd); break;
                case 'd': print_d(va_arg(args, long int), fd); break;
                case 'x': print_x(va_arg(args, unsigned int), fd); break;
                case 'c': print_c(va_arg(args, int), fd); break;
                case '%': write(fd, "%", 1); break;
                case '0': is_zero = 1; break;
            }
            fmt++;
            while (*fmt >= '0' && *fmt <= '9') {
                length *= 10;
                length += (*fmt - 48);
                fmt++;
            }
            if (length > 0) {
                char *s = ft_itoa(va_arg(args, unsigned int), 16);
                length -= ft_strlen(s);
                char c = is_zero ? '0' : ' ';
                while (length > 0) {
                    write(fd, &c, 1);
                    length--;
                }
                write(fd, s, ft_strlen(s));
                fmt++;
            }
        } else {
            write(fd, fmt, 1);
            fmt++;
        }
        is_zero = 0;
        length = 0;
    }

    va_end(args);
    return fd - 1;
}
