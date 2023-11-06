#include <stdio.h>
#include <string.h>


int main()
{
    int a = 0;
    
    memset((char *)(&a), 57, 1);
    memset((char *)(&a)+1, 5, 1);
    // memset((char *)(&a)+2, 0, 1);
    // memset((char *)(&a)+3, 0, 1);

    printf(">>%d",a);
}

// 101      00111001