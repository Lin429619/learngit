#include<stdio.h>
int main()
{
    int a;
    scanf("%d",&a);
    int num,result;
    scanf("%d",&num);
    while(num>0){
        result=num%a;
        printf("%d %% %d is %d",num,a,result);
        scanf("%d",&num);
    }
    if(num<=0) printf("Done!\n");
    return 0;
}