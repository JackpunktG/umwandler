#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void print_binary(long n)
{

    printf("Binary: ");
    if (n == 0)
    {
        printf("0\n");
        return;
    }
    if (n < 0)
    {
        putchar('-');
        n = -n;
    }
    int started = 0;
    for (int i = sizeof(n) * 8 - 1; i >= 0; i--)
    {
        if (n & (1L << i))
        {
            started = 1;
            putchar('1');
        }
        else if (started)
        {
            putchar('0');
        }
    }
    printf("\n");
}

void print_binary_uint128(__uint128_t n)
{
    printf("Binary: ");

    int started = 0;
    for (int i = 127; i >= 0; i--)
    {
        if (n & ((__uint128_t)1 << i))
        {
            putchar('1');
            started = 1;
        }
        else if (started)
        {
            putchar('0');
        }
    }
    if (!started)
        putchar('0');

    printf("\n");
}

void print_hex_uint128(__uint128_t n)
{
    unsigned long long high = (unsigned long long)(n >> 64);
    unsigned long long low = (unsigned long long)(n & 0xFFFFFFFFFFFFFFFFULL);
    if (high)
        printf("Hexa: %llx%016llx\n", high, low);
    else
        printf("Hexa :%llx\n", low);
}

__uint128_t string_to_uint128(const char *str)
{
    __uint128_t result = 0;
    while (*str)
    {
        if (*str >= '0' && *str <= '9')
        {
            result = result * 10 + (*str - '0');
        }
        str++;
    }
    return result;
}

__uint128_t binary_string_to_uint128(const char *str)
{
    __uint128_t result = 0;
    // Skip "0b" or "0B" prefix if present
    if (str[0] == '0' && (str[1] == 'b' || str[1] == 'B'))
    {
        str += 2;
    }
    while (*str)
    {
        if (*str == '0' || *str == '1')
        {
            result = (result << 1) + (*str - '0');
        }
        str++;
    }
    return result;
}

__uint128_t hex_string_to_uint128(const char *str)
{
    __uint128_t result = 0;
    // Skip "0x" or "0X" prefix if present
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        str += 2;
    }
    while (*str)
    {
        result <<= 4; // Multiply by 16
        if (*str >= '0' && *str <= '9')
        {
            result += *str - '0';
        }
        else if (*str >= 'A' && *str <= 'F')
        {
            result += *str - 'A' + 10;
        }
        else if (*str >= 'a' && *str <= 'f')
        {
            result += *str - 'a' + 10;
        }
        str++;
    }
    return result;
}

void print_uint128(__uint128_t n)
{

    printf("Decimal: ");
    if (n == 0)
    {
        putchar('0');
        return;
    }

    char buffer[40]; // 128-bit max is about 39 digits
    int pos = 0;

    // Extract digits in reverse order
    while (n > 0)
    {
        buffer[pos++] = '0' + (n % 10);
        n /= 10;
    }

    // Print digits in correct order
    for (int i = pos - 1; i >= 0; i--)
    {
        putchar(buffer[i]);
    }
    printf("\n");
}

void print_umwandlung(char *number, char option)
{

    switch (option)
    {
    case 'b':
        __uint128_t n = binary_string_to_uint128(number);
        print_uint128(n);
        print_hex_uint128(n);
        break;
    case 'h':
        __uint128_t h = hex_string_to_uint128(number);
        print_uint128(h);
        print_binary_uint128(h);
        break;
    default:
        __uint128_t d = string_to_uint128(number);
        print_binary_uint128(d);
        print_hex_uint128(d);
        break;
    }
}

bool number_check(char *n)
{
    for (int i = 0; n[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)n[i]))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *args[])
{
    if (args[1] != NULL)
    {
        if (strcmp(args[1], "b") == 0 || strcmp(args[1], "B") == 0)
            print_umwandlung(args[2], 'b');
        else if (strcmp(args[1], "h") == 0 || strcmp(args[1], "H") == 0)
            print_umwandlung(args[2], 'h');
        else if (number_check(args[1]))
            print_umwandlung(args[1], 'n');

        else
            printf("INVALID ARGS\n");
    }
    else
    {
    }
}