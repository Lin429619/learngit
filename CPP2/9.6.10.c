#include<stdio.h>
void to_base_n(unsigned long n,unsigned int t);

int main()
{
    unsigned long num;
    unsigned int t;
    printf("Enter the interger and N(q to quit):\n");
    while(scanf("%lu %u",&num,&t)==2){
        if(t<2 || t>10){
            printf("t is between 2~10\n");
            printf("Enter the interger and N(q to quit):\n");
            continue;
        }
        to_base_n(num,t);
        putchar('\n');
        printf("Enter the interger and N(q to quit):\n");
    }
    return 0 ;
}

void to_base_n(unsigned long n,unsigned int t){
    if(t<2 || t>10){
        printf("t is between 2~10\n");
    }
    int a;
    a=n%t;
    if(n>=2) to_base_n(n/t,t);
    printf("%d",a);
}
