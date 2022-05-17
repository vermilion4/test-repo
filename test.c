#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int print_char(va_list c)
{
    char ch;

    ch = va_arg(c, int);
    return (write(1, &ch, 1));
}

int print_string(va_list s)
{
    char *str;

    str = va_arg(s, char *);
    if (str == NULL)
        str = "(null)";
    return (write(1, str, strlen(str)));
}

int print_int(va_list i)
{
    char *str;
    int a = va_arg(i, int);
    int j = 0;
    int k = 0;

    if (a < 0)
    {
        j = 1;
        a = -a;
    }
    str = malloc(sizeof(char) * 12);
    if (str == NULL)
        return (-1);
    while (a > 0)
    {
        str[k] = a % 10 + '0';
        a = a / 10;
        k++;
    }
    if (j == 1)
        str[k] = '-';
    else
    k--;
    k++;
    str[k] = '\0';
    k--;
    while (k >= 0)
    {
        write(1, &str[k], 1);
        k--;
    }
    free(str);
    return (0);
    
}

int print_unint(va_list u)
{
    char *str;
    unsigned int a = va_arg(u, unsigned int);
    int k = 0;

    str = malloc(sizeof(char) * 12);
    if (str == NULL)
        return (-1);
    while (a > 0)
    {
        str[k] = a % 10 + '0';
        a = a / 10;
        k++;
    }
    str[k] = '\0';
    k--;
    while (k >= 0)
    {
        write(1, &str[k], 1);
        k--;
    }
    free(str);
    return (0);
}

int print_octal(va_list o)
{
    char *str;
    unsigned int a = va_arg(o, unsigned int);
    int j = 0;
    int k = 0;

    str = malloc(sizeof(char) * 12);
    if (str == NULL)
        return (-1);
    while (a > 0)
    {
        str[k] = a % 8 + '0';
        a = a / 8;
        k++;
    }
    str[k] = '\0';
    k--;
    while (k >= 0)
    {
        write(1, &str[k], 1);
        k--;
    }
    free(str);
    return (0);
}

int print_hex(va_list h)
{
    char *str;
    unsigned int a = va_arg(h, unsigned int);
    int k = 0;

    str = malloc(sizeof(char) * 12);
    if (str == NULL)
        return (-1);
    while (a > 0)
    {
        if (a % 16 < 10)
            str[k] = a % 16 + '0';
        else
            str[k] = a % 16 + 'a' - 10;
        a = a / 16;
        k++;
    }
    str[k] = '\0';
    k--;
    while (k >= 0)
    {
        write(1, &str[k], 1);
        k--;
    }
    free(str);
    return (0);
}

int print_address(va_list a)
{
    char *str;
    unsigned int b = va_arg(a, unsigned int);
    int k = 0;

    str = malloc(sizeof(char) * 12);
    if (str == NULL)
        return (-1);
    while (b > 0)
    {
        if (b % 16 < 10)
            str[k] = b % 16 + '0';
        else
            str[k] = b % 16 + 'A' - 10;
        b = b / 16;
        k++;
    }
    str[k] = '\0';
    k--;
    while (k >= 0)
    {
        write(1, &str[k], 1);
        k--;
    }
    free(str);
    return (0);
}



int _printf(const char *format, ...)
{
    va_list args;
    int i;
    int (*f[8])(va_list);

    f[0] = &print_char;
    f[1] = &print_string;
    f[2] = &print_int;
    f[3] = &print_unint;
    f[4] = &print_octal;
    f[5] = &print_hex;
    f[6] = &print_address;
    f[7] = NULL;
    va_start(args, format);
    i = 0;

    while (format[i])
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == 'c')
                f[0](args);
            else if (format[i] == 's')
                f[1](args);
            else if (format[i] == 'd' || format[i] == 'i')
                f[2](args);
            else if (format[i] == 'u')
                f[3](args);
            else if (format[i] == 'o')
                f[4](args);
            else if (format[i] == 'x' || format[i] == 'X')
                f[5](args);
            else if (format[i] == 'p')
                f[6](args);
            else if (format[i] == '%')
                write(1, "%", 1);
            else if (format[i] == 'a' || format[i] == 'b' || format[i] == 'e' || format[i] == 'f' || format[i] == 'g' || format[i] == 'n' || format[i] == 'r' || format[i] == 's' || format[i] == 't')
            {
                write(1, "%", 1);
                write(1, &format[i], 1);
            }

            else
                f[0](args);
        }
        else
            write(1, &format[i], 1);
        i++;
    }

    va_end(args);
    return (i);

}
