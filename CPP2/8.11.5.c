#include<stdio.h>
int main()
{
    int guess=50;
    int left=1;
    int right=100;
    char ch;
    printf("Pick an integer from 1 to 100.I will try to guess it.\n");
    do{
        printf("The number is %d ?\n",guess);
        if(getchar() == 'y') break;
        printf("The number is larger or small,l or s?\n");
        while((ch=getchar()) == '\n') continue;
        if(ch=='l'){
            right=guess-1;
            guess=left+(right-left)/2;
            continue;
        }
        else if(ch=='s'){
            left=guess+1;
            guess=left+(right-left)/2;
            continue;
        }else 
            continue;
    }while(getchar() !='y');
    printf("I guess it!\n");
    return 0;
}