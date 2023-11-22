#include<stdio.h>
int main()
{
    char c[256];
    int i=0;
    do{
        scanf("%c",&c[i]);
    }while(c[i]!='\n' && ++i);
    for(i-1;i>=0;i--){
        printf("%c",c[i]);
    }
    printf("\n");
    return 0;
}