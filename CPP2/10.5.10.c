#include<stdio.h>
#define N 4
void add(int n,int sum[n],int s1[n],int s2[n]);

int main()
{
    int n=4;
    int sum[N],s1[N]={2,4,5,8},s2[N]={1,0,4,6};
    add(n,sum,s1,s2);
    for(int i=0;i<n;i++){
        printf("%d ",sum[i]);
    }
    printf("\n");
    return 0;
}

void add(int n,int sum[n],int s1[n],int s2[n]){
    for(int i=0;i<n;i++){
        sum[i]=s1[i]+s2[i];
    }
}