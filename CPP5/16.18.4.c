#include<stdio.h>
#include<time.h>

void delay(int num);

int main(){
    int second;
    printf("Enter a number:");
    while(scanf("%d",&second) == 1){
        delay(second);
        printf("Enter a number:");
    }
    return 0;
}

void delay(int num){
    clock_t start = clock();
    clock_t end = clock();
    while(((double)(end-start)/CLOCKS_PER_SEC)<num){
        end = clock();
    }
    printf("Delay %.2lf second.\n",(double)(end-start)/CLOCKS_PER_SEC);
}
