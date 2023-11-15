#include<stdio.h>
int main()
{

    int n,cnt=7;
    int cnt1;
    scanf("%d",&n);
    int x[7],a[n][7],b[7]={0};
    for(int i=0;i<7;i++){
        scanf("%d",&x[i]);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<7;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<7;j++){
            for(int k=0;k<7;k++){
                if(x[j]==a[i][k])
                    cnt--;
            }
        }
        b[cnt]++;
        cnt=7;

    }
    for(int i=0;i<7;i++){
        printf("%d ",b[i]);
    }
    printf("\n");
    return 0;
}