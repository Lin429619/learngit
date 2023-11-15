#include<stdio.h>
int main()
{
    int n,x=0,y=0;
    scanf("%d",&n);
    int num[45][45]={0};
    y=n/2;
    num[x][y]=1;//准备工作

    for(int k=2;k<=n*n;k++){
        if(x==0 && y!=n-1){
            x=n-1;
            y++;
        }else if(x!=0 && y==n-1){
            x--;
            y=0;
        }else if(x==0 && y==n-1){
            x++;
        }else if(x!= 0 && y!=n-1){
            if(num[x-1][y+1]==0) {
                x--;
                y++;
            }else {
                x++;
            }
        }
    num[x][y]=k;
    }//对下标进行讨论会更方便快捷

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ",num[i][j]);
        }
        printf("\n");
    } 
}