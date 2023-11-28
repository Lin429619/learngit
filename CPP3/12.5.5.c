#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define SIZE 100

void BubbleSort(int array[],int len);

int main()
{
    int num[SIZE];
    srand((unsigned int) time(0));
    for(int i=0;i<SIZE;i++){
        num[i]=rand() % 10 + 1;
    }
    printf("The numbers are:\n");
    for(int i=0;i<SIZE;i++){
        printf("%4d",num[i]);
    }
    printf("\n");
    BubbleSort(num,SIZE);
    printf("The sored numbers are:\n");
    for(int i=0;i<SIZE;i++){
        printf("%3d",num[i]);
    }
    printf("\n");
    return 0;
}

void BubbleSort(int array[],int len){
    int flag;
    for(int i=0;i<len-1;i++){
        flag=1;
        for(int j=0;j<len-i-1;j++){
            if(array[j]>array[j+1]){
                int temp=array[j];
                array[j]=array[j+1];
                array[j+1]=temp;
                flag=0;
            }
        }
        if(flag==1) break;
    }
}
