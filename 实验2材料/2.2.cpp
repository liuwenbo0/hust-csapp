#pragma warning(disable:4996)
#include<stdio.h>
#include<iostream>
using namespace std;
int main()
{
    int op = 1;
    short a, b, ab;
    unsigned short c, d, cd;
    float e;
    int* f;
    unsigned int g = 1;
    while (op)
    {
        printf("\n");
        printf("judge your input\n");
        printf("1.signed(- 32768 ~ 32767)    2.unsigned(0 ~ 65535)     3.float     0.quit\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("please input two signed short num\n");
            scanf("%hd%hd", &a, &b);
            ab = a + b;
            if (a > 0 && b > 0 && ab < 0) printf("POSITIVE OVERFLOW\n");
            else if (a < 0 && b < 0 && ab>0) printf("NEGATIVE OVERFLOW\n");
            else printf("%hd\n", ab);
            break;

        case 2:
            printf("please input two unsigned short num\n");
            scanf("%hu%hu", &c, &d);
            cd = c + d;
            if (cd < c) printf("OVERFLOW\n");
            else printf("%hu\n", cd);
            break;

        case 3:
            g <<= 31;
            printf("please input ont float num\n");
            scanf("%f", &e);
            f = (int*)(&e);
            printf("the float num output in form of 16 base is -> ");
            printf("%x\n", *f);
            if (*f & g) printf("- ");
            else printf("+ ");
            printf("exp=");
            for (int i = 1; i < 9; i++)
            {
                g >>= 1;
                if (g & *f) printf("1");
                else printf("0");
            }
            printf(" fra=");
            for (int i = 1; i < 24; i++)
            {
                g >>= 1;
                if (g & *f) printf("1");
                else printf("0");
            }
            printf("\n");
            break;
        defalut:
            op = 0;
        }
    }
}