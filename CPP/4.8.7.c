#include<stdio.h>
#include<float.h>
int main()
{
    double d=1.0/3.0;
    float f=1.0/3.0;
    printf("%.6lf\n",d);
    printf("%.12lf\n",d);
    printf("%.16lf\n",d);
    printf("%.6lf\n",f);
    printf("%.12lf\n",f);
    printf("%.16lf\n",f);
    printf("%d\n",DBL_DIG);
    printf("%d\n",FLT_DIG);
    return 0;
}