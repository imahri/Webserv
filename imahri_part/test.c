#include <stddef.h>
#include <stdio.h>
#include <string.h>


size_t  ft_strlen(const char* str)
{
    size_t i = 0;
    while (str[i])
        i++;
    return i;
}

int main()
{
    long a = 2000;
    printf("%zu\n",strlen(((char *)a)));
}
