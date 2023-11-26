#include<stdio.h>
void copy(int m,int n,double first[m][n],double second[m][n]);
void print(int m,int n,double arr[m][m]);

int main()
{
    int m=3;
    int n=5;
    double second[m][n],first[][5]={
                {1,2,3,4,5},
                {6,7,8,9,10},
                {11,12,13,14,15},
                };
    copy(m,n,first,second);
    print(m,n,second);
    return 0;
}

void copy(int m,int n,double first[m][n],double second[m][n]){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            second[i][j]=first[i][j];
        }
    }
}
void print(int m,int n,double arr[m][m]){
     for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%-5.1lf ",arr[i][j]);
        }
        printf("\n");
    }
}