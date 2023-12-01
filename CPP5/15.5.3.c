#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<stdlib.h>

int one_count(int n);

int main(int argc,char *argv[])
{
    int num;
    num=atoi(argv[1]);
    int n=one_count(num);
    printf("%d's one bit is %d\n",num,n);
    return 0;
}

int one_count(int n){
   // int size=CHAR_BIT * sizeof(int);
    int cnt= 0;
    while(n != 0){
        if(n & 1) {
            cnt++;
        }
        n >>= 1;
    }
    return cnt;
}