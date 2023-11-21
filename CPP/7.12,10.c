#include<stdio.h>
int main()
{
    int m;
    char type; 
    double pay;
    do{
        scanf(" %c",&type);
        switch (type)
        {
            case '1'://单身
                scanf("%d",&m);
                if(m<=17850) pay=m*0.15;
                else pay=17850*0.15+(m-17850)*0.28;
                printf("pay = %.2lf\n",pay);
                break;
            case '2'://户主
                scanf("%d",&m);
                if(m<=23900) pay=m*0.15;
                else pay=23900*0.15+(m-23900)*0.28;
                printf("pay = %.2lf\n",pay);
                break;
            case '3'://已婚，共有
                scanf("%d",&m);
                if(m<=29750) pay=m*0.15;
                else pay=29750*0.15+(m-29750)*0.28;
                printf("pay = %.2lf\n",pay);
                break;
            case '4'://已婚，离异
                scanf("%d",&m);
                if(m<=14875) pay=m*0.15;
                else pay=14875*0.15+(m-14875)*0.28;
                printf("pay = %.2lf\n",pay);
                break;
            case '5':
                break;
            default:
                printf("Wrong type!\n");                
        }
    }while(type !='5');
    return 0;
}