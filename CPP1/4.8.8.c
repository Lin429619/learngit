#include<stdio.h>
#define JIALUN_TO_L 3.785
#define YINGLI_TO_KM 1.609
int main()
{
    double licheng,oil;
    printf("输入旅行的里程：");
    scanf("%lf",&licheng);
    printf("输入消耗的油量：");
    scanf("%lf",&oil);
    printf("英里/加仑：%.1lf\n",oil/licheng);
    printf("升/100公里：%.1lf\n",oil*JIALUN_TO_L/licheng*YINGLI_TO_KM);
    return 0;
}