#include<stdio.h>
int main()
{
    float speed,size,time;
    printf("输入速度：");
    scanf("%f",&speed);
    printf("输入文件大小：");
    scanf("%f",&size);
    time = size*8/speed;
    printf("大小为 %.2f 的文件以 %.2f 兆每秒的速度下载需要 %.2f 秒\n",size,speed,time);
    return 0;
}