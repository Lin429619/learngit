#include<stdio.h>
#include<string.h>

int change(char *str);

int main()
{
    char *pbin="01001001";
    int result=change(pbin);
    printf("%d\n",result);
    return 0;
}

int change(char *str){
    int len=strlen(str);
    int x=1;
    int sum=0;
    for(int i=len-1;i>=0;i--,x *=2 ){
        sum += (str[i]-'0')*x;
    }
    return sum;
}