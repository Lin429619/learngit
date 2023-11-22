#include<stdio.h>
int main()
{
    int days,week,day;
    scanf("%d",&days);
    while(days>0){
        week=days/7;
        day=days%7;
        printf("%d days are %d weeks, %d days",days,week,day);
        scanf("%d",&days);
    }
    printf("Wrong days!\n");
    return 0;
}