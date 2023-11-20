#include<stdio.h>
void Temperatures(double huashi);
int main()
{
    double huashi;
    while(scanf("%lf",&huashi)==1){
        Temperatures(huashi);
    }
    printf("Over!\n");
    return 0;

}
    
void Temperatures(double huashi){
    const double cha1=32.0;
    const double cha2=237.16;
    double sheshi,kaishi;
    sheshi=5.0/9.0*(huashi-cha1);
    kaishi=sheshi+cha2;
    printf("华氏温度是：%.3lf\n",huashi);
    printf("摄氏温度是：%.3lf\n",sheshi);
    printf("开氏温度是：%.3lf\n",kaishi);
}

