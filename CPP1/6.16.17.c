#include<stdio.h>
int main()
{
    float account=100;
    int year=0;
    while(account>0){
        account += account*0.08;
        account -= 10;
        year++;
    }
    printf("%d\n",year);
    return 0;
}