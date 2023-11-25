#include<stdio.h>
double power(double n,int p);

int main()
{
    double x,xpow;
    int p;
    printf("Enter a number and the integer power");
    printf(" to which \nthe number will be raiaed. Enter q");
    printf(" to quit.\n");
    while(scanf("%lf %d",&x,&p)==2){
        xpow=power(x,p);
        printf("%.3g to the power %d is %.5g\n",x,p,xpow);
        printf("Enter next pair of numbers or q to quit.\n");
    }
    return 0;
}

double power(double n,int p){
    double pow=1;
    int i;
    if(n==0 && p==0) return 0;
    if(n==0) return 0;
    if(p==0) return 1;
    if(p>0)
        return n*power(n,p-1);
    else return power(n,p+1)/n;
}

