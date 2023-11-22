#include<stdio.h>
int main()
{
    char ch,c;
    int num;
    int j,i;
    scanf("%c",&ch);
    num=ch-'A'+1;
    for(i=1;i<=num;i++){
        for(j=0;j<num-i;j++){
            printf(" ");
        }
        for(c='A';j<num;j++){
            printf("%c",c++);
        }//正序输出
        for(j=1,c-=2;j<i;j++,c--){
            printf("%c",c);
        }//逆序输出
        printf("\n");
    }
    return 0;
}